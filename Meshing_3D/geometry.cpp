#include "geometry.h"

geometry::geometry() {}
geometry::~geometry() {}


string geometry::createGeometry(shapeType type, double height, string pathToSave) {
	string message = checkIfPathExists(pathToSave);
	if (message._Equal(this->success)) {
		createPointCloud(type, height);
	}
	else {
		return message;
	}
	message = triangulate();
	if (message._Equal(this->success)) {
		calculateVolume();
		saveObject3D(pathToSave);
	}
	return message;
}

string geometry::checkIfPathExists(string path) {
	/*
	Check if the given path exists
	If not return failure message
	*/
	string parentFolder = experimental::filesystem::path(path).parent_path().generic_string();
	struct stat buffer; 
	return stat(parentFolder.c_str(), &buffer) == 0 ? success : "The given path is not correct";
}



void geometry::createPointCloud(shapeType type, double height) {
	/* 
	Create a shape of the selected type. The shape contains x, y, z points
	*/
	for (double i = 0; i <= height - 1; i += getMeshDensity(type)) {
		shape sh = createShape(type, i);
		sh.loadPoints(this->pointCloud);
	}
}

double geometry::getMeshDensity(shapeType type) {
	/*
	Select the Mesh density according to the type of the shape.
	Curved objects need high mesh density to be reconstructed (e.g cylinder)
	not curved objects need less mesh deshity to be reconstructed (e.g. bar, triangular object)
	*/
	switch (type)
	{
	case geometry::circle:
		return 0.1;
	case geometry::rectangle:
	case geometry::triangle:
	default:
		return 1;
	}
}

shape geometry::createShape(shapeType type, double depth) {
	/*
	This design pattern is called "factory"
	we use this to manage better the construction of the objects
	*/
	switch (type)
	{
	case shapeType::circle:
		return *new Circle(1, depth);
	case shapeType::rectangle:
		return *new Rectangle(1, 1, depth);
	case shapeType::triangle:
		return *new Triangle(1, depth);
	default:
		break;
	}
}

string geometry::triangulate() {
	/* 
	Triangulate an object given the point cloud of it.
	Briefly, this method is achieved by connecting (faces/triangulars) the opposite points 
	between two continious contours that contain equal number of x,y,z points
	In fact, 4 points needs 2 faces to be connected
	e.g. Lets suppose that we have 4 points: P1, P2, P3, P4
		 P1 and P2 belong to the same set and P3 and P4 to another same set.
		 P1 is opposite to P3 while P2 is opposite to P4
		 Therefore, we need two faces: F1, F2
		 The F1 is defined as following: P1, P2, P3
		 The F2 is defined as following: P2, P3, P4
	*/
	try {
		if (!this->pointCloud.empty()) {
			vtkSmartPointer<vtkPoints> points = vtkSmartPointer< vtkPoints >::New();
			for (int i = 0; i < this->pointCloud.size(); i++) {
				for (int j = 0; j < this->pointCloud[i].size(); j++) {
					points->InsertNextPoint(this->pointCloud[i][j].x, this->pointCloud[i][j].y, this->pointCloud[i][j].z);
				}
			}
			int numPoints = this->pointCloud[0].size();
			vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();

			for (int i = 0; i < this->pointCloud.size() - 1; i++) {

				//connect the last two points of the i-th contour with the first point of conntour (i+1)-th contour
				vtkSmartPointer<vtkTriangle> triangle_1 = vtkSmartPointer<vtkTriangle>::New();
				triangle_1->GetPointIds()->SetId(0, i * numPoints);
				triangle_1->GetPointIds()->SetId(1, (i + 1) * numPoints - 1);
				triangle_1->GetPointIds()->SetId(2, (i + 1) * numPoints);
				triangles->InsertNextCell(triangle_1);

				//process for the middle points
				for (int j = 0; j < numPoints - 1; j++) {
					vtkSmartPointer<vtkTriangle> triangle_2 = vtkSmartPointer<vtkTriangle>::New();
					triangle_2->GetPointIds()->SetId(2, i * numPoints + j);
					triangle_2->GetPointIds()->SetId(1, i * numPoints + j + 1);
					triangle_2->GetPointIds()->SetId(0, i * numPoints + j + numPoints);
					triangles->InsertNextCell(triangle_2);

					vtkSmartPointer<vtkTriangle> triangle_3 = vtkSmartPointer<vtkTriangle>::New();
					triangle_3->GetPointIds()->SetId(0, i * numPoints + j + numPoints);
					triangle_3->GetPointIds()->SetId(1, i * numPoints + j + numPoints + 1);
					triangle_3->GetPointIds()->SetId(2, i * numPoints + j + 1);
					triangles->InsertNextCell(triangle_3);
				}

				//connect the first two points of the (i+1)-th contour with the last point of the i-th contour
				vtkSmartPointer<vtkTriangle> triangle_4 = vtkSmartPointer<vtkTriangle>::New();
				triangle_4->GetPointIds()->SetId(2, i * numPoints + numPoints - 1);
				triangle_4->GetPointIds()->SetId(1, i * numPoints + numPoints);
				triangle_4->GetPointIds()->SetId(0, i * numPoints + 2 * numPoints - 1);
				triangles->InsertNextCell(triangle_4);
			}

			object3D = vtkSmartPointer<vtkPolyData>::New();
			object3D->SetPolys(triangles);
			object3D->SetPoints(points);
			return this->success;
		}
		else {
			return "Something went wrong during the triangulation process";
		}
	}
	catch (Exception ex) {
		return "Something went wrong during the triangulation process";
	}
}

void geometry::saveObject3D(string path) {
	/*
	Save the 3D object as an STL file into a given path
	*/
	vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();
	writer->SetFileName(path.c_str());
	writer->SetInputData(this->object3D);
	writer->Write();
}

void geometry::calculateVolume() {
	/*
	Caclulate the volume of the 3D object
	*/
	vtkSmartPointer<vtkMassProperties> massProperties = vtkSmartPointer<vtkMassProperties>::New();
	massProperties->SetInputData(this->object3D);
	massProperties->Update();
	this->objectVolume = massProperties->GetVolume();
}