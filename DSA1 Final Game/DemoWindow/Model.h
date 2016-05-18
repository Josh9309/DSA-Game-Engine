#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include "ShaderManager.h"

#include <string>
#include<sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using glm::vec3;
using glm::mat4;
using std::cout;
using std::cin;
using std::endl;

#pragma once

struct Vertex
{
	vec3 location;
	glm::vec2 uv;
	vec3 normal;
};

struct VertInd
{
	unsigned int  locInd;
	unsigned int uvInd;
	unsigned normInd;
};

class Model
{
public:
	Model();
	~Model();
	Model(std::string modFile);
	bool Buffer();
	bool Buffer(std::string objFile);
	void render(); 

private:
	GLuint vertArr;
	GLuint vertBuf;
	unsigned int vertCount;
	std::string modelFile;
};

