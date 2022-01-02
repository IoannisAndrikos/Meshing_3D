#include "Circle.h"

Circle::Circle() {}
Circle::~Circle() {}


Circle::Circle(double radius, int numPoints, double depth) {

    float x, y;
    float angle = 0.0;
    float angle_stepsize = 360/numPoints;
    // go through all angles from 0 to 2 * PI radians
    while (angle < 360)
    {
       // calculate x, y from a vector with known length and angle
       x = radius * cos(angle * CV_PI / 180);
       y = radius * sin(angle * CV_PI / 180);
  
       this->points.push_back(Point3f(x, y, depth));
       angle += angle_stepsize;
    }
}