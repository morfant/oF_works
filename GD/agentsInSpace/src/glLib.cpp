//
//  glLib.cpp
//  noiseLandscape
//
//  Created by Gang il Lee on 12/23/24.
//


#include "gdLib.h"


float seed = 0;

float fractalNoise(float x, float y, int octaves, float falloff) {
    float noiseValue = 0.0;
    float amplitude = 1.0;
    float frequency = 1.0;
    float maxAmplitude = 0.0;
    
    for (int i = 0; i < octaves; i++)
    {
        noiseValue += getNoise(x * frequency, y * frequency) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= falloff;
        frequency *= 2.0;
    }
    
    return noiseValue / maxAmplitude;
}

float fractalNoise(float x, float y, float z, int octaves, float falloff) {
    float noiseValue = 0.0;
    float amplitude = 1.0;
    float frequency = 1.0;
    float maxAmplitude = 0.0;
    
    for (int i = 0; i < octaves; i++)
    {
        noiseValue += getNoise(x * frequency, y * frequency, z * frequency) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= falloff;
        frequency *= 2.0;
    }
    
    return noiseValue / maxAmplitude;
}


ofColor lerpColor(const ofColor& color1, const ofColor& color2, float t) {
    // t는 0.0 ~ 1.0 사이의 값 (0.0이면 color1, 1.0이면 color2)
    ofColor result;
    result.r = ofLerp(color1.r, color2.r, t);
    result.g = ofLerp(color1.g, color2.g, t);
    result.b = ofLerp(color1.b, color2.b, t);
    result.a = ofLerp(color1.a, color2.a, t); // 알파 값도 보간
    return result;
}

ofColor hsbToRgb(float hue, float saturation, float brightness) {
    hue = fmod(hue, 360); // Hue는 0-360 범위에서 순환
    if (hue < 0) hue += 360;

    saturation = ofClamp(saturation / 100.0f, 0, 1); // 0~100 → 0~1
    brightness = ofClamp(brightness / 100.0f, 0, 1); // 0~100 → 0~1

    float c = brightness * saturation;
    float x = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
    float m = brightness - c;

    float r = 0, g = 0, b = 0;
    if (hue < 60) {
        r = c; g = x; b = 0;
    } else if (hue < 120) {
        r = x; g = c; b = 0;
    } else if (hue < 180) {
        r = 0; g = c; b = x;
    } else if (hue < 240) {
        r = 0; g = x; b = c;
    } else if (hue < 300) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }

    return ofColor((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

ofVec3f rgbToHsb(const ofColor& color) {
    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;

    float maxVal = std::max(r, std::max(g, b));
    float minVal = std::min(r, std::min(g, b));
    float delta = maxVal - minVal;

    float hue = 0;
    if (delta != 0) {
        if (maxVal == r) {
            hue = 60 * fmod(((g - b) / delta), 6);
        } else if (maxVal == g) {
            hue = 60 * (((b - r) / delta) + 2);
        } else {
            hue = 60 * (((r - g) / delta) + 4);
        }
    }
    if (hue < 0) hue += 360;

    float saturation = (maxVal == 0) ? 0 : (delta / maxVal) * 100; // 0~100
    float brightness = maxVal * 100; // 0~100

    return ofVec3f(hue, saturation, brightness); // Hue: 0-360, Saturation: 0-100, Brightness: 0-100
}

void setNoiseSeed(unsigned int _seed) {
    seed = _seed;
}

float getNoise(float x) {
    return ofNoise(x + seed);
}

float getNoise(float x, float y) {
    return ofNoise(x + seed, y + seed);
}

float getNoise(float x, float y, float z) {
    return ofNoise(x + seed, y + seed, z + seed);
}


