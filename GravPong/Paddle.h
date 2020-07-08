#pragma once
#include <SFML/Graphics.hpp>
class Paddle : public sf::RectangleShape
{
	friend class Ball;
public:
	Paddle(bool l);
	~Paddle();
	void restrictIfOutOfBounds();
	void resetPosition();
private:
	const float pHeight = 270.f;
	const float pWidth = 25.f;
	const float P_DISTANCE_FROM_WALL = 90.f;
	bool left;

};

