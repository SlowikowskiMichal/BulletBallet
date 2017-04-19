#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;

class Floor : public sf::Drawable {
public:

	Floor();
	Floor(float,float);
	~Floor();
	bool isColliding(Vector2f);

private:
	std::vector<int> collisions;
	sf::VertexArray quads;
	sf::Texture texture;
	int width;
	int height;
	float tileSize;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
