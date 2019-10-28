#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Graphics.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

class Core
{
public:
	Core();
	~Core();

	void run();

private:
	void init();
	void render();
	void processEvents();
	void update(float& deltaTime);
	void updateMousePositions(float& deltaTime);
	void startDeltaTimeClock();

	std::unique_ptr<Graphics> mGraphics;
	std::unique_ptr<Shader> mShader;
	std::vector<std::unique_ptr<Mesh>> mMesh;

	sf::Window mWindow;
	sf::Clock mClock;

	bool mIsOpen;

	float mDeltaTime;
	float mMousePosX;
	float mMousePosY;

	int WIDTH = 1366;
	int HEIGHT = 950;

	

	glm::mat4 mProjection;
};