#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include "ShaderManager.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>

#pragma once
class Engine
{
public:
	Engine();
	~Engine();
	bool init();
	bool bufferModel();
	bool gameLoop();
	bool useShaders();
	

private:
	GLFWwindow* GLFWwindowPtr;
	GLuint vertArr;
	GLuint vertBuf;
	unsigned int vertCount;
	ShaderManager shademanage;
};

