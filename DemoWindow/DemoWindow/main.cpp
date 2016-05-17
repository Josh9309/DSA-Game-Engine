#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <iostream>
#include <vector>

int main()
{
	if(glfwInit() == GL_FALSE)
	{
		return -1;
	}

	GLFWwindow* GLFWwindowPtr = glfwCreateWindow(800, 600, "Josh Malmquist DSA1 Engine", NULL, NULL);

	if(GLFWwindowPtr != nullptr)
	{
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else
	{
		glfwTerminate();
		return -1;
	}

	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	std::vector<glm::vec3> locs = 
	{
		{.9,.9,0},
		{-.9, .9,0},
		{-.9,-.9,0},
		{.9,-.9,0}
	};

	std::vector<unsigned int> locInds =
	{
		0, 1,2,
		0, 2,3
	};

	unsigned int vertCount = locInds.size();

	std::vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = locs[locInds[i]];
	}

	GLuint vertArr;
	GLuint vertBuf;

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
	
	//clear canvas
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	

	//game loop until the user closes the window
	while(!glfwWindowShouldClose(GLFWwindowPtr))
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

	std::cin.ignore();
	return 0;
}
