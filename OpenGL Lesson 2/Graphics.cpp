#include "Graphics.hpp"

Graphics::Graphics() : mDirection(true), mSizeDirection(true), mTriOffset(0.F), 
mTriMaxOffset(0.7F), mTriIncrement(0.0005F), mCurAngle(0.F), mCurSize(0.4F), 
mMaxSize(0.8F), mMinSize(0.0005F), mousePosX(0.F), mousePosY(0.F), mIsCursorGrabbed(false)
{
	createObjects();

	init();
}

Graphics::Graphics(sf::Window& window) : mDirection(true), mSizeDirection(true), mTriOffset(0.F),
mTriMaxOffset(0.7F), mTriIncrement(0.0005F), mCurAngle(0.F), mCurSize(0.4F),
mMaxSize(0.8F), mMinSize(0.0005F), mousePosX(0.F), mousePosY(0.F), mIsCursorGrabbed(false)
{
	createObjects();

	setProjection(window);

	init();
}

Graphics::~Graphics() = default;

void Graphics::render()
{
	objectData();
}

void Graphics::updateCamera(sf::Window& window, float & deltaTime)
{
	if (mIsCursorGrabbed == true)
	{
		mFPSCamera->rotate(static_cast<float>(window.getSize().x / 2.F - mousePosX) * 
			MOUSE_SENSITIVITY, static_cast<float>(window.getSize().y / 2.F - mousePosY)
			* MOUSE_SENSITIVITY);

		sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), 
			window);

		window.setMouseCursorVisible(false);

		//Forward and Backwards
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			mFPSCamera->move(MOVE_SPEED * deltaTime * mFPSCamera->getLook());

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mFPSCamera->move(MOVE_SPEED * deltaTime * -mFPSCamera->getLook());

		//Left and Right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			mFPSCamera->move(MOVE_SPEED * deltaTime * mFPSCamera->getRight());

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			mFPSCamera->move(MOVE_SPEED * deltaTime * -mFPSCamera->getRight());

		//Up and Down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			mFPSCamera->move(MOVE_SPEED * deltaTime * mFPSCamera->getUp());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			mFPSCamera->move(MOVE_SPEED * deltaTime * -mFPSCamera->getUp());
	}

	if(mIsCursorGrabbed == false)
		window.setMouseCursorVisible(true);
}

void Graphics::update(float & deltaTime) 
{ 
	setDirection(); 
}

void Graphics::updatePositions(sf::Window & window, float & deltaTime)
{
	mousePosX = static_cast<float>(sf::Mouse::getPosition(window).x);
	mousePosY = static_cast<float>(sf::Mouse::getPosition(window).y);
}

void Graphics::mouseControl(sf::Event & e)
{
	if (e.mouseButton.button == sf::Mouse::Left)
		mIsCursorGrabbed = true;
	

	if (e.mouseButton.button == sf::Mouse::Right)
		mIsCursorGrabbed = false;
}

void Graphics::init()
{
	mShader = std::make_unique<Shader>("Shaders/vertexShader.vert",
		"Shaders/fragmentShader.frag");

	mFPSCamera = std::make_unique<FPSCamera>(glm::vec3(0.F, 3.F, 15.F));

	mBrickTexture = std::make_unique<Texture>("Textures/awesomeface.png");
	mWhiteBrickTexture = std::make_unique<Texture>("Textures/awesomeface.png");

	mBrickTexture->loadTexture();
	mWhiteBrickTexture->loadTexture();
}

void Graphics::setProjection(sf::Window& window)
{
	mProjectionModel = glm::mat4(1.F);
	mProjectionModel = glm::perspective(45.F, static_cast<GLfloat>(window.getSize().x) /
		static_cast<GLfloat>(window.getSize().y), 0.1F, 200.F);
}

