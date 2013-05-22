//
//  MyPage.h
//  ofxUIButtons
//
//  Created by Chris Mullany on 22/05/2013.
//  Made for AllofUs
//

#pragma once
#include "ofxUIPageManager.h"
#include "ofxUIPage.h"
class MyPage : public ofxUIPage {
public:
	void setup(){
        
    }
    void guiEvent(ofxUIEventArgs &e){
        GUIConfigurable::guiEvent(e);
        
    }
protected:
private:
};