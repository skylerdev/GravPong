#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include <iostream>
#include "Consts.h"
#include <string>
#include <SFML/Audio.hpp>

class Game{

	public:
			Game();
		void run();

	private:
		void setup();
		void processEvents();
		void update(sf::Time);
		void render();
		void handlePlayerInput(sf::Keyboard::Key, bool);
		void resetPositions();
		void collision();

	private:
		sf::RenderWindow mWindow;
		Ball ball;
		Paddle lPaddle = Paddle(true);
		Paddle rPaddle = Paddle(false);
		bool lIsMovingUp = false;
		bool lIsMovingDown = false;
		bool lIsGrav = false;
		bool rIsGrav = false;

		int lScore = 0;
		int rScore = 0;

		sf::Text lScoreText;
		sf::Text rScoreText;

		sf::Font font;

		const sf::Time TimePerFrame = sf::seconds(1.f / 120.f);

		//background shapes

		sf::RectangleShape bg;
		sf::RectangleShape lGravShape;
		sf::RectangleShape rGravShape;
		sf::RectangleShape speedMeterShape;
		sf::SoundBuffer hitBuf;
	    sf::SoundBuffer scoreBuf;
		sf::Sound hitSound;
		sf::Sound scoreSound;

	 

};

//This constuctor not only constructs Game(), but also creates an mWindow with args and uses methods
//to set properties of mPlayer somehow
Game::Game()
: mWindow(sf::VideoMode(width, height), "SFML")
, ball()
{
	setup();

}

void Game::setup() {
	bg.setSize(sf::Vector2f(width, height));
	bg.setPosition(0, 0);
	bg.setFillColor(sf::Color::White);

	sf::Color gravColor = sf::Color(169, 169, 169, 200);

	lGravShape.setSize(sf::Vector2f(width / 2, height));
	rGravShape.setSize(sf::Vector2f(width / 2, height));

	lGravShape.setFillColor(gravColor);
	rGravShape.setFillColor(gravColor);

	lGravShape.setPosition(0, 0);
	rGravShape.setPosition(width / 2, 0);

	font.loadFromFile("resources/Roboto-Regular.ttf");

	lScoreText.setCharacterSize(30);
	lScoreText.setStyle(sf::Text::Bold);
	lScoreText.setFillColor(sf::Color::Red);
	lScoreText.setFont(font);
	lScoreText.setPosition(width / 2 - 130, 30);

	rScoreText.setCharacterSize(30);
	rScoreText.setStyle(sf::Text::Bold);
	rScoreText.setFillColor(sf::Color::Red);
	rScoreText.setFont(font);
	rScoreText.setPosition(width / 2 + 100, 30);


	hitBuf.loadFromFile("resources/hit.wav");
	scoreBuf.loadFromFile("resources/score.wav");
	hitSound.setBuffer(hitBuf);
	scoreSound.setBuffer(scoreBuf);


	
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

void Game::resetPositions() {
	ball.resetPosition();
	lPaddle.resetPosition();
	rPaddle.resetPosition();
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lIsGrav = true;
	}
	else {
		lIsGrav = false;
	}

	//gravity
	if (lIsGrav && ball.getPosition().x < width / 2)
		ball.velocity.x -= GRAV_SPEED_INCREASE;
	if (rIsGrav && ball.getPosition().x > width / 2)
		ball.velocity.x += GRAV_SPEED_INCREASE;



	//right paddle ai
	sf::Vector2f movement(0.f, 0.f);
	if (ball.getPosition().y + ball.getRadius()/2 < rPaddle.getPosition().y + rPaddle.pWidth / 2)
		movement.y -= AI_SET_PADDLE_SPEED;
	if (ball.getPosition().y + ball.getRadius() / 2 > rPaddle.getPosition().y + rPaddle.pWidth/2)
		movement.y += AI_SET_PADDLE_SPEED;
	rPaddle.move(movement);
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
	lPaddle.updateWithMouse(sf::Mouse::getPosition(mWindow));
	//rPaddle.updateWithBall(ball.getPosition());


	lPaddle.restrictIfOutOfBounds();
	rPaddle.restrictIfOutOfBounds();
	
	//run collision detection code
	collision();

	//update score text 
	lScoreText.setString(std::to_string(lScore));
	rScoreText.setString(std::to_string(rScore));

	//update the ball
	ball.move(ball.velocity * deltaTime.asSeconds());


	

}

//
//COLLISION DETECTION CODE
//

void Game::collision() {
	
	sf::Vector2f bPos = ball.getPosition();

	//detect if ball is above or below screen
	if (bPos.y < 0) {
		ball.setPosition(bPos.x, 0);
		ball.velocity.y = ball.velocity.y * -1;
	}
	if (bPos.y + ball.getRadius() > height) {
		ball.setPosition(bPos.x, height - ball.getRadius());
		ball.velocity.y = ball.velocity.y * -1;
	}


	//collide with paddles

	if (lPaddle.getGlobalBounds().contains(bPos)) {
		ball.setPosition(lPaddle.P_DISTANCE_FROM_WALL + lPaddle.pWidth, bPos.y);
		ball.velocity.x = ball.velocity.x * -1;
		hitSound.play();
	}

	if (rPaddle.getGlobalBounds().contains(bPos)) {
		ball.setPosition(width - rPaddle.P_DISTANCE_FROM_WALL - rPaddle.pWidth, bPos.y);
		ball.velocity.x = ball.velocity.x * -1;
		hitSound.play();
	}

	//detect is ball is to the right of screen
	if (ball.getPosition().x + ball.getRadius() > width) {
		resetPositions();
		lScore++;
		scoreSound.play();
	}

	//detect if ball is left of screen
	if (ball.getPosition().x < 0) {
		resetPositions();
		rScore++;
		scoreSound.play();
	}

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
	mWindow.draw(lScoreText);
	mWindow.draw(rScoreText);

	mWindow.display();
}



int main(){

	Game game;
	game.run();
}