//
//  gdLib.h
//  noiseLandscape
//
//  Created by Gang il Lee on 12/23/24.

#pragma once

#include "ofMain.h"

float fractalNoise(float x, float y, int octaves, float falloff);
ofColor lerpColor(const ofColor& color1, const ofColor& color2, float t);
ofColor hsbToRgb(float hue, float saturation, float brightness);
ofVec3f rgbToHsb(const ofColor& color);

