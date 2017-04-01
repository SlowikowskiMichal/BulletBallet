#pragma once
#include <SFML\Graphics.hpp>


class Map : public sf::Drawable, public sf::Transformable {
public:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
};