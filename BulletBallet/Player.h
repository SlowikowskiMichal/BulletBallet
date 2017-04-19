#pragma once
#include <SFML\Graphics.hpp>
#include "Bullet.h"
#include <vector>

using namespace sf;
using namespace std;

class Player : public Drawable, Transformable
{
public:
	Player();
	Player(float,float);
	~Player();
	//-------------------------------------------------------------
	//Stats

	int getHealth();
	bool hit();

	//-------------------------------------------------------------
	//Player move

	Vector2f getPosition();

	void setRotation(Vector2i);
	void setPosition(int, int);
	void setSpeedX(int);
	void setSpeedY(int);
	void restorePosition();
	void move(int,int);

	//-------------------------------------------------------------
	//Player shoots
	float getShootDelay();
	float getshootTime();
	Vector2f getBulletPosition(int i);
	size_t getBulletsCount();

	void shoot(Vector2i);
	bool moveBullet(int,int,int);
	void killBullet(int);
	void drawBullets(RenderWindow &);

	//-------------------------------------------------------------
	//Player Update Sprites
	void animation();

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
	Vector2f lastPos;


	//-------------------------------------------------------------
	//Player shoots
	Clock shootTime;
	float shootDelay;
	vector<Bullet *> bullets;
	float bulletSpeed;
	enum shotType {rifle,shotgun};
	shotType type;

	//-------------------------------------------------------------
	//Draw player
	virtual void draw(RenderTarget &target, RenderStates states) const;
};