#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Game
{	
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
		sf::Texture mTexture;
		sf::Sprite mPlayer;
		sf::Text mTxtFPS;
		sf::Font font;
		bool mIsMovingUp;
		bool mIsMovingDown;
		bool mIsMovingLeft;
		bool mIsMovingRight;
};

Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Application"), mPlayer(), mTexture(), mTxtFPS(),
			   mIsMovingDown(false), mIsMovingUp(false), 
			   mIsMovingLeft(false), mIsMovingRight(false)
{
	if (!mTexture.loadFromFile("media/textures/mother.bmp"))
	{
		// Handle loading error
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);
	
	if (!font.loadFromFile("media/fonts/consola.ttf"))
	{
		// error...
	}
	mTxtFPS.setFont(font);
	mTxtFPS.setString("hola");
	mTxtFPS.setCharacterSize(12);
}

void Game::run() 
{
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{		
		std::ostringstream oss_time_update;
		oss_time_update << clock.getElapsedTime().asMicroseconds();
		std::string str_time_update = oss_time_update.str();

		std::ostringstream oss_fps;
		oss_fps << 1.f/clock.getElapsedTime().asSeconds();
		std::string str_fps = oss_fps.str();

		mTxtFPS.setString("Time/Update = " + str_time_update + "us \n" +"Frames/Second = " + str_fps );
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}		
		render();
	}		
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
		}	
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

//Deltatime: We call the time that has elapsed since
//the last frame delta time(or time step)
void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= 1.f;
	if (mIsMovingDown)
		movement.y += 1.f;
	if (mIsMovingLeft)
		movement.x -= 1.f;
	if (mIsMovingRight)
		movement.x += 1.f;

	mPlayer.move(movement * deltaTime.asSeconds() * 100.f);
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.draw(mTxtFPS);
	mWindow.display();
}

int main()
{	
	Game game;
	game.run();		
}