#pragma once
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

class Texture
{
public:
	Texture();
	~Texture();
	Texture(std::string file);
	void LoadTexture();
	unsigned int texID;

private:
	std::string textureFile;
};

