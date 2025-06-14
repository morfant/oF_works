//
//  Ribbon3d.cpp
//  agentsInSpace
//
//  Created by Gang il Lee on 12/28/24.
//

#include "Ribbon3d.hpp"

Ribbon3d::Ribbon3d(glm::vec3 theP, int theCount)
{
    count = theCount;
    
    for (int i = 0; i < count; i++)
    {
        p.push_back(theP);
        isGap.push_back(false);
    }
    
}

void Ribbon3d::update(glm::vec3 theP, bool theIsGap)
{
    
    for (int i = count - 1; i > 0; i--)
    {
        p.at(i) = p.at(i - 1);
        isGap.at(i) = isGap.at(i - 1);
    }
    
    p.at(0) = theP;
    isGap.at(0) = theIsGap;
    
}

void Ribbon3d::drawLineRibbon(ofColor theStrokeCol, float theWidth)
{
    ofNoFill();
    ofSetLineWidth(theWidth);
    ofSetColor(theStrokeCol);
    
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < count; i++)
    {
        glVertex3f(p.at(i).x, p.at(i).y, p.at(i).z);
//        cout << p.at(1).x << endl;
        
        if (isGap.at(i) == true)
        {
            glEnd();
            glBegin(GL_QUAD_STRIP);
        }
    }
    
    glEnd();
    
}

void Ribbon3d::drawMeshRibbon(ofColor theStrokeCol, float theWidth)
{
    ofNoFill();
    ofSetLineWidth(theWidth);
    ofSetColor(theStrokeCol);
    
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < count - 1; i++)
    {
        if (isGap.at(i) == true)
        {
            glVertex3f(p.at(i).x, p.at(i).y, p.at(i).z);
            glVertex3f(p.at(i).x, p.at(i).y, p.at(i).z);
            glEnd();
            glBegin(GL_QUAD_STRIP);
        }
        else
        {
            glm::vec3 v1, v2, v3;
            v1 = p.at(i) - p.at(i + 1);
            v2 = p.at(i + 1) + p.at(i);
            v3 = glm::cross(v1, v2);
            v2 = glm::cross(v1, v3);
            v2 = glm::normalize(v2);
            v2 = v2 * theWidth;
            glVertex3f(p.at(i).x + v2.x, p.at(i).y + v2.y, p.at(i).z + v2.z);
            glVertex3f(p.at(i).x - v2.x, p.at(i).y - v2.y, p.at(i).z - v2.z);
            
        }
    }
    
    glEnd();
    
}

void Ribbon3d::drawMeshRibbonTriangle(ofColor theMeshCol, float theWidth) {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.clear();
    
    // Set the ribbon color
    ofNoFill();
    ofSetColor(theMeshCol);

    for (int i = 0; i < p.size() - 1; i++) {
        if (isGap[i]) {
            // Finish the current strip and start a new one
            if (!mesh.getVertices().empty()) {
                mesh.draw();
                mesh.clear();
            }
        } else {
            // Calculate the width direction vector
            glm::vec3 v1 = glm::normalize(p[i + 1] - p[i]); // Direction vector
            glm::vec3 v2 = glm::cross(v1, glm::vec3(0, 0, 1)); // Perpendicular vector
            v2 = glm::normalize(v2) * theWidth;

            // Add two vertices for the strip
            mesh.addVertex(p[i] + v2); // Top edge
            mesh.addVertex(p[i] - v2); // Bottom edge
        }
    }

    // Draw the remaining mesh
    if (!mesh.getVertices().empty()) {
        mesh.draw();
    }
}
