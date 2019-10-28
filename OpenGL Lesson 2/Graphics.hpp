#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "SFML/Graphics.hpp"

#include <vector>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "MainCamera.hpp"
#include "Texture.hpp"

class Graphics
{
public:
	Graphics();
	Graphics(sf::Window& window);
	~Graphics();

	void render();
	void updateCamera(sf::Window& window, float& deltaTime);
	void update(float& deltaTime);
	void updatePositions(sf::Window& window, float& deltaTime);
	void mouseControl(sf::Event& e);
	void setCursorGrabbed(bool t_f) { mIsCursorGrabbed = t_f; }

private:
	void init();
	void setProjection(sf::Window& window);
	void objectData();
	void createObjects();
	void glmData();
	void setDirection();
	void calcAverageNormals(unsigned int* indices, unsigned int indicesCount, GLfloat* vertices,
		unsigned int verticesCount, unsigned int vLength, unsigned int normalOffset);

	bool mDirection;
	bool mSizeDirection;
	bool mIsCursorGrabbed;

	const double ZOOM_SENSITIVITY = -3.0;
	const float MOVE_SPEED = 5.F;
	const float MOUSE_SENSITIVITY = 0.1F;

	float mousePosX;
	float mousePosY;
	float mTriOffset;
	float mTriMaxOffset;
	float mTriIncrement;
	float mCurAngle;
	float mCurSize;
	float mMaxSize;
	float mMinSize;

	glm::mat4 mModel;
	glm::mat4 mProjectionModel;

	std::unique_ptr<Texture> mBrickTexture;
	std::unique_ptr<Texture> mWhiteBrickTexture;

	std::unique_ptr<FPSCamera> mFPSCamera;
	std::unique_ptr<Shader> mShader;
	std::vector<std::unique_ptr<Mesh>> mMesh;
};

