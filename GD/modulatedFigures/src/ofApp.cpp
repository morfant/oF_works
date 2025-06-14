#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    
    gui.setup();
    
    gui.add(iSlider[0].setup("FREQ_X", freqX, 0, 30));
    gui.add(iSlider[1].setup("FREQ_Y", freqY, 0, 30));
    gui.add(iSlider[2].setup("PHASE_X", phiX, -360, 360));
    gui.add(iSlider[3].setup("PHASE_Y", phiY, -360, 360));
    gui.add(iSlider[4].setup("MOD_FREQ_X", modFreqX, 0, 30));
    gui.add(iSlider[5].setup("MOD_FREQ_Y", modFreqY, 0, 30));
    iSlider[2].addListener(this, &ofApp::onSliderChanged);
    iSlider[3].addListener(this, &ofApp::onSliderChanged);

   }

void ofApp::calculateLissajousPoints()
{
    points.clear();
    float f = w / 2;
    for (int i = 0; i <= pointCount; i++){
        float angle = ofMap(i, 0, pointCount, 0, TWO_PI);
        float x = sin(angle*freqX + ofDegToRad(phiX)) * sin(angle*modFreqX) * f;
        float y = sin(angle*freqY + ofDegToRad(phiY)) * sin(angle*modFreqY) * f;
        float z = sin(angle*freqZ) * f;
        points.push_back(glm::vec3(x, y, z));
    }
}


void ofApp::onSliderChanged(int &value)
{
    const int step = 5;
    value = (value / step) * step;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    freqX = iSlider[0];
    freqY = iSlider[1];
    phiX = iSlider[2];
    phiY = iSlider[3];
    modFreqX = iSlider[4];
    modFreqY = iSlider[5];
    
    
    calculateLissajousPoints();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(237, 237, 233);
    cam.begin();
    
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<pointCount-2; i++) {
      if (i%3 == 0) {
        //gradient for every trinangle to lissajou path
          glColor4f(0, 119/255.0, 182/255.0, 90/255.0);
          glVertex3f(0, 0, 0);
          glVertex3f(points[i].x, points[i].y, points[i].z);
          glVertex3f(points[i + 2].x, points[i + 2].y, points[i + 2].z);
          
      }
    }
    glEnd();
     
    
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<pointCount; i++) {
      glColor4f(0.1f, 0.1f, 0.1f, 0.7f);
      glVertex3f(points[i].x, points[i].y, points[i].z);
    }
    glEnd();



    
    
//    ofNoFill();
//    ofBeginShape();
//    for (int i = 0; i <= pointCount; i++)
//    {
//        angle = ofMap(i, 0, pointCount, 0, TWO_PI);
//        x = sin(angle * freqX + ofDegToRad(phiX)) * cos(angle * modFreqX);
//        y = cos(angle * freqY) * cos(angle * modFreqY);
//        
//        x = x * (w/2-50);
//        y = y * (h/2-50);
//        
//        ofVertex(x, y);
//
//    }
//    ofEndShape();
    
    
//    ofPopMatrix();
    cam.end();
    
    gui.draw();
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
