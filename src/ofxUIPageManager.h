//
//  ofxUIPageManager.h
//  impression
//
//  Created by chris@allofus.com
//  Copyright (c) 2012 AllofUs. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "ofxUI.h"

#define UI_SAVE_LABEL "save"


class ofxUIPageManager {
public:
	
    ofxUIPageManager();
	void setup(string dir="GUI", float spacer=OFX_UI_GLOBAL_WIDGET_SPACING, float pageWidth=OFX_UI_GLOBAL_CANVAS_WIDTH);
    void setupPages();
	void exit();
    
    ofxUICanvas* createPage(string name);
    ofxUICanvas* addPage(ofxUICanvas* ui);
    
    void showNextPage();
    void showPreviousPage();
    void showPage(int num);
    void showAllPages();
    void hideAllPages();
    void updateAllPages();
    void show();
    void hide();
    
    
protected:
    
	void keyPressed(ofKeyEventArgs &e);
	void exit(ofEventArgs &e);
    void guiEvent(ofxUIEventArgs &e);
    void guiPageListEvent(ofxUIEventArgs &e);
    string getPath(string name);
    
    string name, dir;
    ofxUICanvas* gui;
    ofxUICanvas* pageList;
    vector<ofxUICanvas*> pages;
    int currentPageNum;
    bool isVisible, isPageListVisible;
    ofColor bgColour;
    float spacer;
    float listWidth;
    float pageWidth;
    
};
