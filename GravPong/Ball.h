#pragma once
#include <SFML/Graphics.hpp>
class Ball :
	public sf::CircleShape
{
public:
	Ball();
	~Ball();
public:

	 sf::Vector2f velocity;
private:
	const float MAX_SPEED = 25.f;
	const float INIT_SPEED = 200.f;
	const float BALL_SIZE = 10.f;
	//const float INIT_POS;
};

