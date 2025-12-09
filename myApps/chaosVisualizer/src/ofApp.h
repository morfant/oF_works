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
	void onTimeScaleChanged(float & val);
	void onIndexScaleChanged(float & val);
	void onFieldScaleChanged(float & val); // <- 새로 추가
	void onToggleChanged(bool & val);
	void onToggleDrawThings(bool & val);
	void onToggleFieldArrows(bool & val); // 콜백 선언
	void onToggleFieldDots(bool & val); // 콜백 선언
	void onToggleAttractor(bool & val);
	void onToggleMainCircle(bool & val);
	void onToggleFieldClip(bool & val);

	void sendLatooParams();
	void sendLatooInit();
	void sendLatooRate();
	void sendLatooAmpState(bool isOn);
	void sendShutdown();
	void sendSeedPositions();
	void sendSeedVelocity();
	void sendBlackholeStates();   // ← 이 줄 추가
	void sendMoverCollision(int idxA, int idxB);
	void sendCollisionCountWindow(int count); // ★ 추가
	void removeSeedAt(int index);
	void oscReceive();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	// void onSliderChanged(int& value);

	void exit();

	int width, height;

	bool drawThings, ampLatoo, useLines;
	bool isDragging, overToggle, overSlider;
	bool drawFieldArrows; // 화살표를 그릴지 여부
	bool drawFieldDots;
	bool drawAttractor; // attractor를 그릴지 여부
	bool drawMainCircle; // 화면 중앙 메인 원 표시 여부
	bool clipFieldToCircle;
	Blackhole * draggingBlackhole = nullptr;

	float lat_x, lat_y, lat_a, lat_b, lat_c, lat_d;
	float convergeAmount;
	int lat_rate;
	float seedMass;
	float strengthRangeScale; // 1st stage: Perlin 기반 strength 범위 스케일
	float forceBaseScale; // 2nd stage: 거리 기반 1/r^2 기본 힘 스케일
	float timeScale; // Perlin 시간 흐름 속도
	float indexScale; // 링을 따라 패턴 변화 속도
	float fieldScale;

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
	ofxFloatSlider timeScaleSlider;
	ofxFloatSlider indexScaleSlider;
	ofxFloatSlider fieldScaleSlider;  // <- 새로 추가
	ofxToggle toggle;
	ofxToggle toggleDraw;
	ofxToggle toggleFieldArrows; // force-field 화살표 표시 토글
	ofxToggle toggleFieldDots; // force-field 화살표 표시 토글
	ofxToggle toggleAttractor; // Latoocarfian attractor 그리기 토글
	ofxToggle toggleMainCircle; // 메인 원 표시 토글
	ofxToggle toggleFieldClip;

	// OSC
	ofxOscSender sender;
	ofxOscReceiver receiver;

	vector<AttractorPoint> attractorPoints;
	ofFbo attractorFbo;

	// Collision counting over time window
	float collisionWindowDuration = 0.1f; // 0.1초 윈도우
	float collisionWindowTimer = 0.0f; // dt 누적
	int collisionCountInWindow = 0; // 이 윈도우 동안 충돌 횟수

	// mover 간 충돌 상태를 기억하기 위한 2D 매트릭스
	// moverCollisionState[i][j] == true 이면, 이전 프레임에서 i,j 가 이미 충돌 중이었다는 의미
	std::vector<std::vector<bool>> moverCollisionState;
};
