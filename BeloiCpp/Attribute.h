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
    
public:
    Attribute(string name);
    void setData(string PublisherNetAddress,
                 float &data,
                 float TimeStamp);
    void setData(string &data);
    void* getData();

private:
    /*
     Name
    Unique identifier of an attribute offered by a service.
    */
    string name;
    
    /*
     Value
    Current value of the attribute.
    */
    void *data;
    
    /*
     Net Adress
    Current network location for the service (IP Address and Port)
        Subscribers
        Collection of NetAdresses of the services registered to the attribute.
    */
    
    string PublisherNetAddress;
    
    
    /*
     Collection of NetAddresses of the applications
     
     */
    vector <string> Subscribers;
    
    /*
     time in seconds when the last update was issued (The timestamp of the OSC message that was update)
     */
     float TimeStamp;
    
    
    void addSubscriber(string subscriber);
    void removeSubscriber(string subscriber);
};
