#include "pch.h"

#include "../Meshing_3D/geometry.h"

TEST(Test1, Create_circular_3D_oject) {
	/*
	 * To run the test just change the path argument.
	 */
  geometry* geo = new geometry();
  string message = geo->createGeometry(geometry::shapeType::circle, 10, "C:/Users/Legion Y540/Desktop/cylinder.stl");
  EXPECT_EQ(message, "success");
}

TEST(Test2, Create_rectangular_3D_object) {

	geometry* geo = new geometry();
	string message = geo->createGeometry(geometry::shapeType::rectangle, 10, "C:/Users/Legion Y540/Desktop/bar.stl");
	EXPECT_EQ(message, "success");
}


TEST(Test3, Create_triangular_3D_object) {

	geometry* geo = new geometry();
	string message = geo->createGeometry(geometry::shapeType::triangle, 10, "C:/Users/Legion Y540/Desktop/triangular.stl");
	EXPECT_EQ(message, "success");
}


TEST(Test4, Problem_during_the_triangulation_process) {

	geometry* geo = new geometry();
	string message = geo->createGeometry(geometry::shapeType::triangle, 0, "C:/Users/Legion Y540/Desktop/triangular_with_zero_volume.stl");
	EXPECT_EQ(message, "Something went wrong during the triangulation process");
}


TEST(Test5, Give_wrong_path) {

	geometry* geo = new geometry();
	string message = geo->createGeometry(geometry::shapeType::circle, 10, "C:/Users/Legion Y540/Desktop/!!!WRONG PATH!!!! /cylinder.stl");
	EXPECT_EQ(message, "The given path is not correct");
}




int main(int argc, char* argv[]) {

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}