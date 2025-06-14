#include "ofApp.h"


int bgColor = 255;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetCircleResolution(32);
    
    radius = 120;
    circleX = ofGetWidth() * 0.5;
    circleY = ofGetHeight() * 0.5;
    speedX = 2.0;
    speedY = 2.0;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    circleX += speedX;
    circleY += speedY;
    
    if (circleX + radius >= ofGetWidth() || circleX - radius <= 0)
    {
        speedX = speedX * -1;
    }
    
    if (circleY + radius >= ofGetHeight() || circleY - radius <= 0)
    {
        speedY = speedY * -1;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(bgColor);
    
    float diffX = ofGetMouseX() - circleX;
    float diffY = ofGetMouseY() - circleY;
    
    float dist = sqrt(diffX * diffX + diffY * diffY);
    
    if (dist <= radius)
    {
        ofSetColor(100, 200, 0);
    }
    else
    {
        ofSetColor(0, 100, 200);
    }
    
    ofDrawCircle(circleX, circleY, radius);


    
    
//    ofNoFill();
//    
//    ofSetColor(0);
//    
//    ofSetColor(255, 0, 0);
//    ofFill();
//    ofDrawCircle(100, 100, 100);
//    
//    
//    ofSetColor(0, 0, 255);
//    ofFill();
//    ofDrawRectangle(300, 300, 100, 100);
//    
//    ofSetColor(0, 255, 0);
//    ofDrawLine(0, 0, ofGetWidth(), ofGetHeight());
//    
//    ofSetColor(0, 255, 255);
//    ofDrawLine(0, ofGetHeight(), ofGetWidth(), 0);
//    
//    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 100);
    
//    cout << ofGetMousePressed() << endl;

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
