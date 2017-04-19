#include "Bullet.h"
#include <iostream>

Bullet::Bullet(Vector2f bPosition, float bAngle, float bSpeed, float scale) : frame(0)
{

	if (!texture.loadFromFile("files/textures/bullet1.png"))
		exit(-200);

	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	sprite.setPosition(bPosition);
	sprite.setOrigin(16, 16);
	sprite.setScale(1, 1);
	sprite.setColor(Color::Cyan);
	sprite.setScale(scale, scale);
	speed = Vector2f(cosf(bAngle), sinf(bAngle)) * bSpeed;

	alive = true;


}


Bullet::~Bullet()
{

}

void Bullet::update()
{
	if (frame < 4)
		frame++;
	else
		frame = 0;

	sprite.setTextureRect(IntRect(frame * 32, 0, 32, 32));

}

void Bullet::move()
{
	sprite.move(speed * moveTime.getElapsedTime().asSeconds());
	moveTime.restart();
}

Vector2f Bullet::getPosition()
{
	return sprite.getPosition();
}

bool Bullet::isAlive()
{
	return alive;
}

void Bullet::setDead()
{
	alive = false;
}


bool Bullet::isInside(int windowWidth, int windowHeight)
{
	if (sprite.getPosition().x > windowWidth || sprite.getPosition().x < 0 ||
		sprite.getPosition().y > windowHeight || sprite.getPosition().y < 0)
		return false;
	else
		return true;
	
}

void Bullet::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(sprite, states);
}