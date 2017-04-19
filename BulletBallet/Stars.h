#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;

class Stars : public sf::Drawable, public sf::Transformable
{
public:

	Stars();
	Stars(int, int);
	void update();

private:

	struct Particle
	{
		Vector2f speed;
		Clock time;
	};

	int width;
	int height;
	std::vector<Particle> particles;
	VertexArray vert;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void reset(size_t);
	

};