//
//  ofxBeloi.cpp
//  ofWeavingVoices
//
//  Created by Ovidiu on 06/08/14.
//
//

#include "ofxBeloi.h"

#if 0
WeavingVoicesService::WeavingVoicesService(){
    sender.setup(SERVER_IP, SERVER_PORT);
    
    receiver.setup(SERVER_PORT);
    
    
    
}

void WeavingVoicesService::init(string ServiceName, string LocalAddress, string BroadCastAddress){
    this->LocalAddress = LocalAddress;
    this->BroadCastAddress = BroadCastAddress;
    this->ServiceName = ServiceName;
}

void WeavingVoicesService::put(WeavingVoicesAttribute &attribute){
    ofxOscMessage m;
    m.setAddress("/test");
    m.addIntArg(1);
    m.addFloatArg(3.5f);
    m.addStringArg("hello");
    m.addFloatArg(ofGetElapsedTimef());
    sender.sendMessage(m);
}

void WeavingVoicesService::subscribe(WeavingVoicesAttribute &attribute){
    
}

void WeavingVoicesService::unsubscribe(WeavingVoicesAttribute &attribute){
    
}

void WeavingVoicesService::update(){
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/mouse/position"){
			// both the arguments are int32's
			//mouseX = m.getArgAsInt32(0);
			//mouseY = m.getArgAsInt32(1);
		}
		// check for mouse button message
		else if(m.getAddress() == "/mouse/button"){
			// the single argument is a string
			//mouseButtonState = m.getArgAsString(0);
		}
		else{
			// unrecognized message: display on the bottom of the screen
			/*
             string msg_string;
             msg_string = m.getAddress();
             msg_string += ": ";
             for(int i = 0; i < m.getNumArgs(); i++){
             // get the argument type
             msg_string += m.getArgTypeName(i);
             msg_string += ":";
             // display the argument - make sure we get the right type
             if(m.getArgType(i) == OFXOSC_TYPE_INT32){
             msg_string += ofToString(m.getArgAsInt32(i));
             }
             else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
             msg_string += ofToString(m.getArgAsFloat(i));
             }
             else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
             msg_string += m.getArgAsString(i);
             }
             else{
             msg_string += "unknown";
             }
             }
             // add to the list of strings to display
             msg_strings[current_msg_string] = msg_string;
             timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
             current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
             // clear the next line
             msg_strings[current_msg_string] = "";
             */
		}
        
	}
}

#endif
