#include "Player.h"
#include <math.h>
#include <iostream>

Player::Player()
{
	//Sprite
	if (!texture.loadFromFile("files/textures/pointer.png"))
	{
			
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 64, 64));
	sprite.setPosition(400, 300);
	sprite.setOrigin(32, 32);
	sprite.setScale(0.5f, 0.5f);

	//Velocity
	maxSpeed = 250.f;
	speed = Vector2f(0.f, 0.f);

	//Time
	moveTime.restart();

	//Shoot
	shootDelay = 0.05;
	bulletSpeed = 600.f;
	
}

Player::~Player()
{

}
//-------------------------------------------------------------
//Player move

void Player::setRotation(Vector2i mouse)
{
	sprite.setRotation(-atan2(mouse.x - sprite.getPosition().x, mouse.y - sprite.getPosition().y) * 180 / 3.14159265 + 180);
}

void Player::setSpeedY(int y)
{
	speed.y = y*maxSpeed;
}

void Player::setSpeedX(int x)
{
		speed.x = x*maxSpeed;
}

void Player::move()
{
	if (speed.x || speed.y)
	{
		sprite.move(speed * moveTime.getElapsedTime().asSeconds());
		speed = Vector2f(0.f, 0.f);
		if (sprite.getPosition().x > 800)
			sprite.setPosition(0, sprite.getPosition().y);
		else if (sprite.getPosition().x < 0)
			sprite.setPosition(800, sprite.getPosition().y);
		if (sprite.getPosition().y > 600)
			sprite.setPosition(sprite.getPosition().x, 0);
		else if (sprite.getPosition().y < 0)
			sprite.setPosition(sprite.getPosition().x, 600);
	}
	moveTime.restart();
}

//-------------------------------------------------------------
//Player shoots

void Player::shoot(Vector2i mouse)
{
	bullets.push_back(* new Bullet(sprite.getPosition(), -atan2(mouse.x - sprite.getPosition().x, mouse.y - sprite.getPosition().y) + 1.57079632, bulletSpeed));
	shootTime.restart();
	
}

float Player::getShootDelay()
{
	return shootDelay;
}

float Player::getshootTime()
{
	return shootTime.getElapsedTime().asSeconds();
}

void Player::moveBullets()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if(bullets[i].outside())
			bullets[i].move();
		else
			bullets.erase(bullets.begin() + i);
	}
}

//-------------------------------------------------------------
//Player Update
void Player::update()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].update();
	}
}


//-------------------------------------------------------------
//Draw player

void Player::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(sprite);
}

void Player::drawBullets(RenderWindow & window)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window.draw(bullets[i]);
	}
}