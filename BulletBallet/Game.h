#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "SFML\Network.hpp"
#include "Player.h"
#include "Enemy.h"
#include "Floor.h"
#include "Explosion.h"
#include "Member.h"

using namespace sf;

class Game
{
public:
	Game(RenderWindow &, Sprite, string,Font);
	~Game();

	int start();

private:

	bool stay;
	int score;

	RenderWindow &window;
	Music theme;
	Sprite sight;
	Player player;
	map<int, Enemy*> enemies;
	vector<Explosion*> explosions;
	Texture explosionTexture;
	Floor floor;

	Clock frameTime;
	Clock explosionTime;
	Clock sendPosTime;

	TcpSocket socket;
	Packet packet;
	Packet packetRecive;
	Mutex mutex;

	void recive();
	void update();
	void animation();
	void draw();
};