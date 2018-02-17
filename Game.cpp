#include "Game.hpp"
#include "BasicMinionCards.hpp"
#include "EquipCards.hpp"
#include "SpellCards.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>


using namespace std;

/*
	Initialise game data
*/
Game::Game(std::string wizFile, std::string sorFile) : m_Round(1), ended(false)
{
	m_Players	 = new shared_ptr<Player>[2];
	m_Players[0] = make_shared<Player>("Sorceress", m_kMaxHealth);
	m_Players[1] = make_shared<Player>("Wizard", m_kMaxHealth);

	m_MinionCards["Orc"]          = 0;
	m_MinionCards["Goblin"]       = 1;
	m_MinionCards["Pooka"]        = 2;
	m_MinionCards["Thorns"]       = 3;
	m_MinionCards["Giant"]        = 4;
	m_MinionCards["Dwarf"]        = 5;
	m_MinionCards["Cannon"]       = 6;
	m_MinionCards["Swordswinger"] = 7;
	m_MinionCards["Spearcarrier"] = 8;
	m_MinionCards["Elf"]          = 9;

	try
	{
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

	while (!ended && m_Round <= m_kMaxRounds)
	{
		cout << "\nRound " << m_Round << "\n";

		Play(S);
		if(!ended) Play(W);

		m_Round++;

		if (m_Round > m_kMaxRounds)
			cout << "Game ended\n";
	}

	int n;
	cin >> n;
}

/*
	Each players turn
*/
void Game::Play(EPlayers player) {
	string playerStr = (player == S) ? "Sorceress" : "Wizard";
	EPlayers oPlayer = (player == S) ? W : S;

	/* Draw and play cards */

	CardPtr drawn = m_Players[player]->DrawCard();

	cout << playerStr << " draws " << drawn->GetType() << "\n";
	
	auto card = m_Players[player]->PlayCard();
	cout << playerStr << " plays " << card->GetType() << "\n";

	auto cTable = m_Players[player]->GetTable();
	auto oTable = m_Players[oPlayer]->GetTable();

	/* Activate spells */

	for (auto card : cTable)
		cout << card->OnActivate(card, m_Players[player], m_Players[oPlayer]);

	cout << "Cards on table: " << OutputTable(cTable);

	/* Minions on table attack other players minions */

	for (auto card : cTable)
		cout << card->OnPlay(card, m_Players[player], m_Players[oPlayer]);

	cout << "\n";

	/* Checks for end game */

	if (m_Players[player]->GetDeck().empty())
	{
		ended = true;
		cout << "Game has ended, no more cards on the deck\n";
		return;
	}

	if (m_Players[S]->GetHealth() < 0 || m_Players[W]->GetHealth() < 0)
	{
		ended = true;
		cout << (m_Players[S]->GetHealth() < 0) ? "Sorceress was killed\n" : "Wizard was killed\n";
		return;
	}
}

/*
	Read the deck from a file
*/
void Game::ReadDeck(string file, std::shared_ptr<Player> player)
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
	ostringstream str;

	for (auto card : table)
	{
		if(dynamic_pointer_cast<MinionCard>(card))
			str << card->GetType() << "(" << dynamic_pointer_cast<MinionCard>(card)->GetHealth() << ") ";
	}

	str << "\n";

	return str.str();
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
		case 7:  return make_shared<HordeMinionCard>   (name,    1, v[0], v[1]);
		case 8:  return make_shared<TrampleMinionCard> (name, v[0], v[1]);
		case 9:  return make_shared<LeechMinionCard>   (name, v[0], v[1],    2);
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