#pragma once
#include "GL/glew.h"
#include "stb_image.h"

#include <iostream>

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);
	~Texture();

	void loadTexture();
	void useTexture();
	void clearTexture();

private:
	GLuint mTextureID;
	int mWidth, mHeight, mBitDepth;

	const char* mFileLocation;
};

