#include "ofxUIPageManager.h"

ofxUIPageManager::ofxUIPageManager(){
    gui = NULL;
    pageList = NULL;
    currentPageNum = 0;
    // defaults
    listWidth = 110;
    name = "GUI";
    isVisible = false;
    isPageListVisible = true;
    // listeners
	ofAddListener(ofEvents().keyPressed, this, &ofxUIPageManager::keyPressed);
	ofAddListener(ofEvents().exit, this, &ofxUIPageManager::exit);
}

void ofxUIPageManager::setup(string dir, float spacer, float pageWidth) {
    this->dir = dir;
    this->spacer = spacer;
    this->pageWidth = pageWidth;
}


void ofxUIPageManager::exit() {
    ofLogNotice("ofxUIPageManager::deleting gui for GUI and Pagelist");
    delete gui;
    delete pageList;
}


//////////////////////////////////////////////////////////////////////////////////
// public: page related
//////////////////////////////////////////////////////////////////////////////////


ofxUICanvas* ofxUIPageManager::createPage(string name) {
    // setup gui page with common stuff
    gui = new ofxUIScrollableCanvas(0, 0, pageWidth, ofGetHeight());
    gui->setName(name);
    gui->setWidgetSpacing(spacer);
    ((ofxUIScrollableCanvas*)gui)->setScrollAreaToScreenHeight();
    gui->setDrawBack(true);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui->addWidgetDown(new ofxUILabel("page", "--/--", OFX_UI_FONT_SMALL));
    gui->addWidgetRight(new ofxUILabel("title", ofToUpper(name), OFX_UI_FONT_LARGE));
    gui->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_SMALL));
    gui->addButton(UI_SAVE_LABEL, false);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addSpacer(0, spacer);
    gui->addButton("<", false);
    gui->addButton(">", false);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui->addSpacer(pageWidth, 2);
    gui->addSpacer(0, spacer);
    return gui;
}

ofxUICanvas* ofxUIPageManager::addPage(ofxUICanvas* ui){
    ui->addSpacer(0, 100);
    ui->autoSizeToFitWidgets();
    // add listener for common gui events like save and paging
    ofAddListener(ui->newGUIEvent, this, &ofxUIPageManager::guiEvent);
    ui->loadSettings(getPath(ui->getName()));
    // add to our pages
    pages.push_back(ui);
	return ui;
}

void ofxUIPageManager::updateAllPages() {
    int n = pages.size();
    int x = (isPageListVisible) ? pageList->getRect()->width+1 : 0;
    for (int i=0; i<n; i++) {
        pages[i]->setColorBack(bgColour);
        pages[i]->update();
        pages[i]->setPosition(x, 0);
    }
    if (pageList != NULL) {
        pageList->setColorBack(bgColour);
        pageList->update();
    }
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
    if (isPageListVisible) pageList->setVisible(true);
    showPage(currentPageNum);
}

void ofxUIPageManager::hide(){
    if (!pages.size() > 0) return;
    isVisible = false;
    pageList->setVisible(false);
    hideAllPages();
}


//////////////////////////////////////////////////////////////////////////////////
// protected
//////////////////////////////////////////////////////////////////////////////////

void ofxUIPageManager::setupPages() {
    
    if (pageList != NULL) {
        ofLogWarning() << "ofxUIPageManager pages are already setup!";
        return;
    }
    
    // Add a nice list of pages to help toggle them!
    pageList = new ofxUICanvas(0,0,listWidth,ofGetHeight());
    
    // add gui config page
    gui = createPage(name);
    gui->addToggle("show page list", &isPageListVisible);
    gui->addWidgetDown(new ofxUILabel("background", OFX_UI_FONT_MEDIUM));
    gui->addSlider("bg r", 0, 255, 0.)->setIncrement(1);
    gui->addSlider("bg g", 0, 255, 0.)->setIncrement(1);
    gui->addSlider("bg b", 0, 255, 0.)->setIncrement(1);
    gui->addSlider("bg a", 0, 255, 0.)->setIncrement(1);
    
    // add listener for gui events
    ofAddListener(gui->newGUIEvent, this, &ofxUIPageManager::guiEvent);
    // add gui page to gui manager
    addPage(gui);
    // load in our existing saved settings
    gui->loadSettings(getPath(name));
    
    
    // finish nice list of pages
    pageList->setWidgetSpacing(spacer);
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
    
    // update all pages with pages numbers
    int n = pages.size();
    for (int i=0; i<n; i++) {
        ofxUILabel* title = (ofxUILabel*)pages[i]->getWidget("page");
        string label = ofToString(i+1) +  "/" + ofToString(n);
        title->setLabel(label);
    }
    updateAllPages();
    
    // gui is hidden by default
    hide();
}

void ofxUIPageManager::keyPressed(ofKeyEventArgs &e) {
	int key = e.key;
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
        default:
            break;
    }
}

void ofxUIPageManager::exit(ofEventArgs &e) {
	exit();
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
    string name = e.widget->getName();
    // Event listener for all gui pages
    if (e.widget->getKind() == OFX_UI_WIDGET_BUTTON) {
        ofxUIButton* w = (ofxUIButton*)e.widget;
        if (w->getValue()) {
            if(name == UI_SAVE_LABEL){
                // get the widget parent which will be a page (ofxUICanvas)
                ofxUICanvas* page = (ofxUICanvas*)e.widget->getParent();
                string pageName = page->getName();
                string path = getPath(pageName);
                ofLogNotice() << "ofxUIPageManager::saving " << path;
                page->saveSettings(path);
            }
            else if(name == "<" && w->getValue()){
                w->mouseReleased(0, 0, true);
                showPreviousPage();
            }
            else if(name == ">" && w->getValue()){
                w->mouseReleased(0, 0, true);
                showNextPage();
            }
        }
    }
    // Page manager specific
    else if(name == "bg r"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bgColour.r = slider->getScaledValue();
        updateAllPages();
    } else if(name == "bg g"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bgColour.g = slider->getScaledValue();
        updateAllPages();
    } else if(name == "bg b"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bgColour.b = slider->getScaledValue();
        updateAllPages();
    } else if(name == "bg a"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        bgColour.a = slider->getScaledValue();
        updateAllPages();
    } else if (name == "show page list") {
        pageList->setVisible(isPageListVisible);
        updateAllPages();
    }
}

string ofxUIPageManager::getPath(string name){
    return dir + "/" + name + ".xml";
}


