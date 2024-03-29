#pragma once
#include "GL/glew.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void createMesh(GLfloat* vertices, unsigned int *indices, unsigned int numOfVertices, 
		unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();

private:
	GLuint mVAO, mVBO, mIBO;
	GLsizei mIndexCount;
};

