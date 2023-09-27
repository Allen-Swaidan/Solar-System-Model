#include "shape.h"

Shape::Shape()
{
	cubeVertices = 
	{
		-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
	};

	pyramidVertices = 
	{
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //front face
		 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, //right face
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, //back face
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //left face
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, //base – left front
		 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f //base- right back
	};

	octahedronVertices =
	{
		0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, //front top face
		0.0f, 1.0f, 0.0f, -1.0, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, //left-most top face
		0.0f, 1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f, -1.0f, //back top face
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f, //right-most top face
		1.0f, 0.0f, -1.0f, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, //base - left back
		1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, //base - right front
		0.0f, -1.0f, 0.0f, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, //left-most bottom face
		0.0f, -1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f, -1.0f, //back bottom face
		0.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f, //right-most bottom face
		0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f // front bottom face
	};

}

void Shape::cube()
{
	buffer.createBuffer(108);
	buffer.FillVBO(Buffer::VERTEX_BUFFER, sizeof(cubeVertices), cubeVertices.data(), Buffer::SINGLE);
	buffer.LinkBuffer("position", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	buffer.LinkBuffer("varyingColor", Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	buffer.Render(Buffer::TRIANGLES);
	buffer.DestroyBuffer();
}

void Shape::pyramid()
{
	buffer.createBuffer(54);
	buffer.FillVBO(Buffer::VERTEX_BUFFER, sizeof(pyramidVertices), pyramidVertices.data(), Buffer::SINGLE);
	buffer.LinkBuffer("position", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	buffer.LinkBuffer("varyingColor", Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	buffer.Render(Buffer::TRIANGLES);
	buffer.DestroyBuffer();
}

void Shape::octahedron()
{
	buffer.createBuffer(108);
	buffer.FillVBO(Buffer::VERTEX_BUFFER, sizeof(octahedronVertices), octahedronVertices.data(), Buffer::SINGLE);
	buffer.LinkBuffer("position", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	buffer.LinkBuffer("varyingColor", Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	buffer.Render(Buffer::TRIANGLES);
	buffer.DestroyBuffer();
}



