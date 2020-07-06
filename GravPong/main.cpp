#include <SFML/Graphics.hpp>

class Game{

	public:
			Game();
		void run();

	private:
		void processEvents();
		void update();
		void render();
		void handlePlayerInput(sf::Keyboard::Key, bool);

	private:
		sf::RenderWindow mWindow;
		sf::CircleShape mPlayer;
		bool mIsMovingUp = false;
		bool mIsMovingDown = false;
		bool mIsMovingRight = false;
		bool mIsMovingLeft = false;
	

};

//This constuctor not only constructs Game(), but also creates an mWindow with args and uses methods
//to set properties of mPlayer somehow
Game::Game()
: mWindow(sf::VideoMode(640, 480), "SFML")
, mPlayer()
{
	mPlayer.setRadius(40.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run(){

	while (mWindow.isOpen()) {
		processEvents();
		update();
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

void Game::update() {
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= 1.f;
	if (mIsMovingDown)
		movement.y += 1.f;
	if (mIsMovingRight)
		movement.x += 1.f;
	if (mIsMovingLeft)
		movement.x -= 1.f;

	mPlayer.move(movement);
}

void Game::render(){
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}



int main(){


	Game game;
	game.run();
}