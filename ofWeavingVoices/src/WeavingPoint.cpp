//
//  WeavingPoint.cpp
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/06/14.
//
//

#include "WeavingPoint.h"

#define		IDLE_COLOR		0xFFFFFF
#define		OVER_COLOR		0x00FF00
#define		DOWN_COLOR		0xFF0000

WeavingPoint::WeavingPoint(unsigned int x, unsigned int y, char trigerringChar){
    this->trigerringChar = trigerringChar;
    set(x, y, WEAVING_POINT_WIDTH, WEAVING_POINT_HEIGHT);
    saveX = x;
    saveY = y;
    bVisible = true;
    setup();
}

void WeavingPoint::setup() {
    //printf("MyTestObject::setup() - hello!\n");
    enableMouseEvents();
    enableKeyEvents();
}


void WeavingPoint::exit() {
    //printf("MyTestObject::exit() - goodbye!\n");
}


void WeavingPoint::update() {
    //		x = ofGetWidth()/2 + cos(ofGetElapsedTimef() * 0.2) * ofGetWidth()/4;
    //		y = ofGetHeight()/2 + sin(ofGetElapsedTimef() * 0.2) * ofGetHeight()/4;
}

void WeavingPoint::SetVisible(bool flag){
    bVisible = flag;
}

void WeavingPoint::draw() {
    if(bVisible){
        if(isMousePressed()) ofSetHexColor(DOWN_COLOR);
        else if(isMouseOver()) ofSetHexColor(OVER_COLOR);
        else ofSetHexColor(IDLE_COLOR);
    
        ofRect(x, y, width, height);
    }
   /* if(isMousePressed()) {
        ofNoFill();
        ofSetColor(0xFF0000);
        ofRect(x, y, width, height);
    } else if(isMouseOver()){
        ofNoFill();
        ofSetColor(0x00FF00);
        ofRect(x, y, width, height);
    }*/
    
}

void WeavingPoint::onRollOver(int x, int y) {
    //printf("MyTestObject::onRollOver(x: %i, y: %i)\n", x, y);
}

void WeavingPoint::onRollOut() {
    //printf("MyTestObject::onRollOut()\n");

}

void WeavingPoint::onMouseMove(int x, int y){
    //printf("MyTestObject::onMouseMove(x: %i, y: %i)\n", x, y);
}

void WeavingPoint::onDragOver(int x, int y, int button) {
    //printf("MyTestObject::onDragOver(x: %i, y: %i, button: %i)\n", x, y, button);
    if(!onPressed) return;
    this->x = x - saveX;    // update x position
    this->y = y - saveY;    // update mouse y position
}

void WeavingPoint::onDragOutside(int x, int y, int button) {
    //printf("MyTestObject::onDragOutside(x: %i, y: %i, button: %i)\n", x, y, button);
    if(!onPressed) return;
    isDraggedOut = true;
    this->x = x - saveX;    // update x position
    this->y = y - saveY;    // update mouse y position
}

void WeavingPoint::onPress(int x, int y, int button) {
    //printf("MyTestObject::onPress(x: %i, y: %i, button: %i)\n", x, y, button);
    isDraggedOut = false;
    // save the offset of where the mouse was clicked...
    // ...relative to the position of the object
    saveX = x - this->x;
    saveY = y - this->y;
    onPressed = true;
}

void WeavingPoint::onRelease(int x, int y, int button) {
    //printf("MyTestObject::onRelease(x: %i, y: %i, button: %i)\n", x, y, button);
    onPressed = false;
    isDraggedOut = false;
}

void WeavingPoint::onReleaseOutside(int x, int y, int button) {
    //printf("MyTestObject::onReleaseOutside(x: %i, y: %i, button: %i)\n", x, y, button);
}

void WeavingPoint::keyPressed(int key) {
    //printf("MyTestObject::keyPressed(key: %i)\n", key);
    if (key == 'V'){
        bVisible = !bVisible;
    }
    else if (key == 'D'){
        verbose = !verbose;
    }
}

void WeavingPoint::keyReleased(int key) {
    //printf("MyTestObject::keyReleased(key: %i)\n", key);
}
