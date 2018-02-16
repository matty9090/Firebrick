#include "Game.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>

using namespace std;

/*
	Initialise game data
*/
Game::Game(std::string wizFile, std::string sorFile) : m_Round(1)
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
	cout << "Sorceress begins with " << m_Players[S]->DrawCard()->GetType() << "\n";
	cout << "Wizard begins with "    << m_Players[W]->DrawCard()->GetType() << "\n";

	while (true)
	{
		cout << "\nRound " << m_Round << "\n";

		Play(S);
		Play(W);

		int num;
		cin >> num;

		m_Round++;
	}
}

/*
	Each players turn
*/
void Game::Play(EPlayers player) {
	string playerStr = (player == S) ? "Sorceress" : "Wizard";

	/* Draw and play cards */
	cout << playerStr << " draws " << m_Players[player]->DrawCard()->GetType() << "\n";
	
	CardPtr card = m_Players[player]->PlayCard();
	cout << playerStr << " plays " << card->GetType() << "\n";

	cout << "Cards on table: " << OutputTable(m_Players[player]->GetTable());

	/* TODO: Cards on table attack other players table */

	cout << "\n";
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

string Game::OutputTable(std::vector<CardPtr> table)
{
	string str = "";

	for (auto card : table)
		str += card->GetType() + card->GetHealthStr() + "\n";

	return str;
}

CardPtr Game::CreateCard(int type, string name, vector<int> v)
{
	switch (type)
	{
		case 1:
			switch (m_MinionCards[name]) {
				case 0: return make_shared<OrcBasicMinion>          (name, v[0], v[1]);
				case 1: return make_shared<GoblinBasicMinion>       (name, v[0], v[1]);
				case 2: return make_shared<PookaBasicMinion>        (name, v[0], v[1]);
				case 3: return make_shared<ThornsBasicMinion>       (name, v[0], v[1]);
				case 4: return make_shared<GiantBasicMinion>        (name, v[0], v[1]);
				case 5: return make_shared<DwarfBasicMinion>        (name, v[0], v[1]);
				case 6: return make_shared<CannonBasicMinion>       (name, v[0], v[1]);
				case 7: return make_shared<SwordswingerBasicMinion> (name, v[0], v[1]);
				case 8: return make_shared<SpearcarrierBasicMinion> (name, v[0], v[1]);
				case 9: return make_shared<ElfBasicMinion>          (name, v[0], v[1]);
			}

		case 2:  return make_shared<FireballSpell>     (name, v[0]);
		case 3:  return make_shared<LightningSpell>    (name, v[0]);
		case 4:  return make_shared<BlessSpell>        (name, v[0], v[1]);
		case 5:  return make_shared<VampireMinionCard> (name, v[0], v[1], v[2]);
		case 6:  return make_shared<WallMinionCard>    (name, v[0], v[1]);
		case 7:  return make_shared<HordeMinionCard>   (name, v[0], v[1], v[2]);
		case 8:  return make_shared<TrampleMinionCard> (name, v[0], v[1]);
		case 9:  return make_shared<LeechMinionCard>   (name, v[0], v[1], v[2]);
		case 10: return make_shared<SwordEquip>        (name, v[0]);
		case 11: return make_shared<ArmourEquip>       (name, v[0]);
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