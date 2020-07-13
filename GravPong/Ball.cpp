#include "Ball.h"
#include "Consts.h"


Ball::Ball()
{

	resetPosition();
	setRadius(BALL_SIZE);
	
	setFillColor(sf::Color::Cyan);
}


Ball::~Ball()
{
}


void Ball::resetPosition() {
	velocity = sf::Vector2f(0.f, 0.f);
	velocity.x += INIT_SPEED;
	velocity.y += INIT_SPEED;

	setPosition(INIT_POS, INIT_POS);

}
