# socketio-client-ue4
socket.io client plugin for UE4

[Socket.io](http://socket.io/) is a performant real-time bi-directional communication library. There are two parts, the server written in node.js and the client typically javascript for the web. There are alternative client implementations and this repo uses the [C++11 client library](https://github.com/socketio/socket.io-client-cpp) ported to UE4.

Uses [Socket.io prebuild libraries for VS2015](https://github.com/getnamo/socketio-client-prebuild)

[Unreal Forum Thread](https://forums.unrealengine.com/showthread.php?110680-Plugin-Socket-io-Client)


Recommended socket.io server: 1.2+ for regular (e.g. JSON or string transport), 1.4+ if you're using Binary data transport.


## Quick Install & Setup ##

 1.	[Download Latest Release](https://github.com/getnamo/socketio-client-ue4/releases)
 2.	Create new or choose project.
 3.	Browse to your project folder (typically found at Documents/Unreal Project/{Your Project Root})
 4.	Copy *Plugins* folder into your Project root.
 5.	Restart the Editor and open your project again. Plugin is now ready to use.


## How to use - BP Basics

Add the SocketIO Client Component to your blueprint actor of choice 

![IMG](http://i.imgur.com/lSkfHQ2.png)

Specify your address and port, defaults to localhost (127.0.0.1) at port 3000

![IMG](http://i.imgur.com/rjm2pKw.png)

Call *Bind Event* for each event you wish the client to subscribe, e.g. 'chat message'

If you expect to receive events, select your component and in the Details pane press the + to add an 'On' event to your event graph

![IMG](http://i.imgur.com/mZVTJWE.png)

Handle this event for your event types, e.g. printing 'chat message' event strings.

![IMG](http://i.imgur.com/0BCFOoS.png)

If you want to send information to the server, emit events on the SocketIO Client Component, e.g. pressing M to emit a 'chat message' string

![IMG](http://i.imgur.com/EOadatA.png)

## How to use - C++

### Setup

To use the C++ code from the plugin add it as a dependency module in your project build.cs

```PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SocketIOClient"});```

```#include "SocketIOClientComponent.h"``` and add *USocketIoClientComponent* to your actor of choice or reference it from another component by getting it on begin play e.g.

```
SIOComponent = Cast<USocketIOClientComponent>(this->GetOwner()->GetComponentByClass(USocketIOClientComponent::StaticClass()));
if (!SIOComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("No sister socket IO component found"));
	return;
}
else
{
	UE_LOG(LogTemp, Log, TEXT("Found SIOComponent: %s"), *SIOComponent->GetDesc());
}
```

### Connect / Disconnect

To connect simply change your address, the component will auto-connect on component initialization.


```
USocketIOClientComponent* SIOComponent; //get a reference or add as subobject in your actor

//the component will autoconnect, but you may wish to change the url before it does that via
SIOComponent->AddressAndPort = FString("http://127.0.0.1:3000"); //change your address
```

You can also connect at your own time of choosing by disabling auto-connect and connecting either to the default address or one of your choosing

```
//you can also disable auto connect and connect it at your own time via
SIOComponent->ShouldAutoConnect = false;
SIOComponent->Connect(); 

//You can also easily disconnect at some point, reconnect to another address
SIOComponent->Disconnect();
SIOComponent->Connect(FString("http://127.0.0.1:3000"));
```

### Emitting Events

####String

Emit a string via

```SIOComponent->Emit(FString("myevent"), FString(TEXT("some data or stringified json"));```

####Binary or raw data

Emit raw data via

```
TArray<uint8> Buffer;

//fill buffer with your data

SIOComponent->EmitBuffer(FString("myBinarySendEvent"), Buffer.GetData(), Buffer.Num());
```

####Complex message using sio::message

see [sio::message](https://github.com/socketio/socket.io-client-cpp/blob/master/src/sio_message.h) for how to form a raw message. Generally it supports a lot of std:: variants e.g. std::string or more complex messages e.g. [socket.io c++ emit readme](https://github.com/socketio/socket.io-client-cpp#emit-an-event)

e.g. emitting {type:"image"} object

```
//create object message
auto message = sio::object_message::create();

//set map property string
message->get_map()["type"] = sio::string_message::create(std::string("image"));

//emit message
SIOComponent->EmitRaw(ShareResourceEventName, message);
```

with a callback

```
SIOComponent->EmitRawWithCallback(FString("myRawMessageEventWithAck"), string_message::create(username), [&](message::list const& msg) {
	//got data, handle it here
});
```


### Receiving Events

To receive events you can bind lambdas which makes things awesomely easy e.g.

#### String

```
SIOComponent->BindStringMessageLambdaToEvent([&](const FString& Name, const FString& Data)
		{
			//do something with your string data
		}, FString(TEXT("myStringReceiveEvent")));
```

#### Binary

```
SIOComponent->BindBinaryMessageLambdaToEvent([&](const FString& Name, const TArray<uint8>& Buffer)
		{
			//Do something with your buffer
		}, FString(TEXT("myBinaryReceiveEvent")));
```

####Complex message using sio::message

Currently the only way to handle json messages as the plugin doesn't auto-convert json types to UE4 types (contribute!). See [sio::message](https://github.com/socketio/socket.io-client-cpp/blob/master/src/sio_message.h) or [socket.io c++ readme](https://github.com/socketio/socket.io-client-cpp#emit-an-event) for examples.

e.g. expecting a result {type:"some type"}

```
SIOComponent->BindRawMessageLambdaToEvent([&](const FString& Name, const sio::message::ptr& Message)
		{
		        //if you expected an object e.g. {}
			if (Message->get_flag() != sio::message::flag_object)
			{
				UE_LOG(LogTemp, Warning, TEXT("Warning! event did not receive expected Object."));
				return;
			}
			auto MessageMap = Message->get_map();
			
			//use the map to decode an object member e.g. type string
			auto typeObject = MessageMap["type"];
			if (uriObject->get_flag() == uriObject->flag_string)
			{
				FString TypeValue = USocketIOClientComponent::FStringFromStd(typeObject->get_string());
			}
			
		}, FString(TEXT("myArbitraryReceiveEvent")));
```

## License

MIT
