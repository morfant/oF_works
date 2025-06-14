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
            coordinate[i][j] = ofPoint(GRID_X * i, GRID_Y * j);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
  
    
    if (ofGetFrameNum() % 30 == 0 && ofGetFrameNum() != 0) {
        
        for (int i = lockIdx; i < NUM_X; ++i) {
            for (int j = 0; j < NUM_Y; ++j) {
                if (j == (count % NUM_Y)) {
                    coins[i][j] = ofRandom(1.0);
                }
            }
        }
        count++;
        lockIdx = count / NUM_Y;
        lockIdx %= NUM_X;
    
        if (count % NUM_Y == 0) {
            for (int i = lockIdx; i < NUM_X; ++i) {
                for (int j = 0; j < NUM_Y; ++j) {
                    coins[i][j] = 0;
                }
            }
        }
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    
    for (int i = 0; i < NUM_X; ++i) {
        for (int j = 0; j < NUM_Y; ++j) {
            ofPoint p = coordinate[i][j];
            
            float x1, y1, x2, y2, x3, y3;
            if (coins[i][j] > 0.5) {
                x1 = p.x; y1 = p.y;
                x2 = p.x; y2 = p.y + GRID_Y;
                x3 = p.x + GRID_X; y3 = p.y + GRID_Y;
            } else {
                x1 = p.x; y1 = p.y;
                x2 = p.x + GRID_X; y2 = p.y;
                x3 = p.x + GRID_X; y3 = p.y + GRID_Y;
            }
            
            ofFill();
            ofSetColor(0);
            ofDrawTriangle(x1, y1, x2, y2, x3, y3);
            
//            ofNoFill();
//            ofSetColor(0);
//            ofDrawRectangle(p.x, p.y, GRID_X, GRID_Y);
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
