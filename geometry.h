#ifndef GEOMETRY_H
#define GEOMETRY_H

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


// ----------------------------VTK Triangulation----------------------
#include "vtk-9.0/vtkSmartPointer.h"
#include "vtk-9.0/vtkTriangle.h"
#include "vtk-9.0/vtkPoints.h"
#include "vtk-9.0/vtkPolyData.h"
#include "vtk-9.0/vtkSTLWriter.h"
//---------------------------------------------------------------------

#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

using namespace std;
using namespace cv;

class geometry {
public:
	enum shapeType
	{
		circle,
		rectangle,
		triangle,
	};

	geometry(); 
	//custom constructor
	geometry(shapeType type, string pathToSave);
	~geometry();

	
	vector<vector<Point3f>> getPointCloud() {
		return this->pointCloud;
	}
	
private:
	//functions
	void triangulate();
	void createPointCloud(shapeType type);
	void saveObject3D(string path);
	shape createShape(shapeType type, double depth);

	//variables
	vector<vector<Point3f>> pointCloud;
	vtkSmartPointer<vtkPolyData> object3D;

protected:

};

#endif #pragma once
