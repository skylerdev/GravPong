#include "Paddle.h"
#include "Consts.h"


Paddle::Paddle(bool l)
{	
	left = l;
	if (l) {
		setPosition(P_DISTANCE_FROM_WALL, 20);
	}
	else {
		setPosition(1200-P_DISTANCE_FROM_WALL, 20);
	}

	setSize(sf::Vector2f(pWidth, pHeight));
	setOutlineColor(sf::Color::Red);
	setOutlineThickness(5);
	

}


Paddle::~Paddle()
{
}

void Paddle::restrictIfOutOfBounds() {
	if (getPosition().y < 0)
		setPosition(getPosition().x, 0);
	if (getPosition().y + pHeight > height)
		setPosition(getPosition().x, height-pHeight);

}

void Paddle::resetPosition() {
	setPosition(getPosition().x, 20);
}

void Paddle::updateWithMouse(sf::Vector2i mousePos) {
	setPosition(getPosition().x, mousePos.y - pHeight/2);
}

void Paddle::updateWithBall(sf::Vector2f ballPos) {
	setPosition(getPosition().x, ballPos.y - 100);
}