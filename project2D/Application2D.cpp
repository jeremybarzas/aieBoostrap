#include "Application2D.h"

Application2D::Application2D()
{
	
}

Application2D::~Application2D() {

}

bool Application2D::startup()
{
	m_input = aie::Input::getInstance();
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	m_player1 = new Player();
	m_player2 = new Player();

	lastclick = Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	return true;
}

void Application2D::shutdown() 
{
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;

	delete m_player1;
	delete m_player2;
}

void Application2D::update(float deltaTime)
{
	m_timer += deltaTime;

	/*========== Player Movement ==========*/

	SetMousePos();

	m_player1->MouseMove(lastclick);

	m_player2->KeyboardMove(m_input, deltaTime);

	/*========== Exit ==========*/

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
	
	// click to move ship
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_shipTexture, m_player1->getX(), m_player1->getY(), 0, 0, 0, 1);

	// w,a,s,d moved ship
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_shipTexture, m_player2->getX(), m_player2->getY(), 0, 0, 0, 1);

	// draws a bottom line
	m_2dRenderer->drawLine(0, 0, SCREEN_WIDTH, 0, 10, 1);
	
	// draws a top line
	m_2dRenderer->drawLine(0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 1);
	
	// draws a right line
	m_2dRenderer->drawLine(SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 10, 1);

	// draws a left line
	m_2dRenderer->drawLine(0, 0, 0, SCREEN_HEIGHT, 10, 1);

	// done drawing sprites
	m_2dRenderer->end();
}