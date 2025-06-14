#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    
    gui.setup();
    
    gui.add(iSlider[0].setup("FREQ_X", freqX, 0, 30));
    gui.add(iSlider[1].setup("FREQ_Y", freqY, 0, 30));
    gui.add(iSlider[2].setup("PHASE", phi, -360, 360));
    iSlider[2].addListener(this, &ofApp::onSliderChanged);

    gui.add(toggle.setup("DRAW_ANIMATION", true));

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
    phi = iSlider[2];
    doDrawAnimation = (int)toggle;
}


void ofApp::drawAnimation()
{
    ofPushStyle();
    ofNoFill();
    
    // draw x oscillator
    ofSetColor(0);
    ofBeginShape();
    for (int i = 0; i <= pointCoount; i++)
    {
        angle = ofMap(i, 0, pointCoount, 0, TWO_PI);
        x = sin(angle * freqX + ofDegToRad(phi));
        x = x * (w * 0.25 - margin);
        y = -h * 2 / 3.0 - margin + (float)i / pointCoount * (h * 0.5 - 2 * margin);
        ofVertex(x, y);
    }
    ofEndShape();
    
    
    // draw y oscillator
    ofSetColor(0);
    ofBeginShape();
    for (int i = 0; i <= pointCoount; i++)
    {
        angle = ofMap(i, 0, pointCoount, 0, TWO_PI);
        y = sin(angle * freqY);
        y = y * (h * 0.25 - margin);
        x = -w * 2 / 3.0 - margin + (float)i / pointCoount * (w * 0.5 - 2 * margin);
        ofVertex(x, y);
    }
    ofEndShape();
    
    angle = ofMap(ofGetFrameNum(), 0, pointCoount, 0, TWO_PI);
    x = sin(angle * freqX + ofDegToRad(phi));
    y = sin(angle * freqY);
    x = x * (w * 0.25 - margin);
    y = y * (h * 0.25 - margin);
    
    float oscYx = -w * 2 / 3.0 - margin + fmod(angle / TWO_PI, 1.0) * (w * 0.5 - 2 * margin);
    float oscXy = -h * 2 / 3.0 - margin + fmod(angle / TWO_PI, 1.0) * (h * 0.5 - 2 * margin);

    ofSetColor(0, 80);
    ofDrawLine(x, oscXy, x, y);
    ofDrawLine(oscYx, y, x, y);
    
    ofSetColor(0);
    ofFill();
    ofSetLineWidth(2);
    ofDrawEllipse(x, oscXy, 8, 8);
    ofDrawEllipse(oscYx, y, 8, 8);
    ofDrawEllipse(x, y, 10, 10);

    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(0);
    ofSetLineWidth(1);
    
    ofPushMatrix();
    
    if (doDrawAnimation)
    {
        ofTranslate(w * 3 / 4.0, h * 3 / 4.0);
        factorX = w / 4 - margin;
        factorY = h / 4 - margin;
    }
    else
    {
        ofTranslate(w * 0.5, h * 0.5);
        factorX = w * 0.5 - margin;
        factorY = h * 0.5 - margin;
    }
    
    ofNoFill();
    ofBeginShape();
    for (int i = 0; i <= pointCoount; i++)
    {
        angle = ofMap(i, 0, pointCoount, 0, TWO_PI);
        x = sin(angle * freqX + ofDegToRad(phi));
        y = sin(angle * freqY);
        
        x = x * factorX;
        y = y * factorY;
        ofVertex(x, y);
    }
    ofEndShape();
    
    if (doDrawAnimation)
    {
        drawAnimation();
    }
    
    ofPopMatrix();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if(key == 's' || key == 'S') saveFrame(timestamp()+".png");
//    if(key == 'p' || key == 'P') {
//      savePDF = true;
//      println("saving to pdf - starting");
//    }

    if (key == 'a' || key == 'A') doDrawAnimation = !doDrawAnimation;

    if(key == '1') freqX--;
    if(key == '2') freqX++;
    freqX = max(freqX, 1);

    if(key == '3') freqY--;
    if(key == '4') freqY++;
    freqY = max(freqY, 1);

    if (key == OF_KEY_LEFT) phi -= 15;
    if (key == OF_KEY_RIGHT) phi += 15;

    string str = "freqX: " + ofToString(freqX) + ", freqY: " + ofToString(freqY) + ", phi: " + ofToString(phi);
    
    cout << str << endl;

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
