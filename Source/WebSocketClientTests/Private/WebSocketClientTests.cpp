// Copyright 2026-current Getnamo. All Rights Reserved

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "WebSocketClientComponent.h"
#include "WebSocketNative.h"
#include "WebSocketTestListener.h"
#include "WebSocketTestServer.h"
#include "WebSocketTestUtils.h"
#include "SIOJConvert.h"
#include "SIOJsonObject.h"
#include "SIOJsonValue.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Tests/AutomationCommon.h"

#include <atomic>

using namespace WebSocketTest;

namespace WebSocketClientTests
{
	static constexpr EAutomationTestFlags TestFlags = EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::EngineFilter;

	/** Records FWebSocketNative callbacks. Game thread mode only touches it on the game thread, network thread mode uses the lock. */
	struct FNativeRecorder
	{
		FCriticalSection Lock;
		int32 Connects = 0;
		FString Protocol;
		int32 Disconnects = 0;
		int32 StatusCode = 0;
		FString Reason;
		bool bWasClean = false;
		TArray<FString> Errors;
		TArray<FString> Messages;
		TArray<TSharedPtr<FJsonValue>> JsonValues;
		TArray<TArray<uint8>> Binaries;
		bool bAllOnGameThread = true;
		bool bAnyOnGameThread = false;

		void NoteThread()
		{
			bAllOnGameThread &= IsInGameThread();
			bAnyOnGameThread |= IsInGameThread();
		}

		template<typename ValueType>
		ValueType Get(ValueType FNativeRecorder::* Member)
		{
			FScopeLock Guard(&Lock);
			return this->*Member;
		}
	};

	typedef TSharedRef<FNativeRecorder, ESPMode::ThreadSafe> FNativeRecorderRef;

	static FNativeRecorderRef Record(FWebSocketNative& Native, bool bWithJson = true)
	{
		FNativeRecorderRef Recorder = MakeShared<FNativeRecorder, ESPMode::ThreadSafe>();
		Native.OnConnectedCallback = [Recorder](const FString& Protocol)
		{
			FScopeLock Guard(&Recorder->Lock);
			Recorder->NoteThread();
			Recorder->Connects++;
			Recorder->Protocol = Protocol;
		};
		Native.OnDisconnectedCallback = [Recorder](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			FScopeLock Guard(&Recorder->Lock);
			Recorder->NoteThread();
			Recorder->Disconnects++;
			Recorder->StatusCode = StatusCode;
			Recorder->Reason = Reason;
			Recorder->bWasClean = bWasClean;
		};
		Native.OnErrorCallback = [Recorder](const FString& Error)
		{
			FScopeLock Guard(&Recorder->Lock);
			Recorder->NoteThread();
			Recorder->Errors.Add(Error);
		};
		Native.OnMessageCallback = [Recorder](const FString& Message)
		{
			FScopeLock Guard(&Recorder->Lock);
			Recorder->NoteThread();
			Recorder->Messages.Add(Message);
		};
		Native.OnBinaryMessageCallback = [Recorder](const TArray<uint8>& Bytes)
		{
			FScopeLock Guard(&Recorder->Lock);
			Recorder->NoteThread();
			Recorder->Binaries.Add(Bytes);
		};
		if (bWithJson)
		{
			Native.OnJsonMessageCallback = [Recorder](const TSharedPtr<FJsonValue>& JsonValue)
			{
				FScopeLock Guard(&Recorder->Lock);
				Recorder->NoteThread();
				Recorder->JsonValues.Add(JsonValue);
			};
		}
		return Recorder;
	}
}

using namespace WebSocketClientTests;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketNativeGameThreadTest, "WebSocketClient.Native.GameThread", WebSocketClientTests::TestFlags)

bool FWebSocketNativeGameThreadTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}

	TSharedPtr<FWebSocketNative> Native = MakeShared<FWebSocketNative>();
	FNativeRecorderRef Recorder = Record(*Native);
	Native->Protocols = { TEXT("json.v1") };
	Native->Connect(Server.GetUrl());

	if (!TestTrue(TEXT("Connected"), WaitFor([&]() { return Recorder->Connects == 1; }, 5.f, true)))
	{
		return false;
	}
	TestTrue(TEXT("IsConnected"), Native->IsConnected());
	TestEqual(TEXT("Protocol in callback"), Recorder->Protocol, FString(TEXT("json.v1")));
	TestEqual(TEXT("GetProtocol"), Native->GetProtocol(), FString(TEXT("json.v1")));

	//Order is kept through the game thread queue
	const int32 Count = 200;
	for (int32 Index = 0; Index < Count; Index++)
	{
		Native->SendText(FString::Printf(TEXT("m%d"), Index));
	}
	TestTrue(TEXT("All ordered messages arrived"), WaitFor([&]() { return Recorder->Messages.Num() == Count; }, 5.f, true));
	bool bInOrder = Recorder->Messages.Num() == Count;
	for (int32 Index = 0; bInOrder && Index < Count; Index++)
	{
		bInOrder = Recorder->Messages[Index] == FString::Printf(TEXT("m%d"), Index);
	}
	TestTrue(TEXT("Messages arrive in order"), bInOrder);
	TestEqual(TEXT("Plain text isn't JSON"), Recorder->JsonValues.Num(), 0);
	Recorder->Messages.Empty();

	//JSON object
	TSharedPtr<FJsonObject> Object = MakeShared<FJsonObject>();
	Object->SetNumberField(TEXT("a"), 1);
	Object->SetStringField(TEXT("s"), TEXT("x"));
	TestTrue(TEXT("JSON queued"), Native->SendJson(Object));
	TestTrue(TEXT("JSON arrived"), WaitFor([&]() { return Recorder->JsonValues.Num() == 1; }, 5.f, true));
	if (Recorder->JsonValues.Num() == 1 && Recorder->JsonValues[0]->Type == EJson::Object)
	{
		TestEqual(TEXT("JSON number field"), (int32)Recorder->JsonValues[0]->AsObject()->GetNumberField(TEXT("a")), 1);
		TestEqual(TEXT("JSON string field"), Recorder->JsonValues[0]->AsObject()->GetStringField(TEXT("s")), FString(TEXT("x")));
	}
	else
	{
		AddError(TEXT("Expected one JSON object"));
	}

	//JSON string value is sent quoted
	Recorder->Messages.Empty();
	TestTrue(TEXT("JSON string queued"), Native->SendJson(MakeShared<FJsonValueString>(TEXT("quoted \"text\""))));
	TestTrue(TEXT("JSON string arrived"), WaitFor([&]() { return Recorder->Messages.Num() == 1; }, 5.f, true));
	TestEqual(TEXT("JSON string encoded as JSON"), Recorder->Messages.Num() ? Recorder->Messages[0] : FString(), FString(TEXT("\"quoted \\\"text\\\"\"")));

	//Struct round trip
	FWebSocketTestStruct Sent;
	Sent.Name = TEXT("ws");
	Sent.Count = 3;
	Sent.Values = { 1.5f, 2.5f };
	const int32 JsonBefore = Recorder->JsonValues.Num();
	TestTrue(TEXT("Struct queued"), Native->SendStruct(Sent));
	TestTrue(TEXT("Struct arrived"), WaitFor([&]() { return Recorder->JsonValues.Num() == JsonBefore + 1; }, 5.f, true));
	FWebSocketTestStruct Received;
	if (Recorder->JsonValues.Num() == JsonBefore + 1 && Recorder->JsonValues.Last()->Type == EJson::Object)
	{
		TestTrue(TEXT("Struct converts back"), USIOJConvert::JsonObjectToUStruct(Recorder->JsonValues.Last()->AsObject(), FWebSocketTestStruct::StaticStruct(), &Received));
		TestEqual(TEXT("Struct name"), Received.Name, Sent.Name);
		TestEqual(TEXT("Struct count"), Received.Count, Sent.Count);
		TestTrue(TEXT("Struct values"), Received.Values == Sent.Values);
	}

	//Binary
	const TArray<uint8> Bytes = MakeBytes(4096, 7);
	TestTrue(TEXT("Binary queued"), Native->SendBinary(Bytes));
	TestTrue(TEXT("Binary arrived"), WaitFor([&]() { return Recorder->Binaries.Num() == 1; }, 5.f, true));
	TestTrue(TEXT("Binary round trips"), Recorder->Binaries.Num() == 1 && Recorder->Binaries[0] == Bytes);

	//Top level JSON values other than objects/arrays, informational
	Recorder->JsonValues.Empty();
	Native->SendText(TEXT("123"));
	Native->SendText(TEXT("true"));
	Settle(0.3f, true);
	AddInfo(FString::Printf(TEXT("Top level primitives parsed as JSON: %d of 2"), Recorder->JsonValues.Num()));

	Native->Disconnect(4010, TEXT("native bye"));
	TestTrue(TEXT("Disconnected"), WaitFor([&]() { return Recorder->Disconnects == 1; }, 5.f, true));
	TestEqual(TEXT("Disconnect code"), Recorder->StatusCode, 4010);
	TestEqual(TEXT("Disconnect reason"), Recorder->Reason, FString(TEXT("native bye")));
	TestTrue(TEXT("Disconnect clean"), Recorder->bWasClean);
	TestFalse(TEXT("Not connected"), Native->IsConnected());
	TestTrue(TEXT("Every callback ran on the game thread"), Recorder->bAllOnGameThread);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketNativeNetworkThreadTest, "WebSocketClient.Native.NetworkThread", WebSocketClientTests::TestFlags)

bool FWebSocketNativeNetworkThreadTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}

	TSharedPtr<FWebSocketNative> Native = MakeShared<FWebSocketNative>();
	Native->bCallbackOnGameThread = false;
	FNativeRecorderRef Recorder = Record(*Native);
	Native->Connect(Server.GetUrl());

	//Not pumping the game thread, callbacks must arrive anyway
	TestTrue(TEXT("Connected"), WaitFor([&]() { return Recorder->Get(&FNativeRecorder::Connects) == 1; }));
	Native->SendText(TEXT("{\"k\":2}"));
	TestTrue(TEXT("Message arrived"), WaitFor([&]() { return Recorder->Get(&FNativeRecorder::JsonValues).Num() == 1; }));
	TestEqual(TEXT("Text callback too"), Recorder->Get(&FNativeRecorder::Messages).Num(), 1);
	Native->SyncDisconnect(1000, TEXT("sync"));
	TestEqual(TEXT("SyncDisconnect waits for the close"), Recorder->Get(&FNativeRecorder::Disconnects), 1);
	TestFalse(TEXT("No callback on the game thread"), Recorder->Get(&FNativeRecorder::bAnyOnGameThread));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketNativeErrorsTest, "WebSocketClient.Native.Errors", WebSocketClientTests::TestFlags)

