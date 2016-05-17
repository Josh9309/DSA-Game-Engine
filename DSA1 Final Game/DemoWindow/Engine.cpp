#include "Engine.h" 
#include "Texture.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace {
	std::map<int, bool> keyIsDown;
	std::map<int, bool> keyWasDown;
	
	void mouseClick(GLFWwindow * windowPtr, int button, int action, int mods)
	{
		keyIsDown[button] = action;
	}

	void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keyIsDown[key] = action;
	}
}

struct Vertex {
	glm::vec3 loc;
	glm::vec2 uv;
};

struct Transform {
	glm::vec3 loc;
	glm::vec3 rot;
	glm::vec3 size;
	glm::mat4 world; // object-world transform matrix
};

struct Object {
	Transform transform;
	std::string  textureFile;
};


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

	//This Enables the Alpha Transparency for Blending 
	//Some Graphic Techniques wont work with this on
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

bool Engine::bufferModel()
{

	std::vector<glm::vec3> locs =
	{
		{ 1,1,0 },
		{ -1, 1,0 },
		{ -1,-1,0 },
		{ 1,-1,0 }
	};

	std::vector<unsigned int> locInds =
	{
		0, 1,2,
		0, 2,3
	};

	std::vector<glm::vec2> uvs = 
	{
		{1,1},
		{0,1},
		{0,0},
		{1,0}
	};

	std::vector<unsigned int> uvInds =
	{
		0, 1, 2,
		0, 2, 3
	};

	vertCount = locInds.size();

	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i].loc = locs[locInds[i]];
		vertBufData[i].uv = uvs[uvInds[i]];
	}

	

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, //where to copy to
		sizeof(Vertex) * vertCount, //# bytes to copy
		&vertBufData[0], //where to copy from
		GL_STATIC_DRAW); //"hint to OpenGL

	//Location
	glEnableVertexAttribArray(0); //Attribute index - 0
	glVertexAttribPointer(
		0, //Attribute index - 0 in this case
		3, //Number of components (x,y,z)
		GL_FLOAT, //Type of data
		GL_FALSE, //should we normalize the data
		sizeof(Vertex), // stride (bytes per vertex)
		0); // offset to this attribute

	//UV 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, //Attribute index - 0 in this case
		2, //Number of components (x,y,z)
		GL_FLOAT, //Type of data
		GL_FALSE, //should we normalize the data
		sizeof(Vertex), // stride (bytes per vertex)
		(void*)sizeof(glm::vec3)); // offset to this attribute
	return true;
}

