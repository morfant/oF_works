//
//  gdLib.h
//  noiseLandscape
//
//  Created by Gang il Lee on 12/23/24.

#pragma once

#include "ofMain.h"


float fractalNoise(float x, float y, int octaves, float falloff);
float fractalNoise(float x, float y, float z, int octaves, float falloff);
ofColor lerpColor(const ofColor& color1, const ofColor& color2, float t);
ofColor hsb2rgb(float hue, float saturation, float brightness);
ofColor hsb2rgba(float hue, float saturation, float brightness, float alpha);
ofVec3f rgb2hsb(const ofColor& color);
void setNoiseSeed(unsigned int seed);
float getNoise(float x);
float getNoise(float x, float y);
float getNoise(float x, float y, float z);


