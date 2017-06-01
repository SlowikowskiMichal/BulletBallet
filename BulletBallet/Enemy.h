#pragma once
#include "Member.h"

using namespace sf;


class Enemy : public Member
{
public:
	Enemy(float, float,int);
	~Enemy();

	//-------------------------------------------------------------
	//Enemy move

	void setRotation(float);
	void move(float, float);

	//-------------------------------------------------------------
	//Enemy shoots

	void shoot(Vector2f, float);

private:

};