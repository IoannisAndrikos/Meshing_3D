#include "Rectangle.h"

Rectangle::Rectangle() {}
Rectangle::~Rectangle() {}

Rectangle::Rectangle(double fistEdgeSize, double secondEdgeSize, double depth) {
	/*
	 4 points to define a rectangle
	*/
	this->points.push_back(Point3f(fistEdgeSize / 2, secondEdgeSize / 2, depth));
	this->points.push_back(Point3f(fistEdgeSize / 2, -secondEdgeSize / 2, depth));
	this->points.push_back(Point3f(-fistEdgeSize / 2, -secondEdgeSize / 2, depth));
	this->points.push_back(Point3f(-fistEdgeSize / 2, secondEdgeSize / 2, depth));
}