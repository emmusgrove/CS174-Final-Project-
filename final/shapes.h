#ifndef SHAPES_H
#define SHAPES_H

#include "simplecanvas/simplecanvas.h"
#include <iostream>
#include <string>
using namespace std;

class Shape {
    protected:
        float thickness;
        int color[3];
    public:
        /**
        * @brief Constructor for the shape object that takes the thickness and color. 
        * 
        * @param thickness The thickness of the shape
        * @param color The color of the shape
        */
        Shape(float thickness, int color[3]);

        // Dummy constructor for empty object declarations
        Shape(){};

        /**
         * @brief Draw the shape on a particle canvas
         * 
         * @param canvas Pointer to canvas
         */
        void draw(SimpleCanvas* canvas);
};

class Point: public Shape {
    private:
        float ax;
        float ay;
    public:
        /**
        * @brief Constructor for a point object that takes the thickness, color, x coordinate, and y coordiate
        * 
        * @param thickness The thickness of the point
        * @param color The color of the point 
        * @param ax The x coordinate
        * @param ay The y coordinate
        */
        Point(float thickness, int color[3], float ax, float ay);

        // Dummy constructor for empty object declarations
        Point(){};

        /**
        * @brief Returns the x value of the point
        * 
        * @return The x value of the point
        */
        float getX();

        /**
        * @brief Returns the y value of the point
        * 
        * @return The y value of the point
        */
        float getY();

        /**
         * @brief Draw the point on a particle canvas
         * 
         * @param canvas Pointer to canvas
         */
        void draw(SimpleCanvas* canvas);
};



class LineSegment: public Shape {
    private:
        Point a;
        Point b;
    public:
        /**
         * @brief A constructor for the line shape that accepts the two points that make up the line, the thickness, and the color.
         * 
         * @param thickness The thickness of the line
         * @param color The color of the line
         * @param a The first point of the line
         * @param b The second point of the line
         */
        LineSegment(float thickness, int color[3], Point a, Point b);

        // Dummy constructor for empty object declarations
        LineSegment(){};
        
        /**
         * @brief Draw the line on a particle canvas
         * 
         * @param canvas Pointer to canvas
         */
        void draw(SimpleCanvas* canvas);
};

class Triangle: public Shape {
    private:
        LineSegment la;
        LineSegment lb;
        LineSegment lc;
        Point a;
        Point b;
        Point c;
    public:

        /**
         * @brief A constructor for the square shape that accepts the three points that make up the vertices, the thickness, and the color.
         * 
         * @param thickness The thickness of the triangle
         * @param color The color of the triangle
         * @param a The first vertice of the triangle
         * @param b The second vertice of the triangle
         * @param c The third vertice of the triangle
         */
        Triangle(float thickness, int color[3], Point a, Point b, Point c);

        // Dummy constructor for empty object declarations
        Triangle(){};
        
        /**
         * Draw the triangle on a particular canvas
         * 
         * @param canvas Pointer to canvas 
         */
        void draw(SimpleCanvas* canvas);
};


class Square: public Shape {
    private:
    LineSegment la;
    LineSegment lb;
    LineSegment lc;
    LineSegment ld;

    public:
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
    Square(float thickness, int color[3], Point a, Point b, Point c, Point d);

    // Dummy constructor for empty object declarations
    Square(){};

    /**
     * Draw the square on a particular canvas
     * 
     * @param canvas Pointer to canvas 
     */
    void draw(SimpleCanvas* canvas);

};

class Circle: public Shape {
    private:
    float numOfLines;
    Point center;
    float radius;

    public:
    /**
     * Circle constructor that accepts the intended center point of the circle, the number of lines, and 
     * the radius of the circle.
     * 
     * @param thickness Thickness of pen drawing
     * @param color Color to draw
     * @param center Point object that represents the center of the shape
     * @param numOfLines The number of line segments that the circle is made up of
     * @param radius The radius of the circle shape
     */
    Circle(float thickness, int color[3], Point center, float numOfLines, float radius);

    // Dummy constructor for empty object declarations
    Circle(){};

    /**
     * Draw the circle on a particular canvas
     * 
     * @param canvas Pointer to canvas
     */
    void draw(SimpleCanvas* canvas);

};

#endif