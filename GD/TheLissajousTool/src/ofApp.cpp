#include "ofApp.h"


int i1 = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofBackground(237, 237, 233);

    
    width = ofGetWidth();
    height = ofGetHeight();
    
    gui.setup();
    
    int si = 0;
    int fi = 0;
    int ti = 0;
    
    gui.add(iSlider[si++].setup("POINT_COUNT", pointCount, 1, 8000));
    gui.add(iSlider[si++].setup("FREQ_X", freqX, 0, 30));
    gui.add(iSlider[si++].setup("FREQ_Y", freqY, 0, 30));
    gui.add(iSlider[si++].setup("PHASE_X", phiX, -360, 360));
    gui.add(iSlider[si++].setup("PHASE_Y", phiY, -360, 360));
    gui.add(iSlider[si++].setup("MOD_FREQ_X", modFreqX, 0, 50));
    gui.add(iSlider[si++].setup("MOD_FREQ_Y", modFreqY, 0, 50));
    gui.add(iSlider[si++].setup("MOD_FREQ_2X", modFreq2X, 0, 50));
    gui.add(iSlider[si++].setup("MOD_FREQ_2Y", modFreq2Y, 0, 50));
    gui.add(fSlider[fi++].setup("MOD_FREQ_2_STRENGTH", modFreq2Strength, 0, 1));
    gui.add(iSlider[si++].setup("RAND_OFFSET", randomOffset, 0, 50));
    gui.add(toggle[ti++].setup("INV_BG", invertBackground));
    gui.add(fSlider[fi++].setup("LINE_WEIGHT", lineWeight, 1, 50));
    gui.add(fSlider[fi++].setup("LINE_ALPHA", lineAlpha, 0, 100));
    
    gui.add(toggle[ti++].setup("CONNECT_ALL_POINTS", connectAllPoints));
    
    
    // PHASE sliders step
    for (int i = 0; i < 10; i++)
    {
        if (i != 3 && i != 4)
        {
            iSlider[i].addListener(this, &ofApp::onSliderChangedInt);
        }
        fSlider[i].addListener(this, &ofApp::onSliderChangedFloat);
    }
    
    iSlider[3].addListener(this, &ofApp::onSliderChangedIntStep);
    iSlider[4].addListener(this, &ofApp::onSliderChangedIntStep);

    
    calculateLissajousPoints();
    
}
//--------------------------------------------------------------
void ofApp::update(){
    int si = 0;
    int fi = 0;
    int ti = 0;
    
    pointCount = iSlider[si++];
    freqX = iSlider[si++];
    freqY = iSlider[si++];
    phiX = iSlider[si++];
    phiY = iSlider[si++];
    modFreqX = iSlider[si++];
    modFreqY = iSlider[si++];
    modFreq2X = iSlider[si++];
    modFreq2Y = iSlider[si++];
    randomOffset = iSlider[si++];
    
    modFreq2Strength = fSlider[fi++];
    lineWeight = fSlider[fi++];
    lineAlpha = fSlider[fi++];
    
    invertBackground = toggle[ti++];
    connectAllPoints = toggle[ti++];

//    calculateLissajousPoints();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    ofColor bgColor = ofColor(237, 237, 233);
    
    if (invertBackground) {
        bgColor = ofColor(0);
    }
    
    if (reDraw || i1 == 0) {
        calculateLissajousPoints();
        ofBackground(bgColor);
        i1 = 0;
        reDraw = false;
    }

    if (!connectAllPoints) {
        ofBackground(bgColor);
        i1++;

        for (int i = 0; i <= pointCount - 1; i++) {
            drawLine(*lissajousPoints[i], *lissajousPoints[i+1]);
        }
    }
    else {
        // drawing method where all points are connected with each other
        // alpha depends on distance of the points
        
        // draw lines not all at once, just the next 100 milliseconds to keep performance
        int drawEndTime = ofGetElapsedTimeMillis() + 100;
//        if (saveOneFrame || savePDF) {
//            drawEndTime = Integer.MAX_VALUE;
//        }
        
        while (i1 < pointCount && ofGetElapsedTimeMillis() < drawEndTime) {
            for (int i2 = 0; i2 < i1; i2++) {
                drawLine(*lissajousPoints[i1], *lissajousPoints[i2]);
            }
            i1++;

            
//            if (savePDF) {
//                println("saving to pdf – step " + i1 + "/" + pointCount);
//            }
        }
        
        
    }
    cam.end();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}


//--------------------------------------------------------------
void ofApp::calculateLissajousPoints() {
    
    lissajousPoints.clear();

    srand(0);

    float t, x, y, rx, ry;

    for (int i = 0; i <= pointCount; i++) {
        float angle = ofMap(i, 0, pointCount, 0, TWO_PI);

        // an additional modulation of the osscillations
        float fmx = sin(angle * modFreq2X) * modFreq2Strength + 1;
        float fmy = sin(angle * modFreq2Y) * modFreq2Strength + 1;

        x = sin(angle * freqX * fmx + ofDegToRad(phiX)) * cos(angle * modFreqX);
        y = sin(angle * freqY * fmy + ofDegToRad(phiY)) * cos(angle * modFreqY);

        rx = ofRandom(-randomOffset, randomOffset);
        ry = ofRandom(-randomOffset, randomOffset);

        x = (x * (width * 0.5 - 30 - randomOffset) + width * 0.0) + rx;
        y = (y * (height * 0.5 - 30 - randomOffset) + height * 0.0) + ry;

        lissajousPoints.push_back(make_shared<glm::vec2>(x, y));
    }
}


void ofApp::drawLine(const glm::vec2& p1, const glm::vec2& p2) {
    float d, a, h;

    d = glm::distance(p1, p2);
    a = pow(1/(d/connectionRadius+1), 6);

    if (d <= connectionRadius) {
        if (!invertHue) {
            h = static_cast<int>(ofMap(a, 0, 1, minHueValue, maxHueValue)) % 360;
        }
        else {
            h = static_cast<int>(ofMap(1 - a, 0, 1, minHueValue, maxHueValue)) % 360;
        }
        ofColor c = hsb2rgba(h, saturationValue, brightnessValue, a * lineAlpha + (i1%2 * 2));
        ofSetColor(c);
        ofSetLineWidth(lineWeight);
        ofDrawLine(p1.x, p1.y, p2.x, p2.y);
    }
}


//--------------------------------------------------------------
void ofApp::onSliderChangedIntStep(int &value)
{
    reDraw = true;
    const int step = 5;
    value = (value / step) * step;
}

//--------------------------------------------------------------
void ofApp::onSliderChangedInt(int &value)
{
    reDraw = true;
}

//--------------------------------------------------------------
void ofApp::onSliderChangedFloat(float &value)
{
    reDraw = true;
}





//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r')
        reDraw = true;

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
