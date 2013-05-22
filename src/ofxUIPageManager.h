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

#define UI_W 360
#define UI_WIDGET_SPACER 10
#define UI_SLIDER_H 16
#define UI_SLIDER_W 314
#define UI_SLIDER_SMALL_W 96
#define UI_SLIDER_MED_W 150
#define UI_BUTTON_H 16
#define UI_SAVE_LABEL "save"


class ofxUIPageManager {
public:
	
    ofxUIPageManager();
    
	void setup();
    void setupGUI();
	void update();
	void draw();
	void exit();
    
    ofxUICanvas* addPage(ofxUICanvas* ui);
    ofxUICanvas* createPage(string title);
    
    void showNextPage();
    void showPreviousPage();
    void showPage(int num);
    void showAllPages();
    void hideAllPages();
    void show();
    void hide();
    
    void updateAllPages();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    
	void _keyPressed(ofKeyEventArgs &e);
	void _exit(ofEventArgs &e);
    
    void guiEvent(ofxUIEventArgs &e);
    void guiPageListEvent(ofxUIEventArgs &e);
    
private:
    
    string title, path, name;
    ofxUICanvas* gui;
    ofxUICanvas* pageList;
    vector<ofxUICanvas*> pages;
    int currentPageNum;
    bool isVisible;
    
    ofColor bgColour;
    float padding;
    
    bool isCursorVisible;
    
};
