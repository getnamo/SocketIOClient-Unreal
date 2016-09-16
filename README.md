# socketio-client-ue4
socket.io client plugin for UE4

[Socket.io](http://socket.io/) is a performant real-time bi-directional communication library. There are two parts, the server written in node.js and the client typically javascript for the web. There are alternative client implementations and this repo uses the [C++11 client library](https://github.com/socketio/socket.io-client-cpp) ported to UE4.

Uses [Socket.io prebuild libraries for VS2015](https://github.com/getnamo/socketio-client-prebuild)

[Unreal Forum Thread](https://forums.unrealengine.com/showthread.php?110680-Plugin-Socket-io-Client)




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

Call bind for each event you wish the client to subscribe, e.g. 'chat message'

If you expect to receive events, select your component and in the Details pane press the + to add an 'On' event to your event graph

![IMG](http://i.imgur.com/mZVTJWE.png)

Handle this event for your event types, e.g. printing 'chat message' event strings.

![IMG](http://i.imgur.com/0BCFOoS.png)

If you want to send information to the server, emit events on the SocketIO Client Component, e.g. pressing M to emit a 'chat message' string

![IMG](http://i.imgur.com/EOadatA.png)

## License

MIT
