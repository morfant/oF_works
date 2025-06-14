#include "ofApp.h"

float tileCount = 20;
float step;
int width, height;
int mX, mY;
int theSeed = 0;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    width = ofGetWidth();
    height = ofGetHeight();
    step = width / tileCount;
    
    dist_int = uniform_int_distribution<int>(0, 1);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    tileCount = ofMap(mY, 0, height, 50, 2);
    step = width / tileCount;

    ofBackground(255);
    ofSetColor(0);
    mt.seed(theSeed);
    
    for (int y = 0; y < tileCount; y++)
    {
        for (int x = 0; x < tileCount; x++)
        {
            float posX = x * step;
            float posY = y * step;
            
            if (dist_int(mt) == 0)
            {
                ofSetLineWidth(1 + mX / 15);
                ofDrawLine(posX, posY, posX + step, posY + step);
            }
            else
            {
                ofSetLineWidth(1 + mX / 15);
                ofDrawLine(posX + step, posY, posX, posY + step);
            }
        }
    }
        

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == '1')
    {
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mX = ofClamp(x, 0, width);
    mY = ofClamp(y, 0, height);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (button == 0)
    {
        theSeed = ofRandom(2000);
    }

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
