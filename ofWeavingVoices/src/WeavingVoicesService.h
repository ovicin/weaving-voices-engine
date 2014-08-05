//
//  WeavingVoicesService.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/08/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include "WeavingVoicesAttribute.h"


#define SERVER_IP ""
#define SERVER_PORT

class WeavingVoicesService{
public:
    

    WeavingVoicesService();
    
    /*PUT: Updates an attribute locally and remotely.
    
     Properties:
    
        Name
        Value
     Actions:
    
     Update the Arbiter attributes dictionary
     Update the Local attributes dictionary
     */
    void put(WeavingVoicesAttribute &attribute);
    
    /*SUBSCRIBE: Subscribes to an attribute locally or remotely.
    
     Properties:
    
        Attribute Name
     Actions:
    
     Updates the Subscribers for a particular Name on the Arbiter attributes dictionary
            Return the current Value for the particular Name
     */
    
    WeavingVoicesAttribute subscribe();
    
private:
    
    ofxOscReceiver receiver;
    ofxOscSender sender;
    
};
