#include "Game.h"
#include <iostream>

Game::Game(RenderWindow &win, Sprite mouse, string ip, Font font) : window(win), sight(mouse), player(window.getSize().x, window.getSize().y), floor(window.getSize().x, window.getSize().y)
{
	stay = true;


	try
	{
		if (!theme.openFromFile("files/music/game.ogg") && stay)
			throw Error(Error::music);

		if (!explosionTexture.loadFromFile("files/textures/explosion.png") && stay)
				throw Error(Error::texture);
	}
	catch (Error &error)
	{
		error.err();
	}


	theme.setLoop(true);

	if(socket.connect(ip,42081) != sf::Socket::Done && stay)
	{
		stay = false;
		Text monit = Text(L"Error\nNie uda³osiê\npo³¹czyæ z serwerem", font, window.getSize().x / 30);
		Clock time;
		monit.setOrigin(monit.getGlobalBounds().width / 2, monit.getGlobalBounds().height / 2);
		monit.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		monit.setOutlineThickness(window.getSize().y / 200);
		monit.setOutlineColor(Color(255, 0, 0, 255));
		monit.setFillColor(Color(255, 255, 255, 220));
		while (time.getElapsedTime().asSeconds() < 3)
		{
			sight.setPosition(static_cast<Vector2f>(Mouse::getPosition()));
			window.clear(Color(10,0,15,255));
			window.draw(monit);
			window.display();
		}
	}


	if (stay)
	{
		int id;
		int size;
		int start = 0;

		socket.receive(packet);
		packet >> id >> size;
		player.setID(id);
		packet.clear();

		while (start != size)
		{
			socket.receive(packet);
			
			packet >> start;
			packet.clear();

		}



		for (int i = 0; i < size; i++)
		{
			if (i != id)
			{
				enemies[i] = new Enemy(window.getSize().x, window.getSize().y,i);
			}
		}

		switch (id)
		{
		case 0:
			player.setPosition(window.getSize().x / 8, window.getSize().y / 6);
			player.setColor(Color::Magenta);
			break;
		case 1:
			player.setPosition(window.getSize().x / 8 + window.getSize().x / 8 * 6, window.getSize().y / 6 + window.getSize().y / 6 * 4);
			player.setColor(Color::Red);
			break;
		case 2:
			player.setPosition(window.getSize().x / 8 + window.getSize().x / 8 * 6, window.getSize().y / 6);
			player.setColor(Color::Cyan);
			break;
		case 3:
			player.setPosition(window.getSize().x / 8, window.getSize().y / 6 + window.getSize().y / 6 * 4);
			player.setColor(Color::Green);
			break;
		default:
			player.setPosition(window.getSize().x / 2, window.getSize().y / 2);
			player.setColor(Color::Black);
			break;
		}

		for (map<int, Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
		{
			switch (i->first)
			{
			case 0:
				i->second->setPosition(window.getSize().x / 8, window.getSize().y / 6);
				i->second->setColor(Color::Magenta);
				break;
			case 1:
				i->second->setPosition(window.getSize().x / 8 + window.getSize().x / 8 * 6, window.getSize().y / 6 + window.getSize().y / 6 * 4);
				i->second->setColor(Color::Red);
				break;
			case 2:
				i->second->setPosition(window.getSize().x / 8 + window.getSize().x / 8 * 6, window.getSize().y / 6);
				i->second->setColor(Color::Cyan);
				break;
			case 3:
				i->second->setPosition(window.getSize().x / 8, window.getSize().y / 6 + window.getSize().y / 6 * 4);
				i->second->setColor(Color::Green);
				break;
			default:
				i->second->setPosition(window.getSize().x / 2, window.getSize().y / 2);
				i->second->setColor(Color::Black);
				break;
			}
		}


		score = 0;
	}

}

Game::~Game()
{

}

void Game::recive()
{
	Uint8 choice;
	int enemyID;

	float x, y, z;
	while (true )
	{
		socket.receive(packetRecive);
		if (packetRecive >> choice)
			switch (choice)
			{
			case 1://zmiana pozycji przeciwnika
				packetRecive >> enemyID >> x >> y >> z;
				mutex.lock();
				enemies[enemyID]->setPosition(x * window.getSize().x, y * window.getSize().y);
				enemies[enemyID]->setRotation(z);
				mutex.unlock();
				break;
			case 2://strza³ przeciwnika
				packetRecive >> enemyID >> x >> y >> z;
				mutex.lock();
				enemies[enemyID]->shoot(Vector2f(x * window.getSize().x, y * window.getSize().y), z);
				mutex.unlock();
				break;
			case 0://sygna³ koñca gry
				stay = false;
				break;
			default:
				break;
			}
		
		packetRecive.clear();
	}
}

int Game::start()
{
	if (stay)
	{
		theme.play();
		sight.setColor(player.getColor());
		Thread netThread(&Game::recive, this);
		netThread.launch();

		while (stay)
		{
			{
				//-----------------------------------------------------------------------------------
				//Input
				if (window.hasFocus())
				{
					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
							stay = false;

					}


					if (Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S))
					{
						player.setSpeedY(-1);
					}
					else if (Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::W))
					{
						player.setSpeedY(1);
					}
					if (Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
					{
						player.setSpeedX(-1);
					}
					else if (Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A))
					{
						player.setSpeedX(1);
					}
					if (Mouse::isButtonPressed(Mouse::Left) && player.getshootTime() > player.getShootDelay())
					{
						mutex.lock();
						player.shoot(Mouse::getPosition(window));
						packet << Uint8(2) << player.getID() << player.getPosition().x / window.getSize().x << player.getPosition().y / window.getSize().y << player.getAngle();
						socket.send(packet);
						packet.clear();
						mutex.unlock();
					}
				}

				//------------------------------------------------------------------------------------------
				//Set Objects Positions
				update();

				if (sendPosTime.getElapsedTime().asSeconds() > 0.016)
				{
					mutex.lock();
					packet << Uint8(1) << player.getID() << player.getPosition().x / window.getSize().x << player.getPosition().y / window.getSize().y << player.getRotation();
					socket.send(packet);
					packet.clear();
					mutex.unlock();
					sendPosTime.restart();
				}
				//--------------------------------------------------------------------------------------------
				//Update

				animation();
			}
			//------------------------------------------------------------------------
			//Draw
			draw();

		}
		theme.stop();
		netThread.terminate();
		sight.setColor(Color::Red);
		socket.disconnect();
	}
	return score;
}

