#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
	glDeleteTextures(1, &texID);
}

Texture::Texture(std::string file)
{
	textureFile = file;
}

void Texture::LoadTexture()
{
	//This sets up one texture
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(textureFile.c_str(), 0), textureFile.c_str());
	if (image == nullptr)
	{
		//load failed
	}

	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);

	FreeImage_Unload(image);

	
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
}
