#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true); 
	ofEnableSmoothing();
    
    //
    //
    // 1. call setup first to specifiy directory for gui xml, spacing and page width
    pageManager.setup("GUI", 10, 300);
    // pageManager.setup("GUI", 10); // <- or this
    // pageManager.setup("GUI");     // <- or this
    // pageManager.setup();          // <- or even this
    
    
    //
    //
    // 2. create some pages
    float dim = 16;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 255-xInit;
    vector<string> names;
	names.push_back("RAD1");
	names.push_back("RAD2");
	names.push_back("RAD3");
    
    // page 1
	page1 = pageManager.createPage("Page 1");
	page1->addWidgetDown(new ofxUILabel("H SLIDERS", OFX_UI_FONT_MEDIUM));
	page1->addSlider("RED", 0.0, 255.0, 0.);
	page1->addSlider("GREEN", 0.0, 255.0, 0.);
	page1->addSlider("BLUE", 0.0, 255.0, 0.);
    page1->addSpacer(0, 5);
    page1->addWidgetDown(new ofxUILabel("V SLIDERS", OFX_UI_FONT_MEDIUM));
	page1->addSlider("0", 0.0, 255.0, 150, dim, 160);
	page1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	page1->addSlider("1", 0.0, 255.0, 150, dim, 160);
	page1->addSlider("2", 0.0, 255.0, 150, dim, 160);
	page1->addSlider("3", 0.0, 255.0, 150, dim, 160);
	page1->addSlider("4", 0.0, 255.0, 150, dim, 160);
	page1->addSlider("5", 0.0, 255.0, 150, dim, 160);
	page1->addSlider("6", 0.0, 255.0, 150, dim, 160);
	page1->addSlider("7", 0.0, 255.0, 150, dim, 160);
	page1->addSlider("8", 0.0, 255.0, 150, dim, 160);
	page1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    // page 2
	page2 = pageManager.createPage("Page 2");
    page2->addWidgetDown(new ofxUILabel("RADIO BUTTONS", OFX_UI_FONT_MEDIUM));
	page2->addRadio("RADIO HORIZONTAL", names, OFX_UI_ORIENTATION_HORIZONTAL, dim, dim);
	page2->addRadio("RADIO VERTICAL", names, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    page2->addSpacer(0, 5);
	page2->addWidgetDown(new ofxUILabel("BUTTONS", OFX_UI_FONT_MEDIUM));
	page2->addButton("DRAW GRID", false, dim, dim);
	page2->addWidgetDown(new ofxUILabel("TOGGLES", OFX_UI_FONT_MEDIUM));
	page2->addToggle( "D_GRID", false, dim, dim);
    page2->addSpacer(0, 5);
    page2->addWidgetDown(new ofxUILabel("RANGE SLIDER", OFX_UI_FONT_MEDIUM));
	page2->addRangeSlider("RSLIDER", 0.0, 255.0, 50.0, 100.0, length-xInit,dim);
    page2->addSpacer(0, 5);
	page2->addWidgetDown(new ofxUILabel("2D PAD", OFX_UI_FONT_MEDIUM));
	page2->add2DPad("PAD", ofPoint(0,length-xInit), ofPoint(0,120), ofPoint((length-xInit)*.5,120*.5), length-xInit,120);
    
    
    //
    //
    // 3. add pages to page manager
    pageManager.addPage(page1);
    pageManager.addPage(page2);
    
    
    //
    //
    // 4. finally, tell page manage to setup the pages
    pageManager.setupPages();
    
    
    // listen to your page gui events as normal
    ofAddListener(page1->newGUIEvent,this,&testApp::guiEvent);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    string s = "\nGUI Pages Example";
    s += "\nHit space to toggle the GUI";
    s += "\nHit '<' to page left";
    s += "\nHit '>' to page right";
    ofDrawBitmapStringHighlight(s, ofGetWidth()-250, 10);
    ofDrawBitmapString(s, ofGetWidth()-250, 10);
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e){
	string name = e.widget->getName(); 
	int kind = e.widget->getKind();
    if(kind == OFX_UI_WIDGET_BUTTON){
        ofxUIButton* w = (ofxUIButton*)e.widget;
        if (w->getValue()) {
            ofLogNotice() << "testApp button clicked: " << name;
        }
    }
}
//--------------------------------------------------------------
void testApp::exit(){
    ofLogNotice() << "testApp::exit deleting pages";
    delete page1;
	delete page2;
	delete page3;
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
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