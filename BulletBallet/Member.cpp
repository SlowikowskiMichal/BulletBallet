#include "Member.h"

Member::Member()
{
	try
	{
		if (!textureTutu.loadFromFile("files/textures/player.png"))
			throw Error(Error::texture);
	}
	catch (Error &error)
	{
		error.err();
	}

	textureTutu.setSmooth(true);
	spriteTutu.setTexture(textureTutu);
	spriteTutu.setTextureRect(IntRect(0, 0, 32, 32));
	spriteTutu.setPosition(100, 100);
	lastPos = spriteTutu.getPosition();
	spriteTutu.setOrigin(16, 16);


	//Stats
	color = Color::Blue;

	//Velocity
	maxSpeed = 300.f;
	angle = 0;
	speed = Vector2f(0.f, 0.f);

	//Time
	moveTime.restart();

	//Shoot
	shootDelay = 0.00015;
	bulletSpeed = 0.f;
	type = shotType::shotgun;
}

Member::Member(float windowWidth, float windowHeight) : color(Color::Magenta)
{
	try
	{
		if (!textureTutu.loadFromFile("files/textures/bal_tutu.png"))
			throw Error(Error::texture);

		if (!textureTors.loadFromFile("files/textures/bal_tors.png"))
			throw Error(Error::texture);
	}
	catch (Error &error)
	{
		error.err();
	}

	textureTutu.setSmooth(true);
	spriteTutu.setColor(color);
	spriteTutu.setTexture(textureTutu);
	spriteTutu.setTextureRect(IntRect(0, 0, 32, 32));
	spriteTutu.setPosition(windowWidth / 8, windowWidth / 6);
	spriteTutu.setOrigin(16, 16);
	spriteTutu.setScale(windowWidth / 800, windowWidth / 800);

	sprite.setTexture(textureTors);
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	sprite.setPosition(windowWidth / 8, windowWidth / 6);
	sprite.setOrigin(16, 16);
	sprite.setScale(windowWidth / 800, windowWidth / 800);


	if (!bulletTexture.loadFromFile("files/textures/bullet1.png"))
		exit(-200);

	//Stats
	lastPos = spriteTutu.getPosition();

	//Velocity
	maxSpeed = 0.5f * windowHeight;
	angle = 0;
	speed = Vector2f(0.f, 0.f);

	//Time
	moveTime.restart();

	//Shoot
	shootDelay = 0.0001;
	bulletSpeed = 1.f * windowHeight;
	type = shotType::rifle;

	id = 0;
}

Member::~Member()
{
	for (int i = 0; i < bullets.size();)
	{
		delete bullets[bullets.size() - 1];
		bullets.pop_back();
	}
}

//-------------------------------------------------------------

int Member::getID()
{
	return id;
}

void Member::setID(int iid)
{
	id = iid;
}

Color Member::getColor()
{
	return color;
}

void Member::setColor(Color newColor)
{
	color = newColor;
	spriteTutu.setColor(color);
}

//-------------------------------------------------------------
//Member move

Vector2f Member::getPosition()
{
	return spriteTutu.getPosition();
}

void Member::setPosition(float x, float y)
{
	spriteTutu.setPosition(x, y);
	sprite.setPosition(x, y);
}

float Member::getRotation()
{
	return spriteTutu.getRotation();
}

void Member::restorePosition()
{
	spriteTutu.setPosition(lastPos);
	sprite.setPosition(lastPos);
}

float Member::getAngle()
{
	return angle;
}

FloatRect Member::getGlobalBounds()
{
	return FloatRect(spriteTutu.getPosition(), Vector2f(spriteTutu.getGlobalBounds().width / 4, spriteTutu.getGlobalBounds().height / 4));
}

FloatRect Member::getBulletGlobalBounds(int i)
{
	return FloatRect(bullets[i]->getPosition() ,Vector2f(bullets[i]->getGlobalBounds().width/4, bullets[i]->getGlobalBounds().height / 4));
}


//-------------------------------------------------------------
//Member shoots

float Member::getShootDelay()
{
	return shootDelay;
}

float Member::getshootTime()
{
	return shootTime.getElapsedTime().asSeconds();
}

float Member::getBulletAngle(int i)
{
	return bullets[i]->getAngle();
}

Vector2f Member::getBulletPosition(int i)
{
	return bullets[i]->getPosition();
}

size_t Member::getBulletsCount()
{
	return bullets.size();
}


bool Member::moveBullet(int i, int windowWidth, int windowHeight)
{

	if (bullets[i]->isAlive() && bullets[i]->isInside(windowWidth, windowHeight))
	{
		bullets[i]->move();
		return true;
	}

	return false;
}

void Member::setDead(int i)
{
	bullets[i]->setDead();
}

void Member::killBullet(int i)
{
	std::swap(bullets[i], bullets.back());
	delete bullets[bullets.size() - 1];
	bullets.pop_back();
}

//-------------------------------------------------------------
//Member Update
void Member::animation()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
	}
	if (frame < 3)
		frame++;
	else
		frame = 0;
	spriteTutu.setTextureRect(IntRect(frame * spriteTutu.getTextureRect().width, 0, spriteTutu.getTextureRect().width, spriteTutu.getTextureRect().height));
	sprite.setTextureRect(IntRect(frame * sprite.getTextureRect().width, 0, sprite.getTextureRect().width, sprite.getTextureRect().height));
}


//-------------------------------------------------------------
//Draw player

void Member::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(spriteTutu);
	target.draw(sprite);
}

void Member::drawBullets(RenderWindow & window)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window.draw(*bullets[i]);
	}
}
