#include "Player.h"
#include <math.h>

Player::Player(float windowWidth, float windowHeight) : Member(windowWidth,windowHeight)
{

}

Player::~Player()
{
	for (int i = 0; i < bullets.size();)
	{	
		delete bullets[bullets.size() - 1];
		bullets.pop_back();
	}
}

//-------------------------------------------------------------
//Player move


void Player::setRotation(Vector2i mouse)
{
	float angle = -atan2(mouse.x - spriteTutu.getPosition().x, mouse.y - spriteTutu.getPosition().y) * 180 / 3.14159265;
	spriteTutu.setRotation(angle);
	sprite.setRotation(angle);
}

void Player::setSpeedY(int y)
{
	speed.y = y*maxSpeed;
}

void Player::setSpeedX(int x)
{
		speed.x = x*maxSpeed;
}

void Player::move(float width, float height)
{
	if (speed.x || speed.y)
	{
		lastPos = spriteTutu.getPosition();
		spriteTutu.move(speed * moveTime.getElapsedTime().asSeconds());
		speed = Vector2f(0.f, 0.f);
		if (spriteTutu.getPosition().x >= width)
			spriteTutu.setPosition(1, spriteTutu.getPosition().y);
		else if (spriteTutu.getPosition().x <= 0)
			spriteTutu.setPosition(width - 1, spriteTutu.getPosition().y);
		if (spriteTutu.getPosition().y >= height)
			spriteTutu.setPosition(spriteTutu.getPosition().x, 1);
		else if (spriteTutu.getPosition().y <= 0)
			spriteTutu.setPosition(spriteTutu.getPosition().x, height - 1);
		sprite.setPosition(spriteTutu.getPosition());
	}
	moveTime.restart();
}

//-------------------------------------------------------------
//Player shoots

void Player::shoot(Vector2i mouse)
{
	angle = -atan2(mouse.x - spriteTutu.getPosition().x, mouse.y - spriteTutu.getPosition().y) + 1.57079632;
	switch (type)
	{
	case rifle:
		bullets.push_back(new Bullet(spriteTutu.getPosition(), angle, bulletSpeed, spriteTutu.getScale().x, bulletTexture, color));
		break;
	case shotgun:
		bullets.push_back(new Bullet(spriteTutu.getPosition(), angle, bulletSpeed, spriteTutu.getScale().x, bulletTexture, color));
		bullets.push_back(new Bullet(spriteTutu.getPosition(), angle - 0.2, bulletSpeed, spriteTutu.getScale().x, bulletTexture, color));
		bullets.push_back(new Bullet(spriteTutu.getPosition(), angle + 0.2, bulletSpeed, spriteTutu.getScale().x, bulletTexture, color));
		break;
	default:
		break;
	}
	shootTime.restart();
}
