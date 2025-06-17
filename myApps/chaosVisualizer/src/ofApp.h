#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "Mover.h"
#include "Seed.h"
#include "Grid.h"
#include "Blackhole.h"
// #include "UIControls.h"

#define HOST "127.0.0.1"
#define PORT_OUT 57120
#define PORT_IN 12000

#define SEED_SIT_THR 5
#define ATTR_ITER_NUM 5000
#define ATTR_RAD 1

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

	void updateParameters();
	void applyBlackholeForce();
	void renderAttractor();
	void updateGridFromAmp();

	// ofApp.h
	void onInitXChanged(float & val);
	void onInitYChanged(float & val);
	void onRateChanged(int & val);
	void onToggleChanged(bool & val);

	void sendLatooParams();
	void sendLatooInit();
	void sendLatooRate();
	void sendLatooAmpState(bool isOn);
	void sendShutdown();
	void sendSeedPositions();
	void removeSeedAt(int index);
	void oscReceive();


    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
	// void onSliderChanged(int& value);

	void exit();


    bool ampLatoo, useLines;
	bool isDragging, overToggle, overSlider;
	Blackhole* draggingBlackhole = nullptr;

    float lat_x, lat_y, lat_a, lat_b, lat_c, lat_d;
	int lat_rate;

    Mover mover;
    vector<Seed> seeds;
    vector<Blackhole> blackholes;
    Grid grid;
    ofImage hiddenImg;

    ofFbo attractorLayer;

	// UI
	ofxPanel gui;
	ofxFloatSlider fSlider[2];    // Float 타입 슬라이더
	ofxIntSlider iSlider;    // Int 타입 슬라이더
	ofxToggle toggle;

	// OSC
	ofxOscSender sender;
	ofxOscReceiver receiver;

};
