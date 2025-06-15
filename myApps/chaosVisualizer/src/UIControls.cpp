// // UIControls.cpp
// #include "UIControls.h"

// void UIControls::setup(float defaultX, float defaultY, int defaultRate) {
//     gui.setup("Latoocarfian Controls");

//     lat_x.set("Initial X", defaultX, -5.0, 5.0);
//     lat_y.set("Initial Y", defaultY, -5.0, 5.0);
//     lat_rate.set("Rate (Hz)", defaultRate, 10, 48000);
//     ampLatoo.set("AMP ON", false);

//     gui.add(lat_x);
//     gui.add(lat_y);
//     gui.add(lat_rate);
//     gui.add(ampLatoo);

//     toggleRect.set(20, 160, 60, 30);  // AMP ON/OFF 버튼의 위치

//     setupListeners();
// }

// void UIControls::setupListeners() {
//     lat_x.addListener([this](float&) {
//         if (onParamChange) onParamChange();
//     });
//     lat_y.addListener([this](float&) {
//         if (onParamChange) onParamChange();
//     });
//     lat_rate.addListener([this](int&) {
//         if (onRateChange) onRateChange();
//     });
//     ampLatoo.addListener([this](bool&) {
//         if (onAmpToggle) onAmpToggle();
//     });
// }

// void UIControls::draw() {
//     gui.draw();
// }

// void UIControls::drawOverlay(int width) {
//     ofSetColor(255);
//     ofDrawBitmapStringHighlight("Latoocarfian", 20, 20);
//     ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 2), 20, 40);

//     ofSetColor(ampLatoo ? ofColor::green : ofColor::gray);
//     ofDrawRectangle(toggleRect);
//     ofSetColor(255);
//     ofDrawBitmapString(ampLatoo ? "AMP ON" : "AMP OFF",
//                        toggleRect.getX() + 5, toggleRect.getY() + 20);
// }

// void UIControls::mousePressed(int x, int y) {
//     if (toggleRect.inside(x, y)) {
//         ampLatoo = !ampLatoo;
//         if (onAmpToggle) onAmpToggle();
//     }
// }
