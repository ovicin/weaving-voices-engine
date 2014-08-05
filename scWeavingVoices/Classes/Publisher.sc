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
	var <putResponder, <subscribeResponder;
	var <attributes;

	*enable { this.default.enable }
	*disable { this.default.disable }
	enable { [putResponder, subscribeResponder] do: _.enable; }
	disable { [putResponder, subscribeResponder] do: _.disable; }

	*default { ^this.new }

	*new { | name = \default |
		^Registry(this, name, { this.newCopyArgs(name).initPublisher });
	}

	initPublisher {
		putResponder = OSCFunc({ | msg, time, senderAddr |
			// attribute ... data
			this.put(msg[1], msg[2..], time, senderAddr);
		}, ('/put' ++ '/' ++ name).asSymbol);
		subscribeResponder = OSCFunc({ | msg |
			// attribute, ip, port
			this.subscribe(msg[1], msg[2], msg[3])
		}, ('/subscribe' ++ '/' ++ name).asSymbol);
		attributes = IdentityDictionary();
	}

	publish { | attributeName, data, time, senderAddr |
		var attribute;
		attribute = attributes[attributeName];
		if (attribute.isNil) {
			attribute = Attribute(attributeName, senderAddr);
			attributes[attributeName] = attribute;
		}{
			if (attribute.address != senderAddr) {
				attribute.changeSender(senderAddr);
			}
		};
		attribute.setData(data, time);
	}

	addSubscriber { | attributeName subscriberAddress |
		
	}

	removeSubscriber { | attributeName subscriberAddress |

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
	var <attributes;
	var <responder;

	*new { | ip, port, name = 'default' |
		^Registry(this, ip, port, name, {
			super.new(ip, port).initSubscriber(name);
		});
	}

	initSubscriber { | argName |
		name = argName;
		attributes = IdentityDictionary();
		responder = OSCFunc({ | msg |
			this.changed(msg[1..])
		}, '/update')
	}

	subscribe { | attribute |
		this.sendMsg(attribute)
	}

	unSubscribe { | attribute |
		
	}
	enable { responder.enable }
	disable { responder.disable }
}

Attribute {
	/*  Data item stored in any node of the network.
		Broadcast  changes in your data to all subscribed nodes in the system */
	var <name, <sender, <data, <time, <subscribers;

	*new { | name, sender, data, time, subscribers |
		^this.newCopyArgs(name, sender, data, time ?? { Process.elapsedTime }, Set());
	}

	changeSender { | newSender |
		postf(
			"Sender change in attribute: %.\nOld sender: %\nNew sender: %\n",
			name, sender, newSender
		);
		sender = newSender;
	}

	setData { | argData argTime |
		data = argData;
		time = argTime ?? { Process.elapsedTime };
		this.broadcast;
	}

	broadcast {
		subscribers do: { | s |
			s.sendMsg('/update', name, *data);
		}
	}

	addSubscriber { | subscriber |
		subscribers add: subscriber;
	}

	removeSubscriber { | subscriber |
		subscribers remove: subscriber;
	}
}