bool FWebSocketNativeErrorsTest::RunTest(const FString& Parameters)
{
	AddExpectedMessage(TEXT("Connect failed"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 1);

	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}

	//Bad url: reported through the error callback, on a later tick
	{
		TSharedPtr<FWebSocketNative> Native = MakeShared<FWebSocketNative>();
		FNativeRecorderRef Recorder = Record(*Native);
		Native->Connect(TEXT("localhost:3000"));
		TestEqual(TEXT("Error isn't delivered inside Connect"), Recorder->Errors.Num(), 0);
		TestTrue(TEXT("Bad url error"), WaitFor([&]() { return Recorder->Errors.Num() == 1; }, 2.f, true));
	}

	//Handshake refused
	{
		TSharedPtr<FWebSocketNative> Native = MakeShared<FWebSocketNative>();
		FNativeRecorderRef Recorder = Record(*Native);
		Native->Connect(Server.GetUrl(TEXT("127.0.0.1"), TEXT("/reject")));
		TestTrue(TEXT("Rejected error"), WaitFor([&]() { return Recorder->Errors.Num() == 1; }, 5.f, true));
		TestTrue(TEXT("Error has the HTTP status"), Recorder->Errors.Num() == 1 && Recorder->Errors[0].Contains(TEXT("401")));
		TestEqual(TEXT("No disconnect for a failed connect"), Recorder->Disconnects, 0);
	}

	//Nothing listening
	{
		const FString Url = Server.GetUrl();
		Server.Stop();
		TSharedPtr<FWebSocketNative> Native = MakeShared<FWebSocketNative>();
		FNativeRecorderRef Recorder = Record(*Native);
		Native->Connect(Url);
		TestTrue(TEXT("Refused error"), WaitFor([&]() { return Recorder->Errors.Num() == 1; }, 10.f, true));
		AddInfo(FString::Printf(TEXT("Refused: %s"), Recorder->Errors.Num() ? *Recorder->Errors[0] : TEXT("")));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketNativeLifetimeTest, "WebSocketClient.Native.Lifetime", WebSocketClientTests::TestFlags)

bool FWebSocketNativeLifetimeTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}

	//Released while connecting, and while open with queued callbacks
	{
		TSharedPtr<FWebSocketNative> Connecting = MakeShared<FWebSocketNative>();
		FNativeRecorderRef ConnectingRecorder = Record(*Connecting);
		Connecting->Connect(Server.GetUrl());
		Connecting.Reset();

		TSharedPtr<FWebSocketNative> Open = MakeShared<FWebSocketNative>();
		FNativeRecorderRef OpenRecorder = Record(*Open);
		Open->Connect(Server.GetUrl());
		WaitFor([&]() { return OpenRecorder->Connects == 1; }, 5.f, true);
		for (int32 Index = 0; Index < 20; Index++)
		{
			Open->SendText(TEXT("queued"));
		}
		//Let replies land on the game thread queue without running them, then release
		FPlatformProcess::Sleep(0.1f);
		const int32 MessagesBefore = OpenRecorder->Messages.Num();
		Open.Reset();

		Settle(0.3f, true);
		TestEqual(TEXT("Released while connecting: no callbacks"), ConnectingRecorder->Connects + ConnectingRecorder->Errors.Num() + ConnectingRecorder->Disconnects, 0);
		TestEqual(TEXT("Released while open: queued callbacks dropped"), OpenRecorder->Messages.Num(), MessagesBefore);
		TestEqual(TEXT("Released while open: no disconnect callback"), OpenRecorder->Disconnects, 0);
	}

	//A callback releases the last reference to its native
	{
		TSharedPtr<FWebSocketNative> Native = MakeShared<FWebSocketNative>();
		FNativeRecorderRef Recorder = Record(*Native);
		bool bReleased = false;
		Native->OnMessageCallback = [&Native, &bReleased](const FString& Message)
		{
			Native.Reset();
			bReleased = true;
		};
		Native->Connect(Server.GetUrl());
		TestTrue(TEXT("Connected"), WaitFor([&]() { return Recorder->Connects == 1; }, 5.f, true));
		Native->SendText(TEXT("release me"));
		TestTrue(TEXT("Released from its own callback"), WaitFor([&]() { return bReleased; }, 5.f, true));
		Settle(0.2f, true);
		TestEqual(TEXT("No disconnect callback after release"), Recorder->Disconnects, 0);
	}

	//Connect again while connected
	{
		TSharedPtr<FWebSocketNative> Native = MakeShared<FWebSocketNative>();
		FNativeRecorderRef Recorder = Record(*Native);
		Native->Connect(Server.GetUrl());
		TestTrue(TEXT("First connect"), WaitFor([&]() { return Recorder->Connects == 1; }, 5.f, true));
		Native->Connect(Server.GetUrl());
		TestTrue(TEXT("Second connect"), WaitFor([&]() { return Recorder->Connects == 2; }, 5.f, true));
		Settle(0.2f, true);
		TestEqual(TEXT("Replaced connection closes silently"), Recorder->Disconnects, 0);
		TestTrue(TEXT("Still connected"), Native->IsConnected());
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketComponentTest, "WebSocketClient.Component.Basics", WebSocketClientTests::TestFlags)

