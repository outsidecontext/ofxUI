//
//  ofxUIPage.h
//  impression
//
//  Created by chris@allofus.com
//  Copyright (c) 2012 AllofUs. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxUIPageManager.h"
#include "ofxUI.h"

//
// Base class that encapsulates common code for creating a new gui page
// and gluing paramaters to gui widgets
//
class ofxUIPage {
public:
    
    ofxUIPageManager* guiManager;
    ofxUICanvas *gui;
	string title, path;
    
    
	virtual void setup(){}
    
    void setup(string title, string path);
    
    // override this to create a bespoke gui
    virtual void setupGUI(){
        // setup gui page with common stuff
        //gui = guiManager->createPage(title);
    }
    
    // actions to be carried out once the gui is setup
    virtual void postSetupGUI(){
        // autosize
        gui->addSpacer(0, 100);
        gui->autoSizeToFitWidgets();
        // add listener for gui events
        ofAddListener(gui->newGUIEvent, this, &ofxUIPage::guiEvent);
        // load
        loadSettings();
        // add gui page to gui manager
        //guiManager->addPage(gui);
    }
    
    virtual void loadSettings() {
        // load in our existing saved settings
        gui->loadSettings(path);
    }
    
	virtual void update(){}
    
	virtual void draw(){}
    
    virtual void exit(){}
    
    // gui event listener
    // override this method to implement additional actions for ui widgets
    // but make sure you still call this method too: ofxUIPage::guiEvent(e);
    virtual void guiEvent(ofxUIEventArgs &e){
        if (e.widget->getKind() == OFX_UI_WIDGET_BUTTON) {
            ofxUIButton* w = (ofxUIButton*)e.widget;
            if(e.widget->getName() == UI_SAVE_LABEL){
                gui->saveSettings(path);
            }
            else if(e.widget->getName() == "<" && w->getValue()){
                w->mouseReleased(0, 0, true);
                guiManager->showPreviousPage();
            }
            else if(e.widget->getName() == ">" && w->getValue()){
                w->mouseReleased(0, 0, true);
                guiManager->showNextPage();
            }
        }
    }
    
    void _exit(ofEventArgs &e);
    
};