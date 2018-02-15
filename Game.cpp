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

	m_MinionCards["Orc"] = 0;

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
	m_Players[S]->DrawCard(), m_Players[W]->DrawCard();

	cout << "Sorceress begins with " << m_Players[S]->PlayCard()->GetType() << "\n";
	cout << "Wizard begins with "    << m_Players[W]->PlayCard()->GetType() << "\n";

	while (true)
	{
		m_Players[S]->DrawCard(), m_Players[W]->DrawCard();

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
			
			player->AddCardToDeck(CreateCard(cardType, name, values));

#ifdef _DEBUG
			cout << "Read " << name << " (" << values.size() << " values)" << endl;
#endif // DEBUG
		}
	}
	else
	{
		throw exception("Invalid deck file");
	}
}

CardPtr Game::CreateCard(int type, string name, vector<int> values)
{
	switch (type)
	{
		case 1:
			switch (m_MinionCards[name]) {
				case 0: return make_shared<OrcBasicMinion>(name);
				case 1: return make_shared<GoblinBasicMinion>(name);
				case 2: return make_shared<PookaBasicMinion>(name);
				case 3: return make_shared<ThornsBasicMinion>(name);
				case 4: return make_shared<GiantBasicMinion>(name);
				case 5: return make_shared<DwarfBasicMinion>(name);
				case 6: return make_shared<CannonBasicMinion>(name);
				case 7: return make_shared<SwordswingerBasicMinion>(name);
				case 8: return make_shared<SpearcarrierBasicMinion>(name);
				case 9: return make_shared<ElfBasicMinion>(name);
			}

		case 2:  return make_shared<FireballSpell>(name);
		case 3:  return make_shared<LightningSpell>(name);
		case 4:  return make_shared<BlessSpell>(name);
		case 5:  return make_shared<VampireMinionCard>(name);
		case 6:  return make_shared<WallMinionCard>(name);
		case 7:  return make_shared<HordeMinionCard>(name);
		case 8:  return make_shared<TrampleMinionCard>(name);
		case 9:  return make_shared<LeechMinionCard>(name);
		case 10: return make_shared<SwordEquip>(name);
		case 11: return make_shared<ArmourEquip>(name);
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