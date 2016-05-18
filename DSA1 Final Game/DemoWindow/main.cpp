#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <iostream>
#include <vector>
#include "Engine.h"

int main()
{
	Engine train = Engine();

	if (train.init() == false)
	{
		return -1;
	}

	if (train.bufferModels() == false)
	{
		return -1;
	}
	
	if(train.useShaders())
	{
		train.gameLoop();
	}
	
	std::cin.ignore();
	return 0;
}
