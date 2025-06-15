// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetCircleResolution(32);
	ofBackground(0);
	sender.setup(HOST, PORT_OUT);

	width = ofGetWidth();
	height = ofGetHeight();

	lat_x = 2.5;
	lat_y = 0.5;
	lat_a = 1.0;
	lat_b = 3.0;
	lat_c = 0.5;
	lat_d = 0.5;
	ampLatoo = false;
	useLines = false;
	ampFromSC = 0.0f;

	mover = Mover(ofGetWidth() / 2, ofGetHeight() / 2, 5);

	hiddenImg.load("cloud_0301.jpg");
	hiddenImg.resize(ofGetWidth(), ofGetHeight());

	grid = Grid(60, 40, ofGetWidth(), ofGetHeight());
	grid.setFromImage(hiddenImg);
	grid.reset();

	attractorLayer.allocate(width, height, GL_RGBA);

	blackholes.push_back(Blackhole(ofGetWidth() * 2 / 3, ofGetHeight() / 3, 1));

	// UI
	gui.setup("GUI");

	gui.add(fSlider[0].setup("INIT_X", init_x, -5, 5));
	gui.add(fSlider[1].setup("INIT_Y", init_y, -5, 5));
	gui.add(iSlider.setup("RATE", rate, 10, 48000));
	fSlider[0].addListener(this, &ofApp::onInitXChanged);
	fSlider[1].addListener(this, &ofApp::onInitYChanged);
	iSlider.addListener(this, &ofApp::onRateChanged);

	gui.add(toggle.setup("Amp On", true));
	toggle.addListener(this, &ofApp::onToggleChanged);

	sendLatooInit();
	sendLatooAmpState(ampLatoo);
}

//--------------------------------------------------------------
void ofApp::update() {
	mover.update();
	updateParameters();
	applyBlackholeForce();

	for (int i = seeds.size() - 1; i >= 0; --i) {
		Blackhole * nearest = nullptr;
		float minDist = FLT_MAX;

		for (auto & b : blackholes) {
			float d = ofDist(seeds[i].pos.x, seeds[i].pos.y, b.pos.x, b.pos.y);
			if (d < minDist) {
				minDist = d;
				nearest = &b;
			}

			if (seeds[i].isCollidingWith(b)) {
				seeds.erase(seeds.begin() + i);
				goto next_seed;
			}
		}

		if (nearest) seeds[i].attract(nearest->pos);
		seeds[i].update();

		if (seeds[i].revealGridCell(grid, 5)) {
			seeds.erase(seeds.begin() + i);
			continue;
		}

		if (seeds[i].isOffscreen()) {
			seeds.erase(seeds.begin() + i);
		}

	next_seed:;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	grid.display();

	attractorLayer.begin();
	ofClear(0, 0, 0, 0);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetLineWidth(1.5);
	ofSetColor(255);

	float x = lat_x, y = lat_y;
	float prevX = 0, prevY = 0;
	bool isFirst = true;

	for (int i = 0; i < 1000; ++i) {
		float nextX = sin(lat_b * y) + lat_c * sin(lat_b * x);
		float nextY = sin(lat_a * x) + lat_d * sin(lat_a * y);
		float px = ofMap(nextX, -2, 2, -ofGetWidth() / 2, ofGetWidth() / 2);
		float py = ofMap(nextY, -2, 2, -ofGetHeight() / 2, ofGetHeight() / 2);

		if (useLines) {
			if (!isFirst) ofDrawLine(prevX, prevY, px, py);
		} else {
			ofDrawCircle(px, py, 1);
		}

		isFirst = false;
		prevX = px;
		prevY = py;
		x = nextX;
		y = nextY;
	}

	ofPopMatrix();
	attractorLayer.end();

	mover.draw();
	for (auto & s : seeds)
		s.display();
	for (auto & b : blackholes)
		b.display();

	attractorLayer.draw(0, 0);

	// UI
	gui.draw();

	// ---- Debug Info: lat params & FPS ----
	ofSetColor(255);
	ofDrawBitmapStringHighlight("Latoocarfian Parameters:", 20, 200);
	ofDrawBitmapString("lat_a: " + ofToString(lat_a, 2), 20, 220);
	ofDrawBitmapString("lat_b: " + ofToString(lat_b, 2), 20, 240);
	ofDrawBitmapString("lat_c: " + ofToString(lat_c, 2), 20, 260);
	ofDrawBitmapString("lat_d: " + ofToString(lat_d, 2), 20, 280);
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 1), 20, 300);
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
    Blackhole* nearest = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (auto& b : blackholes) {
        float d = ofDist(mover.pos.x, mover.pos.y, b.pos.x, b.pos.y);
        if (d < minDist) {
            minDist = d;
            nearest = &b;
        }
        b.display();  // 만약 display()가 const 함수면, b를 const 참조로 받아야 함
    }

    if (nearest != nullptr) {
        ofVec2f force = nearest->pos - mover.pos;
        force.normalize();
        force *= 0.2;
        mover.applyForce(force);
    }
}



void ofApp::onInitXChanged(float & val) {
	init_x = val;
	sendLatooInit();
}

void ofApp::onInitYChanged(float & val) {
	init_y = val;
	sendLatooInit();
}

void ofApp::onRateChanged(int & val) {
	rate = val;
	sendLatooRate();
}

void ofApp::onToggleChanged(bool & val) {
	ampLatoo = val;

	sendLatooAmpState(ampLatoo);

	if (!ampLatoo) {
		sendLatooParams();
		sendLatooInit();
		sendLatooRate();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'm') {
		ofLog() << "Line mode toggle: " << useLines;
		useLines = !useLines;
	}
	if (key == 's') {
		ofLog() << "Seed released!";
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
	ofxOscMessage msg = ofxOscMessage("/latoo");
	msg.addFloatArg(lat_a);
	msg.addFloatArg(lat_b);
	msg.addFloatArg(lat_c);
	msg.addFloatArg(lat_d);
	sender.sendMessage(msg, false);
}

void ofApp::sendLatooInit() {
	ofxOscMessage msg = ofxOscMessage("/init/latoo");
	msg.addFloatArg(lat_x);
	msg.addFloatArg(lat_y);
	sender.send(msg, false);
}

void ofApp::sendLatooRate() {
	ofxOscMessage msg = ofxOscMessage("/rate/latoo");
	msg.addIntArg(rate);
	sender.send(msg, false);
}

void ofApp::sendLatooAmpState(bool isOn) {
	ofxOscMessage msg = ofxOscMessage("/latoo/mul");
	msg.addIntArg(isOn);
	sender.send(msg, false);


}

void ofApp::sendShutdown() {
	ofxOscMessage msg = ofxOscMessage("/shutdown");
	sender.send(msg, false);
}
