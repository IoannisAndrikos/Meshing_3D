#ifndef GEOMETRY_H
#define GEOMETRY_H

#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <experimental/filesystem>
#include <sys/stat.h>
// ----------------------------OpenCv----------------------
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

// ----------------------------VTK Triangulation----------------------
#include "vtk-9.0/vtkSmartPointer.h"
#include "vtk-9.0/vtkTriangle.h"
#include "vtk-9.0/vtkPoints.h"
#include "vtk-9.0/vtkPolyData.h"
#include "vtk-9.0/vtkSTLWriter.h"
#include "vtk-9.0/vtkMassProperties.h"

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
	~geometry();

	string createGeometry(shapeType type, double height, string pathToSave);

	vector<vector<Point3f>> getPointCloud() {
		return this->pointCloud;
	}

	vtkSmartPointer<vtkPolyData> getObject3D() {
		return this->object3D;
	}

	double getObjectVolume() {
		return this->objectVolume;
	}

	
private:
	//functions
	string triangulate();
	void createPointCloud(shapeType type, double height);
	void saveObject3D(string path);
	void calculateVolume();
	shape createShape(shapeType type, double depth);
	string checkIfPathExists(string path);

	//variables
	vector<vector<Point3f>> pointCloud;
	vtkSmartPointer<vtkPolyData> object3D;

	double getMeshDensity(shapeType type);

	//variables
	double objectVolume = 0;

protected:
	string success = "success";

};

#endif #pragma once
