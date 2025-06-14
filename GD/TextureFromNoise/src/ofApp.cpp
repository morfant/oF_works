#include "ofApp.h"

int width, height;
int mX, mY;
float noiseXRange, noiseYRange;
int noiseMode = 1;
int octave = 4;
float falloff = 0.5;

ofPixels pixels;
ofTexture texture;


//--------------------------------------------------------------
void ofApp::setup(){
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    
    pixels.allocate(width, height, OF_PIXELS_RGB);
    texture.allocate(pixels);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    noiseXRange = mX / 40;
    noiseYRange = mY / 40;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            
            float noiseX = ofMap(x, 0, width, 0, noiseXRange);
            float noiseY = ofMap(y, 0, width, 0, noiseYRange);
            
            float noiseValue = 0;
            
            if (noiseMode == 1)
            {
//                noiseValue = ofNoise(noiseX, noiseY) * 255;
                noiseValue = fractalNoise(noiseX, noiseY, octave, falloff) * 255;

            }
            else if (noiseMode == 2)
            {
//                float n = ofNoise(noiseX, noiseY) * 24;
                float n = fractalNoise(noiseX, noiseY, octave, falloff) * 24;

                noiseValue = (n - (int)n) * 255;
//                cout << "n: " << n << ", (int)n: " << (int)n << ", diff: " << n - (int)n << endl;
            }
            pixels.setColor(x, y, ofColor(noiseValue));

        }
    }
    texture.loadData(pixels);
    texture.draw(0, 0);

}

float ofApp::fractalNoise(float x, float y, int octaves, float falloff) {
    float noiseValue = 0.0;
    float amplitude = 1.0;
    float frequency =1.0;
    float maxAmplitude = 0.0;
    
    for (int i = 0; i < octaves; i++)
    {
        noiseValue += ofNoise(x * frequency, y * frequency) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= falloff;
        frequency *= 2.0;
    }
    
    return noiseValue / maxAmplitude;
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') noiseMode = 1;
    if (key == '2') noiseMode = 2;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == OF_KEY_UP)
    {
        octave += 1;
        octave = ofClamp(octave, 1, 9);
        cout << "ocatave: " << octave << endl;
    }
    else if (key == OF_KEY_DOWN)
    {
        
        octave -= 1;
        octave = ofClamp(octave, 1, 9);
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
