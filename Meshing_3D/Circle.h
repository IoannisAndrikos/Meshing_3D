#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <direct.h>
#include <iostream>
#include <iterator>
#include <mutex>
#include <numeric>
#include <thread>
#include <future>
#include <string>
#include <locale>
#include <codecvt>
#include <experimental/filesystem>

#include "shape.h"

using namespace std;
using namespace cv;

class Circle : public shape {
public:
	Circle();
	//custom constructor
	Circle(double radius, int numPoints, double depth);
	~Circle();

private:


protected:

};

#endif #pragma once
