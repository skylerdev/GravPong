#pragma once
#include <SFML/Graphics.hpp>
class Paddle : public sf::RectangleShape
{
public:
	Paddle(bool l);
	~Paddle();
private:
	const float wide = 270.f;
	const float depth = 25.f;
	const float distanceFromWall = 90.f;
	bool left;

};

