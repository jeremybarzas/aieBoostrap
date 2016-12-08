#include "Application2D.h"

Application2D::Application2D()
{
	
}

Application2D::~Application2D() {

}

bool Application2D::startup()
{
	m_input = aie::Input::getInstance();
	
	m_player = new Player();
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_audio = new aie::Audio("./audio/powerup.wav");
	
	lastclick = Vector2D(500, 500);
	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	m_resX = 1920;
	m_resY = 1080;

	return true;
}

void Application2D::shutdown() 
{
	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;

	delete m_player;
}

void Application2D::update(float deltaTime)
{
	m_timer += deltaTime;

	// use arrow keys to move camera
	if (m_input->isKeyDown(aie::INPUT_KEY_W))
		m_cameraY += 300.0f * deltaTime;

	if (m_input->isKeyDown(aie::INPUT_KEY_S))
		m_cameraY -= 300.0f * deltaTime;

	if (m_input->isKeyDown(aie::INPUT_KEY_A))
		m_cameraX -= 300.0f * deltaTime;

	if (m_input->isKeyDown(aie::INPUT_KEY_D))
		m_cameraX += 300.0f * deltaTime;

	// use mouse clicks to move character
	if (m_input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		lastclick.x = m_input->getMouseX();
		lastclick.y = m_input->getMouseY();
	}

	if (!(m_player->getPos() == lastclick))
	{
		float m_length = sqrt(((m_player->getX() - lastclick.getX()) * (m_player->getX() - lastclick.getX())) + ((m_player->getY() - lastclick.getY()) * (m_player->getY() - lastclick.getY())));
		
		m_player->setPos(m_player->Move(m_player->getPos(), lastclick, m_length));
	}

	/*
	m_player->Move(lastclick);
	
	if (m_player->getY() > this->getY())
	{
		m_player->moveDown();
	}
	if (m_player->getY() < this->getY())
	{
		m_player->moveUp();
	}
	if (m_player->getX() > this->getX())
	{
		m_player->moveLeft();
	}
	if (m_player->getX() < this->getX())
	{
		m_player->moveRight();
	}*/

	// example of audio
	if (m_input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		m_audio->play();

	// exit the application
	if (m_input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();
	

	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_shipTexture, m_player->getX(), m_player->getY(), 0, 0, 0, 1);


	// demonstrate animation
	m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	// draws a bottom line
	m_2dRenderer->drawLine(0, 0, this->m_resX, 0, 10, 1);
	
	// draws a top line
	m_2dRenderer->drawLine(0, this->m_resY, this->m_resX, this->m_resY, 10, 1);
	
	// draws a right line
	m_2dRenderer->drawLine(this->m_resX, 0, this->m_resX, this->m_resY, 10, 1);

	// draws a left line
	m_2dRenderer->drawLine(0, 0, 0, this->m_resY, 10, 1);

	// draw a moving purple circle
	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red box
	m_2dRenderer->setRenderColour(1, 0, 0, 1);
	m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press Space for sound!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}