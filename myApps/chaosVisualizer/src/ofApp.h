#pragma once
#include "Blackhole.h"
#include "Grid.h"
#include "Mover.h"
#include "Seed.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
// #include "UIControls.h"
#include "AttractorPoint.h"

#define HOST "127.0.0.1"
#define PORT_OUT 57120
#define PORT_IN 12000

#define SEED_SIT_THR 5
#define ATTR_ITER_NUM 10000
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
	void assignTargetPositionsFromImage(
		const ofImage & img, vector<AttractorPoint> & points,
		float threshold = 200.f, int step = 4);
	void drawTargetPositions(const vector<AttractorPoint> & points);

	// ofApp.h
	void drawUI();
	void onInitXChanged(float & val);
	void onInitYChanged(float & val);
	void onRateChanged(int & val);
	void onConvergeChanged(float & val);
	void onStrengthRangeScaleChanged(float & val);
	void onForceBaseScaleChanged(float & val);
	void onToggleChanged(bool & val);
	void onToggleDrawThings(bool & val);
	void onToggleFieldArrows(bool & val); // 콜백 선언
	void onToggleFieldDots(bool & val); // 콜백 선언
	void onToggleAttractor(bool & val);

	void sendLatooParams();
	void sendLatooInit();
	void sendLatooRate();
	void sendLatooAmpState(bool isOn);
	void sendShutdown();
	void sendSeedPositions();
	void sendSeedVelocity();
	void removeSeedAt(int index);
	void oscReceive();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	// void onSliderChanged(int& value);

	void exit();

	bool drawThings, ampLatoo, useLines;
	bool isDragging, overToggle, overSlider;
	bool drawFieldArrows; // 화살표를 그릴지 여부
	bool drawFieldDots;
	bool drawAttractor; // attractor를 그릴지 여부
	Blackhole * draggingBlackhole = nullptr;

	float lat_x, lat_y, lat_a, lat_b, lat_c, lat_d;
	float convergeAmount;
	int lat_rate;
	float seedMass;
	float strengthRangeScale; // 1st stage: Perlin 기반 strength 범위 스케일
	float forceBaseScale; // 2nd stage: 거리 기반 1/r^2 기본 힘 스케일

	Mover mover; // 원래 있던 메인 Mover
	std::vector<Mover> movers; // 키로 추가/삭제하는 extra Mover들
	int controllerMoverIndex; // which mover controls updateParameters & forces (-1 = none)

	vector<Seed> seeds;
	vector<Blackhole> blackholes;
	Grid grid;
	ofImage hiddenImg;

	ofFbo attractorLayer;

	// UI
	ofxPanel gui;
	ofxFloatSlider fSlider[3]; // Float 타입 슬라이더
	ofxFloatSlider correctionSlider;
	ofxIntSlider iSlider; // Int 타입 슬라이더
	ofxFloatSlider strengthRangeScaleSlider;
	ofxFloatSlider forceBaseScaleSlider;
	ofxToggle toggle;
	ofxToggle toggleDraw;
	ofxToggle toggleFieldArrows; // force-field 화살표 표시 토글
	ofxToggle toggleFieldDots; // force-field 화살표 표시 토글
	ofxToggle toggleAttractor; // Latoocarfian attractor 그리기 토글

	// OSC
	ofxOscSender sender;
	ofxOscReceiver receiver;

	vector<AttractorPoint> attractorPoints;
	ofFbo attractorFbo;
};
