/*
Redo of Publisher-Subscriber using broadcast.

Wed, Aug  6 2014, 04:13 EEST

For documentation: 

The functionalithy is organized in the following categories (groups of methods)

1. Init subscriber : Initializing the communication process (setup of IPs and responders)
2. Actions triggered locally by the app: get, put, request a subscription or a value.
3. Actions triggered remotely from other nodes (via OSC): 
   - return a requested value, 
   - update a received attribute value
   - subcribe 
   - unsubscribe


*/

Subscriber : IdentityDictionary {
	
	//	classvar <servicesBroadcastMessage = '/services';
	classvar <localAddress;
	classvar <broadcastAddress;

	var <>requestMsg = '/request';
	var <>unsubscribeMsg = '/unsubscribe';
	var <>updateMsg = '/update';
	var <name;
	var <broadcastRoutine;
	var <broadcastRate = 1;
	var <port = 57130;
	var serviceRegistrationResponder;

	*initClass {
		NetAddr.broadcastFlag = true;
	}

	*new { | name = 'default' |
		^Registry(this, name, {
			super.new.initSubscriber(name);
		});
	}

	initSubscriber { | argName |
		name = argName;
		broadcastAddress = NetAddr(NetAddr.getBroadcastIp, port);
		localAddress = NetAddr(NetAddr.getLocalIp, port);
		this.initSubscriptionResponses;
	}

	// ================================================================
	// responses to requests from subscribers or remote subsciptions
	// ================================================================

	initSubscriptionResponses {
		// var <>updateMsg = '/update';
		OSCFunc({ | msg, time, address |
			// msg[0] -> updateMsg
			// msg[1] -> Name of attribute updated
			// msg[2...] -> Data sent (value of attribute)
			var attribute_name, attribute, data;
			attribute_name = msg[1];
			data = msg[2..];
			attribute = this.getAttribute(
				attributeName, 
				remotely: false, 
				subscribe: false
			);
			attribute.data = data;
			this,changed(attributeName, *data);
		}, updateMsg)

		// var <>requestMsg = '/request';
		OSCFunc({ | msg, time, address |
			// msg[0] -> requestMsg
			// msg[1] -> Name of attribute requested
			// msg[2] -> flag: if true then subscribe
			var attribute_name, subcsribe_p, attribute;
			attribute_name = msg[1];
			subscribe_p = msg[2];
			attribute = this.getAttribute(
				attributeName, 
				remotely: false, 
				subscribe: false
			);
			if (subscribe_p === true) { attribute addSubscriber: address };
			address.sendMsg(\update, attributeName, *attribute.data);
		}, requestMsg);
	
		// var <>unsubscribeMsg = '/unsubscribe';
		OSCFunc({ | msg, time, address |
			// msg[0] -> requestMsg
			// msg[1] -> Name of attribute requested
			// msg[2] -> flag: if true then subscribe
			var attribute_name, attribute;
			attribute_name = msg[1];
			attribute = this.[attributeName];
			attribute !? { attribute unsubscribe: address };
		}, unsubscribeMsg)
	}

	// ================================================================
	// access and setting of attributes
	// ================================================================
	get { | attributeName, subscribe = true |
		/*  --- if attribute exists, get its local cached value.
			--- Else:
			   (1) create attribute, setting its value to nil.
			   (2) request the value from network and  when received set its value.
			   (3) if subscribe is true, then subscribe to the attribute remotely. 
			--- Finally: return the current value of the attribute
 		*/
		var attribute;
		attribute = this[attributeName];
		attribute ?? {
			attribute = Attribute(attributeName);
			this[attributeName] = attribute;
			this.request(attributeName, subscribe);
		};
		^attribute.data;
	}

	put { | attributeName, value, broadcast = true |
		var attribute;
		attribute = this.getAttribute(attributeName, value, remotely: false);
		if (broadcast) { attribute.broadcast };
	}

	getAttribute { | attributeName, remotely = true, subscribe = true |
		var attribute;
		attribute = this[attributeName];
		attribute ?? {
			attribute = Attribute(attributeName);
			this[attributeName] = attribute;
			if (remotely) { this.request(attributeName, subscribe) };
		};
		^attribute;
	}

	request { | attributeName, subscribe = true |
		broadcastAddress.sendMsg(requestMsg, subscribe);
	}

	unsubscribe { | attributeName |
		var attribute;
		attribute = this[attributeName];
		attribute !? {
			attribute.sender.sendMsg(unsubscribeMsg);
		}
	}

	addSubscriber { | attributeName, subscriberAddress |
		var attribute;
		attribute = this[attributeName];
		attribute ?? {
			attribute = Attribute(attributeName, nil, nil);
			this[attributeName] = attribute;
		};
		attribute addSubscriber: subscriberAddress;
	}

	// ================================================================
	// Interface to local logic: Actions to be executed when an attribute is updated
	// ================================================================

	addUpdateAction { | listener, attributeName, action |
		listener.addNotifier(this, attributeName, action);
	}

	removeUpdateAction { | listener, attributeName |
		listener.removeNotifier(this, attributeName);
	}
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

	broadcast {
		subscribers do: { | s |
			if (Subscriber.localAddr != s) { s.sendMsg('/update', name, *data); }
		} 
	}
	addSubscriber { | subscriber | subscribers add: subscriber; }
	removeSubscriber { | subscriber | subscribers remove: subscriber; }
}