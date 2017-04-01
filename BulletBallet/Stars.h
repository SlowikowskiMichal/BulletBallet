#pragma once
#include <SFML\Graphics.hpp>
//#include <iostream>

using namespace sf;

class Stars : public sf::Drawable, public sf::Transformable
{
public:

	Stars(int);
	Stars();
	void update();

private:


	struct Particle
	{
		Vector2f speed;
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void reset(size_t);


	std::vector<Particle> particles;
	VertexArray vert;
};