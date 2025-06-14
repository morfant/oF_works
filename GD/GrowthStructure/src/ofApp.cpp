#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    ofSetFrameRate(60);
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    currentCount = 1;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (loopEnabled == false) return;
    
    int newR = ofRandom(1, 3);
    int newX = ofRandom(newR, w - newR);
    int newY = ofRandom(newR, h - newR);
    
    int closestDist = INT_MAX;
    int closestIdx = 0;
    
    for (int i = 0; i < currentCount; i++)
    {
        float d = ofDistSquared(newX, newY, pos.at(i).x, pos.at(i).y);
        if (d < closestDist)
        {
            closestDist = d;
            closestIdx = i;
        }
    }
    
    float theta = atan2(newY - pos.at(closestIdx).y, newX - pos.at(closestIdx).x);
    float x = pos.at(closestIdx).x + (newR + vecR.at(closestIdx)) * cos(theta);
    float y = pos.at(closestIdx).y + (newR + vecR.at(closestIdx)) * sin(theta);
    pos.push_back(glm::vec2(x, y));
    vecR.push_back(newR);
    
    currentCount++;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    ofNoFill();
    ofFill();
    ofSetColor(0, 0, 0);
    for (int i = 0; i < pos.size(); i++)
    {
        ofDrawCircle(pos.at(i), vecR.at(i));
    }
    
    if (currentCount >= maxCount) loopEnabled = false;
    
    ofSetColor(155, 0, 100);
    ofDrawBitmapString("Number of circles: " + ofToString(currentCount), w * 0.8, h * 0.1);

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

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (button == 0 && loopEnabled == false)
    {
        loopEnabled = true;
        pos.push_back(glm::vec2(x, y));
        vecR.push_back(10);

    }
    

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
