// ofApp.cpp
#include "ofApp.h"

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
	ampLatoo = false;
	useLines = false;
	drawThings = true;

	attractorLayer.allocate(width, height, GL_RGBA);

	hiddenImg.load("cloud_0301.jpg");
	hiddenImg.resize(width, height);

	mover = Mover(ofGetWidth() / 2, ofGetHeight() / 2, 5);

	// grid = Grid(60, 40, width, height);
	grid = Grid(120, 80, width, height);
	grid.setFromImage(hiddenImg);
	grid.reset();

	blackholes.push_back(Blackhole(ofGetWidth() * 2 / 3, ofGetHeight() / 3, 1));

	// UI
	gui.setup("GUI");

	gui.add(fSlider[0].setup("INIT_X", lat_x, -5, 5));
	gui.add(fSlider[1].setup("INIT_Y", lat_y, -5, 5));
	gui.add(iSlider.setup("LAT_RATE", lat_rate, 10, 48000));
	fSlider[0].addListener(this, &ofApp::onInitXChanged);
	fSlider[1].addListener(this, &ofApp::onInitYChanged);
	iSlider.addListener(this, &ofApp::onRateChanged);

	gui.add(toggle.setup("Amp On", ampLatoo));
	toggle.addListener(this, &ofApp::onToggleChanged);

	gui.add(toggleDraw.setup("Draw things", drawThings));
	toggleDraw.addListener(this, &ofApp::onToggleDrawThings);


	// Init values
	sendLatooInit();
	sendLatooAmpState(ampLatoo);
}

//--------------------------------------------------------------
void ofApp::update() {
	mover.update();
	updateParameters();
	applyBlackholeForce();

	// Seed remove
	for (int i = seeds.size() - 1; i >= 0; --i) {
		if (seeds[i].update(blackholes, grid, SEED_SIT_THR)) {
			// removeSeedAt(i);
			// seeds.erase(seeds.begin() + i);
		}
	}

	// OSC
	// sendSeedPositions();
	sendSeedVelocity();
	oscReceive();
}

//--------------------------------------------------------------
void ofApp::draw() {
	hiddenImg.draw(0, 0); // 이미지 그리기

	grid.display(0);

	mover.draw(true);
	for (auto & s : seeds)
		s.display();

	if (drawThings)
	{
		for (auto & b : blackholes)
			b.display();
	}

	renderAttractor();

	// UI
	gui.draw();

	// ---- Debug Info: lat params & FPS ----
	ofSetColor(255);
	ofDrawBitmapStringHighlight("Latoocarfian Parameters:", 20, 200);
	ofDrawBitmapStringHighlight("lat_a: " + ofToString(lat_a, 2), 20, 220);
	ofDrawBitmapStringHighlight("lat_b: " + ofToString(lat_b, 2), 20, 240);
	ofDrawBitmapStringHighlight("lat_c: " + ofToString(lat_c, 2), 20, 260);
	ofDrawBitmapStringHighlight("lat_d: " + ofToString(lat_d, 2), 20, 280);
	ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate(), 1), 20, 300);
	ofDrawBitmapStringHighlight("Seeds: " + ofToString(seeds.size()), 20, 320);
}

void ofApp::updateParameters() {
	lat_a = ofMap(mover.pos.x, 0, width, 0.2, 3.0);
	lat_b = ofMap(mover.pos.y, 0, height, 0.2, 3.0);
	lat_c = ofMap(mover.pos.x, 0, width, 0.5, 1.5);
	lat_d = ofMap(mover.pos.y, 0, height, 0.5, 1.5);

	if (ampLatoo) {
		sendLatooParams();
	};
}

void ofApp::applyBlackholeForce() {
	Blackhole * nearest = nullptr;
	float minDist = std::numeric_limits<float>::max();

	for (auto & b : blackholes) {
		float d = ofDist(mover.pos.x, mover.pos.y, b.pos.x, b.pos.y);
		if (d < minDist) {
			minDist = d;
			nearest = &b;
		}
		// b.display(); // 만약 display()가 const 함수면, b를 const 참조로 받아야 함
	}

	if (nearest != nullptr) {
		ofVec2f force = nearest->pos - mover.pos;
		force.normalize();
		force *= 0.2;
		mover.applyForce(force);
	}
}

void ofApp::renderAttractor() {

	attractorLayer.begin();
	ofClear(0, 0, 0, 0);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetLineWidth(1.5);
	ofSetColor(255);

	float x = lat_x, y = lat_y;
	float prevX = 0, prevY = 0;
	bool isFirst = true;

	for (int i = 0; i < ATTR_ITER_NUM; ++i) {
		float nextX = sin(lat_b * y) + lat_c * sin(lat_b * x);
		float nextY = sin(lat_a * x) + lat_d * sin(lat_a * y);
		float px = ofMap(nextX, -2, 2, -ofGetWidth() / 2, ofGetWidth() / 2);
		float py = ofMap(nextY, -2, 2, -ofGetHeight() / 2, ofGetHeight() / 2);

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
	attractorLayer.end();
	attractorLayer.draw(0, 0);
}

void ofApp::updateGridFromAmp() {
	// float normAmp = ofClamp(ampFromSC, 0.0f, 1.0f); // 0~1 범위로 정규화

	// 예: mover 위치 기준으로 셀에 값을 매핑
	// grid.setValueAt(mover.pos.x, mover.pos.y, normAmp);

	// 예: 주변 3x3 영역 셀에도 값 퍼뜨리기 (부드러운 반응)
	// for (int dx = -1; dx <= 1; dx++) {
	// 	for (int dy = -1; dy <= 1; dy++) {
	// 		float x = mover.pos.x + dx * grid.cellW;
	// 		float y = mover.pos.y + dy * grid.cellH;
	// 		grid.setValueAt(x, y, normAmp * 0.7f); // 중심보다 약하게
	// 	}
	// }

	// (선택) Reveal 형태를 쓰고 싶다면 아래처럼:
	grid.revealValue(mover.pos.x, mover.pos.y);
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
	ofLog() << drawThings;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'm') {
		ofLog() << "Line mode toggle: " << useLines;
		useLines = !useLines;
	}
	if (key == 's') {
		// ofLog() << "Seed released!";
		seeds.push_back(mover.releaseSeed());
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
