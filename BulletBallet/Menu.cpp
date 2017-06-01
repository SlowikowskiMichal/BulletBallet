#include "Menu.h"

Menu::Menu() : window(VideoMode(800, 600), "Gra", Style::Titlebar)
{
	state = END;
	font = new Font[3];
	try
	{
		if (!font[0].loadFromFile("files/font/t1.ttf"))
		{
			throw Error(Error::font);
		}
		if (!font[1].loadFromFile("files/font/n1.ttf"))
		{
			throw Error(Error::font);
		}
		if (!font[2].loadFromFile("files/font/n2.ttf"))
		{
			throw Error(Error::font);
		}

		if (!texture.loadFromFile("files/textures/sight.png"))
		{
			throw Error(Error::texture);
		}

		if (!theme.openFromFile("files/music/menu.ogg"))
		{
			throw Error(Error::music);
		}
	}
	catch (Error &error)
	{
		error.err();
	}

	theme.setLoop(true);

	stars = Stars(window.getSize().x, window.getSize().y);

	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 8, 8));
	sprite.setPosition(Vector2f(Mouse::getPosition(window)));
	sprite.setOrigin(4, 4);
	sprite.setColor(Color::Green);
	sprite.setScale(static_cast<float>(window.getSize().x) / 400, static_cast<float>(window.getSize().x) / 400);
	sprite.setColor(Color::Red);

	Image icon;
	if (!icon.loadFromFile("files/ico.png"))
	{
		icon.create(64, 64, Color(10, 0, 15, 255));
	}

	allInpt = "";

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//	window.setMouseCursorGrabbed(true);
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
			if(theme.getStatus() != Music::Playing)
				theme.play();
			mainMenu();
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
	string ip = ipCheck();
	theme.stop();
	if (ip.length())
	{
		Game game(window, sprite,ip,font[0]);
		int score = game.start();
		scoreBoard(score);
	}
	state = MENU;
}

void Menu::mainMenu()
{	
	Text tytul[2] = { Text("BULLET",font[0], window.getSize().x / 8),Text("BALLET", font[0], window.getSize().x / 8.8) };
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
		{
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
		}

		stars.update();

		sprite.setPosition(Vector2f(mouse));

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

}

void Menu::scoreBoard(int score)
{
	stars = Stars(window.getSize().x, window.getSize().y);
	Text title("Score:", font[0], window.getSize().x / 7);
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
	title.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - window.getSize().y / 5.0f);
	title.setOutlineThickness(window.getSize().y / 200);
	title.setOutlineColor(Color(75, 0, 130, 255));
	title.setFillColor(Color(255, 255, 255, 220));

	Text monit(to_string(score), font[0], window.getSize().x / 8);
	monit.setOrigin(monit.getGlobalBounds().width / 2, monit.getGlobalBounds().height / 2);
	monit.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	monit.setOutlineThickness(window.getSize().y / 200);
	monit.setOutlineColor(Color(75, 0, 130, 255));
	monit.setFillColor(Color(255, 255, 255, 220));

	Clock time;
	bool stay = true;
	while (time.getElapsedTime().asSeconds() < 15 && stay)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				stay = false;
		}

		stars.update();

		window.clear(Color::Color(10, 0, 15, 255));
		window.draw(stars);
		window.draw(title);
		window.draw(monit);
		window.display();
	}

}

string Menu::ipCheck()
{

	bool stay = true;
	regex pattern("\\d{1,3}.\\d{1,3}.\\d{1,3}.\\d{1,3}");

	Text monit = Text("Podaj IP:", font[0], window.getSize().x / 8);
	monit.setOrigin(monit.getGlobalBounds().width / 2, monit.getGlobalBounds().height / 2);
	monit.setPosition(window.getSize().x / 2, window.getSize().y / 2 - window.getSize().y / 6);
	monit.setOutlineThickness(window.getSize().y / 200);
	monit.setOutlineColor(Color(75, 0, 130, 255));
	monit.setFillColor(Color(255, 255, 255, 220));


	Text input = Text(allInpt, font[2], window.getSize().x / 16);
	input.setOrigin(input.getGlobalBounds().width / 2, input.getGlobalBounds().height / 2);
	input.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	Text opcje[3] = { Text("OK",font[1], window.getSize().x / 16),Text(L"Get local host IP", font[1], window.getSize().x / 16),Text(L"EXIT", font[1], window.getSize().x / 16) };
	for (int i = 0; i < 3; i++)
	{
		opcje[i].setOrigin(opcje[i].getGlobalBounds().width / 2, opcje[i].getGlobalBounds().height / 2);
		opcje[i].setPosition(window.getSize().x / 2, window.getSize().y / 2 + (i+1) * window.getSize().y / 16 + window.getSize().y / 16);
		opcje[i].setOutlineColor(Color(253, 25, 153, 255));
		opcje[i].setFillColor(Color(255, 255, 255, 175));
	}



	while (stay)
	{
		Event event;
		Vector2f mouse(Mouse::getPosition(window));
		input.setOutlineColor(Color::Red);
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				return "";
			}

			else if (opcje[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				return "";
			}

			else if (opcje[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				return "127.0.0.1";
			}

			else if (opcje[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				smatch match;
				if (regex_match(allInpt, match, pattern))
				{
					stay = false;
				}
				else
					input.setOutlineThickness(window.getSize().x / 400);
			}

			if (event.type == sf::Event::TextEntered)
			{
				if ((event.text.unicode > 47 && event.text.unicode < 58) || event.text.unicode == 46)
				{
					input.setOutlineThickness(0);
					allInpt += static_cast<char>(event.text.unicode);
					input.setString(allInpt);
					input.setOrigin(input.getGlobalBounds().width / 2, input.getGlobalBounds().height / 2);
					input.setPosition(window.getSize().x / 2, window.getSize().y / 2);
				}
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace)
			{
				if (!allInpt.empty())
				{
					input.setOutlineThickness(0);
					allInpt.erase(allInpt.end() - 1);
					input.setString(allInpt);
					input.setOrigin(input.getGlobalBounds().width / 2, input.getGlobalBounds().height / 2);
					input.setPosition(window.getSize().x / 2, window.getSize().y / 2);
				}

			}

		}

		for (int i = 0; i < 3; i++)
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

		sprite.setPosition(Vector2f(mouse));

		window.clear(Color::Color(10, 0, 15, 255));
		window.draw(stars);
		window.draw(monit);
		window.draw(input);
		for (int i = 0; i < 3; i++)
		{
			window.draw(opcje[i]);
		}
		window.draw(sprite);
		window.display();
	}

	return allInpt;
}