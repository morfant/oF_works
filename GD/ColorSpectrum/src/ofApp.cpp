#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    stepX = 20;
    stepY = 20;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
//    stepX = mx + 2;
//    stepY = my + 2;
    
    uint64_t t = ofGetElapsedTimeMillis() * 0.1;
    stepX = w * (1 + sin(ofDegToRad(t % 360))) * 0.5;
    stepY = h * (1 + cos(ofDegToRad(t % 360))) * 0.5;
    stepX += 2;
    stepY += 2;


    for (int gridY = 0; gridY < h; gridY += stepY)
    {
        for (int gridX = 0; gridX < w; gridX += stepX)
        {
            float hue = ofMap(gridX, 0, w, 0, 255, true);
            float sat = ofMap(gridY, 0, h, 255, 0, true);
            ofColor c = ofColor::fromHsb(hue, sat, 220);
            ofSetColor(c);
            ofDrawRectangle(gridX, gridY, stepX, stepY);
        }
    }

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mx = ofClamp(x, 0, w);
    my = ofClamp(y, 0, h);
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
