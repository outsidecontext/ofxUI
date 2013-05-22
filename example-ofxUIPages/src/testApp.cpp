#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing();
    
	page1 = pageManager.createPage("Page 1");
    page1->addButton("Page 1 button", false);
    
	page2 = pageManager.createPage("Page 2");
    page2->addButton("Page 2 button", false);
    
    pageManager.addPage(page1);
    pageManager.addPage(page2);
    pageManager.setup();
	   
    ofAddListener(page1->newGUIEvent,this,&testApp::guiEvent);
}

//--------------------------------------------------------------
void testApp::update()
{
    pageManager.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
    pageManager.draw();
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
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
void testApp::exit()
{
    ofLogNotice() << "testApp::exit deleting pages";
    delete page1;
	delete page2;
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{ 
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
 
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
 

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}