#pragma once


#include "ofMain.h"
#include "BSmanage.h"
#include "ofxMidi.h"

//#define PI 3.141592
#define BAR_NUM 15
#define BALL_NUM 1
#define BH_NUM 1
#define BLACKHOLE_SIZE 90
#define DEBUG_MODE
#define MIDI_CHANNEL 1 //SET USING MIDI CHANNEL


class ofApp : public ofBaseApp, public ofxMidiListener {

	public:

		void setup();
		void update();
		void draw();
    
        ofVec2f getPosOnCircle(ofVec2f centerPos, float radius, float angle);
		
	
		bool realTime;
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		bool bFill;
		int sLength[BAR_NUM];
        float angleStep;
	
		BSmanage* man;
	
	bool BlackHoleDraw;
	
	//MIDI
    void newMidiMessage(ofxMidiMessage& message) override;
	void midiControlBar(int ccNum);
	
	int port;
	int id; //channel
	int currentCnum;
	int value[BAR_NUM];
//	double timestamp;
//	char msg[255];
	bool midiConReverse;
	bool midiContAll;
	
	// midi addon
	ofxMidiIn	midiIn;
    
    char tempStr[20];


	
	
};
