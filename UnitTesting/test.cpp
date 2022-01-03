#include "pch.h"

#include "../Meshing_3D/geometry.h"

TEST(Test1, Create_circular_3D_oject) {

  geometry* geo = new geometry(geometry::shapeType::circle, 10, "C:/Users/Legion Y540/Desktop/cylinder.stl");
  bool hasVolume = geo->getObjectVolume() > 0 ? true : false;
  EXPECT_EQ(hasVolume, true);
}


TEST(Test2, Create_rectangular_3D_object) {

	geometry* geo = new geometry(geometry::shapeType::rectangle, 10, "C:/Users/Legion Y540/Desktop/bar.stl"); 

	bool hasVolume = geo->getObjectVolume() > 0 ? true : false;
	EXPECT_EQ(hasVolume, true);
}


TEST(Test3, Create_triangular_3D_object) {

	geometry* geo = new geometry(geometry::shapeType::triangle, 10, "C:/Users/Legion Y540/Desktop/triangular.stl");
	bool hasVolume = geo->getObjectVolume() > 0 ? true : false;
	EXPECT_EQ(hasVolume, true);
}


TEST(Test4, Create_triangular_3D_object_with_zero_volome) {

	geometry* geo = new geometry(geometry::shapeType::triangle, 0, "C:/Users/Legion Y540/Desktop/triangular.stl");
	bool hasVolume = geo->getObjectVolume() > 0 ? true : false;
	EXPECT_EQ(hasVolume, false);
}



int main(int argc, char* argv[]) {

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}