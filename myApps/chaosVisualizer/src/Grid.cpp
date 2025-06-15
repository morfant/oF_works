// Grid.cpp
#include "Grid.h"

Grid::Grid(int cols, int rows, int w, int h)
: cols(cols), rows(rows) {
    cellW = w / cols;
    cellH = h / rows;
    values.resize(cols, vector<float>(rows, 0.0f));
    targetValues.resize(cols, vector<float>(rows, 0.0f));
}

void Grid::reset() {
    for (auto& col : values) {
        fill(col.begin(), col.end(), 0.0f);
    }
}

void Grid::display(int mode) {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {

			// placeholders
			// ofNoFill();
			// ofSetColor(255, 100);
			// ofDrawCircle(
			// 	0.5 * cellW + i * cellW,
			// 	0.5 * cellH + j * cellH,
			// 	cellW * 0.5);

            float v = ofClamp(values[i][j], 0, 1);
			ofFill();
            if (mode == 0) {
                ofSetColor(v * 255, 255);
                ofDrawEllipse(i * cellW, j * cellH, cellW * 0.5, cellH * 0.5);
            } else {
                ofSetColor(100, v * 255, 100, v * 255);
                ofDrawRectangle(i * cellW, j * cellH, cellW, cellH);
            }
        }
    }
}

void Grid::setValueAt(float x, float y, float val) {
    int i = int(x / cellW);
    int j = int(y / cellH);
    if (i >= 0 && i < cols && j >= 0 && j < rows) {
        values[i][j] = ofClamp(val, 0, 1);
    }
}

float Grid::getValueAt(float x, float y) {
    int i = int(x / cellW);
    int j = int(y / cellH);
    if (i >= 0 && i < cols && j >= 0 && j < rows) {
        return values[i][j];
    }
    return 0;
}

void Grid::revealValue(float x, float y) {
    int i = int(x / cellW);
    int j = int(y / cellH);
    if (i >= 0 && i < cols && j >= 0 && j < rows) {
        values[i][j] = targetValues[i][j];
    }
}

void Grid::setFromImage(const ofImage& img) {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            int x = i * cellW + cellW / 2;
            int y = j * cellH + cellH / 2;
            ofColor c = img.getColor(x, y);
            targetValues[i][j] = c.getBrightness() / 255.0f;
        }
    }
}

int Grid::countRevealedCells() const {
    int count = 0;
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (fabs(values[i][j] - targetValues[i][j]) < 0.01f) {
                count++;
            }
        }
    }
    return count;
}

void Grid::fade(float amt) {
    for (auto& col : values) {
        for (float& val : col) {
            val = max(0.0f, val - amt);
        }
    }
}

bool Grid::revealNearestCell(float x, float y, float threshold) {
    int i = int(x / cellW);
    int j = int(y / cellH);
    if (i >= 0 && i < cols && j >= 0 && j < rows) {
        float cellCenterX = i * cellW + cellW / 2;
        float cellCenterY = j * cellH + cellH / 2;
        if (ofDist(x, y, cellCenterX, cellCenterY) < threshold) {
            values[i][j] = targetValues[i][j];
            return true;
        }
    }
    return false;
}
