#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	// settings.setSize(1200, 800);
	// settings.setSize(1920, 1080);
	settings.setSize(1710, 1112);
	// settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
	settings.windowMode = OF_FULLSCREEN; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();

}
