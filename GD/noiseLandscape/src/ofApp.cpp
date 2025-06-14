#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
   
    // colors
    topColor = hsbToRgb(0, 0, 100);
    midColor = hsbToRgb(191, 99, 63);
    bottomColor = hsbToRgb(0, 0, 0);
    
    noiseXRange = 40;
    noiseYRange = 40;
    
    
    numX = 32;
    numY = 32;
    width = ofGetWidth();
    height = ofGetHeight();
    stepX = width / numX;
    stepY = height / numY;
    
    for (int meshY = 0; meshY < numY; meshY++)
    {
        for (int meshX = 0; meshX < numX; meshX++)
        {
            float x = ofMap(meshX, 0, numX, -width * 0.5, width * 0.5);
            float y = ofMap(meshY, 0, numY, -height * 0.5, height * 0.5);
            
            mesh.addVertex(ofVec3f(x, y, 0));
            mesh.addColor(ofColor(ofRandom(255)));
        }
    }
    
    // 삼각형 연결
    for (int y = 0; y < numY - 1; y++) {
        for (int x = 0; x < numX - 1; x++) {
            int idx = x + y * numX;
            mesh.addIndex(idx); // left top
            mesh.addIndex(idx + 1); // right top
            mesh.addIndex(idx + numX); // left bottom

            mesh.addIndex(idx + 1); // right top
            mesh.addIndex(idx + 1 + numX); // right bottom
            mesh.addIndex(idx + numX); // left bottom
        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){
     
    noiseStep = (float)noiseXRange / numX;
    
    // mode 선택
    if (prevGlMode != glMode) {
        mesh.setMode(connectingMode[glMode]);
        prevGlMode = glMode;
    }
    
    
    
    float noiseYMax = 0;
    float threshold = 0.30;
    
    for (int x = 0; x < numX; x++)
    {
        for (int y = 0; y < numY; y++)
        {
            int idx = x + (numX * y);
            float noiseX = ofMap(x, 0, numX, 0, noiseXRange);
            float noiseY = ofMap(y, 0, numY, 0, noiseYRange);
            
            float z1 = fractalNoise(noiseX, noiseY, octave, falloff);
            
//            float z1 = ofNoise(noiseX, noiseY);
//            float z2 = ofNoise(noiseX, noiseY + noiseStep);

            ofVec3f p = mesh.getVertex(idx);
            p.z = z1 * zScale;
            
            noiseYMax = max(noiseYMax, z1);
            ofColor interColor;
            if (z1 <= threshold) {
              float amount = ofMap(z1, 0, threshold, 0.15, 1);
                interColor = lerpColor(bottomColor, midColor, amount);
            } else {
              float amount = ofMap(z1, threshold, noiseYMax, 0, 1);
                interColor = lerpColor(midColor, topColor, amount);
            }
            mesh.setColor(idx, interColor);
            mesh.setVertex(idx, p);
        }
    }
    
    if (glMode == 2)
    {
        // line을 위한 mesh
        meshLine = mesh;
        
        // 원하는 색상을 한 번에 적용하고 싶다면:
        ofColor newColor(0, 0, 0);

        for (int i = 0; i < meshLine.getNumVertices(); i++) {
            meshLine.setColor(i, newColor);
        }
            
    }
   


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofEnableDepthTest();
    cam.begin();
    
    mesh.draw(); // 삼각형

    if (glMode == 2 && isDrawLine == true)
    {
        meshLine.setMode(OF_PRIMITIVE_LINES);
        meshLine.draw(); // 선
    }
    
    cam.end();

    ofColor(255);
    ofDrawBitmapString("Adjust resolution: Ctrl + Drag", 100, 70);

    ofDrawBitmapString("Select 1 ~ 3", 100, 100);
    string currentModeName = modeNames[glMode];
    ofDrawBitmapString(currentModeName, 100, 130);
    
    if (glMode == 2)
    {
        ofDrawBitmapString("Toggle line: 'L'", 100, 160);
    }

    ofDrawBitmapString("Octave(UP/DOWN): " + ofToString(octave), 100, 200);
    ofDrawBitmapString("Falloff(LEFT/RIGHT): " + ofToString(falloff), 100, 230);

}

//--------------------------------------------------------------
void ofApp::exit(){

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int n = key - 48;
    if (0 < n && n < 4)
    {
        glMode = n - 1;
    }
    
    
    // ctrl
    if (key == 3682)
    {
        isToggle = true;
    }
    
    // 'l' or 'L'
    if (key == 'l' || key == 'L')
    {
        isDrawLine = !isDrawLine;
    }
    
    
    // adjust noise
    int octaveMax = 12;
    if (key == OF_KEY_UP)
    {
        octave += 1;
        octave = ofClamp(octave, 1, octaveMax);
        cout << "ocatave: " << octave << endl;
    }
    else if (key == OF_KEY_DOWN)
    {
        
        octave -= 1;
        octave = ofClamp(octave, 1, octaveMax);
        cout << "ocatave: " << octave << endl;
    }
    
    if (key == OF_KEY_LEFT)
    {
        falloff -= 0.05;
        falloff = ofClamp(falloff, 0.05, 0.95);
        cout << "falloff: " << falloff << endl;
    }
    else if (key == OF_KEY_RIGHT)
    {
        falloff += 0.05;
        falloff = ofClamp(falloff, 0.05, 0.95);
        cout << "falloff: " << falloff << endl;
    }



}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 3682)
    {
        isToggle = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    if (isToggle == true)
    {
        noiseXRange = x / 10.f;
        noiseYRange = y / 10.f;
    }

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
