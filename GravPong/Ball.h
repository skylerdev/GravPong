#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball :
	public sf::CircleShape
{
public:
	Ball();
	~Ball();
	void resetPosition();

public:

	 sf::Vector2f velocity;
private:
	const float MAX_SPEED = 25.f;
	const float INIT_SPEED = 500.f;
	const float BALL_SIZE = 10.f;
	const float INIT_POS = 120.f;
	//const float INIT_POS;
};

