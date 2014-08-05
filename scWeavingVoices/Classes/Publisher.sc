/*
Implement subscribe-publish of attributes to update values across a distributed system 
over many sclang instances.

Notions: 
- Publisher: 
- Subscriber:
- Subscribe to an attribute.

Mon, Aug  4 2014, 11:52 EEST
*/

Publisher  {
	/* Broadcast changes in any attribute of the model to all nodes that have subscribed 
		to that attribute. */
	var <name;
	var <putResponder, <subscribeResponder, <unsubscribeResponder;
	var <attributes;

	*enable { this.default.enable }
	*disable { this.default.disable }

	enable { 
		[putResponder, subscribeResponder, unsubscribeResponder] do: _.enable;
	}

	disable { 
		[putResponder, subscribeResponder, unsubscribeResponder] do: _.disable;
	}

	*default { ^this.new }

	*new { | name = \default |
		^Registry(this, name, { this.newCopyArgs(name).initPublisher });
	}

	initPublisher {
		putResponder = OSCFunc({ | msg, time, senderAddr |
			// attribute ... data
			this.put(msg[1], msg[2..], senderAddr);
		}, this.class.putMessage(name));
		subscribeResponder = OSCFunc({ | msg |
			// attribute, ip, port
			this.subscribe(msg[1], NetAddr(msg[2], msg[3]))
		}, this.class.subscribeMessage(name));
		unsubscribeResponder = OSCFunc({ | msg |
			// attribute, ip, port
			this.unsubscribe(msg[1], NetAddr(msg[2], msg[3]))
		}, this.class.unsubscribeMessage(name));
		attributes = IdentityDictionary();
	}

	*putMessage { | publisherName = 'default' |
		^('/put' ++ '/' ++ publisherName).asSymbol
	}

	*subscribeMessage { | publisherName = 'default' |
		^('/subscribe' ++ '/' ++ publisherName).asSymbol
	}

	*unsubscribeMessage { | publisherName = 'default' |
		^('/unsubscribe' ++ '/' ++ publisherName).asSymbol
	}

	put { | attributeName, data, senderAddr |
		this.getAttribute(attributeName)
		.setData(data, senderAddr)
		.broadcast;
	}

	getAttribute { | attributeName |
		var attribute;
		attribute = attributes[attributeName];
		if (attribute.isNil) {
			attribute = Attribute(attributeName);
			attributes[attributeName] = attribute;
		};
		^attribute;
	}

	subscribe { | attributeName subscriberAddress |
		this.getAttribute(attributeName).addSubscriber(subscriberAddress);
	}

	unsubscribe { | attributeName subscriberAddress |
		var attribute;
		attribute = attributes[attributeName];
		attribute !? { attribute.removeSubscriber(subscriberAddress) }
	}
}

Subscriber : NetAddr {
	/*  Subscribe to a publisher so as to receive updates when an attribute 
		in the system changes.  
		A Subscriber subscribes many attributes to one publisher.

		The NetAddr of a Subscriber is the address of the publisher.
		The name of a Subscriber is the name of the publisher. Default is: 'default'.
	*/

	var <name;
	var <putMessage, <subscribeMessage, <unsubscribeMessage;
	var <attributes;
	var <responder;

	*new { | ip, port, name = 'default' |
		^Registry(this, ip, port, name, {
			super.new(ip, port).initSubscriber(name);
		});
	}

	initSubscriber { | argName |
		name = argName;
		putMessage = Publisher.putMessage(name);
		subscribeMessage = Publisher.subscribeMessage(name);
		unsubscribeMessage = Publisher.unsubscribeMessage(name);
		attributes = IdentityDictionary();
		responder = OSCFunc({ | msg, time, address |
			// for updates received from the Publisher
			// THIS DOES NOT BROADCAST
			this.updateAttribute(msg[1], msg[2..], address);
		}, '/update')
	}

	put { | attribute, value, address |
		// For internal puts from the local app only
		// THIS BROADCASTS!!!!!
		this.updateAttribute(attribute, value, address ?? { NetAddr.localAddr }); // store + broadcast locally
		this.sendMsg(putMessage, attribute, *value);  // broadcast on network
	}

	updateAttribute { | attributeName, value, address |
		var attribute, time;
		attribute = attributes[attributeName];
		time = Date.getDate.rawSeconds;
		attribute ?? {
			attribute = Attribute(name, value, time, address);
			attributes[name] = attribute;
		};
		attribute.updateValue;
		this.changed(attributeName, value, time, address); // broadcast on local app
	}

	subscribe { | attribute | this.sendMsg(subscribeMessage, attribute) }
	unsubscribe { | attribute | this.sendMsg(unsubscribeMessage, attribute) }

	enable { responder.enable }
	disable { responder.disable }
}

Attribute {
	/*  Data item stored in any node of the network.
		Broadcast  changes in your data to all subscribed nodes in the system */
	var <name, <sender, <data, <time, <subscribers;

	*new { | name, sender, data, time, subscribers |
		^this.newCopyArgs(name, sender, data, time ?? { Date.getDate.rawSeconds }, Set());
	}

	setData { | argData senderAddr |
		data = argData;
		// time = argTime ?? { Process.elapsedTime };
		senderAddr ?? { senderAddr = NetAddr.localAddr };
		if (sender.notNil and: { sender != senderAddr }) {
			this.changeSender(senderAddr);
		};
		//	this.broadcast;
	}

	changeSender { | newSender |
		postf(
			"Sender change in attribute: %.\nOld sender: %\nNew sender: %\n",
			name, sender, newSender
		);
		sender = newSender;
	}

	broadcast { subscribers do: { | s | s.sendMsg('/update', name, *data); } }
	addSubscriber { | subscriber | subscribers add: subscriber; }
	removeSubscriber { | subscriber | subscribers remove: subscriber; }
}
