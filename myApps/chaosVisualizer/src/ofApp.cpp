// ofApp.cpp
#include "ofApp.h"

static const float MAIN_CIRCLE_RADIUS = 400.0f; // 기존 220.0f 에서 확장된 원 경계 반지름

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetCircleResolution(32);
	ofBackground(0);
	sender.setup(HOST, PORT_OUT);
	receiver.setup(PORT_IN);

	width = ofGetWidth();
	height = ofGetHeight();

	lat_x = 2.5;
	lat_y = 0.5;
	lat_a = 1.0;
	lat_b = 3.0;
	lat_c = 0.5;
	lat_d = 0.5;
	lat_rate = 100;
	convergeAmount = 0.f;
	ampLatoo = false;
	seedMass = 0.1f;
	useLines = false;
	drawThings = true;

	attractorLayer.allocate(width, height, GL_RGBA);

	attractorFbo.allocate(width, height, GL_RGBA);
	attractorFbo.begin();
	ofClear(0, 0, 0, 0);
	attractorFbo.end();

	// 초기 AttractorPoint 생성 (예: 1000개)
	for (int i = 0; i < ATTR_ITER_NUM; ++i) {

		float initX = ofRandom(-1, 1);
		float initY = ofRandom(-1, 1);

		// 각각 조금씩 다른 계수로 다양성 부여
		float a = lat_a + ofRandom(-0.1, 0.1);
		float b = lat_b + ofRandom(-0.1, 0.1);
		float c = lat_c + ofRandom(-0.1, 0.1);
		float d = lat_d + ofRandom(-0.1, 0.1);

		attractorPoints.emplace_back(initX, initY, a, b, c, d);
	}

	// get image data
	// Do this after creating AttractorPoint objects
	// ofImage maskImg;
	// maskImg.load("dolphin.png");
	// assignTargetPositionsFromImage(maskImg, attractorPoints, 150, 4);

	// hiddenImg.load("cloud_0301.jpg");
	// hiddenImg.load("dolphin.png");
	// hiddenImg.resize(width, height);

	// 처음에는 아무 Mover 도 없음; 'c' 키로 생성
	controllerMoverIndex = -1;

	// grid = Grid(30, 20, width, height);
	// grid = Grid(60, 40, width, height);
	// grid = Grid(120, 80, width, height);
	// grid.setFromImage(hiddenImg);
	// grid.reset();

	// blackholes.push_back(Blackhole(ofGetWidth() * 2 / 3, ofGetHeight() / 3, 1));

	// 원의 경계 바깥을 둘러싼 링 형태로 72개의 블랙홀 생성
	{
		int numRingBH = 8;
		float R_inner = MAIN_CIRCLE_RADIUS; // 메인 원 반지름
		float ringMargin = 40.0f; // 메인 원보다 얼마나 바깥에 둘 것인지
		float R_outer = R_inner + ringMargin;

		float cx = width * 0.5f;
		float cy = height * 0.5f;

		for (int i = 0; i < numRingBH; ++i) {
			float angleDeg = i * (360.0f / numRingBH);
			float angleRad = ofDegToRad(angleDeg);

			float x = cx + cos(angleRad) * R_outer;
			float y = cy + sin(angleRad) * R_outer;

			// id는 1..72로 부여
			blackholes.emplace_back(x, y, i + 1);
		}
	}

	// UI
	gui.setup("GUI");

	gui.add(fSlider[0].setup("INIT_X", lat_x, -5, 5));
	gui.add(fSlider[1].setup("INIT_Y", lat_y, -5, 5));
	gui.add(iSlider.setup("LAT_RATE", lat_rate, 10, 48000));
	gui.add(fSlider[2].setup("CONVERGE", convergeAmount, 0.0, 1.0));

	// Collision correction factor slider (for Mover-Mover collisions)
	gui.add(correctionSlider.setup("CorrectionFactor", 1.1f, -5.0f, 5.0f));

	fSlider[0].addListener(this, &ofApp::onInitXChanged);
	fSlider[1].addListener(this, &ofApp::onInitYChanged);
	iSlider.addListener(this, &ofApp::onRateChanged);
	fSlider[2].addListener(this, &ofApp::onConvergeChanged);

	// --- Global blackhole force controls ---
	// 1st stage: overall strength range scaling (Perlin output)
	strengthRangeScale = 1.0f;
	gui.add(strengthRangeScaleSlider.setup("Strength Range Scale",
		strengthRangeScale,
		-5.0f, 5.0f));
	strengthRangeScaleSlider.addListener(this, &ofApp::onStrengthRangeScaleChanged);

	// 2nd stage: base (1/r^2) force scaling
	forceBaseScale = 1.0f;
	gui.add(forceBaseScaleSlider.setup("Force Base Scale",
		forceBaseScale,
		-5.0f, 5.0f));
	forceBaseScaleSlider.addListener(this, &ofApp::onForceBaseScaleChanged);

	timeScale = 0.03f;
	indexScale = 0.05f;
	gui.add(timeScaleSlider.setup("Time Scale", timeScale, 0.0f, 0.5f));
	gui.add(indexScaleSlider.setup("Index Scale", indexScale, 0.0f, 0.5f));
	timeScaleSlider.addListener(this, &ofApp::onTimeScaleChanged);
	indexScaleSlider.addListener(this, &ofApp::onIndexScaleChanged);

	gui.add(toggle.setup("Amp On", ampLatoo));
	toggle.addListener(this, &ofApp::onToggleChanged);

	// 블랙홀 그리기 토글
	gui.add(toggleDraw.setup("Draw Blackholes", drawThings));
	toggleDraw.addListener(this, &ofApp::onToggleDrawThings);

	// Latoocarfian attractor(배경) 그리기 토글
	drawAttractor = false;
	gui.add(toggleAttractor.setup("Draw Attractor", drawAttractor));
	toggleAttractor.addListener(this, &ofApp::onToggleAttractor);

	// Toggle for drawing the force-field arrows
	drawFieldArrows = true;
	gui.add(toggleFieldArrows.setup("Field Arrows", drawFieldArrows));
	toggleFieldArrows.addListener(this, &ofApp::onToggleFieldArrows);

	// Toggle for drawing the field dots at arrow tips
	drawFieldDots = false;
	gui.add(toggleFieldDots.setup("Field Dots", drawFieldDots));
	toggleFieldDots.addListener(this, &ofApp::onToggleFieldDots);

	// Initialize collision counting window
	collisionWindowDuration = 0.1f;
	collisionWindowTimer = 0.0f;
	collisionCountInWindow = 0;

	// Init values
	sendLatooInit();
	sendLatooAmpState(ampLatoo);
}

