// #include "AttractorPoint.h"

// int AttractorPoint::count = 0;
// float AttractorPoint::lat_a = 0.f;
// float AttractorPoint::lat_b = 0.f;
// float AttractorPoint::lat_c = 0.f;
// float AttractorPoint::lat_d = 0.f;

// AttractorPoint::AttractorPoint(float x, float y) {
//     pos.set(x, y);
//     radius = 5.0f;
// }

// void AttractorPoint::update() {
//     // float nextX = sin(b * pos.y) + c * sin(b * pos.x);
//     // float nextY = sin(a * pos.x) + d * sin(a * pos.y);

//     float nextX = sin(AttractorPoint::lat_b * pos.y) +
//     AttractorPoint::lat_c * sin(AttractorPoint::lat_b * pos.x);
//     float nextY = sin(AttractorPoint::lat_a * pos.x) +
//     AttractorPoint::lat_d * sin(AttractorPoint::lat_a * pos.y);

//     prevPos = pos;
//     pos.set(nextX, nextY);
//     hasPrev = true;
// }

// void AttractorPoint::draw(bool useLines, ofColor color) {
//     // AttractorPoint::count = AttractorPoint::count % 101;
//     // ofLog() << AttractorPoint::count;
//     // fbo.begin();

//     update();
//     ofPushMatrix();
//     ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
//     ofSetColor(ofColor::red);
//     ofSetLineWidth(5.0);

//     float px = ofMap(pos.x, -2, 2, -ofGetWidth()/2, ofGetWidth()/2);
//     float py = ofMap(pos.y, -2, 2, -ofGetHeight()/2, ofGetHeight()/2);

//     if (useLines && hasPrev) {
//         float prevX = ofMap(prevPos.x, -2, 2, -ofGetWidth()/2, ofGetWidth()/2);
//         float prevY = ofMap(prevPos.y, -2, 2, -ofGetHeight()/2, ofGetHeight()/2);
//         ofDrawLine(prevX, prevY, px, py);
//     } else {
//         ofDrawCircle(px, py, radius);
//     }

//     ofPopMatrix();
//     // fbo.end();
//     AttractorPoint::count++;
// }