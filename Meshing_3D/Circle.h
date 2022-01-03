#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "shape.h"

using namespace std;
using namespace cv;

class Circle : public shape {
public:
	Circle();
	//custom constructor
	Circle(double diameter, double depth);
	~Circle();

private:


protected:

};

#endif #pragma once