void Game::update()
{
	player.setRotation(Mouse::getPosition(window));
	player.move(window.getSize().x, window.getSize().y);

	if (floor.isColliding(player.getPosition()))
		player.restorePosition();
	mutex.lock();
	for (size_t i = 0; i < player.getBulletsCount();)
	{
		if (floor.isColliding(player.getBulletPosition(i)))
		{
			player.setDead(i);
		}
		else
			for (map<int, Enemy*>::iterator j = enemies.begin(); j != enemies.end(); j++)
			{
				if (j->second->getGlobalBounds().intersects(player.getBulletGlobalBounds(i)))
				{
					player.setDead(i);
					score += 50;
				}
			}

		if (player.moveBullet(i, window.getSize().x, window.getSize().y))
		{
			i++;
		}
		else
		{
			explosions.push_back(new Explosion(player.getBulletPosition(i), player.getBulletAngle(i), explosionTexture, window.getSize().x, window.getSize().y, player.getColor()));
			player.killBullet(i);
		}
	}
	for (map<int, Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		for (size_t j = 0; j < i->second->getBulletsCount();)
		{
			if (floor.isColliding(i->second->getBulletPosition(j)))
			{
				i->second->setDead(j);
			}
			else if (player.getGlobalBounds().intersects(i->second->getBulletGlobalBounds(j)))
			{
				i->second->setDead(j);
				score -= 10;
			}
			for (map<int, Enemy*>::iterator k = enemies.begin(); k != enemies.end(); k++)
			{
				if (k != i)
				{
					if (k->second->getGlobalBounds().intersects(i->second->getBulletGlobalBounds(j)))
						i->second->setDead(j);
				}
			}

			if (i->second->moveBullet(j, window.getSize().x, window.getSize().y))
			{
				j++;
			}
			else
			{
				explosions.push_back(new Explosion(i->second->getBulletPosition(j), i->second->getBulletAngle(j), explosionTexture, window.getSize().x, window.getSize().y, i->second->getColor()));
				i->second->killBullet(j);
			}
		}
		
	}
	mutex.unlock();
	
	sight.setPosition(Vector2f(Mouse::getPosition(window)));
}

void Game::animation()
{
	if (frameTime.getElapsedTime().asSeconds() > 0.2)
	{
		player.animation();
		mutex.lock();
		for (map<int, Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
		{
			i->second->animation();
		}
		mutex.unlock();
		frameTime.restart();
	}
	if (explosionTime.getElapsedTime().asSeconds() > 0.1)
	{
		for (size_t i = 0; i < explosions.size();)
		{
			if (explosions[i]->animation())
			{
				i++;
			}
			else
			{
				std::swap(explosions[i], explosions.back());
				delete explosions[explosions.size() - 1];
				explosions.pop_back();
			}
		}
		explosionTime.restart();
	}
}

void Game::draw()
{
	window.clear(Color::Color(10, 0, 15, 255));
	window.draw(floor);
	player.drawBullets(window);
	mutex.lock();
	for (map<int, Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		i->second->drawBullets(window);
		window.draw(* i->second);
	}
	window.draw(player);
	mutex.unlock();
	for (size_t i = 0; i < explosions.size(); i++)
		window.draw(*explosions[i]);
	window.draw(sight);
	window.display();
}