#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "MathLibrary.h"

class Player
{
private:
	Vector2D position;

public:
	Player() 
	{
		position = Vector2D(500, 500);
	};

	~Player() {};

	float getX()
	{
		return position.getX();
	}

	float getY()
	{
		return position.getY();
	}

	Vector2D getPos()
	{
		return position;
	}

	void moveUp()
	{
		position.y += 1;
	}

	void moveDown()
	{
		position.y -= 1;
	}

	void moveRight()
	{
		position.x += 1;
	}

	void moveLeft ()
	{
		position.x -= 1;
	}
};

class Application2D : public aie::Application
{
protected:
	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;
	aie::Input*			m_input;

	Player*				m_player;

	Vector2D			lastclick;

	float m_cameraX, m_cameraY;
	float m_timer;

public:
	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	float m_resX, m_resY;

	float getX()
	{
		return lastclick.getX();
	}

	float getY()
	{
		return lastclick.getY();
	}
};