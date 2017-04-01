#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>

using namespace sf;

class Bullet : public Drawable, Transformable
{
public:

	Bullet(Vector2f, float, float);
	~Bullet();

	float get();
	void update();
	void move();
	bool outside();

private:

	size_t frame;
	Sprite sprite;
	Texture texture;
	Vector2f speed;
	Clock moveTime;

	virtual void draw(RenderTarget &target, RenderStates states) const;
};