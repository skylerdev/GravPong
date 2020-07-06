#pragma once
#include <SFML/Graphics.hpp>
class Paddle : public sf::RectangleShape
{
	friend class Ball;
public:
	Paddle(bool l);
	~Paddle();
private:
	const float height = 270.f;
	const float width = 25.f;
	const float distanceFromWall = 90.f;
	bool left;

};

