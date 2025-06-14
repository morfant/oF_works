//
//  Flock.hpp
//  flock
//
//  Created by giy on 2021/08/07.
//

#ifndef Flock_h
#define Flock_h

#include <stdio.h>
#include "Boid.h"

class Flock {
    
    public:
        std::vector<Boid> boids;
//      std::vector<Boid*> boids_ptr;

    
        Flock();
        void addBoid(Boid b);
//      void addBoid(Boid* b);
        void run();
    void applyForce(float f);
    
    
};

#endif /* Flock_hpp */
