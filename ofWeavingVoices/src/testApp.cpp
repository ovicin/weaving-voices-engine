#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    //ofBackground( 10, 10, 10);
    ofBackground(0);
    
    cam.setNearClip(1e-2);
    cam.setFarClip(1e4);
    cam.setDistance(80);
    cam.lookAt(ofVec3f(0, 20, 0));

    rip.allocate(800,600);
    bounce.allocate(800,600);
    
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<4;j++)
        {
            //ofCircle(200+(i*100), 60+(j*100), 0, 5);
            Points.push_back(new WeavingPoint(200+(i*100), 60+(j*100),'a'));
        }
    
    
    rules.setMaxDepth(300);
    rules.getMeshRef().setMode(OF_PRIMITIVE_LINES);
    
    {
        Rule::Ptr rule = rules.addRule("test", 50);
        
        LineAction::Ptr action = rule->addAction<LineAction>("test");
        action->translate(0, 0.1, 0);
        action->rotate(1, 0, 0);
        action->setNextRuleName("test");
    }
    
    {
        Rule::Ptr rule = rules.addRule("test", 50);
        
        LineAction::Ptr action = rule->addAction<LineAction>("test");
        action->translate(0, 0.1, 0);
        action->rotate(0, 20, 0);
        action->setNextRuleName("test");
    }
    
    {
        Rule::Ptr rule = rules.addRule("test", 100);
        
        LineAction::Ptr action = rule->addAction<LineAction>("test");
        action->translate(0, 0.4, 0);
        action->rotate(1, 0, -2);
        action->setNextRuleName("test");
    }
    
    {
        Rule::Ptr rule = rules.addRule("test", 6);
        
        TransformAction::Ptr left = rule->addAction<TransformAction>("test");
        left->rotate(0, 180, 0);
        left->setNextRuleName("test");
        
        TransformAction::Ptr right = rule->addAction<TransformAction>("test");
        right->rotate(15, 0, 0);
        right->setNextRuleName("test");
    }
    
    rules.setStartRule("test");
    rules.start();
    
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
    
    
    rules.step();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    rip.draw(150,30);
    bounce.draw(640,0);
    
    ofNoFill();
    ofRect(150,30,800,400);
    ofFill();
    
    cam.begin();
    rules.draw();
    cam.end();
   
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == OF_KEY_UP){
        rip.damping += 0.01;
    } else if ( key == OF_KEY_DOWN){
        rip.damping -= 0.01;
    } else if (key == 'S') {
        rules.clear();
        rules.start();
        
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
