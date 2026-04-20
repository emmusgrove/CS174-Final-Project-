#include "simulation.h"
#include "animal.h"
#include "tinygl-cpp.h"
#include "simplecanvas/simplecanvas.h"
#include "shapes.h"
#include <list>
#include <chrono> 
#include <thread> 
#include <iterator>
#include <math.h>
#include <stdio.h>
#include <vector>
using namespace std;
using std::vector;
using namespace tinygl;


/**
 * @brief This is a helper class to wrap around drawing functionality
 * DO NOT TOUCH THIS CLASS
 * 
 * This code is using the "pointer to implementation" design pattern 
 * to work in synchrony with the Simulation class
 * https://en.cppreference.com/w/cpp/language/pimpl
 */
class SimulationCanvas: public Window {
    private:
        int res;
        Simulation* simulation;
        float lastTime;
    public: 
        SimulationCanvas(Simulation* simulation, int res):Window(res, res) {
            this->simulation = simulation;
            this->res = res;
            lastTime = elapsedTime();
        }
        void circle(float x, float y, int r, int g, int b, float diameter) {
            color(r, g, b);
            ellipsoid((int)(res*x), (int)(res*y), res*diameter, res*diameter);
        }
        void square(float x, float y, float width, float height, int r, int g, int b)
        {
            color(r, g, b);
            Window::square((int)(res*x), (int)(res*y), (int)(res*width), (int)(res*height)); 
        }
        void triangle(float x, float y, float width, float height, int r, int g, int b)
        {
            color(r, g, b);
            Window::triangle((int)(res*x), (int)(res*y), (int)(res*width), (int)(res*height));
        }
        float timeElapsed()
        {
            return elapsedTime();
        }
        int getRes()
        {
            return res;
        }
        void draw() {
            background(0.8f, 0.8f, 0.8f);
            float time = elapsedTime();
            float dt = time - lastTime;
            lastTime = time; 
            simulation->step(dt);
        }
};

/**
 * @brief @brief Construct a new simulation object. This is specifically meant to draw the triangle or square
 * shapes without a second overload of the constructor for the circle shape as different values are need.
 * 
 * @param res The square resolution of the window
 * @param shape The shape the user wants to draw
 * @param height The height of the shape (this will also determine the original [x,y] coordinates of the particles)
 * @param width The width of the shape (this will also determine the original [x,y] coordinates of the particles)
 * @param vx The velocity of the particles in the x direction
 * @param vy The velocity of the particles in the y direction
 * @param fileName The name of the resulting .png file
 */
Simulation::Simulation(int res, string shape, float height, float width, float vx, float vy, string fileName) {
    canvas = new SimulationCanvas(this, res);
    this->width = width;
    this->height = height;
    this->shape = shape;
    this->vx = vx;
    this->fileName = fileName; 
    this->vy = vy;
    this->runningStatus = true;
    int yellow[3] = {255, 255, 0};
    int black[3] = {0, 0, 0};
    for (int k = 0; k < 3; k++) {
        this->yellow[k] = yellow[k];
    }
    for (int k = 0; k < 3; k++) {
        this->black[k] = black[k];
    }
    if(shape == "triangle")
    {
        animals.push_back(new Animal(this, 0.5, 0.5+(height/2), vx, vy));
        animals.push_back(new Animal(this, 0.5-(width/2), 0.5-(height/2), vx, vy));
        animals.push_back(new Animal(this, 0.5+(width/2), 0.5-(height/2), vx, vy));
    }
    else if(shape == "square")
    {
        animals.push_back(new Animal(this, 0.5-(width/2), 0.5+(height/2), vx, vy));
        animals.push_back(new Animal(this, 0.5+(width/2), 0.5+(height/2), vx, vy));
        animals.push_back(new Animal(this, 0.5+(width/2), 0.5-(height/2), vx, vy));
        animals.push_back(new Animal(this, 0.5-(width/2), 0.5-(height/2), vx, vy));
    }
    this->res = (float)res;
    time = 0.0;
}