//--------------------------------------------------------------
void ofApp::update() {

	updateParameters();

	// update AttractorPoint objects
	for (auto & pt : attractorPoints) {
		pt.setParams(lat_a, lat_b, lat_c, lat_d);
		pt.convergeAmount = convergeAmount;
		pt.update();
		pt.resetPos();
	}

	// Perlin 노이즈로 각 블랙홀 strength 갱신
	// 하나의 노이즈 값 n(0..1)을 [-maxAbsStrength, +maxAbsStrength] 로 매핑해서
	// 크기와 부호가 함께 변하도록 한다.
	{
		float t = ofGetElapsedTimef();

		float maxAbsStrength = 100.0f; // |strength| 의 최대값

		// 슬라이더에서 1차 스케일 값 읽기
		strengthRangeScale = strengthRangeScaleSlider;

		for (int i = 0; i < (int)blackholes.size(); ++i) {
			float n = ofNoise(t * timeScale, i * indexScale); // 0..1

			// 0..1 -> [-maxAbsStrength, +maxAbsStrength]
			float signedStrength = ofMap(n, 0.0f, 1.0f,
				-maxAbsStrength, maxAbsStrength);

			blackholes[i].strength = signedStrength * strengthRangeScale;
		}
	}

	applyBlackholeForce();

	// Seed remove
	for (int i = seeds.size() - 1; i >= 0; --i) {
		if (seeds[i].update(blackholes, grid, SEED_SIT_THR)) {
			// removeSeedAt(i);
		}
	}

	// 원형 경계 안에서 Mover / movers 튕기기
	ofVec2f center(width / 2.0f, height / 2.0f);
	float R = MAIN_CIRCLE_RADIUS; // 메인 원 반지름
	for (auto & m : movers) {
		m.update();
		m.bounceOnCircleBoundary(center, R);
	}

	// mover 개수가 변했을 수 있으니, 충돌 상태 매트릭스를 movers.size() 에 맞게 리사이즈
	if (moverCollisionState.size() != movers.size()) {
		moverCollisionState.assign(movers.size(), std::vector<bool>(movers.size(), false));
	}

	// movers끼리 간단한 충돌 처리 (GUI에서 correctionFactor 조절)
	for (std::size_t i = 0; i < movers.size(); ++i) {
		for (std::size_t j = i + 1; j < movers.size(); ++j) {

			// 이번 프레임에서의 충돌 여부
			bool isCollidingNow = movers[i].collideWith(movers[j], correctionSlider);

			// 이전 프레임에서의 충돌 상태
			bool wasColliding = moverCollisionState[i][j];

			// "충돌 시작" 이벤트: 이전 프레임에는 안 부딪치다가,
			// 이번 프레임에 처음으로 겹친 경우에만 신호를 보냄
			if (isCollidingNow && !wasColliding) {
				collisionCountInWindow++; // 0.1초 윈도우 카운터도 여기서 증가
				sendMoverCollision(static_cast<int>(i), static_cast<int>(j));
			}

			// 충돌 상태 업데이트
			moverCollisionState[i][j] = isCollidingNow;
		}
	}

	// 0.1초(window) 동안의 충돌 횟수 집계 및 OSC 전송
	{
		float dt = ofGetLastFrameTime(); // 이번 프레임 걸린 시간 (초)
		collisionWindowTimer += dt;

		if (collisionWindowTimer >= collisionWindowDuration) {
			// 누적된 충돌 횟수를 OSC로 전송
			sendCollisionCountWindow(collisionCountInWindow);

			// 윈도우 리셋
			collisionWindowTimer = 0.0f;
			collisionCountInWindow = 0;
		}
	}

	// OSC
	// sendSeedPositions();
	sendSeedVelocity();
	oscReceive();
}

