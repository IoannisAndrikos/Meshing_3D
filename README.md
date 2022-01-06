## Meshing 3D.

**Projects/components**

	1. all functionalities are in Meshing_3D (is a static library .lib file)
	2. the unit test are in UnitTesting (is an executable .exe file)
	3. all the external dependencies are included into thrird_party_libraries

**Third Party libraries:**

	1. OpenCV 4.5.1 -> manage efficiently the 2D and 3D points
	2. Visualization toolkit (VTK) 9.0.3 -> perform computational geometry operations

**TODOs:**

	1. Set to your enviroment variables Path the OpenCV and VTK dll paths:
		a. ...Meshing_3D\third_party_libraries\opencv\x64\vc15\bin
		b. ...Meshing_3D\third_party_libraries\vtk\bin
	3. Change the "myPath" value in UnitTesting/test.cpp (line:6) with a path of your local enviroment
	4. Run tests
	5. Three 3D objects with the names: cylinder.stl, bar.stl, triangular.stl will be generated in path that you set.
	6. Enjoy
