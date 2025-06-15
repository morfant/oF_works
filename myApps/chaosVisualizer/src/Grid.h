// Grid.h
#pragma once
#include "ofMain.h"
#include "Globals.h"

class Grid {
public:
    int cols, rows;
    int cellW, cellH;
    vector<vector<float>> values;
    vector<vector<float>> targetValues;

	Grid() {};
    Grid(int cols, int rows, int w, int h);

    void reset();
    void display(int mode = 0);
    void setValueAt(float x, float y, float val);
    float getValueAt(float x, float y);
    void revealValue(float x, float y);
    void setFromImage(const ofImage& img);
    int countRevealedCells() const;
    void fade(float amt);
    bool revealNearestCell(float x, float y, float threshold);
};
