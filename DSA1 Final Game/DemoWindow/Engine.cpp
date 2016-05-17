#include "Engine.h" 
#include "Texture.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "GameObject.h"


#define _USE_MATH_DEFINES
#include <math.h>

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

/*struct Transform {
	glm::vec3 loc;
	glm::vec3 rot;
	glm::vec3 size;
	glm::mat4 world; // object-world transform matrix
};

struct RigidBody {
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
};

struct Object {
	Transform transform;
	RigidBody rigidBody{ glm::vec3(0,0,0), glm::vec3(0,0,0), 1.0f };
	std::string  textureFile;
};*/




Engine::Engine()
{
	deltaTime = 0.0f;
	previousFrameTime = 0.0f;
	FPSEnable = false;
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

	currentTime = glfwGetTime();
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
	Texture blueFruit = Texture("blueFruit.png");
	Texture yellowFruit = Texture("yellowFruit.png");
	Texture player = Texture("player.png");
	Texture forest = Texture("forest.jpg");

	/*player.LoadTexture();
	blueFruit.LoadTexture();
	yellowFruit.LoadTexture();
	forest.LoadTexture();*/

	//camera creation
	camera = new Camera();

	//object creation
	GameObject * objs = new GameObject[5];

	objs[0] = GameObject(redFruit, vec3(-.60, .30, 0), vec3(0, 0, 0), vec3(.1, .1, 1), axis_Aligned_Bounding_Box);
	objs[1] = GameObject(blueFruit, vec3(.6, .6, 0), vec3(0, 0, 0), vec3(.10, .10, 1), axis_Aligned_Bounding_Box);

	objs[2] = GameObject(yellowFruit, vec3(0, .5, 0), vec3(0, 0, 0), vec3(.10, .10, 1), axis_Aligned_Bounding_Box);

	objs[3] = GameObject(player, vec3(0, -.5, 0), vec3(0, 0, 0), vec3(.20, .30, 1), axis_Aligned_Bounding_Box);

	objs[4] = GameObject(forest, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), colliderless);

	for (int i = 0; i < 5; i++)
	{
		objs[i].texture.LoadTexture();
	}

	/*redFruit.LoadTexture();
	player.LoadTexture();
	blueFruit.LoadTexture();
	yellowFruit.LoadTexture();
	forest.LoadTexture();*/

	//set the click function when loading the game
	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);

	//set the keypress function when loading game
	glfwSetKeyCallback(GLFWwindowPtr, keyCallBack);

	//clear canvas
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	
	//game loop until the user closes the window
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		currentTime = glfwGetTime();
		deltaTime = (currentTime - previousFrameTime);
		previousFrameTime = currentTime;

		objs[0].addForce(vec3(0, -.5, 0), deltaTime);
		objs[1].addForce(vec3(0, -.5, 0), deltaTime);
		objs[2].addForce(vec3(0, -.5, 0), deltaTime);
		

		//update object 4
		glm::vec3 vel4;
		if ((keyIsDown[GLFW_KEY_A] && keyWasDown[GLFW_KEY_A]) || (keyIsDown[GLFW_KEY_LEFT] && keyWasDown[GLFW_KEY_LEFT]))
		{
			vel4 = glm::vec3(-2.5, 0, 0);
		}
		else if ((keyIsDown[GLFW_KEY_D] && keyWasDown[GLFW_KEY_D]) || (keyIsDown[GLFW_KEY_RIGHT] && keyWasDown[GLFW_KEY_RIGHT]))
		{
			vel4 = glm::vec3(2.5, 0, 0);
		}
		else
		{
			objs[3].rigidBody.velocity = glm::vec3(0,0,0);
		}

		objs[3].addForce(vel4, deltaTime);
		cout << objs[1].transform.loc.x << ", " << objs[1].transform.loc.y << ", " << objs[1].transform.loc.z << endl;

		if(objs[3].collidesWith(objs[0]))
		{
			cout << "red Collision" << endl;
			objs[0].transform.loc.y = 0.5;
			objs[0].rigidBody.velocity = glm::vec3(0, 0, 0);

		}
		if (objs[3].collidesWith(objs[1]))
		{
			cout << " blue Collision" << endl;
			objs[1].transform.loc.y = 0.5;
			objs[1].rigidBody.velocity = glm::vec3(0, 0, 0);

		}
		if (objs[3].collidesWith(objs[2]))
		{
			cout << "yellow Collision" << endl;
			objs[2].transform.loc.y = 0.5;
			objs[2].rigidBody.velocity = glm::vec3(0, 0, 0);

		}

		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		////Projection Camera Matrix Stuff

		////View Matrix
		//vec3 camLoc = { 0,0,2 };
		//vec3 camRot = { 0,0,0 };

		//glm::mat3 rotMat = (glm::mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);

		//vec3 eye = camLoc;
		//vec3 center = eye + rotMat * vec3(0, 0, -1);
		//vec3 up = rotMat * vec3(0, 1, 0);

		//mat4 lookAtMat = glm::lookAt(eye, center, up);

		////perspective projection matrix
		//float zoom = 1.0f;
		//int width = 800;
		//int height = 600;

		//float fovy = 3.14159f * .4f / zoom;
		//float aspect = (float)width / (float)height;
		//float zNear = .01f;
		//float zFar = 1000.f;

		//mat4 perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

		///*mat4 cameraMat =
		//{
		//	1,0,0,0,
		//	0,1,0,0,
		//	0,0,1,0,
		//	0,0,0,1
		//};*/

		//mat4 cameraMat = perspectiveMat * lookAtMat;

		//glUniformMatrix4fv(3, 1, false, &cameraMat[0][0]); //sends cameraMat to vertex shader
		///////////////////////////////////////////////////////////////

		if (FPSEnable)
		{
			float sens = .005;
			int w = 800, h = 600;
			double x, y;
			glfwGetCursorPos(GLFWwindowPtr, &x, &y);

			camera->transform.rot.y -= sens*(x - w*.5f); //yaw
			camera->transform.rot.x -= sens*(y - h*.5f); //Pitch
			camera->transform.rot.x = glm::clamp(camera->transform.rot.x, -.5f * (float)M_PI, .5f*(float)M_PI);
			glfwSetCursorPos(GLFWwindowPtr, w * .5f, h * .5f);

			vec3 camVel;
			glm::mat3 R = (glm::mat3)glm::yawPitchRoll(camera->transform.rot.y, camera->transform.rot.x, camera->transform.rot.z);

			if (keyIsDown[GLFW_KEY_H] && keyWasDown[GLFW_KEY_H])
			{
				camVel += R * vec3(-.5, 0, 0);
			}
			else if (keyIsDown[GLFW_KEY_K] && keyWasDown[GLFW_KEY_K])
			{
				camVel += R * vec3(.5, 0, 0);
			}
			else if (keyIsDown[GLFW_KEY_U] && keyWasDown[GLFW_KEY_U])
			{
				camVel += R * vec3(0, 0, -.5);
			}
			else if (keyIsDown[GLFW_KEY_J] && keyWasDown[GLFW_KEY_J])
			{
				camVel += R * vec3(0, 0, .5);
			}
			else 
			{
				camera->rigidBody.velocity = vec3(0,0,0);
			}

			float speed = 1.f;
			if(camVel != vec3())
			{
				camVel = glm::normalize(camVel) * speed;
			}

			camera->Update(camVel, deltaTime);
		}
		else
		{
			camera->Update(vec3(0, 0, 0), deltaTime);
		}

		objs[0].transform.world = translate(objs[0].transform.loc)* glm::yawPitchRoll(objs[0].transform.rot.y, objs[0].transform.rot.x, objs[0].transform.rot.z) * scale(objs[0].transform.size);
		objs[1].transform.world = translate(objs[1].transform.loc)* glm::yawPitchRoll(objs[1].transform.rot.y, objs[1].transform.rot.x, objs[1].transform.rot.z) * scale(objs[1].transform.size);
		objs[2].transform.world = translate(objs[2].transform.loc)* glm::yawPitchRoll(objs[2].transform.rot.y, objs[2].transform.rot.x, objs[2].transform.rot.z) * scale(objs[2].transform.size);
		objs[3].transform.world = translate(objs[3].transform.loc)* glm::yawPitchRoll(objs[3].transform.rot.y, objs[3].transform.rot.x, objs[3].transform.rot.z) * scale(objs[3].transform.size);
		objs[4].transform.world = translate(objs[4].transform.loc)* glm::yawPitchRoll(objs[4].transform.rot.y, objs[4].transform.rot.x, objs[4].transform.rot.z) * scale(objs[4].transform.size);


		glUniformMatrix4fv(2, 1, false, &objs[4].transform.world[0][0]);
		glBindTexture(GL_TEXTURE_2D, objs[4].texture.texID);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);



		glUniformMatrix4fv(2, 1, false, &objs[0].transform.world[0][0]);

		//render game objects
		glBindTexture(GL_TEXTURE_2D, objs[0].texture.texID);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		
		glUniformMatrix4fv(2, 1, false, &objs[1].transform.world[0][0]);
		glBindTexture(GL_TEXTURE_2D, objs[1].texture.texID);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

		glUniformMatrix4fv(2, 1, false, &objs[2].transform.world[0][0]);
		glBindTexture(GL_TEXTURE_2D, objs[2].texture.texID);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

		glUniformMatrix4fv(2, 1, false, &objs[3].transform.world[0][0]);
		glBindTexture(GL_TEXTURE_2D, objs[3].texture.texID);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

		
		

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
		if (keyIsDown[GLFW_KEY_F] && keyWasDown[GLFW_KEY_F] == false)
		{
			if(FPSEnable)
			{
				FPSEnable = false;
			}
			else
			{
				FPSEnable = true;
			}
		}
		if(objs[0].transform.loc.y < -1 )
		{
			objs[0].transform.loc.y = 0.5;
			objs[0].rigidBody.velocity = glm::vec3(0,0,0);
		}
		if (objs[1].transform.loc.y < -1)
		{
			objs[1].transform.loc.y = 0.5;
			objs[1].rigidBody.velocity = glm::vec3(0, 0, 0);
		}
		if (objs[2].transform.loc.y < -1)
		{
			objs[2].transform.loc.y = 0.5;
			objs[2].rigidBody.velocity = glm::vec3(0, 0, 0);
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


