#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>

#include <iostream>
#include <fstream>
#include <cstring>

#pragma once
class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	GLuint getProgram() const; //getter
	bool loadShaders(const char* vertexFile, const char* fragmentFile); //loads shaders to read and compile a shader file and return index where it is stored


private:
	GLuint programIndex; //index where the loaded shaders are stored on the graphics card
	GLuint loadShader(const char* file, GLenum shaderType);
};

