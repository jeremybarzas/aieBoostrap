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

	void setPos(Vector2D newpos)
	{
		position = newpos;
	}

/*
	// Imprecise method which does not guarantee v = v1 when t = 1, due to floating-point arithmetic error.
	  
	// This form may be used when the hardware has a native Fused Multiply-Add instruction.
	
	float lerp(float v0, float v1, float t)
	{
		return v0 + t*(v1-v0);
	}

	// Precise method which guarantees v = v1 when t = 1.
	
	float lerp(float v0, float v1, float t)
	{
		return (1-t)*v0 + t*v1;
	}
*/
	Vector2D Move(Vector2D start, Vector2D end, float p)
	{
		Vector2D newpos = start;
		
		Vector2D step1 = start - end;

		Vector2D step2 = step1 * p;

		newpos = newpos + step2;

		return newpos;
	}

	void Move(Vector2D lastclick)
	{
		float Xdif = position.x - lastclick.getX();
		float Ydif = position.y - lastclick.getY();

		if (Xdif < 0)
		{
			Xdif *= -1;
		}
		if (Ydif < 0)
		{
			Ydif *= -1;
		}

		float rocX;
		float rocY;

		if (Xdif < Ydif)
		{
			rocX = 1;
			rocY = (Ydif / Xdif);
		}
		if (Xdif > Ydif)
		{
			rocX = (Xdif / Ydif);
			rocY = 1;
		}

		// move x
		if (this->getX() < lastclick.getX())
		{
			position.x += rocX;
		}
		if (this->getX() > lastclick.getX())
		{
			position.x -= rocX;
		}

		// move y
		if (this->getY() < lastclick.getY())
		{
			position.y += rocY;
		}
		if (this->getY() > lastclick.getY())
		{
			position.y -= rocY;
		}		
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