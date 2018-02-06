#include "Game.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <vector>

using namespace std;

/*
	Initialise game data
*/
Game::Game(std::string wizFile, std::string sorFile)
{
	players = new Player*[2];

	players[0] = new Player("Sorceress");
	players[1] = new Player("Wizard");

	try {
		ReadDeck(wizFile, players[W]);
		ReadDeck(sorFile, players[S]);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
		exit(0);
	}
}

/*
	Game loop
*/
void Game::Run()
{
	while (true)
	{
		int num;
		cin >> num;
	}
}

/*
	Read the deck from a file
*/
void Game::ReadDeck(string file, Player * player)
{
	ifstream f(file);

	if (f.is_open())
	{
		std::string line;

		while (getline(f, line))
		{
			istringstream stream(line);
			string name;
			int cardType;
			vector<int> values;

			stream >> cardType >> name;

			while (!stream.eof())
			{
				int v;
				stream >> v;
				values.push_back(v);
			}
			
			cout << "Read " << name << " (" << values.size() << " values)" << endl;
		}
	}
	else
	{
		throw exception("Invalid deck file");
	}
}

/*
	Free memory
*/
Game::~Game() {
	delete[] players;
}