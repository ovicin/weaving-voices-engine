//
//  eventWeavingVoicesAttribute.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/08/14.
//
//

#pragma once

#include "ofMain.h"
#include "Attribute.h"

class eventWeavingVoicesAttribute : public ofEventArgs{
public:
    
    Attribute *pWeavingVoicesAttribute;
    
    static ofEvent <eventWeavingVoicesAttribute> onWeavingVoicesAttribute;
    
};
