//
//  eventWeavingVoicesAttribute.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/08/14.
//
//

#pragma once

#include "ofMain.h"
#include "WeavingVoicesAttribute.h"

class eventWeavingVoicesAttribute : public ofEventArgs{
public:
    
    WeavingVoicesAttribute *pWeavingVoicesAttribute;
    
    static ofEvent <eventWeavingVoicesAttribute> onWeavingVoicesAttribute;
    
};
