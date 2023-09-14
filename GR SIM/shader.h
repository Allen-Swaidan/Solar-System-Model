#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "buffer.h"

class Shader
{
public:

	static Shader* Instance();

	GLuint GetShaderProgramID();

	std::string readShaderSource(const char *filePath);
	bool createProgram();
	bool createShaders();
	bool compileShaders();
	void attachShaders();
	GLuint linkProgram();

	bool SendUniformData(const std::string& uniformName, GLint data);
	bool SendUniformData(const std::string& uniformName, GLuint data);
	bool SendUniformData(const std::string& uniformName, GLfloat data);

	bool SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y);
	bool SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z);
	bool SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	bool SendUniformData(const std::string& uniformName, const glm::mat4& data);
	bool SendUniformData(const std::string& uniformName, const GLfloat* data);

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