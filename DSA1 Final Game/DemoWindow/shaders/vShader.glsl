#version 430


layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvPosition; //cordinate
out vec2 fragUV;

layout (location = 2) uniform mat4 worldTransformMatrix;
layout (location = 3) uniform mat4 cameraMat;
void main()
{
	gl_Position = cameraMat * worldTransformMatrix * vec4(position, 1);
	//vec2 heyman = vec2(position.x*1.5f, position.y*1.5f);
	fragUV = uvPosition;
}