#include "ofxUIPageManager.h"

ofxUIPageManager::ofxUIPageManager(){
    currentPageNum = 0;
    isVisible = false;
    pageList = NULL;
	ofAddListener(ofEvents().keyPressed, this, &ofxUIPageManager::_keyPressed);
	ofAddListener(ofEvents().exit, this, &ofxUIPageManager::_exit);
}

void ofxUIPageManager::setup() {
    name = "ofxUIPageManager";
    setupGUI();
    int n = pages.size();
    for (int i=0; i<n; i++) {
        ofxUILabel* title = (ofxUILabel*)pages[i]->getWidget("page");
        string label = ofToString(i+1) +  "/" + ofToString(n);
        title->setLabel(label);
    }
    //isCursorVisible = false;
    //ofHideCursor();
    hide();
}


ofxUICanvas* ofxUIPageManager::createPage(string title) {
    // setup gui page with common stuff
    gui = new ofxUIScrollableCanvas(111,0,UI_W,ofGetHeight()*2);
    gui->setWidgetSpacing(UI_WIDGET_SPACER);
    ((ofxUIScrollableCanvas*)gui)->setScrollAreaToScreenHeight();
    gui->setDrawBack(true);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui->addWidgetDown(new ofxUILabel("page", "99/99", OFX_UI_FONT_SMALL));
    gui->addWidgetRight(new ofxUILabel("title", ofToUpper(title), OFX_UI_FONT_LARGE));
    gui->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUIButton(UI_SAVE_LABEL, false, UI_BUTTON_H, UI_BUTTON_H));
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addSpacer(1, UI_BUTTON_H);
    gui->addButton("<", false);
    gui->addButton(">", false);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui->addSpacer(UI_SLIDER_W, 2);
    return gui;
}

void ofxUIPageManager::setupGUI() {
    
    // Add a nice list of pages to help toggle them!
    pageList = new ofxUIScrollableCanvas(0,0,110,ofGetHeight()*2);
    
    // add gui config page
    title = "GUI";
    path = "GUI/gui.xml";
    gui = createPage(title);
    gui->addWidgetDown(new ofxUILabel("background", OFX_UI_FONT_MEDIUM));
    gui->addSlider("bg r", 0, 255, 0., UI_SLIDER_SMALL_W, UI_SLIDER_H)->setIncrement(1);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addSlider("bg g", 0, 255, 0., UI_SLIDER_SMALL_W, UI_SLIDER_H)->setIncrement(1);
    gui->addSlider("bg b", 0, 255, 0., UI_SLIDER_SMALL_W, UI_SLIDER_H)->setIncrement(1);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui->addSlider("bg a", 0, 255, 0., UI_SLIDER_W, UI_SLIDER_H)->setIncrement(1);

    
    // add listener for gui events
    ofAddListener(gui->newGUIEvent, this, &ofxUIPageManager::guiEvent);
    // add gui page to gui manager
    addPage(gui);
    // load in our existing saved settings
    gui->loadSettings(path);
    
    // finish nice list of pages
    pageList->setWidgetSpacing(UI_WIDGET_SPACER);
    ((ofxUIScrollableCanvas*)pageList)->setScrollAreaToScreenHeight();
    pageList->setDrawBack(true);
    vector<string> names;
    for (int i=0; i<pages.size(); i++) {
        ofxUILabel* title = (ofxUILabel*)pages[i]->getWidget("title");
        string label = title->getLabel();
        if (label.size()>7) label = label.substr(0,7);
        names.push_back( ofToString(i) + ":" + label );
    }
    pageList->addRadio("Pages", names, OFX_UI_ORIENTATION_VERTICAL);
    pageList->addSpacer(0, 40);
    pageList->autoSizeToFitWidgets();
    ofAddListener(pageList->newGUIEvent, this, &ofxUIPageManager::guiPageListEvent);
    
}

void ofxUIPageManager::update() {}

void ofxUIPageManager::draw() {}

void ofxUIPageManager::exit() {
    ofLogNotice("deleting gui for GUI and Pagelist");
    delete gui;
    delete pageList;
}

void ofxUIPageManager::updateAllPages() {
    int n = pages.size();
    for (int i=0; i<n; i++) {
        pages[i]->setColorBack(bgColour);
        pages[i]->update();
    }
    if (pageList != NULL) {
        pageList->setColorBack(bgColour);
        pageList->update();
    }
}


