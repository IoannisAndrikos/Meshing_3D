#ifndef SHAPE_H
#define SHAPE_H

#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class shape {
public:
	shape();
	//custom cinstructor
	~shape();

	//getters
	vector<Point3f> getPoints() {
		return this->points;
	}

	void loadPoints(vector<vector<Point3f>>& pointCloud) {
		pointCloud.push_back(this->points);

		//release memory. The points no longer need after loading
		vector<Point3f>().swap(this->points);
	}


private:
	
protected:
	vector<Point3f> points;
};

#endif #pragma once
