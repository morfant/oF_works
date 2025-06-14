#include "ofApp.h"

int width, height;
int numX, numY;
int stepX, stepY;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetCircleResolution(48);
//    ofEnableSmoothing();

    
    width = ofGetWidth();
    height = ofGetHeight();
    
    numX = 20;
    numY = 20;
    
    stepX = width / numX;
    stepY = height / numY;
    
    for (int y = 0; y < numY; y++)
    {
        for (int x = 0; x < numX; x++)
        {
            circles.emplace_back(new Circle(x * stepX, y * stepY, 10));
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    srand(2000);
    float mx = ofGetMouseX();
    
    float r = ofMap(ofGetMouseY(), 0, height, 2, stepX / 2);
    for (int i = 0; i < circles.size(); i++)
    {
        
        float shiftX = ofRandom(-mx, mx) / 20;
        float shiftY = ofRandom(-mx, mx) / 20;
        
        circles.at(i)->setShift(shiftX, shiftY);
        circles.at(i)->setRadius(r);
        circles.at(i)->setLineWidth(r/2);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255, 255, 255);
    
    ofTranslate(stepX / 2, stepY / 2);
    
    for (int i = 0; i < circles.size(); i++)
    {
        circles.at(i)->draw();
    }

}

//--------------------------------------------------------------
void ofApp::exit(){
    
    for (int i = 0; i < circles.size(); i++)
    {
        delete circles.at(i);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
