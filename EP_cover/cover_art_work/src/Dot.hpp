#ifndef DOT_HPP
#define DOT_HPP

#include <random>
#include "ofMain.h"

class Dot {
public:
    // 생성자 선언
    Dot(
        std::mt19937& generator,
        std::uniform_real_distribution<float>& distribution,
        ofVec2f position,
        float r
    );

    // 멤버 함수 선언
    ofVec2f getPosition();
    float getRadius();
    void printInfo() const;
    void draw();

private:
    std::mt19937& randGen;
    std::uniform_real_distribution<float>& randDist;
    
    // 멤버 변수 선언
    ofVec2f position;
    float radius;
    
    ofPath trianglePath;
    ofMesh mesh;
    
    float angle, L, rotAngle;
    
//    void getVertex();
    void getTrianglePoints(ofVec3f p[]);
    ofPath createWavyPath(ofVec3f start, ofVec3f end, int numSegments, float amplitude);
//    void createWavyTriangle(ofVec2f center, float radius, float angle, int numSegments, float amplitude);
    
    void createWavyTriangle(ofVec2f center, int numSegments, float amplitude);
    void createWavyEdge(ofVec3f start, ofVec3f end, int numSegments, float amplitude, ofColor startColor, ofColor endColor);
    
    ofColor getRandomColor();
};

#endif // DOT_H
