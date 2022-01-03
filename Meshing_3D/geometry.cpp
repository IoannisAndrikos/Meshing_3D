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
	Check if given path exists
	*/
	string parentFolder = experimental::filesystem::path(path).parent_path().generic_string();
	struct stat buffer; 
	return stat(parentFolder.c_str(), &buffer) == 0 ? success : "The given path is not correct";
}



void geometry::createPointCloud(shapeType type, double height) {
	/* here we create a shape of the selected type. The shape contain x, y, z coordinate points
	*/
	for (double i = 0; i <= height - 1; i += getMeshDensity(type)) {
		shape sh = createShape(type, i);
		this->pointCloud.push_back(sh.getPoints());
	}
}

double geometry::getMeshDensity(shapeType type) {
	/* curved objects need high mesh density to be reconstructed (e.g cylinder)
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
	* this design pattern is called "factory"
	we use this to manage better the objects construction
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
	/* this function triangulate on object given the point cloud of it.
	* Briefly, this method is achieved by connecting the opposite points 
	between two coherent contours of equal number of 3D points
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

				//connect the last point of the i-th contour with the first point of the i+1-th contour 
				vtkSmartPointer<vtkTriangle> triangle_4 = vtkSmartPointer<vtkTriangle>::New();
				triangle_4->GetPointIds()->SetId(0, i * numPoints);
				triangle_4->GetPointIds()->SetId(1, (i + 1) * numPoints - 1);
				triangle_4->GetPointIds()->SetId(2, (i + 1) * numPoints);
				triangles->InsertNextCell(triangle_4);

				//process for the middle points
				//connect the opposite points of each contour point set
				for (int j = 0; j < numPoints - 1; j++) {
					vtkSmartPointer<vtkTriangle> triangle_1 = vtkSmartPointer<vtkTriangle>::New();
					triangle_1->GetPointIds()->SetId(2, i * numPoints + j);
					triangle_1->GetPointIds()->SetId(1, i * numPoints + j + 1);
					triangle_1->GetPointIds()->SetId(0, i * numPoints + j + numPoints);

					vtkSmartPointer<vtkTriangle> triangle_2 = vtkSmartPointer<vtkTriangle>::New();
					triangle_2->GetPointIds()->SetId(0, i * numPoints + j + numPoints);
					triangle_2->GetPointIds()->SetId(1, i * numPoints + j + numPoints + 1);
					triangle_2->GetPointIds()->SetId(2, i * numPoints + j + 1);

					triangles->InsertNextCell(triangle_1);
					triangles->InsertNextCell(triangle_2);
				}

				//connect the last point of the i-th contour with the first point of the i+1-th contour 
				vtkSmartPointer<vtkTriangle> triangle_3 = vtkSmartPointer<vtkTriangle>::New();
				triangle_3->GetPointIds()->SetId(2, i * numPoints + numPoints - 1);
				triangle_3->GetPointIds()->SetId(1, i * numPoints + numPoints);
				triangle_3->GetPointIds()->SetId(0, i * numPoints + 2 * numPoints - 1);
				triangles->InsertNextCell(triangle_3);
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
	/*this function save the 3D object as an STL file into a given path
	*/
	vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();
	writer->SetFileName(path.c_str());
	writer->SetInputData(this->object3D);
	writer->Write();
}

void geometry::calculateVolume() {
	/*this caclulates the volume of the 3D object
	*/
	vtkSmartPointer<vtkMassProperties> massProperties = vtkSmartPointer<vtkMassProperties>::New();
	massProperties->SetInputData(this->object3D);
	massProperties->Update();
	this->objectVolume = massProperties->GetVolume();
}