#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    glShadeModel(GL_FLAT);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    numSegment = 12;
    
    w = ofGetWidth();
    h = ofGetHeight();

}

//--------------------------------------------------------------
void ofApp::update(){
    int radius = w * 0.4;
    int angleStep = 360 / numSegment;
    
    mesh.clear();
    mesh.addVertex(ofVec3f(w * 0.5, h * 0.5, 0));
    mesh.addColor(ofColor(255));
    
    for (int ang = 0; ang <= 360; ang += angleStep)
    {
        float theta = ofDegToRad(ang);
        float x = radius * cos(TWO_PI - theta);
        float y = radius * sin(TWO_PI - theta);

        mesh.addVertex(ofVec3f(w * 0.5 + x, h * 0.5 + y, 0));
        ofColor c = ofColor::fromHsb(ofMap(ang, 360, 0, 0, 255), mx255, my255);
        mesh.addColor(c);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    mesh.draw();
    
    // display angle
//    int radius = w * 0.4;
//    int angleStep = 360 / numSegment;
//    for (int ang = 0; ang <= 360; ang += angleStep)
//    {
//        float theta = ofDegToRad(ang);
//        float x = radius * cos(theta);
//        float y = radius * sin(theta);
//        
//        ofSetColor(255, 0, 0);
//        ofDrawBitmapString(ang, w * 0.5 + x, h * 0.5 + y);
//    }
    
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case '1':
            numSegment = 360;
            break;
            
        case '2':
            numSegment = 45;
            break;
            
        case '3':
            numSegment = 24;
            break;
            
        case '4':
            numSegment = 12;
            break;
            
        case '5':
            numSegment = 6;
            break;

        default:
            numSegment = 12;
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mx = ofClamp(x, 0, w);
    my = ofClamp(y, 0, h);
    mx255 = ofMap(mx, 0, w, 0, 255);
    my255 = ofMap(my, 0, h, 0, 255);
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
