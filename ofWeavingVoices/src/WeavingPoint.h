//
//  WeavingPoint.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/06/14.
//
//

#ifndef __ofWeavingVoices__WeavingPoint__
#define __ofWeavingVoices__WeavingPoint__

#include "ofMain.h"

class WeavingPoint{
public:
    WeavingPoint(unsigned int x, unsigned int y, char trigerringChar);
    void draw();
    unsigned int x,y;
    float diameter;
    char trigerringChar;
private:
    bool bVisible;
    
};

#endif /* defined(__ofWeavingVoices__WeavingPoint__) */
