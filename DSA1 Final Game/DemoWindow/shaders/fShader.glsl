#version 430

uniform sampler2D myTexture;

layout (location = 5) uniform vec3 lightLoc;
layout (location = 6) uniform vec3 camLoc;

in vec3 fragLoc;
in vec2 fragUV;
in vec3 fragNormal;

void main()
{
	vec3 L = normalize(lightLoc - fragLoc);
	vec3 E = normalize(camLoc - fragLoc);
	vec3 H = normalize(L+E);
	vec3 N = normalize(fragNormal);

	float amb =.5;
	float diff = .5 *max(dot(L,N), 0);
	float spec = .5 * pow(max(dot(H,N), 0), 16);
	float bright = amb + diff + spec;

	vec4 texColor = texture(myTexture, fragUV);

	
	gl_FragColor = vec4(bright * texColor.rgb , texColor.a);

	//gl_FragColor = vec4(N,1);
	//gl_FragColor = texture(myTexture, fragUV); //applies texture
	//gl_FragColor= vec4(0,0,0,1); turns color black

}