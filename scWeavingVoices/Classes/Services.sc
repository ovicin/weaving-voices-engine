/*
Redo of Publisher-Subscriber using broadcast.

Wed, Aug  6 2014, 04:13 EEST
*/

Services : IdentityDictionary {
	
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
			super.new.initServices(name);
		});
	}

	initServices { | argName |
		name = argName;
		broadcastAddress = NetAddr(NetAddr.getBroadcastIp, port);
		localAddress = NetAddr(NetAddr.getLocalIp, port);
		/*
		serviceRegistrationResponder = OSCFunc({ | msg, time, address |
			[this, thisMethod.name, "attribute list received:", msg[1..]].postln;
			msg[1..] do: this.addAttributeIfNew(_);
		}, servicesBroadcastMsg, nil, port);
		broadcastRoutine = {
			loop {
				this.broadcastServices;
				broadcastRate.wait;
			}
		}.fork;
		*/
	}

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

	getAttribute { | attributeName, value, remotely = true, subscribe = true |
		var attribute;
		attribute = this[attributeName];
		attribute ?? {
			attribute = Attribute(attributeName);
			this[attributeName] = attribute;
			if (remotely) { this.request(attributeName, subscribe) };
		};
		^attribute.data = value;
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

	// Set value 
	set {

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