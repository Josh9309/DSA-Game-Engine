#include "Engine.h"



Engine::Engine()
{
}


Engine::~Engine()
{
}

bool Engine::init()
{
	
	if (glfwInit() == GL_FALSE) //glfwInit() needs to be called before creating window
	{
		return false;
	}

	GLFWwindowPtr = glfwCreateWindow(800, 600, "Josh Malmquist DSA1 Engine", NULL, NULL);

	if (this->GLFWwindowPtr != nullptr)
	{
		glfwMakeContextCurrent(this->GLFWwindowPtr);
	}
	else
	{
		glfwTerminate();
		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}
	return true;
}

bool Engine::bufferModel()
{

	std::vector<glm::vec3> locs =
	{
		{ .9,.9,0 },
		{ -.9, .9,0 },
		{ -.9,-.9,0 },
		{ .9,-.9,0 }
	};

	std::vector<unsigned int> locInds =
	{
		0, 1,2,
		0, 2,3
	};

	vertCount = locInds.size();

	std::vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = locs[locInds[i]];
	}

	

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, //where to copy to
		sizeof(glm::vec3) * vertCount, //# bytes to copy
		&vertBufData[0], //where to copy from
		GL_STATIC_DRAW); //"hint to OpenGL

	glEnableVertexAttribArray(0); //Attribute index - 0
	glVertexAttribPointer(
		0, //Attribute index - 0 in this case
		3, //Number of components (x,y,z)
		GL_FLOAT, //Type of data
		GL_FALSE, //should we normalize the data
		sizeof(glm::vec3), // stride (bytes per vertex)
		0); // offset to this attribute

	return true;
}

bool Engine::gameLoop()
{
	//clear canvas
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);


	//game loop until the user closes the window
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//render game objects
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

		//Swap the front (what the screen displays) and back (what OpenGL draws to) buffers.
		glfwSwapBuffers(GLFWwindowPtr);
		//Update physical simulation
		//draw buffered models
		//Process input/window events
		//process queued window, mouse & keyboard callback events
		glfwPollEvents();
	}

	glfwTerminate();
	return true;
}

bool Engine::useShaders()
{
	bool shaderloaded = shademanage.loadShaders("shaders/vShader.glsl", "shaders/fShader.glsl");

	if(shaderloaded == true)
	{
		glUseProgram(shademanage.getProgram());
		return true;
	}
	return false;
}
