#include "Mesh.hpp"

Mesh::Mesh() : mVAO(0U), mVBO(0U), mIBO(0U), mIndexCount(0)
{
}

Mesh::~Mesh()
{
	clearMesh();
}

void Mesh::createMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, 
	unsigned int numOfIndices)
{
	this->mIndexCount = numOfIndices;

	glGenVertexArrays(1, &this->mVAO);
	glBindVertexArray(this->mVAO);

	glGenBuffers(1, &this->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, 
		indices, GL_STATIC_DRAW);

	glGenBuffers(1, &this->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, 
		vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 
		(GLvoid*)(sizeof(vertices[0]) * 3));

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
		(GLvoid*)(sizeof(vertices[0]) * 5));

	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderMesh()
{
	glBindVertexArray(this->mVAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);

	glDrawElements(GL_TRIANGLES, this->mIndexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::clearMesh()
{
	if (this->mIBO != 0U)
	{
		glDeleteBuffers(1, &this->mIBO);

		this->mIBO = 0U;
	}

	if (this->mVBO != 0U)
	{
		glDeleteBuffers(1, &this->mVBO);

		this->mVBO = 0U;
	}

	if (this->mVAO != 0U)
	{
		glDeleteVertexArrays(1, &this->mVAO);

		this->mVAO = 0U;
	}

	this->mIndexCount = 0;
}
