#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    
    w = ofGetWidth();
    h = ofGetHeight();
    GRID_X = w / NUM_X;
    GRID_Y = h / NUM_Y;
    
    for (int i = 0; i < NUM_X; ++i) {
        for (int j = 0; j < NUM_Y; ++j) {
            coordinate[i][j] = ofPoint(i * GRID_X, j * GRID_Y);
        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    for (int i = 0; i < NUM_X; ++i) {
        for (int j = 0; j < NUM_Y; ++j) {
            ofPoint p = coordinate[i][j];

            float f = ofMap(sin(ofGetFrameNum()/30.0), -1, 1, 50, 120);
            ofFill();
            ofSetColor(
                       255 - (i * 10),
                       255 - (j * 10),
                       255 - f
                       );
            
//            ofFill();
//            ofSetColor(
//                       ofMap(sin((i*5 + ofGetFrameNum())/60.f), -1, 1, 30, 155),
//                       ofMap(cos((j*3 + ofGetFrameNum())/30.f), -1, 1, 50, 80),
//                       ofMap(sin((-j*4 + ofGetFrameNum())/45.f), -1, 1, 106, 175)
//                       );
            
            ofDrawRectangle(p, GRID_X, GRID_Y);
        }
    }
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
