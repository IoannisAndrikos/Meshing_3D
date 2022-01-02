#include "pch.h"

#include "../Meshing_3D/geometry.h"

TEST(TestCaseName, TestName) {

  geometry* geo = new geometry(geometry::shapeType::circle, "C:/Users/Legion Y540/Desktop/cylinder.stl");
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

int main(int argc, char* argv[]) {

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}