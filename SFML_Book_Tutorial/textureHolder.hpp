#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

//Creamos el enum para referirnos de este modo Textures::ID, para que no haya colision de nombres
namespace Textures
{
	enum ID { Landscape, Airplane, Missile };
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