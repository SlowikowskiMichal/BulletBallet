#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Bullet.h"
#include <vector>

using namespace sf;
using namespace std;

class Player : public Drawable, Transformable
{
public:
	Player();
	~Player();
	//-------------------------------------------------------------
	//Stats

	int getHealth();
	bool hit();

	//-------------------------------------------------------------
	//Player move

	void setRotation(Vector2i);
	void setSpeedY(int);
	void setSpeedX(int);
	void move();

	//-------------------------------------------------------------
	//Player shoots
	float getShootDelay();
	float getshootTime();
	void shoot(Vector2i);
	void moveBullets();
	void drawBullets(RenderWindow &);

	//-------------------------------------------------------------
	//Player Update Sprites
	void update();

private:
	//-------------------------------------------------------------
	//Player Sprite & Texture
	Sprite spritePlayer;
	Texture texturePlayer;

	//-------------------------------------------------------------
	//Stats
	int health;

	//-------------------------------------------------------------
	//Player move
	Vector2f speed;
	float maxSpeed;
	Clock moveTime;


	//-------------------------------------------------------------
	//Player shoots
	vector<Bullet *> bullets;
	Clock shootTime;
	float shootDelay;
	float bulletSpeed;
	enum shotType {rifle,shotgun};
	shotType type;

	//-------------------------------------------------------------
	//Draw player
	virtual void draw(RenderTarget &target, RenderStates states) const;
};