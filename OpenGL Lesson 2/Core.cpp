#include "Core.hpp"

Core::Core() : mIsOpen(true), mMousePosX(0.F), mMousePosY(0.F)
{
	init();

	mGraphics = std::make_unique<Graphics>(mWindow);
}

Core::~Core() = default;

void Core::run()
{
	while (mIsOpen)
	{
		processEvents();

		update(mDeltaTime);

		render();

		startDeltaTimeClock();
	}
}

void Core::init()
{
	mWindow.create(sf::VideoMode(WIDTH, HEIGHT), "OpenGL Lesson 2",
		sf::Style::Default, sf::ContextSettings(24));

	mWindow.setActive(true);

	GLenum e = glewInit();

	if (e != GLEW_OK)
		throw std::runtime_error("Glew Failed");

	glClearColor(0.F, 0.F, 0.F, 1.F);

	glEnable(GL_DEPTH_TEST);
}

void Core::render()
{
	mWindow.setActive(true);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mGraphics->render();

	mWindow.display();
}

void Core::processEvents()
{
	sf::Event e;

	while (mWindow.pollEvent(e))
	{
		if (e.type == sf::Event::Resized)
			glViewport(0, 0, e.size.width, e.size.height);

		if (e.type == sf::Event::Closed)
			mIsOpen = false;

		if (e.key.code == sf::Keyboard::Escape)
			mIsOpen = false;

		mGraphics->mouseControl(e);
	}
}

void Core::update(float& deltaTime)
{
	mGraphics->update(deltaTime);

	mGraphics->updatePositions(mWindow, deltaTime);

	mGraphics->updateCamera(mWindow, deltaTime);
}

void Core::updateMousePositions(float& deltaTime)
{
	mMousePosX = static_cast<float>(sf::Mouse::getPosition(mWindow).x);
	mMousePosY = static_cast<float>(sf::Mouse::getPosition(mWindow).y);
}

void Core::startDeltaTimeClock() { mDeltaTime = mClock.restart().asSeconds(); }

