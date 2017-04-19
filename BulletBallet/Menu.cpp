#include "Menu.h"
#include <iostream>

Menu::Menu() : window(VideoMode(800, 600), "Gra", Style::None)
{
	state = END;
	font = new Font[3];
	if (!font[0].loadFromFile("files/font/t1.ttf"))
	{
		delete[]font;
		window.close();
		exit(-1);
	}
	if (!font[1].loadFromFile("files/font/n1.ttf"))
	{
		delete[]font;
		window.close();
		exit(-2);
	}
	if (!font[2].loadFromFile("files/font/n2.ttf"))
	{
		delete[]font;
		window.close();
		exit(-3);
	}

	if (!texture.loadFromFile("files/textures/sight.png"))
	{

	}

	if (!theme.openFromFile("files/music/menu.ogg"))
	{
		cout << "ere" << endl;
	}
	theme.setLoop(true);

	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 8, 8));
	sprite.setPosition(Vector2f(Mouse::getPosition(window)));
	sprite.setOrigin(4, 4);
	sprite.setColor(Color::Green);
	sprite.setScale(static_cast<float>(window.getSize().x) / 400, static_cast<float>(window.getSize().x) / 400);
	sprite.setColor(Color::Red);
	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);
	
	state = MENU;
}

Menu::~Menu()
{
	delete[]font;
}

void Menu::start()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			print();
			break;
		case GameState::GAME:
			play();
			break;
		}
	}

	window.close();
}

void Menu::play()
{
	Game game(window, sprite);
	game.start();
	state = MENU;
}

void Menu::print()
{
	theme.play();

//	Clock starsTime;
	
	Stars stars(window.getSize().x, window.getSize().y);

	Text tytul[2] = { Text("BULLET",font[0], window.getSize().x/8),Text("BALLET", font[0], window.getSize().x / 8.8) };
	Text opcje[2] = { Text("PLAY",font[1], window.getSize().x / 16),Text(L"EXIT", font[1], window.getSize().x / 16) };

	for (int i = 0; i < 2; i++)
	{
		tytul[i].setOrigin(tytul[i].getGlobalBounds().width/2, tytul[i].getGlobalBounds().height/2);
		tytul[i].setPosition(window.getSize().x / 2, window.getSize().y / 20 + i * window.getSize().y / 8);
		tytul[i].setOutlineThickness(window.getSize().y/200);
		tytul[i].setOutlineColor(Color(75, 0, 130, 255));
		tytul[i].setFillColor(Color(255,255,255, 220));
	}


	for (int i = 0; i < 2; i++)
	{
		opcje[i].setPosition(window.getSize().x / 2 - opcje[i].getGlobalBounds().width / 2, window.getSize().y / 2 + i * window.getSize().y / 10);
		opcje[i].setOutlineColor(Color(253, 25, 153, 255));
		opcje[i].setFillColor(Color(255, 255, 255, 175));
	}


	while (state == MENU)
	{

		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				state = END;

			else if (opcje[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = END;

			else if (opcje[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = GAME;
		}

		for (int i = 0; i < 2; i++)
			if (opcje[i].getGlobalBounds().contains(mouse))
			{
				opcje[i].setFont(font[2]);
				opcje[i].setFillColor(Color::White);
			}
			else
			{
				opcje[i].setFillColor(Color::Color(255, 255, 255, 175));
				opcje[i].setFont(font[1]);
			}

		stars.update();

		sprite.setPosition(Vector2f(Mouse::getPosition(window)));

		window.clear(Color::Color(10, 0, 15, 255));
		window.draw(stars);
		for (int i = 0; i < 2; i++)
		{
			window.draw(tytul[i]);
			window.draw(opcje[i]);
		}
		window.draw(sprite);

		window.display();

	}
	theme.stop();
}