#include "simplecanvas/simplecanvas.h"
#include <string>
#include <sstream>
#include <math.h>
#include "shapes.h"
using namespace std;

/**
 * @brief Constructor for the shape object that takes the thickness and color. 
 * 
 * @param thickness The thickness of the shape
 * @param color The color of the shape
 */
Shape::Shape(float thickness, int color[3]) {
    this->thickness = thickness;
    for (int k = 0; k < 3; k++) {
        this->color[k] = color[k];
    }
}

/**
 * @brief Draw the shape on a particle canvas
 * 
 * @param canvas Pointer to canvas
 */
void Shape::draw(SimpleCanvas* canvas) {
    cout << "Warning: Calling draw on base class";
}

/////////////////////////////////////////////////////

/**
 * @brief Constructor for a point object that takes the thickness, color, x coordinate, and y coordiate
 * 
 * @param thickness The thickness of the point
 * @param color The color of the point 
 * @param ax The x coordinate
 * @param ay The y coordinate
 */
Point::Point(float thickness, int color[3], float ax, float ay):Shape(thickness, color) {
    this->ax = ax;
    this->ay = ay;
}

/**
 * @brief Returns the x value of the point
 * 
 * @return The x value of the point
 */
float Point::getX() {
    return ax;
}

/**
 * @brief Return the y value of the point
 * 
 * @return The y value of the point
 */
float Point::getY() {
    return ay;
}

/**
 * @brief Draw the point on a particle canvas
 * 
 * @param canvas Pointer to canvas
 */
void Point::draw(SimpleCanvas* canvas) {
    canvas->fillCircle((int)ax, (int)ay, thickness, color[0], color[1], color[2]);
}

/////////////////////////////////////////////////////

/**
* @brief A constructor for the line shape that accepts the two points that make up the line, the thickness, and the color.
* 
* @param thickness The thickness of the line
* @param color The color of the line
* @param a The first point of the line
* @param b The second point of the line
*/
LineSegment::LineSegment(float thickness, int color[3], 
                        Point a, Point b):Shape(thickness, color) {
    this->a = a;
    this->b = b;
}

/**
 * @brief Draw the line on a particle canvas
 * 
 * @param canvas Pointer to canvas
 */
void LineSegment::draw(SimpleCanvas* canvas) {
    canvas->drawLine(a.getX(), a.getY(), b.getX(), b.getY(), thickness, color[0], color[1], color[2]);
}

/////////////////////////////////////////////////////

/**
 * @brief A constructor for the square shape that accepts the three points that make up the vertices, the thickness, and the color.
 * 
 * @param thickness The thickness of the triangle
 * @param color The color of the triangle
 * @param a The first vertice of the triangle
 * @param b The second vertice of the triangle
 * @param c The third vertice of the triangle
 */
Triangle::Triangle(float thickness, int color[3], Point a, Point b, Point c):Shape(thickness, color)
{
    this->a = a;
    this->b = b;
    this->c = c;
    LineSegment la(thickness, color, a, b);
    LineSegment lb(thickness, color, a, c);
    LineSegment lc(thickness, color, b, c);
    this->la = la;
    this->lb = lb;
    this->lc = lc;
    
}

/**
 * @brief Draw the triangle on a particle canvas
 * 
 * @param canvas Pointer to canvas
 */
void Triangle::draw(SimpleCanvas* canvas) {
    la.draw(canvas);
    lb.draw(canvas);
    lc.draw(canvas);
}

/////////////////////////////////////////////////////


/**
 * @brief A constructor for the Square shape that accepts the four points that make the vertices, the thickness, and the color
 * 
 * @param thickness The thickness of the square
 * @param color The color of the square
 * @param a The first vertice of the square
 * @param b The second vertice of the square
 * @param c The third vertice of the square
 * @param d The fourth vertice of the square
 */
Square::Square(float thickness, int color[3], Point a, Point b, Point c, Point d):Shape(thickness, color)
{
    LineSegment la(thickness, color, a, b);
    LineSegment lb(thickness, color, b, c);
    LineSegment lc(thickness, color, c, d);
    LineSegment ld(thickness, color, d, a);
    this->la = la;
    this->lb = lb;
    this->lc = lc;
    this->ld = ld;

} 

/**
 * This draws a four sided shape in which all the sides are connected for the square. This is draw on the provided canvas. 
 * 
 * @param canvas The pointer to the canvas that the square is drawn on. 
 */
void Square::draw(SimpleCanvas* canvas) {
    la.draw(canvas);
    lb.draw(canvas);
    lc.draw(canvas);
    ld.draw(canvas);
}


/////////////////////////////////////////////////////


/**
 * A constructor for the Circle shape which is a pseudo circle which consists of multiple line segments in the shape of a circle. 
 * 
 * @param thickness Thickness of pen drawing
 * @param color Color to draw
 * @param center Point object that represents the center of the shape
 * @param numOfLines The number of line segments that the circle is made up of
 * @param radius The radius of the circle shape
 */
Circle::Circle(float thickness, int color[3], Point center, float numOfLines, float radius):Shape(thickness, color)
{
    this->center=center;
    this->numOfLines=numOfLines;
    this->radius=radius;
}

/**
 * This draws the circle shape by drawing a line connecting 2 points, X value of which is determined by the formula cx+r*cos((2*pi*i)/N)
 * and the Y value of which is determined by the formula cy+r*sin((2*pi*i)/N). This draws certain amount of lines to form the shape of a
 * circle. 
 * 
 * @param canvas A pointer the canvas to draw on
 */
void Circle::draw(SimpleCanvas* canvas)
{
    for(int i = 1; i < numOfLines+1; i++)
    {
        int xone = center.getX()+radius*cos((2*M_PI*i)/numOfLines);
        int yone = center.getY()+radius*sin((2*M_PI*i)/numOfLines);
        int xtwo = center.getX()+radius*cos((2*M_PI*(i+1))/numOfLines);
        int ytwo = center.getY()+radius*sin((2*M_PI*(i+1))/numOfLines);
        canvas->drawLine(xone, yone, xtwo, ytwo, thickness, color[0], color[1], color[2]);
    }
}