/**
 * @brief Construct a new Simulation::Simulation object. This overload the previous constructor to specifically
 * construct the circle and ask for the appropriate values. 
 * 
 * @param res The square resolution of the window
 * @param shape The shape that the user wants to use (this constructor is specifically made to use the circle shape)
 * @param diameter The diameter of the circle 
 * @param numOfPoints The number of points/particles that are used in the program
 * @param vx The velocity of the particles in the x direction
 * @param vy The velocity of the particles in the y direction
 * @param fileName The name of the resulting .png file created
 */
Simulation::Simulation(int res, string shape, float diameter, int numOfPoints, float vx, float vy, string fileName) {
    canvas = new SimulationCanvas(this, res);
    this->diameter = diameter;
    this->shape = shape;
    this->runningStatus = true;
    this->numOfPoints = numOfPoints; 
    this->fileName = fileName; 
    this->vx = vx;
    this->vy = vy;
    int yellow[3] = {255, 255, 0};
    int black[3] = {0, 0, 0};
    for (int k = 0; k < 3; k++) {
        this->yellow[k] = yellow[k];
    }
    for (int k = 0; k < 3; k++) {
        this->black[k] = black[k];
    } 
    if(shape == "circle")
    {
        for(int i = 1; i < numOfPoints+1; i++)
        {
            animals.push_back(new Animal(this, 0.5+(diameter/2)*cos((2*M_PI*i)/numOfPoints), 0.5+(diameter/2)*sin((2*M_PI*i)/numOfPoints), vx, vy));
        }
    } 
    this->res = (float)res;
    time = 0.0;   
}

/**
 * @brief Destroy the Simulation:: Simulation object and clear the xvalues and yvalues vectors
 * 
 */
Simulation::~Simulation() {
    list<Animal*>::iterator it;
    for(it = animals.begin(); it != animals.end(); it++)
    {
        delete (*it);
        it = animals.erase(it);   
    }
    xvalues.clear();
    yvalues.clear();
    delete canvas; 
    
}

/**
 * @brief Wrapper around tinygl run method for continuous animation
 * 
 */
void Simulation::run() {
    canvas->run();
}

/**
 * @brief Creates the SimpleCanvas and draws the shape and points in accordance with
 * the shape provided by the user
 * 
 */
void Simulation::drawing()
{
    SimpleCanvas canvas(400, 400);
    canvas.clearRect(255, 255, 255);
    if(shape == "triangle")
    {
        drawTriangle(&canvas);
    }
    else if(shape == "square")
    {
        drawSquare(&canvas);
    }
    else if(shape == "circle")
    {
        drawCircle(&canvas);
    }
}

/**
 * @brief Draws the triangle shape and the [x,y] coordinates of the particles during the 
 * entirity of the programs runtime
 * 
 * @param canvas The SimpleCanvas on which to draw the triangle and points
 */
void Simulation::drawTriangle(SimpleCanvas* canvas)
{
    Point a(1, yellow, xvalues.at(1)*getRes(), 400-(yvalues.at(1)*getRes()));
    Point b(1, yellow, xvalues.at(0)*getRes(), 400-(yvalues.at(0)*getRes()));
    Point c(1, yellow, xvalues.at(2)*getRes(), 400-(yvalues.at(2)*getRes()));
    Triangle triangle(5, yellow, a, b, c);
    triangle.draw(canvas);
    drawPoints(canvas);
    canvas->write(fileName);
}

/**
 * @brief Draws the square shape and the [x,y] coordinates of the particles during the 
 * entirity of the programs runtime
 * 
 * @param canvas The SimpleCanvas on which to draw the square and points
 */
void Simulation::drawSquare(SimpleCanvas* canvas)
{
    Point a(5, yellow, xvalues.at(0)*getRes(), 400-(yvalues.at(0)*getRes()));
    Point b(5, yellow, xvalues.at(1)*getRes(), 400-(yvalues.at(1)*getRes()));
    Point c(5, yellow, xvalues.at(2)*getRes(), 400-(yvalues.at(2)*getRes()));
    Point d(5, yellow, xvalues.at(3)*getRes(), 400-(yvalues.at(3)*getRes()));
    Square square(5, yellow, a, b, c, d);
    square.draw(canvas);   
    drawPoints(canvas);
    canvas->write(fileName);
}

