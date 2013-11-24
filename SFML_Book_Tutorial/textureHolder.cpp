#include "textureHolder.hpp"

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