#ifndef TRANGLE_H
#define TRANGLE_H

#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "shape.h"

using namespace std;
using namespace cv;

class Triangle : public shape {
public:
	Triangle();
	//custom constructor
	Triangle(double edgeSize, double depth);

	~Triangle();

private:


protected:

};

#endif #pragma once
