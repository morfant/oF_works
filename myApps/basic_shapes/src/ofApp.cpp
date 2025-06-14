#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofSetCircleResolution(60);
    ofSetWindowTitle("Hello oF!");
    ofSetWindowPosition(0, 0);
    ofSetFrameRate(60);
    
    rx = ofGetWidth() / 2;
    ry =  ofGetHeight() / 2;
    
    rectX = 100;
    rectY = 100;
    
    isDragging = false;
    
    rCount = 0;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    count = count + 1; // count++;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 100);
     
    ofSetColor(0, 200, 0);
    for (int i = 0; i < 10; i++)
    {
        ofDrawLine(400, 100 + (i * 2), 700, 400 + (i * 2));
    }
    

    ofSetColor(255, 255, 255);
    ofFill();
    float centerX = (ofGetWidth() / 2) + sin(ofDegToRad(count%360)) * 200.f;
    float centerY = ofGetHeight() / 2;
    ofDrawCircle(centerX, centerY, 200);
    
    
    ofSetColor(200, 100, 20);
    ofNoFill();
    ofDrawRectangle(rectX, rectY, 200, 300);
    
    
    ofSetColor(255, 0, 0, 255);
    ofDrawBitmapString("Draw circle & rect", 150, 400);
    
    ofSetColor(100, 200, 80);
    
    d = ofDist(centerX, centerY, rx, ry);
    while (d > 100) {
        rx = ofRandom(0, ofGetWidth());
        ry = ofRandom(0, ofGetHeight());
        d = ofDist(centerX, centerY, rx, ry);
    }
                        
    ofDrawCircle(rx, ry, 100);
    
    
    ofFill();
    if (count % 50 == 0)
    {
        ofSetColor((int)ofRandom(255), (int)ofRandom(255), (int)ofRandom(255));
        int rx = ofRandom(10, 200);
        int ry = ofRandom(20, 300);
        ofDrawRectangle(rectX, rectY, rx, ry);
        ofDrawRectangle(rectX + 200 - rx, rectY + 300 - ry, rx, ry);
    }
    
    
    if (isDragging == true) {
        ofSetColor(0, 200, 100, 100);
        ofDrawEllipse(ofGetMouseX(), ofGetMouseY(), rCount, rCount);
    }
    
    
    
    ofSetColor(0, 0, 255);
    ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, 100, 100);
    
    ofSetColor(255, 0, 255);
    ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 50);  // 중심 좌표와 반지름

    
    
    
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

    isDragging = true;
    rCount++;
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    isDragging = true;
    rCount = 0;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    isDragging = false;
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
