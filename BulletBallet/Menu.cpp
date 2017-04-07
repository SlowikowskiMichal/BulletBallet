#include "Menu.h"
#include <iostream>

Menu::Menu() : okno(VideoMode(800, 600), "Gra", Style::None)
{
	stan = END;
	font = new Font[3];
	if (!font[0].loadFromFile("files/font/t1.ttf"))
	{
		delete[]font;
		okno.close();
		exit(-1);
	}
	if (!font[1].loadFromFile("files/font/n1.ttf"))
	{
		delete[]font;
		okno.close();
		exit(-2);
	}
	if (!font[2].loadFromFile("files/font/n2.ttf"))
	{
		delete[]font;
		okno.close();
		exit(-3);
	}

	if (!texture.loadFromFile("files/textures/sight.png"))
	{

	}

	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 8, 8));
	sprite.setPosition(Vector2f(Mouse::getPosition(okno)));
	sprite.setOrigin(4, 4);
	sprite.setColor(Color::Green);
	sprite.setScale(2, 2);

	okno.setMouseCursorGrabbed(true);
	okno.setMouseCursorVisible(false);
	stan = MENU;
}

Menu::~Menu()
{
	delete[]font;
}

void Menu::play()
{
	Game game(okno,sprite);
	game.start();
	stan = MENU;
}


void Menu::start()
{
	while (stan != END)
	{
		switch (stan)
		{
		case StanGry::MENU:
			print();
			break;
		case StanGry::GAME:
			play();
			break;
		}
	}

	okno.close();
}

void Menu::print()
{

	Clock clock;
	Clock starsTime;

	int counter = 0;

	Stars stars;

	Text tytul[2] = { Text("BULLET",font[0], 100),Text("BALLET", font[0], 90) };
	Text opcje[2] = { Text("PLAY",font[1], 40),Text(L"EXIT", font[1], 40) };

	for (int i = 0; i < 2; i++)
	{
		tytul[i].setOrigin(tytul[i].getGlobalBounds().width/2, tytul[i].getGlobalBounds().height/2);
		tytul[i].setPosition(okno.getSize().x / 2, 30 + i * 75);
		tytul[i].setOutlineThickness(3);
		tytul[i].setOutlineColor(Color(75, 0, 130, 255));
		tytul[i].setFillColor(Color(255,255,255, 220));
	}


	for (int i = 0; i < 2; i++)
	{
		opcje[i].setPosition(800 / 2 - opcje[i].getGlobalBounds().width / 2, 300 + i * 45);
		opcje[i].setOutlineColor(Color(253, 25, 153, 255));
		opcje[i].setFillColor(Color(255, 255, 255, 175));
	}


	while (stan == MENU)
	{

		Vector2f mouse(Mouse::getPosition(okno));
		Event event;

		while (okno.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				stan = END;

			else if (opcje[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				stan = END;

			else if (opcje[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				stan = GAME;
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


		if (starsTime.getElapsedTime().asSeconds() > 0.016)
		{
			stars.update();
			starsTime.restart();
		}
		sprite.setPosition(Vector2f(Mouse::getPosition(okno)));

		okno.clear(Color::Color(10, 0, 15, 255));
		okno.draw(stars);
		for (int i = 0; i < 2; i++)
		{
			okno.draw(tytul[i]);
			okno.draw(opcje[i]);
		}
		okno.draw(sprite);

		okno.display();

//		if (clock.getElapsedTime().asSeconds() > 1)
//		{
//			cout << counter << endl;
//			counter = 0;
//			clock.restart();
//		}
//		else
//			counter++;

	}

}