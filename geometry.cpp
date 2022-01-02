#include "geometry.h"

geometry::geometry() {}
geometry::~geometry() {}


//this design pattern is called "factory"
shape geometry::createShape(shape::shapeType type) {
	switch (type)
	{
	case shape::shapeType::circle:
		return *new Circle();
	case shape::shapeType::rectangle:
		return *new Rectangle();
	case shape::shapeType::triangle:
		return *new Triangle();
	default:
		break;
	}
}