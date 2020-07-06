#include "Ball.h"

Ball::Ball() : velocity(0.f, 0.f)
{
	velocity.x += INIT_SPEED;
	velocity.y += INIT_SPEED;

	setRadius(BALL_SIZE);
	setPosition(120.f, 120.f);
	setFillColor(sf::Color::Cyan);
}


Ball::~Ball()
{
}
