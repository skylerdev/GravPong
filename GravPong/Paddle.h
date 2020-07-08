#pragma once
#include <SFML/Graphics.hpp>
class Paddle : public sf::RectangleShape
{
	friend class Ball;
public:
	Paddle(bool l);
	~Paddle();
	void restrictIfOutOfBounds();
private:
	const float pHeight = 270.f;
	const float pWidth = 25.f;
	const float distanceFromWall = 90.f;
	bool left;

};

