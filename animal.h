#include "simulation.h"
#ifndef ANIMAL_H
#define ANIMAL_H

/**
 * TODO: You will need to extend this quite a bit the full 
 * functionality in this assignment.  This includes adding
 * variables and methods to the Animal class, as well as 
 * defining subclasses for Female, Male, and SuperMale
 * 
 */
class Animal {
    protected:
        float vx;
        float vy;
        float x;
        float y;
        int r;
        int b;
        int g;
        float speed;
        Simulation* simulation;
    public:
        Animal(Simulation* simulation, float x, float y, float vx, float vy);
        virtual ~Animal(){};
        virtual void action(float dt);
        void draw();
        void test();
        float getX();
        float getY();

};

#endif