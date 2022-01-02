// Meshing_3D.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "geometry.h"

int main()
{

    geometry* geo = new geometry(geometry::shapeType::circle, "C:/Users/Legion Y540/Desktop/cylinder.stl");

    vector<vector<Point3f>> points = geo->getPointCloud();

}
