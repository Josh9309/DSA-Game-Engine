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

#include "Texture.h"

struct Transform {
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

enum Colliders {
	colliderless = 0,
	axis_Aligned_Bounding_Box =1,
	sphere=2
};

using glm::vec3;
using glm::mat4;
using std::cout;
using std::cin;
using std::endl;

#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();
	GameObject(Texture text, vec3 loc, vec3 rot, vec3 siz, Colliders collideType);
	Texture texture;
	Transform transform;
	RigidBody rigidBody;
	void addForce(vec3 addedForce, float deltaTime);
	void resetVelocity();
	bool collidesWith(GameObject &object2);

private:
	Colliders colliderType;
};

