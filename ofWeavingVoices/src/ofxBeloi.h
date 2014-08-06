//
//  ofxBeloi.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 06/08/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"


#define SERVER_IP "localhost"
#define SERVER_PORT 57130

class ofxBeloi{

private:
ofxOscReceiver receiver;
ofxOscSender sender;
}