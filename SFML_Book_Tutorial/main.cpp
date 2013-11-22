#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

//Creamos el enum para referirnos de este modo Textures::ID, para que no haya colision de nombres
namespace Textures
{
	enum ID {Landscape, Airplane, Missile};
}

//Es un contenedor generico de texturas
class TextureHolder
{
	//Constructor
	private:
		//el identificador sera el enum ID, y en el otro miembro de map almacenamos el puntero a la textura
		std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;

	//Metodos
	public:
		//para cargar la textura desde un fichero del sistema
		void load(Textures::ID id, const std::string& filename);
		//para que nos de la textura solicitada
		sf::Texture& get(Textures::ID id);
		//en el caso de que se referencie a una const TextureHolder
		const sf::Texture& get(Textures::ID id) const;
};

void TextureHolder::load(Textures::ID id, const std::string& filename)
{
	//primero creamos un objeto del tipo sf::Texture y lo almacenamos un un unique pointer
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	//cargamos la textura desde el fichero
	if (!texture->loadFromFile(filename))
	{
		std::cout << "error cargando fichero" << std::endl;		
	}
	//Insertamos la textura en el map que hemos definido en la clase
	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::get(Textures::ID id)
{
	//hacemos una busqueda en el map por el id para encontrar la correspodiente textura
	//auto utiliza "type inference" que es nuevo en c++11, y que hace que infiera el tipo de found segun la operacion
	auto found = mTextureMap.find(id);
	//accedemos al segundo miembro que es el que tiene el unique_pointer de la textura, y deferenciamos para obtener la textura
	return *found->second;
}

const sf::Texture& TextureHolder::get(Textures::ID id) const
{
	//hacemos una busqueda en el map por el id para encontrar la correspodiente textura
	auto found = mTextureMap.find(id);
	//accedemos al segundo miembro que es el que tiene el unique_pointer de la textura, y deferenciamos para obtener la textura
	return *found->second;
}

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
	TextureHolder texture;
	texture.load(Textures::Airplane, "media/textures/mother.bmp");	
	mPlayer.setTexture(texture.get(Textures::Airplane));
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