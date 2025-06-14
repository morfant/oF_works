#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    // 한 번만 실행되는 부분
    tweakRange = 2.f;
    shapeName = "Lines";
    ofSetFrameRate(60);
    msg = to_string(n);
    
    w = ofGetWidth();
    h = ofGetHeight();
    depthAbs = 300.f;
    
    ofSetBackgroundAuto(false);
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    // 반복 실행되는 부분
}

//--------------------------------------------------------------
void ofApp::draw(){
    // 반복 실행되는 부분
    
    // add loading dot ......
    if (ofGetFrameNum() % 30 == 0) {
        loading = loading + ".";
    }
    
    if (ofGetFrameNum() % 300 == 0 || ofGetFrameNum() == 0) {
        loading = "";
        bx = ofRandom(w);
        by = ofRandom(h);
        bz = ofRandom(depthAbs);

        ex = ofRandom(w);
        ey = ofRandom(h);
        ez = -ofRandom(depthAbs);
        
        
        switch (n) {
            case 1:
                lineColor = ofColor(10, ofRandom(255), 140, 60 + ofRandom(90));
                // refresh msg background
                ofFill();
                ofSetColor(200, 100, 100);
                ofDrawRectangle(100, 110, 300, 20);
                break;
                
            case 2:
                lineColor = ofColor(255, 255, 255, ofRandom(20));
                // refresh msg background
                ofFill();
                ofSetColor(55, 100, 100);
                ofDrawRectangle(100, 110, 300, 20);
                break;
            default:
                break;
        }
        
        ofNoFill();
        ofSetColor(255);
        ofDrawBitmapString("color mode is " + msg, 100, 120); // msg
        
    }
    
    ofSetLineWidth(0.4f);
    auto r = ofRandom(-tweakRange, tweakRange);
    ofSetColor(lineColor);
    ofDrawLine(
               bx = bx + r,
               by = by + r,
               bz = bz + r,
               ex = ex + r,
               ey = ey + r,
               ez = ez + r
    );
    
    // Display Text
    ofSetColor(255);
    ofDrawBitmapString(shapeName, 100, 100); // title
    ofDrawBitmapString("wait " + loading, 250, 120); // loading
    
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    n = key - '0'; // get key as int : 1
    cout << to_string(n) << endl;
    msg = to_string(n);
    
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
