# socketio-client-ue4
Socket.io client plugin for UE4.

[![GitHub release](https://img.shields.io/github/release/getnamo/socketio-client-ue4.svg)](https://github.com/getnamo/socketio-client-ue4/releases)
[![Github All Releases](https://img.shields.io/github/downloads/getnamo/socketio-client-ue4/total.svg)](https://github.com/getnamo/socketio-client-ue4/releases)

[Socket.io](http://socket.io/) is a performant real-time bi-directional communication library. There are two parts, the server written in node.js and the client typically javascript for the web. There are alternative client implementations and this repo uses the [C++11 client library](https://github.com/socketio/socket.io-client-cpp) ported to UE4.

Socket.IO Lib uses _asio_, _rapidjson_, and _websocketpp_. SIOJson is originally forked from ufna's [VaRest](https://github.com/ufna/VaRest)

[Unreal Forum Thread](https://forums.unrealengine.com/showthread.php?110680-Plugin-Socket-io-Client)


Recommended socket.io server version: 1.4+.

### Contribute! Current Main Issues:

Current platform issues:

* Xbox/PS4 platform untested - see [issue 117](https://github.com/getnamo/socketio-client-ue4/issues/117)
* Lumin platform untested - see [issue 114](https://github.com/getnamo/socketio-client-ue4/issues/114)

HTTPS currently not yet supported
* OpenSSL Support - [issue39](https://github.com/getnamo/socketio-client-ue4/issues/39), temporary [workaround available](https://github.com/getnamo/socketio-client-ue4/issues/72#issuecomment-371956821).

## Quick Install & Setup ##

### Via Github Releases
 1. [Download Latest Release](https://github.com/getnamo/socketio-client-ue4/releases)
 2. Create new or choose project.
 3. Browse to your project folder (typically found at Documents/Unreal Project/{Your Project Root})
 4. Copy *Plugins* folder into your Project root.
 5. Plugin should be now ready to use.
 
 ### Via Unreal Engine Marketplace (helps support plugin development and maintenance)
 
 Available at this link: [Socket.IO Client - Marketplace](https://www.unrealengine.com/marketplace/socket-io-client)
 
 ### Optional Plugin Enabled Check
 5. If your plugin isn't enabled for whatever reason you can enable the plugin via Edit->Plugins. Scroll down to Project->Networking. Click Enabled.
 6. Restart the Editor and open your project again. Plugin is now ready to use.


## Example Project - Chat

For an example project check out https://github.com/getnamo/socketio-client-ue4-example which contains both server and client parts required to try out socket.io based chat, from UE4 to any other client and vice versa.

## How to use - BP Basics

Add the SocketIO Client Component to your blueprint actor of choice 

![IMG](http://i.imgur.com/lSkfHQ2.png)

By default the component will auto connect *on begin play* to your default address and port [http://localhost:3000](http://localhost:3000). You can change this default address to connect to your service instead.

![IMG](http://i.imgur.com/dWxCmvQ.png)

If you want to connect at your own time, you change the default variable *Should Auto Connect* to false and then call *Connect* with your address

Call *Bind Event* for each event you wish the client to subscribe, e.g. 'chat message'

If you expect to receive events, select your component and in the Details pane press the + to add an 'OnEvent' event to your event graph

Handle this event for your event types, e.g. printing 'chat message' event strings.

![IMG](http://i.imgur.com/vVlNBlx.png)


If you want to send information to the server, emit events on the SocketIO Client Component, e.g. pressing M to emit a 'chat message' string

![IMG](http://i.imgur.com/nihMSPz.png)

### Note on Printing Json Value

A very common mistake is to drag from a ```SIOJsonValue``` to the print string for basic debug. By default the engine will pick ```Get Display Name```, this is incorrect as it will only print out the container objects engine name and nothing about the actual value. Instead you want to use either ```Encode Json``` or ```As String(SIOJson Value)```, either of the two will re-encode the value as a json string. Encode Json is also available for ```SIOJsonObject``` types.

![printing a value](https://i.imgur.com/1kwpBYS.png)

## Blueprint - Advanced

### Simple Json

You can formulate any *SIOJsonValue* directly in blueprint. Apart from native basic types which are supported directly via conversion and e.g. *Construct Json String Value*, you can construct *SIOJsonObject*s and fill their fields.

![IMG](http://i.imgur.com/PnxD6Ui.png)

Start with *Construct Json Object* then set any desired fields. In this instance we wanted to make the JSON *{"myString":"Hello"}* so we used *Set String Field* and then auto-convert the object into a message.

### Complex Json

By combining arrays and objects you can form almost any data type, nest away!

![IMG](http://i.imgur.com/lj07Jsw.png)

### Structs

The plugin supports making *SIOJsonValue*s from any unreal structs you make, including ones defined purely in blueprints!

An easy example of a familiar struct is the *Vector* type

![IMG](http://i.imgur.com/mPHOw0C.png)

But you can make a custom type and emit it or nest it inside other *SIOJsonValue*s which should make it easy to organize your data however you want it.

![IMG](http://i.imgur.com/czi0AIF.png)

### Binary

Socket.IO spec supports raw binary data types and these should be capable of being mixed in with other JSON types as usual. This plugin supports binaries as a first class citizen in blueprints and any arrays of bytes can be embedded and decoded in the chain as expected.

![IMG](http://i.imgur.com/PqxEJqI.png)

### Decoding Responses

There are many ways to decode your *SIOJsonValue* message, it all depends on your data setup. You can even decode your *JsonObject*s directly into structs, if the JSON structure has matching variable names.

![IMG](http://i.imgur.com/urAh2TH.png)

Make sure your server is sending the correct type of data, you should not be encoding your data into json strings on the server side if you want to decode them directly into objects in the Unreal side, send the objects as is and the socket.io protocol will handle serialization on both ends.

#### Json Object to Struct Example

Keep in mind that you need to match your json object names (case doesn't matter) and if you are using objects of objects, the sub-objects will need their own structs to build the full main struct. For example if we have the following json object:

```json
{
	"Title":
	{
		"Text":"Example",
		"Caption":"Used to guide developers"
	}
}
```

##### Defined Struct

Make a substruct for the _Title_ object with two string variables, _Text_ and _Caption_ matching your json object format.

![title substruct](https://i.imgur.com/1L8T4Tl.png)

and then make the main struct with the substruct and a member variable with the _Title_ property name to match your json.

![main struct](https://i.imgur.com/gcyDK1l.png)

##### Alternative Struct

If you know that you will have a set of properties of the same type (blueprints only support maps of same type), then you can use a Map property. In this example our title sub-object only has String:String type properties so we could use a String:String map named _Title_ instead of the sub-struct.

![alt struct](https://i.imgur.com/w6tttIh.png)

If you wish to mix types in an object, you will need to use defined structs as before.

##### Arrays of array
An Array of arrays is not supported in Unreal structs, a workaround is to use an array of structs that contains an array of the data type you want. The server side will need to adapt what it sends or you can decode using json fields.

### Conversion

Most primitive types have auto-conversion nodes to simplify your workflow. E.g. if you wanted to emit a float literal you can get a reference to your float and simply drag to the *message* parameter to auto-convert into a *SIOJsonValue*.

![IMG](http://i.imgur.com/4T79TUV.gif)

Supported auto-conversion

* Float
* Int
* Bool
* SIOJsonObject
* String *-technically supported but it will by default pick **Get Display Name** instead, use **As String** to get desired result*

### Emit with Callback

You can have a callback when, for example, you need an acknowledgement or if you're fetching data from the server. You can respond to this callback straight in your blueprint. Keep in mind that the server can only use the callback *once* per emit.

![IMG](http://i.imgur.com/Ed01Jq0.png)

Instead of using *Emit* you use *Emit With Callback* and by default the target is the calling blueprint so you can leave that parameter blank and simply type your function name e.g. *OnEcho* function.

![IMG](http://i.imgur.com/hXMXDd2.png)

If the function is missing or named incorrectly, your output log will warn you.

![IMG](http://i.imgur.com/PQinDYy.gif)

Your function expects a *SIOJsonValue* reference signature. By default this contains your first response value from you callback parameter. If your callback uses more than one parameter, make a second *SIOJsonValue* Input parameter which contains an array of all the responses.

Since 0.6.8, if you know your data type you can use that signature directly in your function name. E.g. if you're sending a callback with a float value you can make a function with the matching name and only one float parameter as your signature.

Supported Signatures:
- SIOJsonValue
- SIOJsonObject
- String
- Float
- Int
- Bool
- Byte Array

#### Emit With Graph Callback

Since v1.1.0 you can get results directly to your calling graph function. Use the ```Emit with Graph Callback``` method and simply drag off from the completed node to receive your result when your server uses the callback. This feature should be useful for fetching data from the server without breaking your graph flow.

![graph callback](https://i.imgur.com/CbFHxRj.png)

Limitations:
- Can only be used in Event Graphs (BP functions don't support latent actions)

#### Emit with Callback node.js server example

If you're unsure how the callbacks look like on the server side, here is a basic example:

```javascript
const io = require('socket.io')(http);

io.on('connection', (socket) => {
	
	//...

	socket.on('getData', (msg, callback) => {
		//let's say your data is an object
		let result = {};
	
		/* do something here to get your data */
		
		//callback with the results, this will call your bound function inside your blueprint
		callback(result);
	});
};
```

See https://socket.io/docs/server-api/#socket-on-eventName-callback for detailed API.

### Binding Events to Functions

Instead of using the event graph and comparing strings, you can bind an event directly to a function. The format to make the function is the same as [callbacks](https://github.com/getnamo/socketio-client-ue4#emit-with-callback).

![IMG](http://i.imgur.com/7fA1qca.png)


### Complex Connect

You can fill the optional _Query_ and _Headers_ parameters to pass in e.g. your own headers for authentication. 

The input type for both fields is a _SIOJsonObject_ with purely string fields or leaving it empty for default.

Here's an example of constructing a single header  _X-Forwarded-Host: qnova.io_ and then connecting.

![connectwithheader](https://cloud.githubusercontent.com/assets/542365/25309683/63bfe26e-27cb-11e7-877e-0590e40605f3.PNG)

### Plugin Scoped Connection

If you want your connection to survive level transitions, you can tick the class default option Plugin Scoped Connection. Then if another component has the same plugin scoped id, it will re-use the same connection. Note that if this option is enabled the connection will not auto-disconnect on *End Play* and you will need to either manually disconnect or the connection will finally disconnect when the program exits.

![plugin scoped connection](https://i.imgur.com/lE8BHbN.png)

This does mean that you may not receive events during times your actor does not have a world (such as a level transition without using a persistent parent map to which the socket.io component actor belongs). If this doesn't work for you consider switching to C++ and using [FSocketIONative](https://github.com/getnamo/socketio-client-ue4#c-fsocketionative), which doesn't doesn't depend on using an actor component.

### Statically Constructed SocketIOClient Component

Since v1.1.0 there is a BPFunctionLibrary method ```Construct SocketIOComponent``` which creates and correctly initializes the component in various execution contexts. This allows you to add and reference a SocketIOClient component inside a non-actor blueprint. Below is an example use pattern. It's important to save the result from the construct function into a member variable of your blueprint or the component will be garbage collected.

![static example](https://i.imgur.com/EX4anxd.png)

#### Note on Auto-connect

Game modes do have actor owners and will correctly respect ```bShouldAutoConnect```. The connection happens one tick after construction so you can disable the toggle and connect at own time.

Game Instances do *not* have actor owners and therefore cannot register and initialize the component. The only drawback is that you must manually connect. ```bShouldAutoConnect``` is disabled in this context.

#### Note on Emit with Graph Callback

Non actor-owners such as Game Instances cannot receive the graph callbacks due to invalid world context. This only affects this one callback method, other methods work as usual.

## How to use - C++

### Setup

To use the C++ code from the plugin add _SocketIOClient_, _SocketIOLib_, and _Json_ as dependency modules in your project build.cs. If you're using conversion methods you will also have to add _SIOJson_.

```c#
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SocketIOClient", "SocketIOLib", "Json", "SIOJson" });
```

This guide assumes you want to use the client component method. See the [_FSocketIONative_](https://github.com/getnamo/socketio-client-ue4#c-fsocketionative) section for non-actor based C++ details.

```#include "SocketIOClientComponent.h"``` and add *USocketIoClientComponent* to your actor of choice via e.g. a UProperty

and *CreateDefaultSubobject* in your constructor

```c++
SIOClientComponent = CreateDefaultSubobject<USocketIOClientComponent>(TEXT("SocketIOClientComponent"));
```

or reference it from another component by getting it on begin play e.g.

```c++
SIOClientComponent = Cast<USocketIOClientComponent>(this->GetOwner()->GetComponentByClass(USocketIOClientComponent::StaticClass()));
if (!SIOClientComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("No sister socket IO component found"));
	return;
}
else
{
	UE_LOG(LogTemp, Log, TEXT("Found SIOClientComponent: %s"), *SIOComponent->GetDesc());
}
```

### Connect / Disconnect

To connect simply change your address, the component will auto-connect on component initialization.


```c++
USocketIOClientComponent* SIOClientComponent; //get a reference or add as subobject in your actor

//the component will autoconnect, but you may wish to change the url before it does that via
SIOClientComponent->AddressAndPort = FString("http://127.0.0.1:3000"); //change your address
```

You can also connect at your own time by disabling auto-connect and connecting either to the default address or a custom one

```c++
//you can also disable auto connect and connect it at your own time via
SIOClientComponent->ShouldAutoConnect = false;
SIOClientComponent->Connect(); 

//You can also easily disconnect at some point, reconnect to another address
SIOClientComponent->Disconnect();
SIOClientComponent->Connect(FString("http://127.0.0.1:3000"));
```

### Receiving Events

To receive events call _OnNativeEvent_ and pass in your expected event name and callback lambda or function with ```void(const FString&, const TSharedPtr<FJsonValue>&)``` signature. Optionally pass in another FString to specify namespace, omit if not using a namespace (default ```TEXT("/")```). 

```c++
SIOClientComponent->OnNativeEvent(FString("MyEvent"), [](const FString& Event, const TSharedPtr<FJsonValue>& Message)
{
	//Called when the event is received. We can e.g. log what we got
	UE_LOG(LogTemp, Log, TEXT("Received: %s"), *USIOJConvert::ToJsonString(Message));
});
```

Message parameter is a [FJsonValue](http://api.unrealengine.com/INT/API/Runtime/Json/Dom/FJsonValue/), if you have a complex message you'll most commonly want to decode it into a [FJsonObject](http://api.unrealengine.com/INT/API/Runtime/Json/Dom/FJsonObject/) via ```AsObject()```.

Note that this is equivalent to the blueprint ```BindEventToFunction``` function and should be typically called once e.g. on beginplay.

### Emitting Events

In C++ you can use *EmitNative*, *EmitRaw*, or *EmitRawBinary*. *EmitNative* is fully overloaded and expects all kinds of native UE4 data types and is the recommended method.

#### String

Emit an FString. Note that *FString(TEXT("yourString"))* is recommended if you have performance concerns due to internal conversion from ```char*```

```c++
SIOClientComponent->EmitNative(FString("nativeTest"), FString("hi"));
```

#### Number

Emit a double

```c++
SIOClientComponent->EmitNative(FString("nativeTest"), -3.5f);
```

#### Boolean

Emit a raw boolean

```c++
SIOClientComponent->EmitNative(FString("nativeTest"), true);
```

#### Binary or raw data

Emit raw data via a TArray<uint8>

```c++
TArray<uint8> Buffer;	//null terminated 'Hi!'
Buffer.Add(0x48);
Buffer.Add(0x69);
Buffer.Add(0x21);
Buffer.Add(0x00);

SIOClientComponent->EmitNative(FString("nativeTest"), Buffer);
```

or

```c++
SIOComponent->EmitRawBinary(FString("myBinarySendEvent"), Buffer.GetData(), Buffer.Num());
```

#### FJsonObject - Simple

Option 1 - Shorthand

```c++
//Basic one field object e.g. {"myKey":"myValue"}
auto JsonObject = USIOJConvert::MakeJsonObject();								
JsonObject->SetStringField(FString("myKey"), FString("myValue"));

SIOClientComponent->EmitNative(FString("nativeTest"), JsonObject);
```

Option 2 - Standard

```c++
TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);	
```

#### FJsonObject - Complex Example

A nested example using various methods

```c++
//All types, nested
TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);						//make object option2
JsonObject->SetBoolField(FString("myBool"), false);
JsonObject->SetStringField(FString("myString"), FString("Socket.io is easy"));
JsonObject->SetNumberField(FString("myNumber"), 9001);

JsonObject->SetField(FString("myBinary1"), USIOJConvert::ToJsonValue(Buffer));				//binary option1 - shorthand
JsonObject->SetField(FString("myBinary2"), MakeShareable(new FJsonValueBinary(Buffer)));	//binary option2

JsonObject->SetArrayField(FString("myArray"), ArrayValue);
JsonObject->SetObjectField(FString("myNestedObject"), SmallObject);

SIOClientComponent->EmitNative(FString("nativeTest"), JsonObject);
```

#### Callback Example

Below is an example of emitting a simple object with the server using the passed in callback to return a response or acknowledgement.

```c++	
//Make an object {"myKey":"myValue"}
TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
JsonObject->SetStringField(FString("myKey"), FString("myValue"));

//Show what we emitted
UE_LOG(LogTemp, Log, TEXT("1) Made a simple object and emitted: %s"), *USIOJConvert::ToJsonString(JsonObject));

//Emit event "callbackTest" expecting an echo callback with the object we sent
SIOClientComponent->EmitNative(FString("callbackTest"), JsonObject, [&](auto Response)
{
	//Response is an array of JsonValues, in our case we expect an object response, grab first element as an object.
	auto Message = Response[0]->AsObject();

	//Show what we received
	UE_LOG(LogTemp, Log, TEXT("2) Received a response: %s"), *USIOJConvert::ToJsonString(Message));
});
```

#### UStruct

Plugin supports automatic conversion to/from UStructs, below is an example of a struct roundtrip, being in Json format on the server side.

```c++
USTRUCT()
struct FTestCppStruct
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	float SomeNumber;

	UPROPERTY()
	FString Name;
};
```

```c++
//Set your struct variables
FTestCppStruct TestStruct;
TestStruct.Name = FString("George");
TestStruct.Index = 5;
TestStruct.SomeNumber = 5.123f;

SIOClientComponent->EmitNative(FString("callbackTest"),  FTestCppStruct::StaticStruct(), &TestStruct, [&](auto Response)
{
	auto Message = Response[0]->AsObject();

	//Show what we received
	UE_LOG(LogTemp, Log, TEXT("Received a response: %s"), *USIOJConvert::ToJsonString(Message));

	//Set our second struct to the new values
	USIOJConvert::JsonObjectToUStruct(Message, FTestCppStruct::StaticStruct(), &MemberStruct);

	//Show that struct
	UE_LOG(LogTemp, Log, TEXT("Our received member name is now: %s"), *MemberStruct.Name);
});
```

## C++ FSocketIONative

If you do not wish to use UE4 AActors or UObjects, you can use the native base class [FSocketIONative](https://github.com/getnamo/socketio-client-ue4/blob/master/Source/SocketIOClient/Public/SocketIONative.h). Please see the class header for API. It generally follows a similar pattern to ```USocketIOClientComponent``` with the exception of native callbacks which you can for example see in use here: https://github.com/getnamo/socketio-client-ue4/blob/master/Source/SocketIOClient/Private/SocketIOClientComponent.cpp#L81

### Example FSocketIONative Custom Game Instance

SIOTestGameInstance.h
```c++
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SocketIONative.h"
#include "SIOTestGameInstance.generated.h"
UCLASS()
class SIOCLIENT_API USIOTestGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
	virtual void Shutdown() override;
	
	TSharedPtr<FSocketIONative> Socket;
};
```
SIOTestGameInstance.cpp
```c++
#include "SIOTestGameInstance.h"
#include "SocketIOClient.h"
void USIOTestGameInstance::Init()
{
	Super::Init();

	Socket= ISocketIOClientModule::Get().NewValidNativePointer();
	
	Socket->Connect("http://localhost:3000", nullptr, nullptr);

	Socket->OnEvent(TEXT("MyEvent"), [this](const FString& Event, const TSharedPtr<FJsonValue>& Message)
		{
			UE_LOG(LogTemp, Log, TEXT("Received: %s"), *USIOJConvert::ToJsonString(Message));
		});

	Socket->Emit(TEXT("MyEmit"), FString("hi"));
}

void USIOTestGameInstance::Shutdown()
{
	Super::Shutdown();

	if (Socket.IsValid())
	{
		ISocketIOClientModule::Get().ReleaseNativePointer(Socket);
		Socket = nullptr;
	}
}
```

## Alternative Raw C++ Complex message using sio::message

see [sio::message](https://github.com/socketio/socket.io-client-cpp/blob/master/src/sio_message.h) for how to form a raw message. Generally it supports a lot of std:: variants e.g. std::string or more complex messages e.g. [socket.io c++ emit readme](https://github.com/socketio/socket.io-client-cpp#emit-an-event). Note that there are static helper functions attached to the component class to convert from std::string to FString and the reverse.

```c++
static std::string USIOMessageConvert::StdString(FString UEString);

static FString USIOMessageConvert::FStringFromStd(std::string StdString);
```

and assuming 

```c++
FSocketIONative* NativeClient;
```
	
e.g. emitting *{type:"image"}* object

```c++
//create object message
auto message = sio::object_message::create();

//set map property string
message->get_map()["type"] = sio::string_message::create(std::string("image"));

//emit message
NativeClient->EmitRaw(ShareResourceEventName, message);
```

with a callback

```c++
NativeClient->EmitRawWithCallback(FString("myRawMessageEventWithAck"), string_message::create(username), [&](message::list const& msg) {
	//got data, handle it here
});
```


### Receiving Events

To receive events you can bind lambdas which makes things awesomely easy e.g.

#### Binary

```c++
NativeClient->OnBinaryEvent([&](const FString& Name, const TArray<uint8>& Buffer)
		{
			//Do something with your buffer
		}, FString(TEXT("myBinaryReceiveEvent")));
```

#### Complex message using sio::message

See [sio::message](https://github.com/socketio/socket.io-client-cpp/blob/master/src/sio_message.h) or [socket.io c++ readme](https://github.com/socketio/socket.io-client-cpp#emit-an-event) for examples.

e.g. expecting a result {type:"some type"}

```c++
NativeClient->OnRawEvent([&](const FString& Name, const sio::message::ptr& Message)
		{
		        //if you expected an object e.g. {}
			if (Message->get_flag() != sio::message::flag_object)
			{
				UE_LOG(LogTemp, Warning, TEXT("Warning! event did not receive expected Object."));
				return;
			}
			auto MessageMap = Message->get_map();
			
			//use the map to decode an object key e.g. type string
			auto typeMessage = MessageMap["type"];
			if (typeMessage->get_flag() == typeMessage->flag_string)
			{
				FString TypeValue = USocketIOClientComponent::FStringFromStd(typeMessage->get_string());
				
				//do something with your received type value!
			}
			
		}, FString(TEXT("myArbitraryReceiveEvent")));
```

## Http JSON requests

Using e.g. https://gist.github.com/getnamo/ced1e6fbee122b640169f5fb867ed540 server

You can post simple JSON requests using the SIOJRequest (this is the same architecture as [VARest](https://github.com/ufna/VaRest)). 

![Sending a JSON post request](https://i.imgur.com/UOJHcP0.png)

These request functions are available globally.

## Packaging

### C++
Works out of the box.

### Blueprint

#### Marketplace
Works out of the box.

#### Github
If you're using this as a project plugin you will need to convert your blueprint only project to mixed (bp and C++). Follow these instructions to do that: https://allarsblog.com/2015/11/04/converting-bp-project-to-cpp/

### iOS

If you're using non-ssl connections (which as of 1.0 is all that is supported), then you need to enable ```Allow web connections to non-HTTPS websites```

![IOS platform setting](https://i.imgur.com/J7Xzy2j.png)

Its possible you may also need to convert your IP4 to IP6, see https://github.com/getnamo/socketio-client-ue4/issues/136#issuecomment-515337500

### Android

Minimum/Target SDK 21 or higher is recommended, but not required.


## License

[![license](https://img.shields.io/github/license/getnamo/socketio-client-ue4.svg)](https://github.com/getnamo/socketio-client-ue4/blob/master/LICENSE)
