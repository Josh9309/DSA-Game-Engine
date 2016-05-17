#version 430


layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvPosition; //cordinate
out vec2 fragUV;

void main()
{
	gl_Position = vec4(position, 1);
	//vec2 heyman = vec2(position.x*1.5f, position.y*1.5f);
	fragUV = uvPosition;
}