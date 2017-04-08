#include "Player.h"
#include <math.h>
#include <iostream>
Player::Player()
{
	//Sprite
	if (!texturePlayer.loadFromFile("files/textures/pointer.png"))
	{
			
	}

	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setTextureRect(IntRect(0, 0, 64, 64));
	spritePlayer.setPosition(400, 300);
	spritePlayer.setOrigin(32, 32);
	spritePlayer.setScale(0.5f, 0.5f);

	//Stats
	health = 3;

	//Velocity
	maxSpeed = 250.f;
	speed = Vector2f(0.f, 0.f);

	//Time
	moveTime.restart();

	//Shoot
	shootDelay = 0.25;
	bulletSpeed = 500.f;
	type = shotType::shotgun;
	
}

Player::~Player()
{

}

//-------------------------------------------------------------
int Player::getHealth()
{
	return health;
}
bool Player::hit()
{
	health--;
	if (health > 0)
		return true;
	return false;
	
}


//-------------------------------------------------------------
//Player move

void Player::setRotation(Vector2i mouse)
{
	spritePlayer.setRotation(-atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) * 180 / 3.14159265 + 180);
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
		spritePlayer.move(speed * moveTime.getElapsedTime().asSeconds());
		speed = Vector2f(0.f, 0.f);
		if (spritePlayer.getPosition().x > 800)
			spritePlayer.setPosition(0, spritePlayer.getPosition().y);
		else if (spritePlayer.getPosition().x < 0)
			spritePlayer.setPosition(800, spritePlayer.getPosition().y);
		if (spritePlayer.getPosition().y > 600)
			spritePlayer.setPosition(spritePlayer.getPosition().x, 0);
		else if (spritePlayer.getPosition().y < 0)
			spritePlayer.setPosition(spritePlayer.getPosition().x, 600);
	}
	moveTime.restart();
}

//-------------------------------------------------------------
//Player shoots

void Player::shoot(Vector2i mouse)
{
	switch (type)
	{
	case rifle:
		bullets.push_back(new Bullet(spritePlayer.getPosition(), -atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) + 1.57079632, bulletSpeed));
		break;
	case shotgun:
		bullets.push_back(new Bullet(spritePlayer.getPosition(), -atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) + 1.57079632, bulletSpeed));
		bullets.push_back(new Bullet(spritePlayer.getPosition(), -atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) + 1.37079632, bulletSpeed));
		bullets.push_back(new Bullet(spritePlayer.getPosition(), -atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) + 1.77079632, bulletSpeed));
		break;
	default:
		break;
	}
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
		if(bullets[i]->outside())
			bullets[i]->move();
		else
		{
			std::swap(bullets[i], bullets.back());
			delete bullets[bullets.size() - 1];
			bullets.pop_back();
		}
			
	}
}

//-------------------------------------------------------------
//Player Update
void Player::update()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
	}
}


//-------------------------------------------------------------
//Draw player

void Player::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(spritePlayer);
}

void Player::drawBullets(RenderWindow & window)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window.draw(*bullets[i]);
	}
}