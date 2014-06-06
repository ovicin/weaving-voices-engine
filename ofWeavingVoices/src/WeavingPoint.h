//
//  WeavingPoint.h
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/06/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxMSAInteractiveObject.h"

class WeavingPoint  : public ofxMSAInteractiveObject{
public:
    WeavingPoint(unsigned int x, unsigned int y, char trigerringChar);
    void setup();
    void exit();
    void update();
    void draw();
    void onRollOver(int x, int y);
	void onRollOut();
	void onMouseMove(int x, int y);
	void onDragOver(int x, int y, int button);
	void onDragOutside(int x, int y, int button);
	void onPress(int x, int y, int button);
	void onRelease(int x, int y, int button);
	void onReleaseOutside(int x, int y, int button);
	void keyPressed(int key);
	void keyReleased(int key);

    void SetVisible(bool flag);
    
    char trigerringChar;
private:
    
    enum {
        WEAVING_POINT_WIDTH = 15,
        WEAVING_POINT_HEIGHT = 15
    };
    
    unsigned int saveX, saveY;
    bool bVisible;
    bool isDraggedOut;
	bool onPressed;
    
};


