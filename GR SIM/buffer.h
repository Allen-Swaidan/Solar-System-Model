#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <string>
#include "shader.h"
#include <iostream>

class Buffer
{
public:

	enum VBOType {VERTEX_BUFFER, COLOR_BUFFER, TEXTURE_BUFFER};

	enum ComponentType { XY = 2, XYZ = 3, RGB = 3, RGBA = 4, UV = 2 };

	enum FillType {SINGLE = GL_STATIC_DRAW, MULTIPLE = GL_DYNAMIC_DRAW};

	enum DataType {INT = GL_INT, FLOAT = GL_FLOAT, UNSIGNED_INT = GL_UNSIGNED_INT};

	enum DrawType {POINTS = GL_POINTS, TRIANGLES = GL_TRIANGLES, LINES = GL_LINES};

	Buffer();
	void createBuffer(GLuint totalVertices);
	void FillVBO(VBOType VBOType, GLsizeiptr buffersize, GLfloat* data, FillType filltype);
	void LinkBuffer(const std::string& attribute, VBOType VBOType, ComponentType componentType, DataType dataType);
	void Render(DrawType drawType);
	void DestroyBuffer();

private:
	GLuint m_VAO;
	GLuint m_vertexVBO;
	GLuint m_colorVBO;
	GLuint m_textureVBO;
	GLuint m_totalVertices;

};

#endif