//--------------------------------------------------------------
void ofApp::draw() {
	// hiddenImg.draw(0, 0); // 이미지 그리기

	// grid.display(0);

	// --- 모든 블랙홀들의 합력 방향을 시각화: 화면 전체에 화살표 필드 ---
	{
		ofPushStyle();
		ofSetLineWidth(2.0f);

		int spacing = 10; // 화살표 간격 (픽셀)
		float fieldScale = 900000.0f; // 힘 → 픽셀 길이 스케일
		float maxLenFactor = 1.0f; // 한 셀 안에서 최대 길이 비율

		for (int gy = spacing / 2; gy < height; gy += spacing) {
			for (int gx = spacing / 2; gx < width; gx += spacing) {

				ofVec2f pos(gx, gy);
				ofVec2f totalForce(0, 0);

				// 이 지점에서의 블랙홀 합력 계산
				for (auto & b : blackholes) {
					ofVec2f dir = b.pos - pos;
					float distSq = dir.lengthSquared();
					float minDist = 1.0f; // 최소 거리
					if (distSq < minDist * minDist) {
						distSq = minDist * minDist;
					}
					if (distSq > 0.0001f) { // 0 나누기 방지
						dir.normalize();
						float base = (10.0f * forceBaseScale) / distSq; // 1/r^2 기본 힘에 글로벌 스케일 적용
						float s = b.strength; // Perlin 노이즈로 제어된 개별 블랙홀 힘
						totalForce += dir * base * s;
					}
				}

				if (totalForce.lengthSquared() > 0.0f) {
					float forceMag = totalForce.length();

					// 길이 스케일링: 힘의 크기를 픽셀 길이로 변환
					float maxLen = spacing * maxLenFactor; // 주위 화살표와 안 겹치도록
					float len = forceMag * fieldScale;
					len = ofClamp(len, 0.0f, maxLen);

					// 애니메이션: 길이를 살짝 펄싱
					float t = ofGetElapsedTimef();
					float pulse = 0.8f + 0.2f * sin(t * 2.0f);
					// len *= pulse;

					ofVec2f dirNorm = totalForce.getNormalized();
					ofVec2f endPos = pos + dirNorm * len;

					// 1) 화살표 (선 + 머리)는 drawFieldArrows 가 true 일 때만
					if (drawFieldArrows) {
						// 본체 선
						ofSetColor(0, 80, 100);
						ofDrawLine(pos, endPos);

						// 화살표 머리
						float headSize = 6.0f;
						ofVec2f perp(-dirNorm.y, dirNorm.x);
						ofVec2f tip = endPos;
						ofVec2f left = endPos - dirNorm * headSize + perp * (headSize * 0.5f);
						ofVec2f right = endPos - dirNorm * headSize - perp * (headSize * 0.5f);
						ofDrawTriangle(tip, left, right);
					}

					// 2) 화살표 끝의 하얀 동그라미는 drawFieldDots 가 true 일 때만
					if (drawFieldDots) {
						ofSetColor(255, 255, 255, drawFieldArrows ? 120 : 200);
						float radius = drawFieldArrows ? 3.5f : 1.0f;
						ofDrawCircle(endPos, radius);
					}
				}
			}
		}

		ofPopStyle();
	}

	for (std::size_t i = 0; i < movers.size(); ++i) {
		auto & m = movers[i];
		m.draw(false);

		// 컨트롤러 Mover 인 경우 노란색 원으로 강조 표시
		if ((int)i == controllerMoverIndex) {
			ofPushStyle();
			ofNoFill();
			ofSetColor(255, 255, 0);
			ofSetLineWidth(2.0f);
			float highlightRadius = m.diameter * 0.5f + 4.0f; // 본체보다 약간 크게
			ofDrawCircle(m.pos, highlightRadius);
			ofPopStyle();
		}
	}

	for (auto & s : seeds) {
		s.display();
	}

	if (drawThings) {
		for (auto & b : blackholes) {
			b.display();
		}
	}

	if (drawAttractor) {

		ofPushStyle(); // ← 추가
		ofFill(); // 또는 ofNoFill() - 필요에 따라
		ofSetColor(255, 255, 255, 255); // 완전 불투명 흰색

		renderAttractor();

		// draw AttractorPoint objects - for convergence
		attractorFbo.begin();
		ofClear(0, 0, 0, 0);

		ofPushMatrix();
		ofTranslate(width / 2, height / 2);
		ofSetColor(255);

		for (auto & pt : attractorPoints) {
			pt.draw(useLines);
		}

		ofPopMatrix();

		attractorFbo.end();
		attractorFbo.draw(0, 0);
		ofPopStyle();

	}

	// 원형 경계 시각화
	ofPushStyle();
	ofNoFill();
	ofSetColor(180);
	ofSetLineWidth(2.0f);
	float R = MAIN_CIRCLE_RADIUS;
	ofDrawCircle(width / 2.0f, height / 2.0f, R);
	ofPopStyle();
	// check for the data from the image
	// drawTargetPositions(attractorPoints);

	drawUI();

	ofSetColor(0, 255, 0);
	ofDrawCircle(width / 2.0f, height / 2.0f, 5); // 블랙홀 링 기준 중심
	ofSetColor(255, 0, 0);
	ofDrawCircle(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, 3); // 현재 창 기준 중심

	// ofLog() << "draw is done!";
}

