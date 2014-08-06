#include "testApp.h"
#include "IPAddress.h"

#define _startX 250
#define _startY 30
#define _width 600
#define _height 400
#define _weavingPontsDist 100

//--------------------------------------------------------------
void testApp::setup(){
    
    
    InitAddresses();
    GetIPAddresses();
    cout <<"IP of the machine: " + ofToString( ip_names[1]) << endl;
    unsigned short a, b, c, d;
    sscanf(ip_names[1], "%hu.%hu.%hu.%hu", &a, &b, &c, &d);
    string broadcastAddr = "Broadcast: " + ofToString(a) + "." + ofToString(b) + "." + ofToString(c) + ".255";
    cout <<broadcastAddr<< endl;
    
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    //ofBackground( 10, 10, 10);
    ofBackground(0);
    
    cam.setNearClip(1e-2);
    cam.setFarClip(1e4);
    cam.setDistance(80);
    cam.lookAt(ofVec3f(0, 20, 0));

    RippleSetup();
    
    int i,j;
    for(i=0;i<(_width / _weavingPontsDist);i++)
        for(j=0;j<(_height / _weavingPontsDist);j++)
        {
            //ofCircle(200+(i*100), 60+(j*100), 0, 5);
            Points.push_back(new WeavingPoint((_startX+(_weavingPontsDist/2))+(i*_weavingPontsDist), (_startY*2)+(j*_weavingPontsDist),'a'));
        }
    
    RulesSetup();
    
    bRipple = false;
    bRules = false;
    
    setupGUI();
    selectedWeavingPoint = NULL;
    
    blur.allocate(_startX+800,600);
    
    ofAddListener(eventSelectedWeavingPoint::onSelectedWeavingPoint,this, &testApp::OnSelectedWeavingPoint);

    
}

void testApp::setupGUI(void){
    gui = new ofxUICanvas();
    gui->addLabel("EFFECTS");
    gui->addToggle("Ripples", false);
    gui->addToggle("Rules1", false);
    gui->addSpacer();
    gui->addLabel("CONTROLS");
    gui->addToggle("Border", true);
    gui->addToggle("WeavingPoints", true);
    gui->addLabel("WeavingChr",OFX_UI_FONT_SMALL);
    InputCharText = new ofxUITextInput("WeavingChar", SelectedWeavingChar,50);
    //gui->addTextInput("WeavingChar", SelectedWeavingChar);
    gui->addWidgetDown(InputCharText);
    gui->addSpacer();
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::OnSelectedWeavingPoint(eventSelectedWeavingPoint & args){
    selectedWeavingPoint = args.pWeavingPoint;
    SelectedWeavingChar = selectedWeavingPoint->trigerringChar;
    InputCharText->setTextString(SelectedWeavingChar);
    
    
} 
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	/*int kind = e.widget->getKind();
    
    if(kind == OFX_UI_WIDGET_BUTTON)
    {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        cout << name << "\t value: " << button->getValue() << endl;
    }
    else if(kind == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
    }
    else if(kind == OFX_UI_WIDGET_IMAGEBUTTON)
    {
        ofxUIImageButton *button = (ofxUIImageButton *) e.widget;
        cout << name << "\t value: " << button->getValue() << endl;
    }
    else if(kind == OFX_UI_WIDGET_IMAGETOGGLE)
    {
        ofxUIImageToggle *toggle = (ofxUIImageToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
    }
	else if(kind == OFX_UI_WIDGET_LABELBUTTON)
    {
        ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
        cout << name << "\t value: " << button->getValue() << endl;
    }
    else if(kind == OFX_UI_WIDGET_LABELTOGGLE)
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
    }
	else if(name == "B1")
	{
        ofxUIButton *button = (ofxUIButton *) e.widget;
        cout << "value: " << button->getValue() << endl;
	}
     */
    if(name == "Ripples")
	{
        ofxUIButton *button = (ofxUIButton *) e.widget;
        cout << "value: " << button->getValue() << endl;
        bRipple = button->getValue();
	}
    else if(name == "Rules1")
	{
        ofxUIButton *button = (ofxUIButton *) e.widget;
        cout << "value: " << button->getValue() << endl;
        bRules = button->getValue();
	}
    else if(name == "WeavingChar"){
        ofxUITextInput *text = (ofxUITextInput *) e.widget;
        cout << "value: " << text->getTextString() << endl;
        SelectedWeavingChar = text->getTextString();
        selectedWeavingPoint->trigerringChar = SelectedWeavingChar[0];
        text->setAutoClear(false);
        
    }

}

//--------------------------------------------------------------
void testApp::update(){
    
    gui->update();

    if (bRipple)
        RippleUpdate();
    if (bRules)
        rules.step();
    blur.setFade(sin( ofGetElapsedTimef() ));
    blur.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    blur.draw();
   
    if (bRipple)
        RippleDraw();
    
     blur.begin();
    ofNoFill();
    ofRect(_startX,_startY,_width,_height);
    ofFill();
    blur.end();
    
    
    if (bRules){
        cam.begin();
        rules.draw();
        cam.end();
    }
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

void testApp::RulesSetup(){
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


void testApp::RippleSetup(){
    rip.allocate(800,600);
    bounce.allocate(800,600);
    
}
void testApp::RippleUpdate(){
    rip.begin();
    ofFill();
    ofSetColor(ofNoise( ofGetFrameNum() ) * 255 * 5, 255);
    ofEllipse(mouseX,mouseY, 10,10);
    rip.end();
    rip.update();
    
    bounce << rip;
    
}
void testApp::RippleDraw(){
    rip.draw(150,30);
    bounce.draw(640,0);
    
}
