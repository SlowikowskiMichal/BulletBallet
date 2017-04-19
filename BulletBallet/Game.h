#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Floor.h"

using namespace sf;

class Game
{
public:
	Game(RenderWindow &, Sprite);
	~Game();

	void start();

private:
	RenderWindow &window;
	Player player;
	Floor floor;
	Clock frameTime;
	Music theme;
	Sprite sight;

	void update();
	void animation();
	void draw();
};