void ofApp::updateParameters() {
	// 어떤 mover 를 참조할지: controllerMoverIndex 로 선택
	if (movers.empty() || controllerMoverIndex < 0 || controllerMoverIndex >= (int)movers.size()) {
		return; // 아직 컨트롤러가 없으면 파라미터를 갱신하지 않음
	}

	const Mover & controller = movers[controllerMoverIndex];

	lat_a = ofMap(controller.pos.x, 0, width, 0.2, 3.0);
	lat_b = ofMap(controller.pos.y, 0, height, 0.2, 3.0);
	lat_c = ofMap(controller.pos.x, 0, width, 0.5, 1.5);
	lat_d = ofMap(controller.pos.y, 0, height, 0.5, 1.5);

	if (ampLatoo) {
		sendLatooParams();
	}
}

// Applay force from nearest blackhole
// void ofApp::applyBlackholeForce() {
// 	// 모든 mover에 대해 블랙홀 힘 적용
// 	for (auto & m : movers) {
// 		Blackhole * nearest = nullptr;
// 		float minDist = std::numeric_limits<float>::max();

// 		for (auto & b : blackholes) {
// 			float d = ofDist(m.pos.x, m.pos.y, b.pos.x, b.pos.y);
// 			if (d < minDist) {
// 				minDist = d;
// 				nearest = &b;
// 			}
// 		}

