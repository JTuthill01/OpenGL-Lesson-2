#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"

#include <iostream>

class Input
{
public:
	Input();
	~Input();

	bool getIsCursorGrabbed() { return mIsCursorGrabbed; }

protected:
	virtual void iUpdate(sf::Window& window, float xPos, float yPos, float& deltaTime);
	virtual void iEvents(sf::Event e);

private:
	bool mIsCursorGrabbed;
	bool mIsMouseMoved;
};

