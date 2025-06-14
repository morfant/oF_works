#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(false);
    ofSetFrameRate(30);
    ofBackground(255);

    w = ofGetWidth();
    h = ofGetHeight();
    
    pos = ofVec2f(w * 0.5, h * 0.5);
    
    stepSize = 1;
    radius = 1;
    
    fbo.allocate(w, h, GL_RGBA);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < mx + 1; i++)
    {
        int r = ofRandom(8);
        
        switch (r) {
            case NORTH:
                pos.y -= stepSize;
                break;
                
            case NORTHEAST:
                pos.x += stepSize;
                pos.y -= stepSize;
                break;
                
            case EAST:
                pos.x += stepSize;
                break;
                
            case SOUTHEAST:
                pos.x += stepSize;
                pos.y += stepSize;
                break;
                
            case SOUTH:
                pos.y += stepSize;
                break;
                
            case SOUTHWEST:
                pos.x -= stepSize;
                pos.y += stepSize;
                break;
                
            case WEST:
                pos.x -= stepSize;
                break;
                
            case NORTHWEST:
                pos.x -= stepSize;
                pos.y -= stepSize;
                break;
                
            default:
                break;
        }
        
        
        if (pos.x > w) pos.x = 0;
        else if (pos.x < 0) pos.x = w;
        
        if (pos.y > h) pos.y = 0;
        else if (pos.y < 0) pos.y = h;
        
        fbo.begin();
//        ofSetColor(0, 0, 0, 30);
        ofSetColor(72, 153, 129, 20);
        ofDrawCircle(pos, radius);
        fbo.end();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.draw(0, 0);

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
    mx = ofClamp(x, 0, w);

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
