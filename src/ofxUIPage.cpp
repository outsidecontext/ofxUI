//
//  ofxUIPage.cpp
//  ofxUIButtons
//
//  Created by Chris Mullany on 22/05/2013.
//  Made for AllofUs
//

#include "ofxUIPage.h"

void ofxUIPage::setup(string title, string path){
    //this->guiManager = guiManager;
    this->title = title;
    this->path = path;
    // setup common gui stuff
    setupGUI();
    // listen for app close so we can delete gui pointer
    ofAddListener(ofEvents().exit, this, &ofxUIPage::_exit);
}

//////////////////////////////////////////////////////////////////////////////////
// oF event handlers
//////////////////////////////////////////////////////////////////////////////////

void ofxUIPage::_exit(ofEventArgs &e) {
    ofLogNotice("deleting gui for " + title);
    delete gui;
    exit();
}

//////////////////////////////////////////////////////////////////////////////////
// private
//////////////////////////////////////////////////////////////////////////////////