// 		if (nearest != nullptr) {
// 			ofVec2f force = nearest->pos - m.pos;
// 			force.normalize();
// 			force *= 0.2;
// 			m.applyForce(force);
// 		}
// 	}
// }

// Apply summed force of all blackholes (with Perlin-controlled strength)
void ofApp::applyBlackholeForce() {
	for (auto & m : movers) {

		ofVec2f totalForce(0, 0);

		for (auto & b : blackholes) {

			ofVec2f dir = b.pos - m.pos;
			float distSq = dir.lengthSquared();
			float minDist = 1.0f; // 최소 거리
			if (distSq < minDist * minDist) {
				distSq = minDist * minDist;
			}
			if (distSq > 0.0001f) { // 0 나누기 방지
				dir.normalize();
				// 기본 1/r^2 에 각 블랙홀의 strength 를 곱해줌
				float base = (10.0f * forceBaseScale) / distSq; // 2차 글로벌 스케일
				float s = b.strength;
				totalForce += dir * base * s;
			}
		}

		m.applyForce(totalForce);
	}
}

void ofApp::renderAttractor() {

	attractorLayer.begin();
	ofPushStyle();
	ofClear(0, 0, 0, 0);
	ofPushMatrix();
	ofTranslate(width / 2, height / 2);
	ofSetLineWidth(1.5);
	ofSetColor(255);
	ofFill();

	float x = lat_x, y = lat_y;
	float prevX = 0, prevY = 0;
	bool isFirst = true;

	for (int i = 0; i < ATTR_ITER_NUM; ++i) {
		float nextX = sin(lat_b * y) + lat_c * sin(lat_b * x);
		float nextY = sin(lat_a * x) + lat_d * sin(lat_a * y);
		float px = ofMap(nextX, -2, 2, -width / 2, width / 2);
		float py = ofMap(nextY, -2, 2, -height / 2, height / 2);

		if (useLines) {
			if (!isFirst) ofDrawLine(prevX, prevY, px, py);
		} else {
			// ofDrawCircle(px, py, ATTR_RAD + (ampFromSC * 10));
			ofDrawCircle(px, py, ATTR_RAD);
		}

		isFirst = false;
		prevX = px;
		prevY = py;
		x = nextX;
		y = nextY;
	}

	ofPopMatrix();
	ofPopStyle();
	attractorLayer.end();
	attractorLayer.draw(0, 0);
}

