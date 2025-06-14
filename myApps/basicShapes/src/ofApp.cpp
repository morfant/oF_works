#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    // 한 번만 실행되는 부분

}

//--------------------------------------------------------------
void ofApp::update(){
    // 반복 실행되는 부분

}

//--------------------------------------------------------------
void ofApp::draw(){
    // 반복 실행되는 부분
    
    ofBackground(255, 255, 255);
    ofFill();
    
    int c = 0;
    switch (n) {
        case 1:
            ofSetColor(0);
            while (c < 10) {
                float f = ofRandom(10.f);
                ofDrawEllipse(
                              ofRandom(ofGetWidth()/2 - 100, ofGetWidth()/2 + 100),
                              ofRandom(ofGetHeight()/2 - 100, ofGetHeight()/2 + 100),
                              f, f);
                c++;
            };
            shapeName = "point";
            break;
            
        case 2:
            ofSetColor(0);
            do {
                float bx = ofRandom(200.f, 600.f);
                float by = ofRandom(200.f, 600.f);
                float ex = ofRandom(300.f, 600.f);
                float ey = ofRandom(300.f, 600.f);
                ofDrawLine(bx, by, ex, ey);
                c++;
            } while (c < 10);
            
            shapeName = "line";
            break;
        case 3:
            ofSetColor(0);
            ofDrawTriangle(100, 100, 200, 200, 300, 100);
            shapeName = "triangle";
            break;
        case 4:
            ofSetColor(0);
            ofDrawRectangle(100, 100, 200, 300);
            shapeName = "rectangle";
            break;
        case 5:
            ofSetColor(0);
            ofNoFill();
            ofSetCircleResolution(100);
            ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2, 100, 100);
            shapeName = "circle";
            break;

        default:
            shapeName = "Unknown. Key input must be 1 ~ 5.";
            break;
    }
    
    
    ofDrawBitmapString(shapeName, 100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
