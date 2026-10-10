// Copyright 2026-current Getnamo. All Rights Reserved

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "WebSocketLibClient.h"
#include "WebSocketTestServer.h"
#include "WebSocketTestUtils.h"

#include <atomic>

using namespace WebSocketTest;

namespace WebSocketLibTests
{
	static constexpr EAutomationTestFlags TestFlags = EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::EngineFilter;

	/** Client with a recorder, connected (or failed) once Connect returns true and WaitFor passes */
	struct FRecordedClient
	{
		FWebSocketLibClient Client;
		FLibRecorderRef Recorder = MakeRecorder();

		bool Connect(const FWebSocketLibConnectParams& Params, FString& OutError)
		{
			Client.SetCallbacks(Recorder->MakeCallbacks());
			return Client.Connect(Params, OutError);
		}

		bool WaitOpen(float Timeout = 5.f)
		{
			return WaitFor([this]() { return Recorder->Get(&FLibRecorder::Opens) > 0; }, Timeout);
		}

		bool WaitFail(float Timeout = 5.f)
		{
			return WaitFor([this]() { return Recorder->Get(&FLibRecorder::Fails) > 0; }, Timeout);
		}

		bool WaitClose(float Timeout = 5.f)
		{
			return WaitFor([this]() { return Recorder->Get(&FLibRecorder::Closes) > 0; }, Timeout);
		}
	};

	static FWebSocketLibConnectParams MakeParams(const FString& Url)
	{
		FWebSocketLibConnectParams Params;
		Params.Url = Url;
		return Params;
	}
}

using namespace WebSocketLibTests;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketLibEchoTest, "WebSocketClient.Lib.Echo", WebSocketLibTests::TestFlags)

bool FWebSocketLibEchoTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}

	FRecordedClient Connection;
	FString Error;
	TestTrue(TEXT("Connect starts"), Connection.Connect(MakeParams(Server.GetUrl()), Error));
	TestFalse(TEXT("Send before open is refused"), Connection.Client.SendText(TEXT("too early")));
	if (!TestTrue(TEXT("Opened"), Connection.WaitOpen()))
	{
		return false;
	}
	TestTrue(TEXT("IsConnected"), Connection.Client.IsConnected());
	TestEqual(TEXT("No subprotocol requested, none picked"), Connection.Recorder->Get(&FLibRecorder::Protocol), FString());

	const TArray<FString> Texts = { TEXT("hello"), TEXT("héllo wörld ✓ 日本"), TEXT("") };
	for (const FString& Text : Texts)
	{
		TestTrue(TEXT("Text queued"), Connection.Client.SendText(Text));
	}
	TestTrue(TEXT("Texts echoed"), WaitFor([&]() { return Connection.Recorder->NumTexts() == Texts.Num(); }));
	const TArray<FString> ReceivedTexts = Connection.Recorder->Get(&FLibRecorder::Texts);
	for (int32 Index = 0; Index < Texts.Num() && Index < ReceivedTexts.Num(); Index++)
	{
		TestEqual(FString::Printf(TEXT("Text %d round trips (incl. UTF-8)"), Index), ReceivedTexts[Index], Texts[Index]);
	}

	const TArray<TArray<uint8>> Binaries = { MakeBytes(1024, 1), MakeBytes(10 * 1024 * 1024, 2), TArray<uint8>() };
	for (const TArray<uint8>& Bytes : Binaries)
	{
		TestTrue(TEXT("Binary queued"), Connection.Client.SendBinary(Bytes));
	}
	TestTrue(TEXT("Binaries echoed"), WaitFor([&]() { return Connection.Recorder->NumBinaries() == Binaries.Num(); }, 15.f));
	const TArray<TArray<uint8>> ReceivedBinaries = Connection.Recorder->Get(&FLibRecorder::Binaries);
	for (int32 Index = 0; Index < Binaries.Num() && Index < ReceivedBinaries.Num(); Index++)
	{
		TestTrue(FString::Printf(TEXT("Binary %d (%d bytes) round trips"), Index, Binaries[Index].Num()), ReceivedBinaries[Index] == Binaries[Index]);
	}

	Connection.Client.SyncClose(1000, TEXT("done"));
	TestEqual(TEXT("Closed once"), Connection.Recorder->Get(&FLibRecorder::Closes), 1);
	TestEqual(TEXT("Close code"), Connection.Recorder->Get(&FLibRecorder::CloseCode), 1000);
	TestTrue(TEXT("Clean close"), Connection.Recorder->Get(&FLibRecorder::bCloseClean));
	TestFalse(TEXT("Not connected after close"), Connection.Client.IsConnected());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketLibHandshakeTest, "WebSocketClient.Lib.Handshake", WebSocketLibTests::TestFlags)

bool FWebSocketLibHandshakeTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}
	FString Error;

	//Headers and subprotocol
	{
		FRecordedClient Connection;
		FWebSocketLibConnectParams Params = MakeParams(Server.GetUrl(TEXT("127.0.0.1"), TEXT("/chat?room=1")));
		Params.Headers.Add(TEXT("X-Test"), TEXT("header value"));
		Params.Protocols = { TEXT("chat.v2"), TEXT("chat.v1") };
		TestTrue(TEXT("Connect starts"), Connection.Connect(Params, Error));
		TestTrue(TEXT("Opened"), Connection.WaitOpen());
		TestEqual(TEXT("Server picked the first subprotocol"), Connection.Recorder->Get(&FLibRecorder::Protocol), FString(TEXT("chat.v2")));

		Connection.Client.SendText(TEXT("header:X-Test"));
		TestTrue(TEXT("Header reply"), WaitFor([&]() { return Connection.Recorder->NumTexts() == 1; }));
		TestEqual(TEXT("Server saw the header"), Connection.Recorder->Get(&FLibRecorder::Texts).Last(), FString(TEXT("header value")));
	}

	//Server refuses the upgrade
	{
		FRecordedClient Connection;
		TestTrue(TEXT("Connect starts"), Connection.Connect(MakeParams(Server.GetUrl(TEXT("127.0.0.1"), TEXT("/reject"))), Error));
		TestTrue(TEXT("Rejected handshake fails"), Connection.WaitFail());
		TestEqual(TEXT("HTTP status reported"), Connection.Recorder->Get(&FLibRecorder::FailHttpStatus), 401);
		TestEqual(TEXT("Never opened"), Connection.Recorder->Get(&FLibRecorder::Opens), 0);
		AddInfo(FString::Printf(TEXT("Rejected: %s"), *Connection.Recorder->Get(&FLibRecorder::FailError)));
	}

	//Invalid subprotocol token
	{
		FRecordedClient Connection;
		FWebSocketLibConnectParams Params = MakeParams(Server.GetUrl());
		Params.Protocols = { TEXT("has space") };
		TestFalse(TEXT("Invalid subprotocol refused"), Connection.Connect(Params, Error));
		AddInfo(FString::Printf(TEXT("Invalid subprotocol: %s"), *Error));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketLibCloseTest, "WebSocketClient.Lib.Close", WebSocketLibTests::TestFlags)

