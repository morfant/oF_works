#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetCircleResolution(40);
    ofSetFrameRate(30);
    ofBackground(255);

    w = ofGetWidth();
    h = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    rbx = ofRandom(w);
    rby = ofRandom(h);
    for (int i = 0; i < 800; i++)
    {
        rex = ofRandom(w);
        rey = ofRandom(h);

//        ofSetLineWidth(1);
//        ofSetColor(0, 0, 0, 50);
//        ofDrawLine(rbx, rby, rex, rey);
        
        ofFill();
        ofSetColor(100, 50, 200, ofMap(i, 0, 299, 80, 255));
        ofDrawCircle(rbx, rby, rby / 10);
        
        ofNoFill();
        ofSetColor(0, 0, 0, ofMap(i, 0, 299, 80, 255));
        ofDrawCircle(rbx, rby, rby / 10);

        
        rbx = rex;
        rby = rey;
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
