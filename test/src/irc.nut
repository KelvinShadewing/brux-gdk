class IRC {
	socket = null;
	nickname = "";
	channel = "";
	connected = false;
	messageHandlers = {};

	constructor() {
		socket = NetSocket();
		messageHandlers = {
			"PING": function(msg) {
				local pong = "PONG :" + msg.split(":")[1] + "\r\n";
				socket.send(pong);
			}
		};
	}

	function connect(server, port, nick, chan) {
		if (!socket.connect(server, port))
			return false;

		nickname = nick;
		channel = chan;
		connected = true;

		// Send IRC registration commands
		if (!send("NICK " + nickname)) return false;
		if (!send("USER " + nickname + " 0 * :" + nickname)) return false;
		if (!send("JOIN #" + channel)) return false;

		return true;
	}

	function disconnect() {
		if (!connected) return false;
		if (socket.disconnect()) {
			connected = false;
			return true;
		}
		return false;
	}

	function send(message) {
		if (!connected) return false;
		return socket.send(message + "\r\n");
	}

	function update() {
		if (!connected) return;

		// Process any new messages
		socket.receive();
		while (socket.hasMessage()) {
			local msg = socket.getNextMessage();
			if (msg != null) {
				handleMessage(msg);
			}
		}
	}

	function handleMessage(raw) {
		// Basic IRC message parsing
		if (raw.len() == 0) return;

		local parts = split(raw, " ");
		if (parts.len() < 2) return;

		// Handle PING specially
		if (parts[0] == "PING") {
			messageHandlers["PING"](raw);
			return;
		}

		// Extract command from standard IRC message
		local command = parts[1];
		if (command in messageHandlers) {
			messageHandlers[command](raw);
		}
	}

	function onCommand(command, handler) {
		messageHandlers[command] <- handler;
	}

	function sendMessage(target, text) {
		return send("PRIVMSG " + target + " :" + text);
	}

	function sendChannelMessage(text) {
		return sendMessage("#" + channel, text);
	}

	function isConnected() {
		return connected;
	}
}
