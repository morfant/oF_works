#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    w = ofGetWidth();
    h = ofGetHeight();
    
//    ofSetBackgroundAuto(false);
    ofBackground(0, 0, 0);
    
    fbo.allocate(300, 300, GL_RGBA);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    ofBackground(0);
    ofSetColor(255, 255, 255);
    ofNoFill();
    ofDrawAxis(w/2);

//    step = 0.01;
//    step = (3 + (ofGetFrameNum() % 10))/10;
//    step = ofRandom(0.5, 0.05);
    step = 0.01 + ofNoise(ofGetFrameNum()/10.f) * 0.01;
//    cout << step << endl;
    r_min = -3.f;
    r_max = 3.f;
    bool gamma_type = ofRandom(1.0) > 0.5 ? true : false;
    for (float f = r_min; f < r_max; f+=step) {
        for (float g = r_min; g < r_max; g+=step) {
            double r = beta(f, g, gamma_type);
            glm::vec3 v = glm::vec3(f*scaleFactor, g*scaleFactor, r);
//            ofDrawSphere(v, 0.5f);
//            ofDrawRectangle(v, 1.f, 1.f);
            ofDrawCircle(v, 0.1f);
//            ofDrawCone(v, 1.f, 3.f);
        }
    }
    
    cam.end();

}

double ofApp::beta(double x, double y, bool isLgamma) {
    
    if (isLgamma) {
        return (lgamma(x) * lgamma(y)) / lgamma(x+y);
    }
    return (tgamma(x) * tgamma(y)) / tgamma(x+y);
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
