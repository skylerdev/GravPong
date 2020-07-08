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

void Ball::collision(Paddle lPaddle, Paddle rPaddle) {

	
	//collision detection

	//detect if ball is above screen
	if (getPosition().y < 0) {
		//set to top of screen, reverse velocity
		setPosition(getPosition().x, 0);
		velocity.y = velocity.y * -1;
	}

	//detect if ball is below screen

	if (getPosition().y + getRadius() > height) {
		setPosition(getPosition().x, height - getRadius());
		velocity.y = velocity.y * -1;
	}


	//collide with paddles

	if (lPaddle.getGlobalBounds().contains(getPosition())){
		setPosition(lPaddle.P_DISTANCE_FROM_WALL + lPaddle.pWidth, getPosition().y);
		velocity.x = velocity.x * -1;
	}

	if (rPaddle.getGlobalBounds().contains(getPosition())) {
		setPosition(width - rPaddle.P_DISTANCE_FROM_WALL - rPaddle.pWidth, getPosition().y);
		velocity.x = velocity.x * -1;
	}

}

void Ball::resetPosition() {
	velocity = sf::Vector2f(0.f, 0.f);
	velocity.x += INIT_SPEED;
	velocity.y += INIT_SPEED;

	setPosition(INIT_POS, INIT_POS);

}
