#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetLineWidth(10);
    ofSetFrameRate(5);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    int rbx, rby, rmx, rmy, rex, rey;
    rbx = ofRandom(ofGetWidth());
    rby = ofRandom(ofGetHeight());
                   
    rmx = ofRandom(ofGetWidth());
    rmy = ofRandom(ofGetHeight());
    
    rex = ofRandom(ofGetWidth());
    rey = ofRandom(ofGetHeight());

    
    ofSetColor(20, 100, 200);
//    ofDrawLine(rbx, rby, rex, rey);
    
    
    
    path.setFilled(true);
    ofColor c = ofColor(200, 100, 100, 90);
//    path.setFillColor(c);
    path.setStrokeColor(ofColor::blueSteel);
    path.setStrokeWidth(2);
    
//    path.clear();
//    path.moveTo(rbx, rby);
    path.curveTo(rmx, rmy);
    path.curveTo(rex, rey);
//    path.close();
    path.simplify();
    path.draw();
    
    
    

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
    
    path.clear();

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
