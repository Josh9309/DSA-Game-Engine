#include "Engine.h" 

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
	
	//COME BACK TO THIS IT IS NOT COMPLETE
	/*std::vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = locs[locInds[i]];

	}*/

	

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
	//This sets up one texture
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType("TestTexture.png", 0), "TestTexture.png");
	if (image == nullptr)
	{
		//load failed
	}

	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);

	FreeImage_Unload(image);

	unsigned int texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//upload texture bytes
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32Bit),
		FreeImage_GetHeight(image32Bit),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit));

	//set min filter to linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	FreeImage_Unload(image32Bit);

	glBindTexture(GL_TEXTURE_2D, 0);

	//This sets up second texture
	FIBITMAP* image2 = FreeImage_Load(FreeImage_GetFileType("paintTexture.jpg", 0), "paintTexture.jpg");
	if (image == nullptr)
	{
		//load failed
	}

	FIBITMAP* image32Bit2 = FreeImage_ConvertTo32Bits(image2);

	FreeImage_Unload(image2);

	unsigned int texID2;
	glGenTextures(1, &texID2);
	glBindTexture(GL_TEXTURE_2D, texID2);

	//upload texture bytes
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32Bit2),
		FreeImage_GetHeight(image32Bit2),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit2));

	//set min filter to linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	FreeImage_Unload(image32Bit2);

	glBindTexture(GL_TEXTURE_2D, 0);

	//This sets up second texture
	FIBITMAP* image3 = FreeImage_Load(FreeImage_GetFileType("paper-blue.jpg", 0), "paper-blue.jpg");
	if (image3 == nullptr)
	{
		//load failed
	}

	FIBITMAP* image32Bit3 = FreeImage_ConvertTo32Bits(image3);

	FreeImage_Unload(image3);

	unsigned int texID3;
	glGenTextures(1, &texID3);
	glBindTexture(GL_TEXTURE_2D, texID3);

	//upload texture bytes
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32Bit3),
		FreeImage_GetHeight(image32Bit3),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit3));

	//set min filter to linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	FreeImage_Unload(image32Bit3);

	glBindTexture(GL_TEXTURE_2D, 0);

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

		//render game objects
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		
		if (keyIsDown[GLFW_MOUSE_BUTTON_1] && keyWasDown[GLFW_MOUSE_BUTTON_1] == false)
		{
			if (i1)
			{
				i1 = false;
				i2 = true;
				i3 = false;
			}
			else if (i2)
			{
				i1 = false;
				i2 = false;
				i3 = true;
			}
			else if (i3)
			{
				i1 = true;
				i2 = false;
				i3 = false;
			}
		}
		
		if (i1) 
		{
			glBindTexture(GL_TEXTURE_2D, texID); // LEFT OFFF HERE
		}
		else if (i2) 
		{
			glBindTexture(GL_TEXTURE_2D, texID2); // LEFT OFFF HERE
		}
		else if (i3)
		{
			glBindTexture(GL_TEXTURE_2D, texID3); // LEFT OFFF HERE
		}

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

	glDeleteTextures(1, &texID);
	glDeleteTextures(1, &texID2);
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


