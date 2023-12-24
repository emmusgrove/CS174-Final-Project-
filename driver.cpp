#include <iostream>
#include <list>
#include <string.h>
#include "animal.h"
#include "randutils.h"
#include "simulation.h"
#include "shapes.h"
#include "simplecanvas/simplecanvas.h"
#include <vector>
#include <cmath> 
#include <math.h>

using namespace std;
using std::vector; 

int main(int argc, char** argv)
{
  if(stof(argv[3]) <= 1)
  {
    Simulation simulation(400, argv[1], stof(argv[2]), stof(argv[3]), stof(argv[4]), stof(argv[5]), argv[6]);
    simulation.run();
  }
  else if(stof(argv[3]) > 1)
  {
    Simulation simulation(400, argv[1], stof(argv[2]), stoi(argv[3]), stof(argv[4]), stof(argv[5]), argv[6]);
    simulation.run();
  }
  return 0;
}