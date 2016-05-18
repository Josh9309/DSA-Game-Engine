#version 430


layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvPosition; //cordinate
layout (location = 2) in vec3 modelNorm;

out vec3 fragLoc;
out vec2 fragUV;
out vec3 fragNormal;

layout (location = 3) uniform mat4 worldTransformMatrix;
layout (location = 4) uniform mat4 cameraMat;

void main()
{
	fragLoc = (worldTransformMatrix * vec4(position, 1)).xyz;
	fragUV = uvPosition;
	vec4 fash = inverse(transpose(worldTransformMatrix))* vec4(modelNorm, 0); //need to figure out how to get model normal
	fragNormal = vec3(fash);
	//fragNormal = modelNorm;
	gl_Position = cameraMat * worldTransformMatrix * vec4(position, 1);
	//vec2 heyman = vec2(position.x*1.5f, position.y*1.5f);
	
}