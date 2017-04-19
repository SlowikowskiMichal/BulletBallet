#include "Game.h"
#include <iostream>

Game::Game(RenderWindow &win, Sprite mouse) : window(win), sight(mouse), player(window.getSize().x, window.getSize().y), floor(window.getSize().x, window.getSize().y)
{
	if (!theme.openFromFile("files/music/game.ogg"))
	{
		cout << "ere" << endl;
	}
	theme.setLoop(true);

}

Game::~Game()
{

}

void Game::start()
{
	theme.play();
	Clock clock;
	int counter = 0;

	bool stay = true;

	while (stay)
	{
		//-----------------------------------------------------------------------------------
		//Input
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
			player.shoot(Mouse::getPosition(window));
		}

		//------------------------------------------------------------------------------------------
		//Set Objects Positions
		update();

		//--------------------------------------------------------------------------------------------
		//Update

		animation();

		//------------------------------------------------------------------------
		//Draw
		draw();

		//FPScounter-------------------------------------------------------------------------------------
		if (clock.getElapsedTime().asSeconds() > 1)
		{
			cout << counter << endl;
			counter = 0;
			clock.restart();
		}
		else
			counter++;
		
	}
	theme.stop();
}

void Game::update()
{
	player.setRotation(Mouse::getPosition(window));
	player.move(window.getSize().x, window.getSize().y);

	if (floor.isColliding(player.getPosition()))
		player.restorePosition();

	for (size_t i = 0; i < player.getBulletsCount();)
	{
		if (floor.isColliding(player.getBulletPosition(i)))
		{
			player.killBullet(i);
		}
		if (player.moveBullet(i, window.getSize().x, window.getSize().y))
			i++;
	}


	sight.setPosition(Vector2f(Mouse::getPosition(window)));


}

void Game::animation()
{
	if (frameTime.getElapsedTime().asSeconds() > 0.2)
	{
		player.animation();
		frameTime.restart();
	}
}

void Game::draw()
{
	window.clear(Color::Color(10, 0, 15, 255));
	window.draw(floor);
	player.drawBullets(window);
	window.draw(player);
	window.draw(sight);
	window.display();
}