bool FWebSocketComponentTest::RunTest(const FString& Parameters)
{
	AddExpectedMessage(TEXT("Connect failed"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 1);
	AddExpectedMessage(TEXT("Connection to"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 1);

	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}

	UWebSocketTestListener* Listener = NewObject<UWebSocketTestListener>();
	UWebSocketClientComponent* Component = NewObject<UWebSocketClientComponent>();
	Listener->AddToRoot();
	Component->AddToRoot();

	Component->OnConnected.AddDynamic(Listener, &UWebSocketTestListener::HandleConnected);
	Component->OnDisconnected.AddDynamic(Listener, &UWebSocketTestListener::HandleDisconnected);
	Component->OnConnectionError.AddDynamic(Listener, &UWebSocketTestListener::HandleError);
	Component->OnMessage.AddDynamic(Listener, &UWebSocketTestListener::HandleMessage);
	Component->OnBinaryMessage.AddDynamic(Listener, &UWebSocketTestListener::HandleBinaryMessage);
	Component->OnJsonMessage.AddDynamic(Listener, &UWebSocketTestListener::HandleJsonMessage);

	TestFalse(TEXT("Send before connecting"), Component->Send(TEXT("nope")));

	Component->Protocols = { TEXT("chat") };
	Component->Headers.Add(TEXT("X-Test"), TEXT("from component"));
	Component->Connect(Server.GetUrl());
	TestTrue(TEXT("OnConnected"), WaitFor([&]() { return Listener->Connects == 1; }, 5.f, true));
	TestTrue(TEXT("bIsConnected"), Component->bIsConnected);
	TestEqual(TEXT("ConnectedProtocol"), Component->ConnectedProtocol, FString(TEXT("chat")));
	TestEqual(TEXT("Protocol in event"), Listener->Protocol, FString(TEXT("chat")));

	TestTrue(TEXT("Send"), Component->Send(TEXT("header:X-Test")));
	TestTrue(TEXT("OnMessage"), WaitFor([&]() { return Listener->Messages.Num() == 1; }, 5.f, true));
	TestEqual(TEXT("Headers reach the server"), Listener->Messages.Num() ? Listener->Messages[0] : FString(), FString(TEXT("from component")));
	TestEqual(TEXT("Plain text doesn't fire OnJsonMessage"), Listener->JsonMessages.Num(), 0);

	USIOJsonObject* Object = USIOJsonObject::ConstructJsonObject(Component);
	Object->SetStringField(TEXT("name"), TEXT("ws"));
	Object->SetNumberField(TEXT("n"), 2.f);
	TestTrue(TEXT("SendJson"), Component->SendJson(USIOJsonValue::ConstructJsonValueObject(Object, Component)));
	TestTrue(TEXT("OnJsonMessage"), WaitFor([&]() { return Listener->JsonMessages.Num() == 1; }, 5.f, true));
	TestEqual(TEXT("JSON text also fires OnMessage"), Listener->Messages.Num(), 2);
	TestTrue(TEXT("JSON content"), Listener->JsonMessages.Num() == 1 && Listener->JsonMessages[0].Contains(TEXT("\"name\":\"ws\"")));
	AddInfo(FString::Printf(TEXT("OnJsonMessage: %s"), Listener->JsonMessages.Num() ? *Listener->JsonMessages[0] : TEXT("")));

	const TArray<uint8> Bytes = { 1, 2, 3, 250 };
	TestTrue(TEXT("SendBinary"), Component->SendBinary(Bytes));
	TestTrue(TEXT("OnBinaryMessage"), WaitFor([&]() { return Listener->BinaryMessages.Num() == 1; }, 5.f, true));
	TestTrue(TEXT("Binary content"), Listener->BinaryMessages.Num() == 1 && Listener->BinaryMessages[0] == Bytes);

	Component->Disconnect(4000, TEXT("bye"));
	TestTrue(TEXT("OnDisconnected"), WaitFor([&]() { return Listener->Disconnects == 1; }, 5.f, true));
	TestEqual(TEXT("Disconnect code"), Listener->StatusCode, 4000);
	TestEqual(TEXT("Disconnect reason"), Listener->Reason, FString(TEXT("bye")));
	TestTrue(TEXT("Disconnect clean"), Listener->bWasClean);
	TestFalse(TEXT("bIsConnected cleared"), Component->bIsConnected);
	TestTrue(TEXT("ConnectedProtocol cleared"), Component->ConnectedProtocol.IsEmpty());

	Component->Connect(TEXT("not a websocket url"));
	TestTrue(TEXT("OnConnectionError"), WaitFor([&]() { return Listener->Errors.Num() == 1; }, 2.f, true));

	Component->NativeClient.Reset();
	Component->RemoveFromRoot();
	Listener->RemoveFromRoot();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketComponentLifecycleTest, "WebSocketClient.Component.Lifecycle", WebSocketClientTests::TestFlags)

bool FWebSocketComponentLifecycleTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}

	FTestWorldWrapper WorldWrapper;
	if (!TestTrue(TEXT("Test world created"), WorldWrapper.CreateTestWorld(EWorldType::Game)))
	{
		return false;
	}
	UWorld* World = WorldWrapper.GetTestWorld();

	AActor* Actor = World->SpawnActor<AActor>();
	UWebSocketClientComponent* Component = NewObject<UWebSocketClientComponent>(Actor);
	Component->Url = Server.GetUrl();
	Component->RegisterComponent();

	TestTrue(TEXT("BeginPlay"), WorldWrapper.BeginPlayInTestWorld());
	TestTrue(TEXT("Native created on initialize"), Component->NativeClient.IsValid());
	TestTrue(TEXT("Auto connects on BeginPlay"), WaitFor([&]() { return Component->bIsConnected; }, 5.f, true));

	TWeakPtr<FWebSocketNative> WeakNative = Component->NativeClient;
	Actor->Destroy();
	TestFalse(TEXT("Native released on EndPlay"), Component->NativeClient.IsValid());
	TestFalse(TEXT("Nothing else holds the native"), WeakNative.IsValid());
	TestFalse(TEXT("Not connected after EndPlay"), Component->bIsConnected);

	WorldWrapper.ForwardErrorMessages(this);
	WorldWrapper.DestroyTestWorld(false);
	return true;
}

#endif
