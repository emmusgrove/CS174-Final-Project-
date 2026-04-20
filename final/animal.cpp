#include "simulation.h"
#include "animal.h"
#include "randutils.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

/**
 * @brief This constructs an animal object to be drawn on a specified SimulationCanvas with a specied
 * x coordinate, y coordinate, velocity in the x direction, and velocity in the y direction. 
 * 
 * @param sim The is a pointer the simulation on which the animal will be drawn 
 * @param x The x coordinate
 * @param y The y coordinate 
 * @param vx The velocity in the x direction
 * @param vy The velocity in the y direction
 */
Animal::Animal(Simulation* sim, float x, float y, float vx, float vy){
    this->simulation = sim;
    RandFloat * r = new RandFloat();
    this->x = x;
    this->y = y; 
    float speed = sqrt(pow(vx, 2)+pow(vy, 2));
    this->speed = speed;
    this->vx = vx;
    this->vy = vy;
    r = 0; 
    b = 0;
    g = 0;
    delete r;
}

/**
 * @brief This draws a circle to represent the animal on the SimulationCanvas
 * 
 */
void Animal::draw()
{
    simulation->circle(x, y, r, g, b, 0.005);
}

/**
 * @brief This makes the animal move with the same speed as the user inputed originally but
 * changes the direction in which the animal moves so that it follows the closest animal determined
 * by findFriends(). The it changes the x and y coordinates while repeatedly testing for the particles going out
 * of bounds. 
 * 
 * @param dt The time since action was last run
 */
void Animal::action(float dt)
{

    Animal* u = simulation->findFriends(this);
    if(u != NULL)
    {
       float dist = sqrt(pow((x-u->getX()), 2) + pow((y-u->getY()), 2));
       vx = speed*(u->getX()-x)/dist;
       vy = speed*(u->getY()-y)/dist;
    } 
    test();
    x += dt*vx;
    test();
    y += dt*vy;
    test();
}

/**
 * @brief This tests for the particles going outside of the bounds of the window
 * 
 */
void Animal::test()
{
    if(x > 1)
    {
        x = 1;
        vx *= (-1);
    }
    else if(x < 0)
    {
        x = 0;
        vx *= (-1);
    }
    if(y > 1)
    {
        y = 1;
        vy *= (-1);
    }
    else if(y < 0)
    {
        y = 0;
        vy *= (-1);
    }
}

/**
 * @brief This returns the x coordinate of the animal 
 * 
 * @return The x coordinate of the animal
 */
float Animal::getX()
{
    
    return x;
}

/**
 * @brief This returns the y coordinate of the animal
 * 
 * @return The y coordinate of the animal
 */
float Animal::getY()
{
    return y;
}


/////////////////////////////////////////////////