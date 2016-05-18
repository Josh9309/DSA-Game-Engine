#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include "ShaderManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Model.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>

using glm::vec3;
using glm::mat4;
using std::cout;
using std::cin;
using std::endl;

#pragma once
class Engine
{
public:
	Engine();
	~Engine();
	bool init();
	bool bufferModels();
	bool gameLoop();
	bool useShaders();
	bool collides();
	
private:
	GLFWwindow* GLFWwindowPtr;
	
	
	ShaderManager shademanage;
	GLfloat deltaTime;
	GLfloat currentTime;
	GLfloat previousFrameTime;
	Camera* camera;
	Model* gameModels = new Model[5];
	bool FPSEnable;
};