/**
 * @brief Draws the circle shape and the [x,y] coordinates of the particles during the 
 * entirity of the programs runtime
 * 
 * @param canvas The SimpleCanvas on which to draw the circle and points
 */
void Simulation::drawCircle(SimpleCanvas* canvas)
{
    Point center(5, yellow, 0.5*getRes(), 400-(0.5*getRes()));
    Circle circle(5, yellow, center, 16, (diameter/2)*getRes());
    circle.draw(canvas);
    drawPoints(canvas);
    canvas->write(fileName);
}

/**
 * @brief Draws points on the SimpleCanvas for the x and y coordinates in the xvalues
 * and yvalues vectors with adjustments made for difference in the coordinates of the SimpleCanvas
 * and the SimulationCanvas.
 * 
 * @param canvas The SimpleCanvas on which to draw the points
 */
void Simulation::drawPoints(SimpleCanvas* canvas)
{
    if(xvalues.size() == yvalues.size())
  {
    for(int i = 0; i < xvalues.size(); i++)
    {
      Point one(1, black, xvalues.at(i)*getRes(), 400-(yvalues.at(i)*getRes()));
      one.draw(canvas);
    }
  }
}

/**
 * @brief Returns the resolution of the SimulationCanvas
 * 
 * @return The resolution of the SimulationCanvas
 */
int Simulation::getRes()
{
    return canvas->getRes();
}

/**
 * @brief Wrapper around tinygl circle method for drawing dots
 * 
 * @param x Location of dot in [0, 1]
 * @param y Location of dot in [0, 1]
 * @param r Red component in [0, 255]
 * @param g Green component in [0, 255]
 * @param b Blue component in [0, 255]
 * @param diameter Diameter of dot, in [0, 1]
 */
void Simulation::circle(float x, float y, int r, int g, int b, float diameter) {
    canvas->circle(x, y, r, g, b, diameter);
}

/**
 * @brief Wrapper around tinygl triangle method
 * 
 * @param x Location of dot in [0, 1]
 * @param y Location of dot in [0, 1]
 * @param r Red component in [0, 255]
 * @param g Green component in [0, 255]
 * @param b Blue component in [0, 255]
 */
void Simulation::triangle(float x, float y, int r, int g, int b)
{
    canvas->triangle(x, y, width, height, r, g, b);
}

/**
 * @brief Wrapper around tinygl square method
 * 
 * @param x Location of dot in [0, 1]
 * @param y Location of dot in [0, 1]
 * @param r Red component in [0, 255]
 * @param g Green component in [0, 255]
 * @param b Blue component in [0, 255]
 */
void Simulation::square(float x, float y, int r, int g, int b)
{
    canvas->square(x, y, width, height, r, g, b);
}

/**
 * @brief This find the closest particle in the list (which is going to be the next particle in the clockwise direction)
 * 
 * @param tu The pointer to the animal that the code is looking for the closest particle to
 * @return A pointer to the closest animal particle
 */
Animal* Simulation::findFriends(Animal* tu)
{
    list<Animal*>::iterator it = animals.begin();
    Animal* huh = NULL;
    bool found = false; 
    if(animals.size() > 1)
    {
        for(it = animals.begin(); it != animals.end(); it++){
            if((*it) == tu)
            {
                found = true;
            }
            else if((*it) != tu && found)
            {
                return (*it);
            }
        }
        if(found)
        {
            list<Animal*>::iterator it = animals.begin();
            return (*it); 
        }
    }
    return huh;
}

