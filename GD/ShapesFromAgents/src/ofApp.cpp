#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);

    w = ofGetWidth();
    h = ofGetHeight();
    
    fbo.allocate(w, h, GL_RGBA);
    
    cx = w * 0.5;
    cy = h * 0.5;

     
    float angle = ofDegToRad(360 / formResolution);
    
    for (int i = 0; i < formResolution; i++)
    {
        vec.push_back( glm::vec3(
                         initialRadius * cos(angle * i),
                         initialRadius * sin(angle * i),
                         0));
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    cx += (ofGetMouseX() - cx) * 0.004;
    cy += (ofGetMouseY() - cy) * 0.004;

    for (int i = 0; i < formResolution; i++)
    {
        if (i < vec.size())
        {
            vec.at(i).x += ofRandomf() * stepSize;
            vec.at(i).y += ofRandomf() * stepSize;
        }
    }
    
    fbo.begin();
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA); // 기본 블렌딩 모드
    ofEnableBlendMode(OF_BLENDMODE_ADD); // 더해질 수록 진해져서 원래 색을 찾는다

    glEnable(GL_LINE_SMOOTH);     // 선 부드럽게
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.0);            // 선 두께 설정

    polyLine.curveTo(
                    vec.at(formResolution - 1).x + cx,
                    vec.at(formResolution - 1).y + cy);

    for (int i = 0; i < formResolution; i++)
    {
        polyLine.curveTo(vec.at(i).x + cx, vec.at(i).y + cy);
    }

    polyLine.curveTo(vec.at(0).x + cx, vec.at(0).y + cy);
    polyLine.curveTo(vec.at(1).x + cx, vec.at(1).y + cy);
    polyLine.close();
    
    ofSetColor(0, 70);
    polyLine.draw();
    polyLine.clear();
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
   
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