void ofxUIPageManager::guiPageListEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    vector<string> tokens = ofSplitString(name, ":");
    if (tokens.size()>0) {
        int i = ofToInt(tokens[0]);
        currentPageNum = i;
        showPage(i);
    }
}

void ofxUIPageManager::guiEvent(ofxUIEventArgs &e){
    //ofLogNotice("GUIConfigurable guiEvent : " + e.widget->getName());
    
    if (e.widget->getKind() == OFX_UI_WIDGET_BUTTON) {
        ofxUIButton* w = (ofxUIButton*)e.widget;
        if (w->getValue()) {
            ofLog() << "button clicked: " << w->getName();
            if(e.widget->getName() == UI_SAVE_LABEL){
                gui->saveSettings(path);
            }
            else if(e.widget->getName() == "<" && w->getValue()){
                w->mouseReleased(0, 0, true);
                showPreviousPage();
            }
            else if(e.widget->getName() == ">" && w->getValue()){
                w->mouseReleased(0, 0, true);
                showNextPage();
            }
        }
    }
    
    else if(e.widget->getName() == "bg r"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bgColour.r = slider->getScaledValue();
        updateAllPages();
    } else if(e.widget->getName() == "bg g"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bgColour.g = slider->getScaledValue();
        updateAllPages();
    } else if(e.widget->getName() == "bg b"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bgColour.b = slider->getScaledValue();
        updateAllPages();
    } else if(e.widget->getName() == "bg a"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bgColour.a = slider->getScaledValue();
        updateAllPages();
    } else if(e.widget->getName() == "padding"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        padding = slider->getScaledValue();
        updateAllPages();
    }
    
}


ofxUICanvas* ofxUIPageManager::addPage(ofxUICanvas* ui){
    // TODO: add param for this?
    // autosize
    ui->addSpacer(0, 100);
    ui->autoSizeToFitWidgets();
    // add listener for gui events
    ofAddListener(ui->newGUIEvent, this, &ofxUIPageManager::guiEvent);
    // load
    //ui->loadSettings();
    
    // Always do this
    pages.push_back(ui);
	return ui;
}

void ofxUIPageManager::showNextPage(){
    if (!pages.size() > 0) return;
    if (++currentPageNum > pages.size()-1) currentPageNum = 0;
    showPage(currentPageNum);
}

void ofxUIPageManager::showPreviousPage(){
    if (!pages.size() > 0) return;
    if (--currentPageNum < 0) currentPageNum = pages.size()-1;
    showPage(currentPageNum);
}

void ofxUIPageManager::showPage(int num){
    if (!pages.size() > 0) return;
    if (!isVisible) return;
    //ofLogNotice("ofxUIPageManager::showPage " + ofToString(num));
    hideAllPages();
    pages[num]->setVisible(true);
}

void ofxUIPageManager::showAllPages(){
    for (int i=0; i<pages.size(); i++) {
        pages[i]->setVisible(true);
    }
}

void ofxUIPageManager::hideAllPages(){
    for (int i=0; i<pages.size(); i++) {
        pages[i]->setVisible(false);
    }
}

void ofxUIPageManager::show(){
    if (!pages.size() > 0) return;
    isVisible = true;
    pageList->setVisible(true);
    showPage(currentPageNum);
}

void ofxUIPageManager::hide(){
    if (!pages.size() > 0) return;
    isVisible = false;
    pageList->setVisible(false);
    hideAllPages();
}


void ofxUIPageManager::keyPressed (int key) {
    switch (key) {
        case '[':
        case '-':
            showPreviousPage();
            break;
        case ']':
        case '+':
            showNextPage();
            break;
        case ' ':
            if (isVisible) hide();
            else show();
            break;
        case 'c':
            if (isCursorVisible) ofHideCursor();
            else ofShowCursor();
            isCursorVisible = !isCursorVisible;
            break;
        default:
            break;
    }
}

void ofxUIPageManager::mouseDragged(int x, int y, int button){}

void ofxUIPageManager::mousePressed(int x, int y, int button){}

void ofxUIPageManager::mouseReleased(int x, int y, int button){}

void ofxUIPageManager::windowResized(int w, int h){}




void ofxUIPageManager::_keyPressed(ofKeyEventArgs &e) {
	int key = e.key;
	keyPressed(key);
}

void ofxUIPageManager::_exit(ofEventArgs &e) {
	exit();
}