/**
 * @brief Do a step of the simulation. This should print the shape provided 
 * by the user and every animal should move and take its action. Then, after it
 * inputs the x and y coordinates of each particle in the xvalues and yvalues vectors.
 * It tests to see if the difference in the x and y coordinates of each particle compared to
 * all the other particles is between -0.0001 and 0.0001 if the amount of particles is equal or 
 * less than 4 and between -0.008 and 0.008 in the amount of particles is equal or greater than 5 
 * (this is because the more particles in a code the lower the standard must be) and if they all 
 * are it stops the code. It outputs the runtime in milliseconds and draws the motion of 
 * the particles during the course of the code on the SimpleCanvas. Then it changes the variable runningStatus  
 * to false which will mean the action() code won't run again.
 * 
 * @param dt The amount of time elaps0ed since the last step
 */
void Simulation::step(float dt) {
    // TODO: You should loop through the animals here
    // and take steps and draw them
    if(shape == "triangle")
    {
        triangle(0.5, 0.5, 255, 255, 0);
    }
    else if(shape == "square")
    {
        square(0.5, 0.5, 255, 255, 0);
    }
    else if(shape == "circle")
    {
        circle(0.5, 0.5, 255, 255, 0, diameter/2);
    }
    list<Animal*>::iterator it;
    list<Animal*>::iterator an; 
    int count = 0; 
    if(animals.size() > 1 && runningStatus == true)
    {
        for(it = animals.begin(); it != animals.end(); it++)
        {
            xvalues.push_back((*it)->getX());
            yvalues.push_back((*it)->getY());
            if(runningStatus == true)
            {
                (*it)->draw();
                (*it)->action(dt);
                for(an = animals.begin(); an != animals.end(); an++)
                {
                    if(animals.size() <= 4)
                    {
                        if(abs((*it)->getX())-abs((*an)->getX()) < 0.001 && abs((*it)->getY()) - abs((*an)->getY()) < 0.001 && abs((*it)->getX())-abs((*an)->getX()) > -0.001 && abs((*it)->getY()) - abs((*an)->getY()) > -0.001)
                        {
                            count++;
                        }
                        else if(abs((*it)->getX())-abs((*an)->getX()) == 0 && abs((*it)->getY())-abs((*an)->getY()) == 0)
                        {
                            count++;
                        }
                        else 
                        {
                            cout << abs((*it)->getX())-abs((*an)->getX()) << " and " << abs((*it)->getY())-abs((*an)->getY()) << "\n";
                        }
                    }
                    else if(animals.size() >= 5)
                    {
                        if(abs((*it)->getX())-abs((*an)->getX()) < 0.008 && abs((*it)->getY()) - abs((*an)->getY()) < 0.008 && abs((*it)->getX())-abs((*an)->getX()) > -0.008 && abs((*it)->getY()) - abs((*an)->getY()) > -0.008)
                        {
                            count++;
                        }
                        else if(abs((*it)->getX())-abs((*an)->getX()) == 0 && abs((*it)->getY())-abs((*an)->getY()) == 0)
                        {
                            count++;
                        }
                        else 
                        {
                            cout << abs((*it)->getX())-abs((*an)->getX()) << " and " << abs((*it)->getY())-abs((*an)->getY()) << "\n";
                        }
                    }
                    /*else if(abs((*it)->getX())-abs((*an)->getX()) > -0.0001 && abs((*it)->getY()) - abs((*an)->getY()) > -0.0001)
                    {
                        cout << "there";
                        cout << abs((*it)->getX())-abs((*an)->getX()) << "\n";
                        count++;
                    }*/
                    
                }
                if(count == animals.size())
                {
                    cout << "The time elapsed is " << (canvas->timeElapsed()*1000) << " milliseconds.\n";
                    this_thread::sleep_for(chrono::milliseconds(2000));
                    runningStatus = false;
                    drawing();
                }
                else if(count != animals.size())
                {
                    count = 0; 
                }
            }
            if(!runningStatus)
            {
                break;
            }
        }
    }
    else if(animals.size() > 1)
    {
        for(it = animals.begin(); it != animals.end(); it++)
        {
            (*it)->draw(); 
        }
    }
}