void ofApp::updateGridFromAmp() {
	float normAmp = ofClamp(ampFromSC, 0.0f, 1.0f); // 0~1 범위로 정규화

	// 모든 mover 위치 기준으로 셀에 값을 매핑
	for (auto & m : movers) {
		grid.setValueAt(m.pos.x, m.pos.y, normAmp * 10);
	}

	// 예: 주변 3x3 영역 셀에도 값 퍼뜨리기 (부드러운 반응)를 쓰고 싶다면,
	// 각 mover에 대해 아래 루프를 돌릴 수 있음 (현재는 주석 처리):
	// for (auto & m : movers) {
	// 	for (int dx = -1; dx <= 1; dx++) {
	// 		for (int dy = -1; dy <= 1; dy++) {
	// 			float x = m.pos.x + dx * grid.cellW;
	// 			float y = m.pos.y + dy * grid.cellH;
	// 			grid.setValueAt(x, y, normAmp * 0.7f); // 중심보다 약하게
	// 		}
	// 	}
	// }

	// (선택) Reveal 형태를 쓰고 싶다면 아래처럼:
	// for (auto & m : movers) {
	// 	grid.revealValue(m.pos.x, m.pos.y);
	// }
}

void ofApp::assignTargetPositionsFromImage(const ofImage & img,
	std::vector<AttractorPoint> & points,
	float threshold, int step) {
	vector<ofVec2f> targetPositions;

	for (int y = 0; y < img.getHeight(); y += step) {
		for (int x = 0; x < img.getWidth(); x += step) {
			float brightness = img.getColor(x, y).getBrightness();
			if (brightness < threshold) {
				float normX = ofMap(x, 0, img.getWidth(), -1, 1);
				float normY = ofMap(y, 0, img.getHeight(), -1, 1);
				targetPositions.emplace_back(normX, normY);
			}
		}
	}

	// 새로운 C++ 방식: std::shuffle + 랜덤 엔진
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(targetPositions.begin(), targetPositions.end(), g);

	for (int i = 0; i < points.size(); i++) {
		if (i < targetPositions.size()) {
			points[i].targetPos = targetPositions[i];
		}
	}
}

void ofApp::drawTargetPositions(const std::vector<AttractorPoint> & points) {
	ofPushMatrix();
	ofTranslate(width / 2, height / 2); // 중심 기준으로

	ofSetColor(255, 0, 0, 100); // 빨간색, 투명도 약간
	for (const auto & pt : points) {
		float x = ofMap(pt.targetPos.x, -1, 1, -width / 2, width / 2);
		float y = ofMap(pt.targetPos.y, -1, 1, -height / 2, height / 2);
		ofDrawCircle(x, y, 2); // 작고 연한 점
	}

	ofPopMatrix();
}

void ofApp::drawUI() {
	// UI
	gui.draw();

	// ---- Debug Info: lat params & FPS ----
	ofSetColor(255);
	ofDrawBitmapStringHighlight("Latoocarfian Parameters:", 20, 420);
	ofDrawBitmapStringHighlight("lat_a: " + ofToString(lat_a, 2), 20, 440);
	ofDrawBitmapStringHighlight("lat_b: " + ofToString(lat_b, 2), 20, 460);
	ofDrawBitmapStringHighlight("lat_c: " + ofToString(lat_c, 2), 20, 480);
	ofDrawBitmapStringHighlight("lat_d: " + ofToString(lat_d, 2), 20, 500);
	ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate(), 1), 20, 520);
	ofDrawBitmapStringHighlight("Seeds: " + ofToString(seeds.size()), 20, 540);
	ofDrawBitmapStringHighlight("Seed mass: " + ofToString(seedMass, 3), 20, 560);
	ofDrawBitmapStringHighlight("Movers: " + ofToString(movers.size()), 20, 580);
}

void ofApp::onInitXChanged(float & val) {
	lat_x = val;
	sendLatooInit();
}

void ofApp::onInitYChanged(float & val) {
	lat_y = val;
	sendLatooInit();
}

void ofApp::onRateChanged(int & val) {
	lat_rate = val;
	sendLatooRate();
}

void ofApp::onConvergeChanged(float & val) {
	convergeAmount = val;
}

void ofApp::onStrengthRangeScaleChanged(float & val) {
	strengthRangeScale = val;
}

void ofApp::onForceBaseScaleChanged(float & val) {
	forceBaseScale = val;
}

void ofApp::onTimeScaleChanged(float & val) {
	timeScale = val;
}

