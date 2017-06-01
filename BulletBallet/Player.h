#pragma once
#include "Member.h"

using namespace sf;
using namespace std;

class Player : public Member
{
public:
	Player(float,float);
	~Player();
	//-------------------------------------------------------------
	//Player move

	void setRotation(Vector2i);
	void setSpeedX(int);
	void setSpeedY(int);
	void move(float, float);
	
	//-------------------------------------------------------------
	//Player shoots

	void shoot(Vector2i);

	//-------------------------------------------------------------
	//Player Update Sprites

private:

};