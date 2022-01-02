#include "geometry.h"

geometry::geometry() {}
geometry::~geometry() {}


geometry::geometry(shapeType type, string pathToSave) {
	createPointCloud(type);
	triangulate();
	saveObject3D(pathToSave);
}

void geometry::createPointCloud(shapeType type) {
	for (double i = 0; i < this->objectWidth; i += get_zAxisDist(type)) {
		shape sh = createShape(type, i);
		this->pointCloud.push_back(sh.getPoints());
	}
}

double geometry::get_zAxisDist(shapeType type) {
	switch (type)
	{
	case geometry::circle:
		return 0.1;
	case geometry::rectangle:
	case geometry::triangle:
		return 5;
	default:
		return 1;
	}
}


//this design pattern is called "factory"
shape geometry::createShape(shapeType type, double depth) {
	switch (type)
	{
	case shapeType::circle:
		return *new Circle(1, 100, depth);
	case shapeType::rectangle:
		return *new Rectangle(1, 1, depth);
	case shapeType::triangle:
		return *new Triangle();
	default:
		break;
	}
}

void geometry::triangulate() {
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer< vtkPoints >::New();
	for (int i = 0; i < this->pointCloud.size(); i++) {
		for (int j = 0; j < this->pointCloud[i].size(); j++) {
			points->InsertNextPoint(this->pointCloud[i][j].x, this->pointCloud[i][j].y, this->pointCloud[i][j].z);
		}
	}
	int numPoints = this->pointCloud[0].size();
	vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();

	for (int i = 0; i < this->pointCloud.size() - 1; i++) {
		vtkSmartPointer<vtkTriangle> triangle_4 = vtkSmartPointer<vtkTriangle>::New();
		triangle_4->GetPointIds()->SetId(0, i * numPoints);
		triangle_4->GetPointIds()->SetId(1, (i + 1) * numPoints - 1);
		triangle_4->GetPointIds()->SetId(2, (i + 1) * numPoints);
		triangles->InsertNextCell(triangle_4);

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
		vtkSmartPointer<vtkTriangle> triangle_3 = vtkSmartPointer<vtkTriangle>::New();
		triangle_3->GetPointIds()->SetId(2, i * numPoints + numPoints - 1);
		triangle_3->GetPointIds()->SetId(1, i * numPoints + numPoints);
		triangle_3->GetPointIds()->SetId(0, i * numPoints + 2 * numPoints - 1);
		triangles->InsertNextCell(triangle_3);
	}

	object3D = vtkSmartPointer<vtkPolyData>::New();
	object3D->SetPolys(triangles);
	object3D->SetPoints(points);
}

void geometry::saveObject3D(string path) {
	vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();
	writer->SetFileName(path.c_str());
	writer->SetInputData(this->object3D);
	writer->Write();
}