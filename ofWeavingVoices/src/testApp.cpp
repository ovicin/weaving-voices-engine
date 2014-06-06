#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground( 10, 10, 10);

    rip.allocate(800,600);
    bounce.allocate(800,600);
    
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<4;j++)
        {
            //ofCircle(200+(i*100), 60+(j*100), 0, 5);
            Points.push_back(new WeavingPoint(200+(i*100), 60+(j*100),'a'));
        }
}

//--------------------------------------------------------------
void testApp::update(){
    rip.begin();
    ofFill();
    ofSetColor(ofNoise( ofGetFrameNum() ) * 255 * 5, 255);
    ofEllipse(mouseX,mouseY, 10,10);
    rip.end();
    rip.update();
    
    bounce << rip;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    rip.draw(150,30);
    bounce.draw(640,0);
    
    ofNoFill();
    ofRect(150,30,800,400);
    ofFill();
   
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == OF_KEY_UP){
        rip.damping += 0.01;
    } else if ( key == OF_KEY_DOWN){
        rip.damping -= 0.01;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
