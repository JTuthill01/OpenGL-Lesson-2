#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SFML/Graphics.hpp"

#include "Input.hpp"

#include <iostream>

class Camera 
{
public:
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
		GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	~Camera();

	void keyInput(float& deltaTime);
	void mouseControl(sf::Window& window, GLfloat xChange, GLfloat yChange);
	void setMouseCursorGrabbed(bool t_f) { mIsCursorGrabbed = t_f; }

	glm::mat4 calculateViewMatrix();

private:
	void update();

	bool mIsCursorGrabbed;

	Input mInput;

	glm::vec3 mPosition;
	glm::vec3 mFront;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mWorld_Up;

	GLfloat mYaw;
	GLfloat mPitch;
	GLfloat mMovementSpeed;
	GLfloat mTurnSpeed;
};

