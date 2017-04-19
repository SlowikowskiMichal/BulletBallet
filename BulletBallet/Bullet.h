#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;

class Bullet : public Drawable, Transformable
{
public:

	Bullet(Vector2f, float, float,float);
	~Bullet();

	void update();
	void move();
	bool isAlive();
	void setDead();
	bool isInside(int, int);
	virtual Vector2f getPosition();

private:
	
	size_t frame;
	Sprite sprite;
	Texture texture;
	Vector2f speed;
	Clock moveTime;
	bool alive;


	virtual void draw(RenderTarget &target, RenderStates states) const;
};