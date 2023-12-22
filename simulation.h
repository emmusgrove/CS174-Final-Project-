#ifndef SIMULATION_H
#define SIMULATION_H

#include <list>
#include <fstream>
#include "simplecanvas/simplecanvas.h" 
#include <vector>

using namespace std;
using std::vector;

class Animal;
class SimulationCanvas;

class Simulation {
    private:
        int yellow[3];
        int black[3];
        float vx; 
        float vy;
        float res;
        list<Animal*> animals;
        SimulationCanvas* canvas;
        vector <float> xvalues;
        vector <float> yvalues;
        float time; 
        string fileName;
        float height;
        float diameter;
        int numOfPoints;  
        string shape;
        float width;
        bool runningStatus;
    
    public:
        /**
         * @brief Construct a new simulation object
         * 
         * @param res The square resolution of the window
         */
        Simulation(int res, string shape, float height, float width, float vx, float vy, string fileName);
        Simulation(int res, string shape, float diameter, int numOfPoints, float vx, float vy, string fileName);
        ~Simulation();

        void circle(float x, float y, int r, int g, int b, float diameter);
        void triangle(float x, float y, int r, int g, int b);
        void square(float x, float y, int r, int g, int b);
        void step(float dt);
        void drawing();
        void drawTriangle(SimpleCanvas* canvas);
        void drawSquare(SimpleCanvas* canvas);
        void drawCircle(SimpleCanvas* canvas);
        void drawPoints(SimpleCanvas* canvas);
        int getRes();
        void run();
        Animal* findFriends(Animal* tu);
};

#endif
