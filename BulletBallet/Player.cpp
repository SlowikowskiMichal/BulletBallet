#include "Player.h"
#include <math.h>
#include <iostream>

Player::Player()
{
	//Sprite
	if (!texturePlayer.loadFromFile("files/textures/player.png"))
	{
			
	}

	texturePlayer.setSmooth(true);
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setTextureRect(IntRect(0, 0, 32, 32));
	spritePlayer.setPosition(100, 100);
	lastPos = spritePlayer.getPosition();
	spritePlayer.setOrigin(16, 16);
//	spritePlayer.setScale(2.f, 2.f);

	//Stats
	health = 3;

	//Velocity
	maxSpeed = 300.f;
	speed = Vector2f(0.f, 0.f);

	//Time
	moveTime.restart();

	//Shoot
	shootDelay = 0.15;
	bulletSpeed = 500.f;
	type = shotType::rifle;
}

Player::Player(float windowWidth, float windowHeight)
{
	//Sprite
	if (!texturePlayer.loadFromFile("files/textures/player.png"))
	{

	}

	texturePlayer.setSmooth(true);
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setTextureRect(IntRect(0, 0, 32, 32));
	spritePlayer.setPosition(windowWidth/8, windowWidth/6);
	lastPos = spritePlayer.getPosition();
	spritePlayer.setOrigin(16, 16);
	spritePlayer.setScale(windowWidth/800, windowWidth/800);

	//Stats
	health = 3;

	//Velocity
	maxSpeed = 0.5f * windowHeight;
	speed = Vector2f(0.f, 0.f);

	//Time
	moveTime.restart();

	//Shoot
	shootDelay = 0.15;
	bulletSpeed = 1.f * windowHeight;
	type = shotType::rifle;

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

Vector2f Player::getPosition()
{
	return spritePlayer.getPosition();
}

void Player::setRotation(Vector2i mouse)
{
	spritePlayer.setRotation(-atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) * 180 / 3.14159265);
}

void Player::setSpeedY(int y)
{
	speed.y = y*maxSpeed;
}

void Player::setSpeedX(int x)
{
		speed.x = x*maxSpeed;
}



void Player::setPosition(int x, int y)
{
	spritePlayer.setPosition(x, y);
}

void Player::restorePosition()
{
	spritePlayer.setPosition(lastPos);
}
void Player::move(int width, int height)
{
	if (speed.x || speed.y)
	{
		lastPos = spritePlayer.getPosition();
		spritePlayer.move(speed * moveTime.getElapsedTime().asSeconds());
		speed = Vector2f(0.f, 0.f);
		if (spritePlayer.getPosition().x >= width)
			spritePlayer.setPosition(1, spritePlayer.getPosition().y);
		else if (spritePlayer.getPosition().x <= 0)
			spritePlayer.setPosition(width - 1, spritePlayer.getPosition().y);
		if (spritePlayer.getPosition().y >= height)
			spritePlayer.setPosition(spritePlayer.getPosition().x, 1);
		else if (spritePlayer.getPosition().y <= 0)
			spritePlayer.setPosition(spritePlayer.getPosition().x, height - 1);
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
		bullets.push_back(new Bullet(spritePlayer.getPosition(), -atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) + 1.57079632, bulletSpeed, spritePlayer.getScale().x));
		break;
	case shotgun:
		bullets.push_back(new Bullet(spritePlayer.getPosition(), -atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) + 1.57079632, bulletSpeed, spritePlayer.getScale().x));
		bullets.push_back(new Bullet(spritePlayer.getPosition(), -atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) + 1.37079632, bulletSpeed, spritePlayer.getScale().x));
		bullets.push_back(new Bullet(spritePlayer.getPosition(), -atan2(mouse.x - spritePlayer.getPosition().x, mouse.y - spritePlayer.getPosition().y) + 1.77079632, bulletSpeed, spritePlayer.getScale().x));
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

Vector2f Player::getBulletPosition(int i)
{
	return bullets[i]->getPosition();
}

size_t Player::getBulletsCount()
{
	return bullets.size();
}

bool Player::moveBullet(int i, int windowWidth, int windowHeight)
{
				
	if (bullets[i]->isAlive() && bullets[i]->isInside(windowWidth, windowHeight))
	{
		bullets[i]->move();
		return true;
	}
	else
	{
		std::swap(bullets[i], bullets.back());
		delete bullets[bullets.size() - 1];
		bullets.pop_back();
	}
	return false;
}

//-------------------------------------------------------------
//Player Update
void Player::animation()
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

void Player::killBullet(int i)
{
	bullets[i]->setDead();
}