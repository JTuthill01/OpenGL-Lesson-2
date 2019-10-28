#include "Camera.hpp"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
	GLfloat startMoveSpeed, GLfloat startTurnSpeed) : 
	mPosition(startPosition), mWorld_Up(startUp), mYaw(startYaw), mPitch(startPitch), 
	mFront(glm::vec3(0.F, 0.F, -1.F)), mMovementSpeed(startMoveSpeed), 
	mTurnSpeed(startTurnSpeed), mIsCursorGrabbed(false)
{
	update();
}

Camera::~Camera() = default;

void Camera::keyInput(float & deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		mPosition += mFront * mMovementSpeed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		mPosition -= mFront * mMovementSpeed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		mPosition -= mRight * mMovementSpeed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		mPosition += mRight * mMovementSpeed * deltaTime;
}

void Camera::mouseControl(sf::Window & window, GLfloat xChange, GLfloat yChange)
{
	if (mIsCursorGrabbed == true)
	{
		sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2),
			window);

		window.setMouseCursorVisible(false);

		xChange *= mTurnSpeed;
		yChange *= mTurnSpeed;

		mYaw += xChange;
		mPitch += yChange;

		if (mPitch > 89.F)
			mPitch = 89.F;

		if (mPitch < -89.F)
			mPitch = -89.F;

		update();
	}

	if(mIsCursorGrabbed == false)
		window.setMouseCursorVisible(true);
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void Camera::update()
{
	mFront.x = cosf(glm::radians(mYaw)) * cosf(glm::radians(mPitch));
	mFront.y = sinf(glm::radians(mPitch));
	mFront.z = sinf(glm::radians(mYaw)) * cosf(glm::radians(mPitch));
	mFront = glm::normalize(mFront);

	mRight = glm::normalize(glm::cross(mFront, mWorld_Up));

	mUp = glm::normalize(glm::cross(mRight, mFront));
}