bool Engine::gameLoop()
{

	Texture paint = Texture("paintTexture.jpg");
	paint.LoadTexture();

	//This sets up second texture
	Texture paperBlue = Texture("paper-blue.jpg");
	paperBlue.LoadTexture();

	Texture redFruit = Texture("redFruit.png");
	redFruit.LoadTexture();

	Texture blueFruit = Texture("blueFruit.png");
	Texture yellowFruit = Texture("yellowFruit.png");
	Texture player = Texture("player.png");
	
	player.LoadTexture();
	blueFruit.LoadTexture();
	yellowFruit.LoadTexture();
	//object creation
	Object * objs = new Object[4];

	objs[0].textureFile = "redFruit.png";
	objs[0].transform.loc = glm::vec3(-.60, .30, 0); //center of screen
	objs[0].transform.rot = glm::vec3(0, 0, 0);
	objs[0].transform.size = glm::vec3(.1, .1, 1); //width, height, depth

	objs[1].textureFile = "blueFruit.png";
	objs[1].transform.loc = glm::vec3(.6, .6, 0); //center of screen
	objs[1].transform.rot = glm::vec3(0, 0, 0);
	objs[1].transform.size = glm::vec3(.10, .10, 1); //width, height, depth

	objs[2].textureFile = "yellowFruit.png";
	objs[2].transform.loc = glm::vec3(0, .5, 0); //center of screen
	objs[2].transform.rot = glm::vec3(0, 0, 0);
	objs[2].transform.size = glm::vec3(.10, .10, 1); //width, height, depth

	objs[3].textureFile = "player.png";
	objs[3].transform.loc = glm::vec3(0, -.5, 0); //center of screen
	objs[3].transform.rot = glm::vec3(0, 0, 0);
	objs[3].transform.size = glm::vec3(.20, .30, 1); //width, height, depth

	//set the click function when loading the game
	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);

	//set the keypress function when loading game
	glfwSetKeyCallback(GLFWwindowPtr, keyCallBack);

	//clear canvas
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	bool i1 = true; //display image 1 bool
	bool i2 = false; //display image 2 bool
	bool i3 = false;
	//game loop until the user closes the window
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		
		glClear(GL_COLOR_BUFFER_BIT);

		objs[0].transform.world = translate(objs[0].transform.loc)* scale(objs[0].transform.size) * glm::yawPitchRoll(objs[0].transform.rot.y, objs[0].transform.rot.x, objs[0].transform.rot.z);
		objs[1].transform.world = translate(objs[1].transform.loc)* scale(objs[1].transform.size) * glm::yawPitchRoll(objs[1].transform.rot.y, objs[1].transform.rot.x, objs[1].transform.rot.z);
		objs[2].transform.world = translate(objs[2].transform.loc)* scale(objs[2].transform.size) * glm::yawPitchRoll(objs[2].transform.rot.y, objs[2].transform.rot.x, objs[2].transform.rot.z);
		objs[3].transform.world = translate(objs[3].transform.loc)* scale(objs[3].transform.size) * glm::yawPitchRoll(objs[3].transform.rot.y, objs[3].transform.rot.x, objs[3].transform.rot.z);

		glUniformMatrix4fv(2, 1, false, &objs[0].transform.world[0][0]);

		//render game objects
		glBindTexture(GL_TEXTURE_2D, redFruit.texID);
		//glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		
		glUniformMatrix4fv(2, 1, false, &objs[1].transform.world[0][0]);
		glBindTexture(GL_TEXTURE_2D, blueFruit.texID);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

		glUniformMatrix4fv(2, 1, false, &objs[2].transform.world[0][0]);
		glBindTexture(GL_TEXTURE_2D, yellowFruit.texID);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

		glUniformMatrix4fv(2, 1, false, &objs[3].transform.world[0][0]);
		glBindTexture(GL_TEXTURE_2D, player.texID);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		//glBindTexture(GL_TEXTURE_2D, player.texID);
		//if (keyIsDown[GLFW_MOUSE_BUTTON_1] && keyWasDown[GLFW_MOUSE_BUTTON_1] == false)
		//{
		//	if (i1)
		//	{
		//		i1 = false;
		//		i2 = true;
		//		i3 = false;
		//	}
		//	else if (i2)
		//	{
		//		i1 = false;
		//		i2 = false;
		//		i3 = true;
		//	}
		//	else if (i3)
		//	{
		//		i1 = true;
		//		i2 = false;
		//		i3 = false;
		//	}
		//}

		//if (i1)
		//{
		//	glBindTexture(GL_TEXTURE_2D, redFruit.texID); // LEFT OFFF HERE
		//}
		//else if (i2)
		//{
		//	glBindTexture(GL_TEXTURE_2D, paint.texID); // LEFT OFFF HERE
		//}
		//else if (i3)
		//{
		//	glBindTexture(GL_TEXTURE_2D, paperBlue.texID); // LEFT OFFF HERE
		//}

		//Swap the front (what the screen displays) and back (what OpenGL draws to) buffers.
		glfwSwapBuffers(GLFWwindowPtr);
		//Update physical simulation
		//draw buffered models
		//Process input/window events
		//process queued window, mouse & keyboard callback events
		keyWasDown = keyIsDown;
		glfwPollEvents();

		if (keyIsDown[GLFW_KEY_ESCAPE] && keyWasDown[GLFW_KEY_ESCAPE] == false) 
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}
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


