#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#define numVAOs 1
#define numVBOs 2

class Buffer
{
public:
	Buffer();
	void createBuffer();


private:
	GLuint vao[numVAOs], vbo[numVBOs];
};

#endif
