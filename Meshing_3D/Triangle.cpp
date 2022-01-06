#include "Triangle.h"

Triangle::Triangle() {}
Triangle::~Triangle() {}

Triangle::Triangle(double edgeSize, double depth) {

    /*
    Three points are enough to define a triangle
    The implementation bellow is based on the follwing link :
    https://en.wikipedia.org/wiki/Equilateral_triangle#/media/File:Equilateral_triangle_construction.svg
    */

    this->points.push_back(Point3f(0, 0, depth));
    this->points.push_back(Point3f(0, edgeSize, depth));

    //all the corners of an equals sides triangle have angle = 60 degrees. 
    double x = edgeSize * cos(60 * CV_PI / 180);
    double y = edgeSize * sin(60 * CV_PI / 180);
    this->points.push_back(Point3f(y, x, depth));
}
