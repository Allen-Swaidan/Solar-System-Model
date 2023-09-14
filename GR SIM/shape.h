#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <array>
#include "buffer.h"

class Shape
{
public:
	Shape();
	void cube();
	void pyramid();
	void octahedron();

private:
	std::array<float, 108> cubeVertices;
	std::array<float, 54> pyramidVertices;
	std::array<float, 108> octahedronVertices;
	Buffer buffer;
};
#endif
