#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
//	ofGLWindowSettings settings;
//	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

    // main.cpp
    ofGLFWWindowSettings settings;
    settings.setSize(1200, 900);
    settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
//    settings.setGLVersion(3, 2);   // OpenGL 버전
//    settings.numSamples = 32;      // MSAA 샘플링 개수 (4x, 8x 등)
//    ofCreateWindow(settings);
    

    
	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
