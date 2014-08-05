//
//  WeavingVoicesAttribute.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/08/14.
//
//

#pragma once

class WeavingVoicesAttribute{
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
};