bool FWebSocketLibCloseTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}
	FString Error;

	//Client closes with an application code
	{
		FRecordedClient Connection;
		Connection.Connect(MakeParams(Server.GetUrl()), Error);
		TestTrue(TEXT("Opened"), Connection.WaitOpen());
		Connection.Client.Close(4001, TEXT("client bye"));
		TestTrue(TEXT("Client close reported"), Connection.WaitClose());
		TestEqual(TEXT("Client close code"), Connection.Recorder->Get(&FLibRecorder::CloseCode), 4001);
		TestEqual(TEXT("Client close reason"), Connection.Recorder->Get(&FLibRecorder::CloseReason), FString(TEXT("client bye")));
		TestTrue(TEXT("Client close is clean"), Connection.Recorder->Get(&FLibRecorder::bCloseClean));
	}

	//Server closes
	{
		FRecordedClient Connection;
		Connection.Connect(MakeParams(Server.GetUrl()), Error);
		TestTrue(TEXT("Opened"), Connection.WaitOpen());
		Connection.Client.SendText(TEXT("close:4002:server bye"));
		TestTrue(TEXT("Server close reported"), Connection.WaitClose());
		TestEqual(TEXT("Server close code"), Connection.Recorder->Get(&FLibRecorder::CloseCode), 4002);
		TestEqual(TEXT("Server close reason"), Connection.Recorder->Get(&FLibRecorder::CloseReason), FString(TEXT("server bye")));
		TestTrue(TEXT("Server close is clean"), Connection.Recorder->Get(&FLibRecorder::bCloseClean));
	}

	//Server drops the TCP connection
	{
		FRecordedClient Connection;
		Connection.Connect(MakeParams(Server.GetUrl()), Error);
		TestTrue(TEXT("Opened"), Connection.WaitOpen());
		Connection.Client.SendText(TEXT("drop"));
		TestTrue(TEXT("Drop reported"), Connection.WaitClose());
		TestEqual(TEXT("Drop is 1006"), Connection.Recorder->Get(&FLibRecorder::CloseCode), 1006);
		TestFalse(TEXT("Drop isn't clean"), Connection.Recorder->Get(&FLibRecorder::bCloseClean));
		AddInfo(FString::Printf(TEXT("Drop reason: %s"), *Connection.Recorder->Get(&FLibRecorder::CloseReason)));
	}

	//Closed before the handshake finished
	{
		FRecordedClient Connection;
		Connection.Connect(MakeParams(Server.GetUrl()), Error);
		Connection.Client.Close(4003, TEXT("never mind"));
		TestTrue(TEXT("Early close reported"), Connection.WaitClose());
		TestEqual(TEXT("Early close code"), Connection.Recorder->Get(&FLibRecorder::CloseCode), 4003);
		TestEqual(TEXT("No open after an early close"), Connection.Recorder->Get(&FLibRecorder::Opens), 0);
		TestEqual(TEXT("No failure after an early close"), Connection.Recorder->Get(&FLibRecorder::Fails), 0);
	}

	//Nothing listening
	{
		const FString Url = Server.GetUrl();
		Server.Stop();
		FRecordedClient Connection;
		TestTrue(TEXT("Connect starts"), Connection.Connect(MakeParams(Url), Error));
		TestTrue(TEXT("Refused connection fails"), Connection.WaitFail(10.f));
		TestEqual(TEXT("Never opened"), Connection.Recorder->Get(&FLibRecorder::Opens), 0);
		AddInfo(FString::Printf(TEXT("Refused: %s"), *Connection.Recorder->Get(&FLibRecorder::FailError)));
	}

	//Urls that can't work
	{
		FWebSocketLibClient Client;
		TestFalse(TEXT("http url refused"), Client.Connect(MakeParams(TEXT("http://localhost:3000")), Error));
		AddInfo(FString::Printf(TEXT("http url: %s"), *Error));
		TestFalse(TEXT("Url without host refused"), Client.Connect(MakeParams(TEXT("ws://")), Error));
		AddInfo(FString::Printf(TEXT("No host: %s"), *Error));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketLibTLSTest, "WebSocketClient.Lib.TLS", WebSocketLibTests::TestFlags)

bool FWebSocketLibTLSTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("TLS server started"), Server.Start(true)))
	{
		return false;
	}
	FString Error;

	//Verification off accepts the test certificate
	{
		FRecordedClient Connection;
		FWebSocketLibConnectParams Params = MakeParams(Server.GetUrl());
		Params.bVerifyTLSCertificate = false;
		Connection.Connect(Params, Error);
		TestTrue(TEXT("Unverified wss opens"), Connection.WaitOpen());
		Connection.Client.SendText(TEXT("secure"));
		TestTrue(TEXT("Unverified wss echoes"), WaitFor([&]() { return Connection.Recorder->NumTexts() == 1; }));
	}

	//Verification on, the test CA isn't trusted
	{
		FRecordedClient Connection;
		Connection.Connect(MakeParams(Server.GetUrl(TEXT("localhost"))), Error);
		TestTrue(TEXT("Untrusted certificate fails"), Connection.WaitFail());
		TestEqual(TEXT("Never opened"), Connection.Recorder->Get(&FLibRecorder::Opens), 0);
		const FString FailError = Connection.Recorder->Get(&FLibRecorder::FailError);
		TestTrue(TEXT("Error names the certificate problem"), FailError.Contains(TEXT("certificate")));
		AddInfo(FString::Printf(TEXT("Untrusted: %s"), *FailError));
	}

	//Verification on with the test CA trusted, host matches
	{
		FRecordedClient Connection;
		FWebSocketLibConnectParams Params = MakeParams(Server.GetUrl(TEXT("localhost")));
		Params.AdditionalCACertificatesPEM = Server.GetCACertificatePEM();
		Connection.Connect(Params, Error);
		TestTrue(TEXT("Trusted certificate opens"), Connection.WaitOpen());
		Connection.Client.SendText(TEXT("verified"));
		TestTrue(TEXT("Verified wss echoes"), WaitFor([&]() { return Connection.Recorder->NumTexts() == 1; }));
	}

	//Trusted CA but the certificate is for localhost, not 127.0.0.1
	{
		FRecordedClient Connection;
		FWebSocketLibConnectParams Params = MakeParams(Server.GetUrl(TEXT("127.0.0.1")));
		Params.AdditionalCACertificatesPEM = Server.GetCACertificatePEM();
		Connection.Connect(Params, Error);
		TestTrue(TEXT("Host mismatch fails"), Connection.WaitFail());
		const FString FailError = Connection.Recorder->Get(&FLibRecorder::FailError);
		TestTrue(TEXT("Error names the host mismatch"), FailError.Contains(TEXT("does not match host")));
		AddInfo(FString::Printf(TEXT("Host mismatch: %s"), *FailError));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWebSocketLibLifetimeTest, "WebSocketClient.Lib.Lifetime", WebSocketLibTests::TestFlags)

