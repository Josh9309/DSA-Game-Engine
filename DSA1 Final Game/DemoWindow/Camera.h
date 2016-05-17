#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include "ShaderManager.h"
#include "GameObject.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Texture.h"

#pragma once
class Camera
{
public:
	Camera();
	~Camera();
	void Update(vec3 addedForce, float deltaTime);
	float FOV; //Field of View
	float aspectRatio;
	float nearDistance;
	float farDistance;
	float zoom;
	float width;
	float height;
	Transform transform;
	RigidBody rigidBody;
	mat4 cameraMatrix;
};

