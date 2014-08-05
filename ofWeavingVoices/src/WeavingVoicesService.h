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
     
     SENDS OSC Message Format
     
        /put /AttributeName val
     
     
     */
    
    void put(WeavingVoicesAttribute &attribute);
    
    /*SUBSCRIBE: Subscribes to an attribute locally or remotely.
    
     Properties:
    
        Attribute Name
     Actions:
    
     Updates the Subscribers for a particular Name on the Arbiter attributes dictionary
            Return the current Value for the particular Name
     
     SENDS OSC Message Format
        /subscribe /AttributeName /ip /port
     */
    
    void subscribe(WeavingVoicesAttribute &attribute);
    
    /*
     SENDS OSC Message Format
     /subscribe /AttributeName /ip /port
     
     */
    
    void unsubscribe(WeavingVoicesAttribute &attribute);
    
    
    /*
     
     READS OSC Message Format
     /update /attribute /value /time /address
     
     receiving of the attributes should be implemented here
     */
    void update();
    
private:
    
    ofxOscReceiver receiver;
    ofxOscSender sender;
    
};
