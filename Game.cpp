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
	m_Players	 = new Player*[2];
	m_Players[0] = new Player("Sorceress");
	m_Players[1] = new Player("Wizard");

	try {
		ReadDeck(wizFile, m_Players[W]);
		ReadDeck(sorFile, m_Players[S]);
	}
	catch (exception &e)
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
void Game::ReadDeck(string file, Player *player)
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
			
			player->AddCardToDeck(CreateCard(cardType, values));

			cout << "Read " << name << " (" << values.size() << " values)" << endl;
		}
	}
	else
	{
		throw exception("Invalid deck file");
	}
}

CardPtr Game::CreateCard(int type, vector<int> values)
{
	switch (type)
	{
		case 1:  return make_shared<BasicMinionCard>();
		case 2:  return make_shared<FireballSpell>();
		case 3:  return make_shared<LightningSpell>();
		case 4:  return make_shared<BlessSpell>();
		case 5:  return make_shared<VampireMinionCard>();
		case 6:  return make_shared<WallMinionCard>();
		case 7:  return make_shared<HordeMinionCard>();
		case 8:  return make_shared<TrampleMinionCard>();
		case 9:  return make_shared<LeechMinionCard>();
		case 10: return make_shared<SwordEquip>();
		case 11: return make_shared<ArmourEquip>();
	}

	throw exception("Invalid card type");

	return nullptr;
}

/*
	Free memory
*/
Game::~Game() {
	delete[] m_Players;
}