void Graphics::objectData()
{
	mShader->use();

	mModel = glm::mat4(1.F);
	mModel = glm::translate(mModel, glm::vec3(0.F, 0.F, -2.5F));

	mShader->setUniform("model", mModel);
	mShader->setUniform("projection", mProjectionModel);
	mShader->setUniform("view", mFPSCamera->getViewMatrix());
	mShader->setUniform("directionalLight.color", glm::vec3(1.F, 1.F, 1.F));
	mShader->setUniform("directionalLight.ambientIntensity", 0.1F);
	mShader->setUniform("directionalLight.direction", glm::vec3(2.F, -1.F, -2.F));
	mShader->setUniform("directionalLight.diffuseIntensity", 0.3F);
	mShader->setUniform("eyePosition", glm::vec3(0.F, 0.5F, 0.2F));
	mShader->setUniform("material.specularIntensity", 0.25F);
	mShader->setUniform("material.shininess", 0.1F);

	mBrickTexture->useTexture();

	mMesh[0]->renderMesh();

	mModel = glm::mat4(1.F);
	mModel = glm::translate(mModel, glm::vec3(0.F, 4.F, -2.5F));

	mShader->setUniform("model", mModel);
	mShader->setUniform("projection", mProjectionModel);
	mShader->setUniform("view", mFPSCamera->getViewMatrix());
	mShader->setUniform("directionalLight.color", glm::vec3(1.F, 1.F, 1.F));
	mShader->setUniform("directionalLight.ambientIntensity", 0.1F);
	mShader->setUniform("directionalLight.direction", glm::vec3(2.F, -1.F, -2.F));
	mShader->setUniform("directionalLight.diffuseIntensity", 0.3F);
	mShader->setUniform("eyePosition", glm::vec3(mFPSCamera->getPosition().x, 
		mFPSCamera->getPosition().y, mFPSCamera->getPosition().z));
	mShader->setUniform("material.specularIntensity", 1.F);
	mShader->setUniform("material.shininess", 0.1F);

	mWhiteBrickTexture->useTexture();

	mMesh[1]->renderMesh();

	mShader->unuse();
}

void Graphics::createObjects()
{
	GLfloat vertices[] =
	{	//X, Y, Z		   UV's      Normals X, Y, Z
		-1.F, -1.F, -0.6F, 0.F, 0.F,  0.F, 0.F, 0.F,
		 0.F, -1.F, 1.F,   0.5F, 0.F, 0.F, 0.F, 0.F,
		 1.F, -1.F, -0.6F, 1.F, 0.F,  0.F, 0.F, 0.F,
		 0.F, 1.F, 0.F,    0.5F, 1.F, 0.F, 0.F, 0.F,
	};

	GLuint indices[] =
	{
		0U, 3U, 1U,

		1U, 3U, 2U,

		2U, 3U, 0U,

		0U, 1U, 2U,
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	std::unique_ptr<Mesh> obj = std::make_unique<Mesh>();
	obj->createMesh(vertices, indices, 32, 12);
	mMesh.push_back(std::move(obj));

	std::unique_ptr<Mesh> obj1 = std::make_unique<Mesh>();
	obj1->createMesh(vertices, indices, 32, 12);
	mMesh.push_back(std::move(obj1));
}

void Graphics::glmData()
{
	mCurAngle += 0.01F;

	if (mCurAngle >= 360.F)
		mCurAngle -= 360.F;

	if (mDirection)
		mCurSize += 0.0001F;

	else
		mCurSize -= 0.0001F;

	if (mCurSize >= mMaxSize || mCurSize <= mMinSize)
		mSizeDirection = !mSizeDirection;
}

void Graphics::setDirection()
{
	if (mDirection)
		mTriOffset += mTriIncrement;

	else
		mTriOffset -= mTriIncrement;

	if (abs(mTriOffset) >= mTriMaxOffset)
		mDirection = !mDirection;

	glmData();
}

void Graphics::calcAverageNormals(unsigned int * indices, unsigned int indicesCount, 
	GLfloat* vertices, unsigned int verticesCount,  unsigned int vLength, 
		unsigned int normalOffset)
{
	for (size_t i = 0; i < indicesCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], 
			vertices[in1 + 2] - vertices[in0 + 2]);

		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], 
			vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; 
		in1 += normalOffset; 
		in2 += normalOffset;

		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; 
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; 
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; 
		vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticesCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;

		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);

		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
}
