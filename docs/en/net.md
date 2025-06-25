# <center>**Brux Scripting Reference Manual**</center>
## <center>Networking</center>



&nbsp;

* <a name="netNewSocket"></a>**`newWebSocket( mode )`**

  Initializes a new websocket. Available modes include `"tcp"`, useful for when reliable connections are needed, but slower, and `"udp"`, for faster connections at the risk of missing messages.

* <a name="netOpen"></a>**`netOpen( id, host, port )`**

  Attempts to connect socket `id` to a given `host` and `port`. Returns true or false if it resolves the host.

* <a name="netClose"></a>**`netClose( id )`**

  Disconnects a socket. The socket still exists, and can be reopened at another address.

* <a name="netDelete"></a>**`netDelete( id )`**

  Deletes a socket. This will also close it. Use this when you're done with it completely.

* <a name="netSend"></a>**`netSend( id, message )`**

  Sends a message up to 1024 characters long. Returns true or false if it succeeds in sending.

* <a name="netReceive"></a>**`netReceive( id )`**

  Attempts to receive data from a socket. If it succeeds, or there is no data to receive, it will return true.

* <a name="netQueued"></a>**`netQueued( id )`**

  Checks if any messages are queued in the socket.

* <a name="netGet"></a>**`netGet( id )`**

  Returns the message at the front of the socket's queue. This works as a pop, and will delete the message from the queue.

* <a name="netClear"></a>**`netClear( id )`**

  Empties the queue of a socket.

* <a name="netFlush"></a>**`netFlush()`**

  Closes and deletes all sockets. IDs for new sockets will be freed as well.