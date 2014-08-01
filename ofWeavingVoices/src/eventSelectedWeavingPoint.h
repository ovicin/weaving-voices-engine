//
//  eventSelectedWeavingPoint.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 27/07/14.
//
//
#pragma once

#include "ofMain.h"
#include "WeavingPoint.h"

class eventSelectedWeavingPoint : public ofEventArgs{
public:
    
    WeavingPoint *pWeavingPoint;
    
    static ofEvent <eventSelectedWeavingPoint> onSelectedWeavingPoint;
    
};
