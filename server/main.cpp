#include <iostream>
#include <SFML\Network.hpp>
#include <vector>


using namespace std;
using namespace sf;

void server();

int main()
{
	server();

	return 0;
}

void server()
{
	bool readyForNewGame = true;
	int size;
	int gameTime = 0;
	int id = 0;
	Clock gameClock;

	cout << "Enter the number of players: ";
	cin >> size;
	if (size > 5)
		size = 5;
	else if (size < 1)
		size = 1;

	cout << "Enter time of round: ";
	cin >> gameTime;
	if (gameTime < 0)
		gameTime = -gameTime;
	else if (gameTime == 0 || gameTime > 420)
		gameTime = 60;

	cout << "Serwer" << endl;
	cout << "Public address: " << IpAddress::getPublicAddress() << endl;
	cout << "Local address: " << IpAddress::getLocalAddress() << endl;

	TcpListener listener;
	vector<TcpSocket*> clients;
	clients.reserve(size);
	listener.listen(42081);

	SocketSelector selector;
	Packet packet;
	selector.add(listener);

	while (true)
	{
		if (selector.wait())
		{
			if (selector.isReady(listener) && readyForNewGame) 
			{

				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
					packet << id << size;
					client->send(packet);
					
					clients.push_back(client);
					selector.add(*client);

					id++;
					cout << "Connected" << endl;
					if (clients.size() == size)
					{
						cout << "Start" << endl;
						Packet temp;
						temp << size;
						for (size_t i = 0; i < clients.size(); i++)
							clients[i]->send(temp);
						temp.clear();
						gameClock.restart();
						readyForNewGame = false;
					}
					packet.clear();
				}
				else
				{
					delete client;
				}
			}
			else
			{
				for (size_t i = 0; i < clients.size(); ++i)
				{
					if (selector.isReady(*clients[i]))
					{
						if (clients[i]->receive(packet) == TcpSocket::Disconnected) 
						{
							std::swap(clients[i], clients.back());
							selector.remove(*clients.back());
							clients.pop_back();
							cout << "Disconnected" << endl;
							id--;

							if (clients.size() == 0)
							{
								readyForNewGame = true;
							}
						}
						else
						{
							for (size_t j = 0; j < clients.size(); j++)
							{
								if (clients[i] != clients[j])
								{
									clients[j]->send(packet);
								}
							}
						}
					}
					packet.clear();
				}
				if (gameClock.getElapsedTime().asSeconds() > gameTime)
				{
					packet << Uint8(0);
					for (int i = 0; i < clients.size(); i++)
					{
						clients[i]->send(packet);
						std::swap(clients[i], clients.back());
						selector.remove(*clients.back());
						clients.pop_back();
						cout << "Disconnected" << endl;
						id--;
					}
					packet.clear();
					readyForNewGame = true;
				}
			}
		}
	}

}