//
//  WeavingVoicesAttribute.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/08/14.
//
//

#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

class Attribute{
    /*
     Name
    Unique identifier of an attribute offered by a service.
    */
    string Name;
    
    /*
     Value
    Current value of the attribute.
    */
    int value;
    
    /*
     Net Adress
    Current network location for the service (IP Address and Port)
        Subscribers
        Collection of NetAdresses of the services registered to the attribute.
    */
    
    string NetAddress;
    
    
    /*
     Collection of NetAddresses of the applications
     
     */
    vector <string> Subscribers;
    
    /*
     time in seconds when the last update was issued (The timestamp of the OSC message that was update)
     */
    string Time;
    
    
    void addSubscriber();
    void removeSubscriber();
};
