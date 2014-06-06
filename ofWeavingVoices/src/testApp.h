#pragma once

#include "ofMain.h"
#include "WeavingPoint.h"

#include "ofxBounce.h"
#include "ofxRipples.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector <WeavingPoint*> Points;
    vector <ofPoint*> upRow, downRow, leftColumn, rightColumn;
    
    
    ofxRipples  rip;
    ofxBounce   bounce;
		
};
