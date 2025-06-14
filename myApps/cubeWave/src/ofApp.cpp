#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    w = ofGetWidth();
    h = ofGetHeight();
    gridX = w / NUM_X;
    gridY = h / NUM_Y;
    gridZ = gridX;
    
    side = gridX;
    
    for (int i = 0; i < coordinate.size(); ++i) {
        for (int j = 0; j < coordinate[i].size(); ++j) {
            for (int k = 0; k < coordinate[i][j].size(); ++k) {
                    
                cout << coordinate[i][j][k] << endl;
            }
        }
    }
    
    for (int i = 0; i < coordinate.size(); ++i) {
        for (int j = 0; j < coordinate[i].size(); ++j) {
            for (int k = 0; k < coordinate[i][j].size(); ++k) {
                    
                coordinate[i][j][k] = ofPoint(gridX * i, gridY * j, gridZ * k);
                
            }
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
    ofBackground(0, 0, 0);
    
    
    for (int i = 0; i < coordinate.size(); ++i) {
        for (int j = 0; j < coordinate[i].size(); ++j) {
            for (int k = 0; k < coordinate[i][j].size(); ++k) {
                
                float d = 20.f;
                
//                float n = ofNoise(ofGetFrameNum()/120.f, ofGetFrameNum()/50.f, ofGetFrameNum()/340.f);
//                float n = ofNoise((i + ofGetFrameNum())/d, (j + ofGetFrameNum())/d, (k + ofGetFrameNum())/d);
                float n = ofNoise((i + count)/d, (j + cos(count))/d, (k + count)/d);
    
                ofFill();
//                ofSetColor(50, 150, 150);
//                ofSetColor(60 + (n * 55), 60 + (n * 155), 60 + (n * 200));
                ofSetColor(
                           ofMap(sin(n + (i*5 + ofGetFrameNum())/60.f), -1, 1, 30, 155),
                           ofMap(cos(n + (j*3 + ofGetFrameNum())/30.f), -1, 1, 50, 80),
                           ofMap(sin(n + (-k*4 + ofGetFrameNum())/45.f), -1, 1, 106, 175),
                           100);

                ofDrawBox(coordinate[i][j][k], n * gridX);
                
            }
        }
    }
    count +=ofMap(ofGetMouseX(), 0, w, 0.001, 0.9);
    
    cam.end();

    
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
