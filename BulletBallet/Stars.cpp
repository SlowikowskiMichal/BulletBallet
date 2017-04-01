#include "Stars.h"

Stars::Stars() : particles(1000), vert(sf::Points, 1000)
{
	for (size_t i = 0; i < 1000; i++)
	{

		float speed = (std::rand() % 150 + 100);
		particles[i].speed = Vector2f(speed / 100, 0);
		vert[i].color.a = (std::rand() % static_cast<int>(speed));
		vert[i].position.y = rand() % 600;
		vert[i].position.x = rand() % 800;
	}
}

Stars::Stars(int n) : particles(n), vert(sf::Points, n)
{
	for (size_t i = 0; i < n; i++)
	{

		float speed = (std::rand() % 150 + 100);
		particles[i].speed = Vector2f(speed / 100, 0);
		vert[i].color.a = (std::rand() % static_cast<int>(speed));
		vert[i].position.y = rand() % 600;
		vert[i].position.x = rand() % 800;
	}
}

void Stars::update()
{

	for (size_t i = 0; i < particles.size(); i++)
	{

		if (vert[i].position.x > 800)
		{
			reset(i);
		}

		vert[i].position += particles[i].speed;

	}

}

void Stars::reset(size_t i)
{
	float speed = (std::rand() % 150 + 100);
	particles[i].speed = Vector2f(speed / 100, 0);
	vert[i].color.a = (std::rand() % static_cast<int>(speed));
	switch (i % 3)
	{
	case 0:
		vert[i].color.r = 200;
		break;
	case 1:
		vert[i].color.b = 200;
		break;
	case 2:
		vert[i].color.b = rand() % 100 + 100;
		vert[i].color.r = rand() % 100 + 100;
		break;
	}
	vert[i].position.y = rand() % 600;
	vert[i].position.x = 0;
}

void Stars::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	states.transform *= getTransform();

	states.texture = NULL;

	target.draw(vert, states);

}