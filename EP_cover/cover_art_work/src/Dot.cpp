#include "Dot.hpp"
#include <iostream>

// 생성자 구현
//Dot::Dot(float x, float y, float r) : posx(x), posy(y), radius(r) {}
Dot::Dot(
         std::mt19937& gen,
         std::uniform_real_distribution<float>& dist,
         ofVec2f pos,
         float r
         ) : randGen(gen), randDist(dist), position(pos), radius(r)
{
    float randomValue = randDist(randGen);

    angle = TWO_PI/3;
    radius = 120.f + (randomValue * 150.f);
    rotAngle = randDist(randGen) * PI;
    
    int numSeg = ofRandom(4, 7);
    float amp = 10.f + (randDist(randGen) * 10.f);
    
    createWavyTriangle(ofVec2f(0, 0), numSeg, amp);

}

// 멤버 함수 구현
void Dot::printInfo() const {
//    std::cout << "Position: (" << posx << ", " << posy << ")" << std::endl;
    std::cout << "Position: (" << position.x << ", " << position.y << ")" << std::endl;
    std::cout << "Radius: " << radius << std::endl;
}

ofVec2f Dot::getPosition()
{
    return position;
}

float Dot::getRadius()
{
    return radius;
}

void Dot::draw()
{
    
//    ofSetColor(255, 0, 100);
//    ofFill();
//    ofDrawEllipse(position.x, position.y, radius, radius);
    
    // 기준 위치 표시
//    ofDrawEllipse(position.x, position.y, 10, 10);
    
    ofPushMatrix();
//    
    ofTranslate(position.x, position.y);
    ofRotateZRad(rotAngle);
    
    ofSetColor(255, 100, 100);
    trianglePath.draw();
//    mesh.draw();
    ofPopMatrix();
}


// 두 점 사이를 N개의 구불구불한 선으로 나누는 함수
ofPath Dot::createWavyPath(ofVec3f start, ofVec3f end, int numSegments, float amplitude)
{
    ofPath path;
    
    // 두 점 사이의 벡터 계산
    ofVec3f direction = end - start;
    
    // 각 세그먼트의 길이
    ofVec3f segment = direction / numSegments;
    
    // 첫 번째 점을 시작점으로 추가
    path.moveTo(start);
    
    // 중간의 각 세그먼트에 랜덤한 노이즈 추가
    for (int i = 1; i < numSegments; i++) {
        // 세그먼트에 따른 중간 점 계산
        ofVec3f currentPoint = start + segment * i;
        
        // 구불구불하게 만들기 위해 노이즈 추가 (X, Y 방향)
        float noiseX = ofRandom(-amplitude, amplitude);
        float noiseY = ofRandom(-amplitude, amplitude);
        currentPoint.x += noiseX;
        currentPoint.y += noiseY;
        
        path.lineTo(currentPoint);  // 선을 구불구불하게 이어줌
    }
    
    // 마지막 점을 추가
    path.lineTo(end);
   
    return path;
}


// 삼각형의 각 변을 구불구불한 선으로 나누는 함수
void Dot::createWavyTriangle(ofVec2f center, int numSegments, float amplitude)
{
    // 삼각형 꼭짓점 설정
    ofVec2f vertex1 = center + ofVec2f(radius * cos(angle * 0), radius * sin(angle * 0));
    ofVec2f vertex2 = center + ofVec2f(radius * cos(angle * 1), radius * sin(angle * 1));
    ofVec2f vertex3 = center + ofVec2f(radius * cos(angle * 2), radius * sin(angle * 2));
 
    // 각 변을 구불구불한 선으로 만듦
    ofPath side1 = createWavyPath(vertex1, vertex2, numSegments, amplitude);
    ofPath side2 = createWavyPath(vertex2, vertex3, numSegments, amplitude);
    ofPath side3 = createWavyPath(vertex3, vertex1, numSegments, amplitude);
    
        // 각 변을 하나로 합침
    trianglePath = ofPath();
    
     
    // 선의 두께와 색상 설정
    trianglePath.setStrokeColor(ofColor(25, 0, 100));
    trianglePath.setStrokeWidth(5);
    trianglePath.setFilled(true);
    trianglePath.setFillColor(ofColor(25, 100, ofRandom(255)));  // 면을 채울 색상을 설정해야 합니다.
    
    trianglePath.append(side1);
    trianglePath.append(side2);
    trianglePath.append(side3);
    trianglePath.close();
   }

