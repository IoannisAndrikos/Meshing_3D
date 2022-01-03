#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "shape.h"

using namespace std;
using namespace cv;

class Rectangle : public shape {
public:
	Rectangle();
	//custom constructor
	Rectangle(double fistEdgeSize, double secondEdgeSize, double depth);
	~Rectangle();

private:


protected:

};

#endif #pragma once
