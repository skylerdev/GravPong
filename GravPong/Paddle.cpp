#include "Paddle.h"



Paddle::Paddle(bool l)
{
	if (l) {
		setPosition(distanceFromWall, 20);
	}
	else {
		setPosition(1200-distanceFromWall, 20);
	}

	setSize(sf::Vector2f(width, height));
	setOutlineColor(sf::Color::Red);
	setOutlineThickness(5);
	

}


Paddle::~Paddle()
{
}