bool FWebSocketLibLifetimeTest::RunTest(const FString& Parameters)
{
	FWebSocketTestServer Server;
	if (!TestTrue(TEXT("Server started"), Server.Start(false)))
	{
		return false;
	}
	FString Error;

	//Destroyed while connecting and while open: no callbacks afterwards
	{
		FLibRecorderRef Connecting = MakeRecorder();
		FLibRecorderRef Open = MakeRecorder();
		{
			FWebSocketLibClient Client;
			Client.SetCallbacks(Connecting->MakeCallbacks());
			Client.Connect(MakeParams(Server.GetUrl()), Error);
		}
		{
			FWebSocketLibClient Client;
			Client.SetCallbacks(Open->MakeCallbacks());
			Client.Connect(MakeParams(Server.GetUrl()), Error);
			WaitFor([&]() { return Open->Get(&FLibRecorder::Opens) > 0; });
		}
		Settle(0.3f);
		TestEqual(TEXT("Destroyed while connecting: no callbacks"), Connecting->Get(&FLibRecorder::Opens) + Connecting->Get(&FLibRecorder::Closes) + Connecting->Get(&FLibRecorder::Fails), 0);
		TestEqual(TEXT("Destroyed while open: no close callback"), Open->Get(&FLibRecorder::Closes), 0);
	}

	//Connecting again retires the previous connection silently
	{
		FLibRecorderRef First = MakeRecorder();
		FLibRecorderRef Second = MakeRecorder();
		FWebSocketLibClient Client;
		Client.SetCallbacks(First->MakeCallbacks());
		Client.Connect(MakeParams(Server.GetUrl()), Error);
		TestTrue(TEXT("First opened"), WaitFor([&]() { return First->Get(&FLibRecorder::Opens) > 0; }));
		Client.SetCallbacks(Second->MakeCallbacks());
		Client.Connect(MakeParams(Server.GetUrl()), Error);
		TestTrue(TEXT("Second opened"), WaitFor([&]() { return Second->Get(&FLibRecorder::Opens) > 0; }));
		Client.SendText(TEXT("to second"));
		TestTrue(TEXT("Second receives"), WaitFor([&]() { return Second->NumTexts() == 1; }));
		Settle(0.2f);
		TestEqual(TEXT("First got no close"), First->Get(&FLibRecorder::Closes), 0);
		TestEqual(TEXT("First got no messages"), First->NumTexts(), 0);
	}

	//A callback destroys its own client on the network thread
	{
		struct FOwner
		{
			FCriticalSection Lock;
			TUniquePtr<FWebSocketLibClient> Client;
			std::atomic<bool> bDestroyed{ false };
		};
		TSharedRef<FOwner, ESPMode::ThreadSafe> Owner = MakeShared<FOwner, ESPMode::ThreadSafe>();
		Owner->Client = MakeUnique<FWebSocketLibClient>();

		FLibRecorderRef Recorder = MakeRecorder();
		FWebSocketLibCallbacks Callbacks = Recorder->MakeCallbacks();
		Callbacks.OnText = [Owner](const FString& Message)
		{
			FScopeLock Guard(&Owner->Lock);
			Owner->Client.Reset();
			Owner->bDestroyed = true;
		};

		{
			FScopeLock Guard(&Owner->Lock);
			Owner->Client->SetCallbacks(Callbacks);
			Owner->Client->Connect(MakeParams(Server.GetUrl()), Error);
		}
		TestTrue(TEXT("Opened"), WaitFor([&]() { return Recorder->Get(&FLibRecorder::Opens) > 0; }));
		{
			FScopeLock Guard(&Owner->Lock);
			Owner->Client->SendText(TEXT("destroy me"));
		}
		TestTrue(TEXT("Client destroyed from its own callback"), WaitFor([&]() { return Owner->bDestroyed.load(); }));
		Settle(0.2f);
		TestEqual(TEXT("No close callback after destruction"), Recorder->Get(&FLibRecorder::Closes), 0);
	}
	return true;
}

#endif
