#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include "Game.h"
#include "Stars.h"

using namespace std;
using namespace sf;

class Menu
{
private:
	RenderWindow okno;
	Font *font;										//przechowuje czcionkê
	Music theme;
	void print();
	void play();
	Texture texture;
	Sprite sprite;

protected:
	enum StanGry { MENU, GAME, GAME_OVER, END };
	StanGry stan;

public:
	Menu();											//ustawia stan gry
	~Menu();

	void start();
};