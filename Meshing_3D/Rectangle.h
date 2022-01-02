#ifndef RECTANGLE_H
#define RECTANGLE_H

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

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>

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
