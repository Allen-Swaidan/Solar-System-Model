#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <string>

class Shader
{
public:
	static Shader* Instance();

	std::string readShaderSource(const char *filePath);
	bool createProgram();
	bool createShaders();
	bool compileShaders();
	void attachShaders();
	GLuint linkProgram();

	//error catching modules
	bool checkOpenGLError();
	void printShaderLog(GLuint shader);
	void printProgramLog(int prog);

private:
	Shader();
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	GLuint vfProgram;
	GLuint vShader;
	GLuint fShader;
};
#endif