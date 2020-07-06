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
		bool mIsMovingUp = false;
		bool mIsMovingDown = false;
		bool mIsMovingRight = false;
		bool mIsMovingLeft = false;
		const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
		
		
	

	 

};

//This constuctor not only constructs Game(), but also creates an mWindow with args and uses methods
//to set properties of mPlayer somehow
Game::Game()
: mWindow(sf::VideoMode(1200, 800), "SFML")
, ball()
{
	
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
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;

}

void Game::update(sf::Time deltaTime) {
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= 2.f;
	if (mIsMovingDown)
		movement.y += 2.f;
	if (mIsMovingRight)
		movement.x += 2.f;
	if (mIsMovingLeft)
		movement.x -= 2.f;

	//update the paddles
	

	//update the ball
	ball.move(ball.velocity * deltaTime.asSeconds());

	//update the paddles
	lPaddle.move(movement);

	//update ball velocity if colliding
	ball.collision(lPaddle, rPaddle);



	

	//update the ball
	ball.move(ball.velocity * deltaTime.asSeconds());

	

}

void Game::render(){
	mWindow.clear();
	mWindow.draw(ball);
	mWindow.draw(lPaddle);
	mWindow.draw(rPaddle);
	mWindow.display();
}



int main(){


	Game game;
	game.run();
}