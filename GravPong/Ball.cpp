#include "Ball.h"
#include "Consts.h"

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

	//detect is ball is to the right of screen

	if (getPosition().x + getRadius() > width) {
		setPosition(width - getRadius(), getPosition().y);
		velocity.x = velocity.x * -1;
	}

	//detect if ball is left of screen

	if (getPosition().x < 0) {
		setPosition(0, getPosition().y);
		velocity.x = velocity.x * -1;
	}

	//collide with paddles

	if (lPaddle.getGlobalBounds().contains(getPosition())){
		setPosition(lPaddle.distanceFromWall + lPaddle.width, getPosition().y);
		velocity.x = velocity.x * -1;
	}

	if (rPaddle.getGlobalBounds().contains(getPosition())) {
		setPosition(width - rPaddle.distanceFromWall - rPaddle.width, getPosition().y);
		velocity.x = velocity.x * -1;
	}

}
