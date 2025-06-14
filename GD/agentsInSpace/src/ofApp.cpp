#include "ofApp.h"

int Agent::width = 0;
int Agent::height = 0;
int Agent::octave = 4;
float Agent::falloff = 0.5;
float Agent::noiseScale = 100.0f;
float Agent::noiseStrength = 10.0f;
float Agent::minStroke = 1.0f;
float Agent::maxStroke = 12.0f;
int Agent::spaceSizeX = 0;
int Agent::spaceSizeY = 0;
int Agent::spaceSizeZ = 0;
bool Agent::mono = false;
float Agent::alpha = 100;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
//    ofSetBackgroundAuto(false);
    
    // GUI 패널 초기화
    gui.setup();
    
    // 이름, 초기값, 최소값, 최대값
    gui.add(iSlider[0].setup("AGENT_COUNT", 100, 0, AGENT_MAX_NUM));
    gui.add(fSlider[0].setup("NOISE_SCALE", 350.0f, 0.0, 1000.0));
    gui.add(fSlider[1].setup("NOISE_STRENGTH", 20.0f, 0.0, 100.0));
    
    gui.add(iSlider[1].setup("OCTAVE", 4, 1, 9));
    gui.add(fSlider[2].setup("FALL_OFF", 0.5f, 0.05, 0.975));
    
    gui.add(rangeSlider.setup("STROKE_WIDTH_RANGE",
                              glm::vec2(1.0, 11.0),
                              glm::vec2(0.0, 0.0),
                              glm::vec2(50.0, 50.0)));
    
    gui.add(toggle.setup("DRAW_MODE", false));
    gui.add(isMono.setup("IS_MONO", false));
    gui.add(fSlider[3].setup("AGENT_ALPHA", 100, 0, 255));

    // 패널의 크기
    gui.setSize(300, 500);
    
    w = ofGetWidth();
    h = ofGetHeight();
    Agent::width = w;
    Agent::height = h;
    
    Agent::spaceSizeX = spaceSizeX;
    Agent::spaceSizeY = spaceSizeY;
    Agent::spaceSizeZ = spaceSizeZ;

    for (int i = 0; i < AGENT_MAX_NUM; i++)
    {
        agents.push_back(make_shared<Agent>());
    }
    
    
}


//--------------------------------------------------------------
void ofApp::update(){
    agentsCount = iSlider[0];
    Agent::noiseScale = fSlider[0];
    Agent::noiseStrength = fSlider[1];
    Agent::octave = iSlider[1];
    Agent::falloff = fSlider[2];
    
    Agent::minStroke = rangeSlider->x;
    Agent::maxStroke = rangeSlider->y;
    drawMode = (int)toggle;
    Agent::mono = (int)isMono;
    Agent::alpha = fSlider[3];
    
//    setNoiseSeed(iSlider[3]);
}

//--------------------------------------------------------------
void ofApp::drawScene() {
//    ofSetColor(255, overlayAlpha);
//    ofDrawRectangle(0, 0, w, h);
    
//    ofSetColor(0, agentAlpha);
    for (int i = 0; i < agentsCount; i++)
    {
        if (drawMode == 0) { agents.at(i)->update1(); }
        else { agents.at(i)->update2(); }

        agents.at(i)->draw();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    
//    if (bSavePdf)
//    {
//        if (count == 0)
//        {
//            string fileName = PROJECTNAME + "_" + ofGetTimestampString("%Y-%m-%d-%H-%M-%S") + ".pdf";
//            ofBeginSaveScreenAsPDF(fileName, false);
//        }
//        drawScene();
//        if (count > pdfAccumulationFrame)
//        {
//            ofEndSaveScreenAsPDF();
//            bSavePdf = false;
//            ofLog() << "PDF saved!";
//        }
//        
//        count++;
//    }
    
//    ofPushMatrix();
//    ofTranslate(w * 0.5, h * 0.5, -450);
    cam.begin();
    
    ofColor boxColor = hsbToRgb(192, 100, 64);
    ofSetColor(boxColor);
    ofSetLineWidth(1);
    ofDrawBox(spaceSizeX * 2, spaceSizeY * 2, spaceSizeZ * 2);
    drawScene();
    
    cam.end();
    
//    ofPopMatrix();
    
    // Hide gui when saving frames as pdf
    if (bSavePdf == false) gui.draw();

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // save PNG
    if (key == 's')
    {
        string fileName = PROJECTNAME + "_" + ofGetTimestampString("%Y-%m-%d-%H-%M-%S") + ".png";
        
        ofSaveScreen(fileName);
        cout << "Screenshot saved as: " << fileName << endl;
    }
    
    // save PDF
    if (key == 'p')
    {
        bSavePdf = true;
        count = 0;
    }

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
