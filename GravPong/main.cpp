#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include <iostream>
#include "Consts.h"


class Game{

	public:
			Game();
		void run();

	private:
		void processEvents();
		void update(sf::Time);
		void render();
		void handlePlayerInput(sf::Keyboard::Key, bool);

	private:
		sf::RenderWindow mWindow;
		Ball ball;
		Paddle lPaddle = Paddle(true);
		Paddle rPaddle = Paddle(false);
		bool lIsMovingUp = false;
		bool lIsMovingDown = false;
		bool lIsGrav = false;
		bool rIsGrav = false;
		const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

		//background shapes

		sf::RectangleShape bg;
		sf::RectangleShape lGravShape;
		sf::RectangleShape rGravShape;
		
	 

};

//This constuctor not only constructs Game(), but also creates an mWindow with args and uses methods
//to set properties of mPlayer somehow
Game::Game()
: mWindow(sf::VideoMode(1200, 800), "SFML")
, ball()
{
	bg.setSize(sf::Vector2f(width, height));
	bg.setPosition(0, 0);
	bg.setFillColor(sf::Color::White);

	sf::Color gravColor = sf::Color(169, 169, 169, 200);

	lGravShape.setSize(sf::Vector2f(width/2, height));
	rGravShape.setSize(sf::Vector2f(width/2, height));

	lGravShape.setFillColor(gravColor);
	rGravShape.setFillColor(gravColor);

	lGravShape.setPosition(0, 0);
	rGravShape.setPosition(width/2, 0);

}

void Game::run(){

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) {
		
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents(){

	sf::Event event;
	while (mWindow.pollEvent(event)) {
		//window.pollEvent(event) looks like it fills up event with info about the current 
		//event being registered
		//and uses some sort of queue
	
		//This does something different for each event
		switch (event.type) {
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			//close the window
			mWindow.close();
			break;
		}
	}

}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::S)
		lIsMovingUp = isPressed;
	else if (key == sf::Keyboard::D)
		lIsMovingDown = isPressed;
	else if (key == sf::Keyboard::F)
		lIsGrav = isPressed;
}

void Game::update(sf::Time deltaTime) {
	sf::Vector2f movement(0.f, 0.f);
	if (lIsMovingUp)
		movement.y -= 25.f;
	if (lIsMovingDown)
		movement.y += 25.f;
	if (lIsGrav && ball.getPosition().x < width/2)
		ball.velocity.x -= GRAV_SPEED_INCREASE;
	if(rIsGrav && ball.getPosition().x > width / 2)
		ball.velocity.x += GRAV_SPEED_INCREASE;
	//update the paddles


	//right paddle ai
	
	if (ball.getPosition().x > width - 300) {
		//trigger grav
		rIsGrav = true;
	}
	else {
		rIsGrav = false;
	}

	//update the ball
	ball.move(ball.velocity * deltaTime.asSeconds());

	//update the paddles
	lPaddle.move(movement);
	lPaddle.restrictIfOutOfBounds();
	
	rPaddle.setPosition(rPaddle.getPosition().x, ball.getPosition().y - 100);

	//update ball velocity if colliding
	ball.collision(lPaddle, rPaddle);



	//ball max velocity check 


	//update the ball
	ball.move(ball.velocity * deltaTime.asSeconds());

	

}

void Game::render(){
	mWindow.clear();
	
	mWindow.draw(bg);

	if (lIsGrav) {
		mWindow.draw(lGravShape);
	}
	if (rIsGrav) {
		mWindow.draw(rGravShape);
	}

	mWindow.draw(ball);
	mWindow.draw(lPaddle);
	mWindow.draw(rPaddle);

	mWindow.display();
}



int main(){

	 
	

	Game game;
	game.run();
}