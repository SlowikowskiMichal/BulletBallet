#pragma once
#include <vector>
#include "GameObject.h"
#include "Bullet.h"
#include "Error.h"

using namespace sf;
using namespace std;

class Member : public GameObject
{
public:
	Member();
	Member(float, float);
	~Member();
	//-------------------------------------------------------------
	//Stats

	int getID();
	void setID(int);
	Color getColor();
	void setColor(Color);


	//-------------------------------------------------------------
	//Member move

	virtual void move(float, float) = 0;
	void setPosition(float, float);
	Vector2f getPosition();
	float getRotation();
	void restorePosition();
	float getAngle();
	FloatRect getGlobalBounds();
	FloatRect getBulletGlobalBounds(int);

	//-------------------------------------------------------------
	//Member shoots

	float getShootDelay();
	float getshootTime();
	float getBulletAngle(int);
	Vector2f getBulletPosition(int i);
	size_t getBulletsCount();

	bool moveBullet(int, int, int);
	void setDead(int);
	void killBullet(int);

	void drawBullets(RenderWindow &);

	//-------------------------------------------------------------
	//Member Update Sprites
	void animation();

protected:

	//-------------------------------------------------------------
	//Member Sprite & Texture
	Sprite spriteTutu;
	Texture textureTutu;
	Texture textureTors;
	size_t frame;

	//-------------------------------------------------------------
	//Stats
	int id;
	Color color;

	//-------------------------------------------------------------
	//Member move
	float angle;
	Vector2f speed;
	float maxSpeed;
	Clock moveTime;
	Vector2f lastPos;

	//-------------------------------------------------------------
	//Member shoots
	Clock shootTime;
	float shootDelay;
	vector<Bullet *> bullets;
	float bulletSpeed;
	enum shotType { rifle, shotgun };
	shotType type;
	Texture bulletTexture;

	virtual void draw(RenderTarget &target, RenderStates states) const;
};