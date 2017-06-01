#include "Enemy.h"

Enemy::Enemy(float windowWidth, float windowHeight,int i) : Member(windowWidth, windowHeight)
{
	setID(i);
}

Enemy::~Enemy()
{
	for (size_t i = 0; i < bullets.size();)
	{
		delete bullets[bullets.size() - 1];
		bullets.pop_back();
	}
}

//-------------------------------------------------------------
//Enemy move
void Enemy::setRotation(float angle)
{
	spriteTutu.setRotation(angle);
	sprite.setRotation(angle);
}

void Enemy::move(float x, float y)
{
	spriteTutu.setPosition(Vector2f(x,y));
	sprite.setPosition(Vector2f(x,y));
}

//-------------------------------------------------------------
//Enemy shoots

void Enemy::shoot(Vector2f pos, float angle)
{

	switch (type)
	{
	case rifle:
		bullets.push_back(new Bullet(pos, angle, bulletSpeed, spriteTutu.getScale().x, bulletTexture, color));
		break;
	case shotgun:
		bullets.push_back(new Bullet(pos, angle, bulletSpeed, spriteTutu.getScale().x, bulletTexture, color));
		bullets.push_back(new Bullet(pos, angle - 0.2, bulletSpeed, spriteTutu.getScale().x, bulletTexture, color));
		bullets.push_back(new Bullet(pos, angle + 0.2, bulletSpeed, spriteTutu.getScale().x, bulletTexture, color));
		break;
	default:
		break;
	}
	shootTime.restart();
}