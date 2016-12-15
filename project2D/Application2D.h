#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "StaticMathLibraryx86.h"
#include <iostream>

using std::cout;


// macros for screen window size
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Player
{
private:
	// Vector2D to store players positon
	Vector2D position;

public:
	// Default constructor for the Player class
	// Sets player's start position
	Player()
	{
		position = Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	};

	// deconstructor for the Player class
	~Player() {};

	// gets x position
	float getX()
	{
		return position.getX();
	}

	// gets y position
	float getY()
	{
		return position.getY();
	}

	// sets x position
	void setX(float x)
	{
		position.setX(x);
	}

	// sets y position
	void setY(float y)
	{
		position.setY(y);
	}

	// moves player based on mouse position on click
	void MouseMove(Vector2D lastclick)
	{
		// moves player up 1 unit if it's y position is lower than last click's y position
		if (position.getY() < lastclick.getY())
		{
			position.setY(position.getY() + 1);
		}

		// moves player down 1 unit if it's y position is higher than last click's y position
		if (position.getY() > lastclick.getY())
		{
			position.setY(getY() - 1);
		}

		// moves player right 1 unit if it's x position is lower than last click's x position
		if (position.getX() < lastclick.getX())
		{
			position.setX(getX() + 1);
		}

		// moves player left 1 unit if it's x position is higher than last click's x position
		if (position.getX() > lastclick.getX())
		{
			position.setX(getX() - 1);
		}
	}

	void KeyboardMove(aie::Input *input, float deltaTime)
	{
		// move up
		if (input->isKeyDown(aie::INPUT_KEY_W))
			position.setY(position.getY() + (300.0f * deltaTime));

		if (position.getY() > (SCREEN_HEIGHT - 45))
			position.setY((SCREEN_HEIGHT - 45));

		// move down
		if (input->isKeyDown(aie::INPUT_KEY_S))
			position.setY(position.getY() - (300.0f * deltaTime));

		if (position.getY() < 45)
			position.setY(45);

		// move left
		if (input->isKeyDown(aie::INPUT_KEY_A))
			position.setX(position.getX() - (300.0f * deltaTime));

		if (position.getX() < 45)
			position.setX(45);

		// move right
		if (input->isKeyDown(aie::INPUT_KEY_D))
			position.setX(position.getX() + (300.0f * deltaTime));

		if (position.getX() > (SCREEN_WIDTH - 45))
			position.setX((SCREEN_WIDTH - 45));
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

private:
	Player*				m_player1;
	Player*				m_player2;

	Vector2D			lastclick;

public:
	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	float m_cameraX, m_cameraY;
	float m_timer;

	// stores location of mouse cursor on click
	void SetMousePos()
	{
		if (m_input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
		{
			if (m_input->getMouseX() > SCREEN_WIDTH)
			{
				lastclick.setX(SCREEN_WIDTH);
			}

			if (m_input->getMouseX() < 0)
			{
				lastclick.setX(0);
			}

			if (m_input->getMouseY() > SCREEN_HEIGHT)
			{
				lastclick.setY(SCREEN_HEIGHT);
			}

			if (m_input->getMouseY() < 0)
			{
				lastclick.setY(0);
			}

			else
			{
				lastclick.setX(m_input->getMouseX());
				lastclick.setY(m_input->getMouseY());
			}
		}
	}
};