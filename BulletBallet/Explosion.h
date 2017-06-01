#pragma once
#include "GameObject.h"

using namespace sf;

class Explosion : public GameObject
{
public:
	Explosion(Vector2f, float, Texture, float, float,Color);
	~Explosion();

	bool animation();

};