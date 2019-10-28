#include "Texture.hpp"

Texture::Texture() : mTextureID(0U), mWidth(0), mHeight(0), mBitDepth(0),
mFileLocation("")
{
}

Texture::Texture(const char* fileLocation) : mTextureID(0U), mWidth(0), mHeight(0), mBitDepth(0),
mFileLocation(fileLocation)
{
}

Texture::~Texture()
{
	clearTexture();
}

void Texture::loadTexture()
{
	unsigned char* texData = stbi_load(mFileLocation, &mWidth, &mHeight, &mBitDepth, 0);

	if (!texData)
	{
		std::cerr << "Failed to find file: " << mFileLocation << '\n';

		EXIT_FAILURE;
	}

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, texData);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

void Texture::useTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &mTextureID);

	mTextureID = 0U;
	mWidth = 0;
	mHeight = 0;
	mBitDepth = 0;
	mFileLocation = "";
}
