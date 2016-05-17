#version 430

uniform sampler2D myTexture;
in vec2 fragUV;

void main()
{
	/*if(fragUV.x < 0 && fragUV.y <0)
	{
	gl_FragColor = vec4(-fragUV.x * 0.6, -fragUV.y *0.6 , -fragUV.x *.8f, fragUV.y * 0.8f);  //fragUV.x*0.9f, -fragUV.y *0.6f , -fragUV.x *.5f, fragUV.y * 0.8f
	}
	else if(fragUV.x < 0)
	{
	gl_FragColor = vec4(-fragUV.x *0.6, fragUV.y *0.6 , -fragUV.x *.8f, fragUV.y * 0.8f);
	}
	else if(fragUV.y < 0)
	{
	gl_FragColor = vec4(fragUV.x*0.6 , -fragUV.y*0.6 , -fragUV.x *.8f, fragUV.y * 0.8f);
	}
	else
	{
	gl_FragColor = vec4(fragUV.x*0.6 , fragUV.y*0.6 , -fragUV.x *.8f, fragUV.y * 0.8f);
	}*/
	
	//gl_FragColor = vec4(fragUV.x*0.9f, -fragUV.y *0.6f , -fragUV.x *.5f, fragUV.y * 0.8f);
	//gl_FragColor = vec4(fragUV.x*0.9f, -fragUV.y *0.6f , 0.2f, 0.9f);
	
	gl_FragColor = texture(myTexture, fragUV);

}