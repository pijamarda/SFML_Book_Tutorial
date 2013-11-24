#include "textureHolder.hpp"

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