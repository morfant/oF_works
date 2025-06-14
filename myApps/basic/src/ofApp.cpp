#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    // 한 번만 실행되는 부분
    float value = 0.2;
    printf("hi %f\n", value);
    ofLogNotice() << "value: " << value;
    ofLogError() << "value: " << value;

}

//--------------------------------------------------------------
void ofApp::update(){
    // 반복 실행되는 부분

}

//--------------------------------------------------------------
void ofApp::draw(){
    // 반복 실행되는 부분

    float value = 0.225;
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255); // "value: 0.225"
    ofDrawBitmapString("value: " + ofToString(value), 100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