/*
// 구불구불한 선을 그리면서 각 정점에 색상을 추가하는 함수
void Dot::createWavyTriangle(ofVec2f center, int numSegments, float amplitude) {
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // 삼각형 꼭짓점 설정
    ofVec2f vertex1 = center + ofVec2f(radius * cos(angle * 0), radius * sin(angle * 0));
    ofVec2f vertex2 = center + ofVec2f(radius * cos(angle * 1), radius * sin(angle * 1));
    ofVec2f vertex3 = center + ofVec2f(radius * cos(angle * 2), radius * sin(angle * 2));
    
//    ofVec2f vertex1 = center + ofVec2f(radius * cos(ofDegToRad(angle)), radius * sin(ofDegToRad(angle)));
//    ofVec2f vertex2 = center + ofVec2f(radius * cos(ofDegToRad(angle * 2)), radius * sin(ofDegToRad(angle * 2)));
//    ofVec2f vertex3 = center + ofVec2f(radius * cos(ofDegToRad(angle * 3)), radius * sin(ofDegToRad(angle * 3)));

    // 무작위 색상 설정
//    ofColor color1 = getRandomColor();
//    ofColor color2 = getRandomColor();
//    ofColor color3 = getRandomColor();

    
    ofColor color1 = ofColor(ofRandom(55), ofRandom(10), ofRandom(100));
    ofColor color2 = ofColor(ofRandom(155), ofRandom(50), ofRandom(100));
    ofColor color3 = ofColor(ofRandom(155), ofRandom(100), ofRandom(100));
    //    mesh.addColor();
    //    mesh.addColor();
    //    mesh.addColor();
    
    // 구불구불한 변을 그리기 (vertex1 -> vertex2)
    createWavyEdge(vertex1, vertex2, numSegments, amplitude, color1, color2);

    // 구불구불한 변을 그리기 (vertex2 -> vertex3)
    createWavyEdge(vertex2, vertex3, numSegments, amplitude, color2, color3);

    // 구불구불한 변을 그리기 (vertex3 -> vertex1)
    createWavyEdge(vertex3, vertex1, numSegments, amplitude, color3, color1);
    
    

    
}

void Dot::createWavyEdge(ofVec3f start, ofVec3f end, int numSegments, float amplitude, ofColor startColor, ofColor endColor) {
    for (int i = 0; i <= numSegments; i++) {
        float t = (float)i / (float)numSegments;
        ofVec3f point = start.getInterpolated(end, t); // 선을 따라 점을 보간
        point.x += ofRandom(-amplitude, amplitude);    // 구불구불하게 변형
        point.y += ofRandom(-amplitude, amplitude);

        // 보간된 색상
        ofColor color = startColor.getLerped(endColor, t);

        // 정점과 색상 추가
        mesh.addVertex(point);
        mesh.addColor(color);
    }
    
    if (numSegments > 1) {
        for (int i = 0; i < numSegments - 1; i++) {
            mesh.addIndex(i);
            mesh.addIndex(i + 1);
            mesh.addIndex(numSegments + i + 1);

            mesh.addIndex(i);
            mesh.addIndex(numSegments + i + 1);
            mesh.addIndex(numSegments + i + 2);
        }
    }
    

}
 
*/

// 정점에 무작위 색상을 지정하는 함수
ofColor Dot::getRandomColor() {
    return ofColor(ofRandom(155), ofRandom(100), ofRandom(100));
}
