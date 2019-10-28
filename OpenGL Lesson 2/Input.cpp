#include "Input.hpp"

Input::Input() : mIsCursorGrabbed(false), mIsMouseMoved(false)
{
}

Input::~Input() = default;

void Input::iUpdate(sf::Window& window, float xPos, float yPos, float& deltaTime)
{
	float lastMousePosX = 0.F;
	float lastMousePosY = 0.F;

	float xChange;
	float yChange;

	if (mIsCursorGrabbed == true)
	{
		window.setMouseCursorVisible(false);

		if (mIsMouseMoved)
		{
			lastMousePosX = xPos;

			lastMousePosY = yPos;

			mIsMouseMoved = false;
		}

		xChange = xPos - lastMousePosX;
		yChange = lastMousePosY - yPos;

		lastMousePosX = xPos;
		lastMousePosY = yPos;
	}

	if (mIsCursorGrabbed == false)
	{
		window.setMouseCursorVisible(true);

		xChange = 0.F;

		yChange = 0.F;
	}
}

void Input::iEvents(sf::Event e)
{
	

	if (e.mouseMove.x && e.mouseMove.y && mIsCursorGrabbed)
		mIsMouseMoved = true;
}
