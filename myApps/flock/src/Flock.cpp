//
//  Flock.cpp
//  flock
//
//  Created by giy on 2021/08/07.
//

#include "Flock.h"

Flock::Flock() {
    boids = {};
//            boids_ptr = {};
}

void Flock::addBoid(Boid b) {
    boids.push_back(b);
//    cout << "len of boids: " << boids.size() << endl;
    
}

//void Flock::addBoid(Boid* b) {
//    boids_ptr.push_back(b);
//}

    
void Flock::run() {

    for (int i = 0; i < boids.size(); i++) {
        boids[i].flock(boids);
        boids[i].run();
    }
    
//   for (std::vector<Boid>::iterator it = boids.begin() ; it != boids.end(); ++it)
//    {
//        (*it).flock(boids);
//        (*it).run();
//    }

    
}

void Flock::applyForce(float f) {
    for (int i = 0; i < boids.size(); i++) {
        boids[i].applyForce(glm::vec3(f, 0.f, 0.f));
    }
}
