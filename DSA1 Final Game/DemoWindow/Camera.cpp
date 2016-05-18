#include "Camera.h"


Camera::Camera()
{
	rigidBody.mass = 1.0f;
	rigidBody.force = vec3();
	rigidBody.velocity = vec3();
	transform.loc = { 0,0,2 };
	transform.rot = { 0,0,0 };

	glm::mat3 rotMat = (glm::mat3)glm::yawPitchRoll(transform.rot.y, transform.rot.x, transform.rot.z);

	vec3 eye = transform.loc;
	vec3 center = eye + rotMat * vec3(0, 0, -1);
	vec3 up = rotMat * vec3(0, 1, 0);

	mat4 lookAtMat = glm::lookAt(eye, center, up);

	zoom = 1.0f;
	width = 800;
	height = 600;

	FOV = 3.14159f * .4f / zoom;
	aspectRatio = (float)width / (float)height;
	nearDistance = .01f;
	farDistance = 1000.f;

	mat4 perspectiveMat = glm::perspective(FOV, aspectRatio, nearDistance, farDistance);

	cameraMatrix = perspectiveMat * lookAtMat;

	glUniformMatrix4fv(4, 1, false, &cameraMatrix[0][0]); //sends cameraMat to vertex shader
}


Camera::~Camera()
{
}

void Camera::Update(vec3 addedForce, float deltaTime)
{

	rigidBody.force = addedForce;
	rigidBody.velocity += (rigidBody.force / rigidBody.mass) *deltaTime;
	rigidBody.force = vec3();
	transform.loc += rigidBody.velocity *deltaTime;


	//////////////////////////////////////////////////////////////////////
	glm::mat3 rotMat = (glm::mat3)glm::yawPitchRoll(transform.rot.y, transform.rot.x, transform.rot.z);

	vec3 eye = transform.loc;
	vec3 center = eye + rotMat * vec3(0, 0, -1);
	vec3 up = rotMat * vec3(0, 1, 0);

	mat4 lookAtMat = glm::lookAt(eye, center, up);
	mat4 perspectiveMat = glm::perspective(FOV, aspectRatio, nearDistance, farDistance);

	cameraMatrix = perspectiveMat * lookAtMat;

	glUniformMatrix4fv( 4, 1, false, &cameraMatrix[0][0]); //sends cameraMat to vertex shader
}
