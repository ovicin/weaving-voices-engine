//
//  WeavingVoicesService.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/08/14.
//
//

#pragma once

#include "Attribute.h"

#include "PlatformSpecific.h"



class Subscriber{
public:
    

    Subscriber();
    
    void init(string ServiceName, string LocalAddress, string BroadCastAddress);
    
    /*PUT: Updates an attribute locally and remotely.
    
     Properties:
    
        Name
        Value
     Actions:
    
     Update the Arbiter attributes dictionary
     Update the Local attributes dictionary
     
     SENDS OSC Message Format
     
        /update /AttributeName val
     
     
     */
    
    void put(Attribute &attribute);
    
    /*SUBSCRIBE: Subscribes to an attribute locally or remotely.
    
     Properties:
    
        Attribute Name
     Actions:
    
     Updates the Subscribers for a particular Name on the Arbiter attributes dictionary
            Return the current Value for the particular Name
     
     SENDS OSC Message Format
        /request /AttributeName /ip /port
     */
    
    void subscribe(Attribute &attribute);
    
    /*
     SENDS OSC Message Format
     /unsubscribe /AttributeName /ip /port
     
     */
    
    void unsubscribe(Attribute &attribute);
    
    
    /*
     
     READS OSC Message Format
     /update /attribute /value /time /address
     
     receiving of the attributes should be implemented here
     */
    void updateCallback();
    
private:
    

    
    string LocalAddress;
    string BroadCastAddress;
    string ServiceName;
    
};