void ofApp::onIndexScaleChanged(float & val) {
	indexScale = val;
}

void ofApp::onToggleChanged(bool & val) {
	ampLatoo = val;

	sendLatooAmpState(ampLatoo);

	if (ampLatoo) {
		sendLatooParams();
		sendLatooInit();
		sendLatooRate();
	}
}

void ofApp::onToggleDrawThings(bool & val) {
	drawThings = val;
}

void ofApp::onToggleFieldArrows(bool & val) {
	drawFieldArrows = val;
}

void ofApp::onToggleFieldDots(bool & val) {
	drawFieldDots = val;
}

void ofApp::onToggleAttractor(bool & val) {
	drawAttractor = val;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'm') {
		ofLog() << "Line mode toggle: " << useLines;
		useLines = !useLines;
	}

	if (key == 's') {
		// 새 Seed를 현재 컨트롤러 mover 로부터 생성
		if (!movers.empty() && controllerMoverIndex >= 0 && controllerMoverIndex < (int)movers.size()) {
			Seed newSeed = movers[controllerMoverIndex].releaseSeed();
			newSeed.mass = seedMass;
			seeds.push_back(newSeed);
		} else {
			ofLogNotice() << "No controller mover set; press 'c' to create one first.";
		}
	}

	// z/x 키로 Seed 질량 조절
	if (key == 'z') {
		seedMass = std::max(0.01f, seedMass - 0.01f);
		for (auto & s : seeds) {
			s.mass = seedMass;
		}
		ofLogNotice() << "Seed mass decreased: " << seedMass;
	}
	if (key == 'x') {
		seedMass = std::min(2.0f, seedMass + 0.01f);
		for (auto & s : seeds) {
			s.mass = seedMass;
		}
		ofLogNotice() << "Seed mass increased: " << seedMass;
	}

	if (key >= '1' && key <= '9') {
		int number = key - '0'; // '1' → 1

		// 이미 존재하는지 확인
		auto it = std::find_if(blackholes.begin(), blackholes.end(),
			[number](const Blackhole & b) {
				return b.id == number;
			});

		if (it != blackholes.end()) {
			ofLogNotice() << "Removing Blackhole #" << number;
			blackholes.erase(it);
		} else {
			float bx = ofGetMouseX();
			float by = ofGetMouseY();
			ofLogNotice() << "Adding Blackhole #" << number;
			blackholes.emplace_back(bx, by, number);
		}
	}

	// 'c' 키: 새로운 Mover 추가
	if (key == 'c') {
		ofVec2f center(width / 2.0f, height / 2.0f);
		float R = MAIN_CIRCLE_RADIUS;
		Mover m(width / 2, height / 2, 5);
		// 원 내부의 랜덤 위치로 이동
		float angle = ofRandom(TWO_PI);
		float rad = ofRandom(R);
		m.pos.set(center.x + cos(angle) * rad,
			center.y + sin(angle) * rad);
		movers.push_back(m);

		// 첫 번째로 생성된 mover 를 controller 로 사용
		if (controllerMoverIndex < 0) {
			controllerMoverIndex = static_cast<int>(movers.size()) - 1;
		}
	}

	// 'v' 키: 마지막 Mover 하나 제거
	if (key == 'v') {
		if (!movers.empty()) {
			movers.pop_back();
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	overToggle = false;
	overSlider = false;

	// if (x > width - 70 && x < width - 10 && y > 10 && y < 40) {
	// 	overToggle = true;
	// 	ampLatoo = !ampLatoo;
	// 	// sendAmpState();
	// }

	if (fSlider[0].getShape().inside(x, y) || fSlider[1].getShape().inside(x, y) || fSlider[2].getShape().inside(x, y) || toggle.getShape().inside(x, y)) {
		overSlider = true;
	}

	// // 슬라이더나 토글 버튼이 아닌 경우에만 clickTarget 갱신
	// if (!overToggle && !overSlider) {
	// 	clickTarget = new PVector(x, y);
	// }

	for (auto & b : blackholes) {
		if (b.isMouseOver(ofGetMouseX(), ofGetMouseY())) {
			draggingBlackhole = &b;
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	isDragging = true;
	if (overToggle) return;

	if (draggingBlackhole != nullptr) {
		draggingBlackhole->moveTo(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	draggingBlackhole = nullptr;
	isDragging = false;
}

void ofApp::sendLatooParams() {
	ofxOscMessage msg;
	msg.setAddress("/latoo");
	msg.addFloatArg(lat_a);
	msg.addFloatArg(lat_b);
	msg.addFloatArg(lat_c);
	msg.addFloatArg(lat_d);
	sender.sendMessage(msg, false);
}

void ofApp::sendLatooInit() {
	ofxOscMessage msg;
	msg.setAddress("/init/latoo");
	msg.addFloatArg(lat_x);
	msg.addFloatArg(lat_y);
	sender.sendMessage(msg, false);
}

void ofApp::sendLatooRate() {
	ofxOscMessage msg;
	msg.setAddress("/rate/latoo");
	msg.addIntArg(lat_rate);
	sender.sendMessage(msg, false);
}

void ofApp::sendLatooAmpState(bool isOn) {
	ofxOscMessage msg;
	msg.setAddress("/latoo/mul");
	msg.addIntArg(isOn);
	sender.sendMessage(msg, false);
}

void ofApp::sendShutdown() {
	ofxOscMessage msg;
	msg.setAddress("/shutdown");
	sender.sendMessage(msg, false);
}

void ofApp::sendSeedPositions() {
	for (auto & seed : seeds) {
		ofxOscMessage msg;
		msg.setAddress("/seed/pos");
		msg.addIntArg(seed.id);
		msg.addFloatArg(seed.pos.x);
		msg.addFloatArg(seed.pos.y);
		sender.sendMessage(msg, false);
	}
}

void ofApp::sendSeedVelocity() {
	for (auto & seed : seeds) {
		ofxOscMessage msg;
		msg.setAddress("/seed/vel");
		msg.addIntArg(seed.id);
		msg.addFloatArg(seed.vel.x);
		msg.addFloatArg(seed.vel.y);
		sender.sendMessage(msg, false);
	}
}

void ofApp::sendMoverCollision(int idxA, int idxB) {
	if (idxA < 0 || idxB < 0 || idxA >= (int)movers.size() || idxB >= (int)movers.size()) {
		return;
	}

	ofxOscMessage msg;
	msg.setAddress("/mover/collision");
	msg.addIntArg(idxA);
	msg.addIntArg(idxB);

	// 현재 mover 개수 추가
	msg.addIntArg(static_cast<int>(movers.size()));

	msg.addFloatArg(movers[idxA].pos.x);
	msg.addFloatArg(movers[idxA].pos.y);
	msg.addFloatArg(movers[idxB].pos.x);
	msg.addFloatArg(movers[idxB].pos.y);
	sender.sendMessage(msg, false);
}

void ofApp::sendCollisionCountWindow(int count) {
	ofxOscMessage msg;
	msg.setAddress("/mover/collision_count");
	msg.addIntArg(count); // 0.1초 동안 발생한 충돌 횟수
	sender.sendMessage(msg, false);
}

void ofApp::removeSeedAt(int index) {
	int id = seeds[index].id;

	// OSC 메시지 전송
	ofxOscMessage msg;
	msg.setAddress("/seed/remove");
	msg.addIntArg(id);
	sender.sendMessage(msg, false); // sender는 ofxOscSender 객체

	seeds.erase(seeds.begin() + index);
}

void ofApp::oscReceive() {
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage msg;
		receiver.getNextMessage(msg);

		// ofLog() << "Received OSC: " << msg.getAddress();

		if (msg.getAddress() == "/amp") {
			ampFromSC = msg.getArgAsFloat(0);
			updateGridFromAmp();
			// ofLog() << "Received amp value: " << amp;
		}

		// 다른 주소도 이와 같이 추가 가능
	}
}

void ofApp::exit() {
	sendShutdown();
}
