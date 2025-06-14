#include "ofApp.h"

int Agent::width = 0;
int Agent::height = 0;
int Agent::octave = 4;
float Agent::falloff = 0.5;
float Agent::noiseScale = 100.0f;
float Agent::noiseStrength = 10.0f;
float Agent::strokeWidth = 0.3f;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    
    // GUI 패널 초기화
    gui.setup();
    
    // 이름, 초기값, 최소값, 최대값
    gui.add(iSlider[0].setup("AGENT_COUNT", 4000, 0, AGENT_MAX_NUM));
    gui.add(fSlider[0].setup("NOISE_SCALE", 300.0f, 0.0, 1000.0));
    gui.add(fSlider[1].setup("NOISE_STRENGTH", 10.0f, 0.0, 100.0));
    
    gui.add(iSlider[1].setup("OCTAVE", 4, 1, 9));
    gui.add(fSlider[2].setup("FALL_OFF", 0.5f, 0.05, 0.975));

    gui.add(fSlider[3].setup("STROKE_WIDTH", 0.3f, 0.01, 5.0));
    gui.add(fSlider[4].setup("AGENT_ALPHA", 90.0f, 0.0, 255));
    gui.add(fSlider[5].setup("OVERLAY_ALPHA", 10.0f, 0.0, 255));
    
    gui.add(toggle.setup("USE_FRACTIONAL", false));
    gui.add(iSlider[3].setup("SEED", 0, 0, 100000));
    
    // 패널의 크기
    gui.setSize(300, 500);
    
    w = ofGetWidth();
    h = ofGetHeight();
    Agent::width = w;
    Agent::height = h;
    
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
    Agent::strokeWidth = fSlider[3];
    agentAlpha = fSlider[4];
    overlayAlpha = fSlider[5];
    drawMode = (int)toggle;
    setNoiseSeed(iSlider[3]);
}

//--------------------------------------------------------------
void ofApp::drawScene() {
    ofSetColor(255, overlayAlpha);
    ofDrawRectangle(0, 0, w, h);
    
    ofSetColor(0, agentAlpha);
    if (drawMode == 0)
    {
        for (int i = 0; i < agentsCount; i++)
        {
            agents.at(i)->update1();
        }
    }
    else if (drawMode == 1)
    {
        for (int i = 0; i < agentsCount; i++)
        {
            agents.at(i)->update2();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    if (bSavePdf)
    {
        if (count == 0)
        {
            string fileName = PROJECTNAME + "_" + ofGetTimestampString("%Y-%m-%d-%H-%M-%S") + ".pdf";
            ofBeginSaveScreenAsPDF(fileName, false);
        }
        drawScene();
        if (count > pdfAccumulationFrame)
        {
            ofEndSaveScreenAsPDF();
            bSavePdf = false;
            ofLog() << "PDF saved!";
        }
        
        count++;
    }
    
   
    drawScene();
    
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
