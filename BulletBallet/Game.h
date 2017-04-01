#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Map.h"
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
	Map board;
	Clock frameTime;

	Sprite sight;

};