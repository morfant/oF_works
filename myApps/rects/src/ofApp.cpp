#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    // 한 번만 실행되는 부분
    
    tweakRange = 30.f;
    shapeName = "Rects";
    ofSetFrameRate(60);
    
    ofSetBackgroundAuto(false);
    ofBackground(0);

    bx = ofGetWidth()/2;
    by = ofGetHeight()/2;

}

//--------------------------------------------------------------
void ofApp::update(){
    // 반복 실행되는 부분
}

void ofApp::RectsValue(float bx, float by) {
    lineColor = ofColor(10, ofRandom(255), 140, 60 + ofRandom(90));
    auto rx = ofRandom(-tweakRange, tweakRange);
    auto ry = ofRandom(-tweakRange, tweakRange);
    ofSetColor(lineColor);
    ofFill();
    ofDrawRectangle(bx = bx + rx, by = by + ry, 100, 100);
}

void ofApp::RectsRef(float& bx, float& by) {
    lineColor = ofColor(10, ofRandom(255), 140, 60 + ofRandom(90));
    auto rx = ofRandom(-tweakRange, tweakRange);
    auto ry = ofRandom(-tweakRange, tweakRange);
    ofSetColor(lineColor);
    ofFill();
    ofDrawRectangle(bx = bx + rx, by = by + ry, 100, 100);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // 반복 실행되는 부분
    
//    RectsValue(200.f, 300.f); // pass by value
    RectsRef(bx, by); // pass by ref
    
    // Display Text
    ofSetColor(255);
    ofDrawBitmapString(shapeName, 100, 100);
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    cout << key << " is pressed" << endl;
    
//    n = (char)key; // get key as char : '1'
    n = key - '0'; // get key as int : 1
    
//    if (key == '1') {
//        n = 1;
//    } else if (key == '2') {
//        n = 2;
//    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
