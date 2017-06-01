#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "SFML\Network\IpAddress.hpp"
#include "Error.h"
#include <string>
#include <regex>
#include "Game.h"
#include "Stars.h"


using namespace std;
using namespace sf;

class Menu
{
public:
	Menu();
	~Menu();
	void start();

protected:
	enum GameState { MENU, GAME, END };
	GameState state;

private:
	RenderWindow window;
	Music theme;
	Font *font;
	Texture texture;
	Sprite sprite;
	Stars stars;
	string allInpt;

	void play();
	void mainMenu();
	void scoreBoard(int);
	string ipCheck();
};