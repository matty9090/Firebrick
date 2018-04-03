#include "Game.hpp"
#include "EquipCards.hpp"
#include "SpellCards.hpp"
#include "MinionCards.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>


using namespace std;

/*
	Initialise game data
*/
CGame::CGame(std::string wizFile, std::string sorFile) : m_Round(1), ended(false)
{
	m_Players	 = new shared_ptr<CPlayer>[2];
	m_Players[0] = make_shared<CPlayer>("Sorceress", m_kMaxHealth);
	m_Players[1] = make_shared<CPlayer>("Wizard", m_kMaxHealth);

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
void CGame::Run()
{
	cout << "Do you want to shuffle the deck? (y/n) ";
	char c = getchar();

	if (c == 'y') {
		m_Players[S]->ShuffleDeck();
		m_Players[W]->ShuffleDeck();

		cout << "Decks shuffled\n";
	}

	cout << "\n";

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
void CGame::Play(EPlayers player) {
	string playerStr = (player == S) ? "Sorceress" : "Wizard";
	EPlayers oPlayer = (player == S) ? W : S;

	/* Draw and play cards */

	CardPtr drawn = m_Players[player]->DrawCard();

	cout << playerStr << " draws " << drawn->GetType() << "\n";
	
	auto card = m_Players[player]->PlayCard();
	
	cout << playerStr << " plays " << card->GetType() << "\n";

	/* Activate spells */

	for (auto card : m_Players[player]->GetTable())
		cout << card->OnActivate(card, m_Players[player], m_Players[oPlayer]);

	cout << "Cards on table: " << OutputTable(m_Players[player]->GetTable());

	/* Minions on table attack other players minions */

	for (auto card : m_Players[player]->GetTable())
	{
		cout << card->OnPlay(card, m_Players[player], m_Players[oPlayer]);

		if (m_Players[oPlayer]->GetHealth() <= 0)
			break;
	}

	cout << "\n";

	/* Checks for end game */

	if (m_Players[player]->GetDeck().empty())
	{
		ended = true;
		cout << "Game has ended, no more cards on the deck\n";
		return;
	}

	if (m_Players[S]->GetHealth() <= 0 || m_Players[W]->GetHealth() <= 0)
	{
		ended = true;
		cout << ((m_Players[S]->GetHealth() <= 0) ? "Sorceress was killed\n" : "Wizard was killed\n");
		return;
	}
}

/*
	Read the deck from a file
*/
void CGame::ReadDeck(string file, std::shared_ptr<CPlayer> player)
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

/*
	Output a player's table to the console with health values
*/
string CGame::OutputTable(std::vector<CardPtr> table)
{
	ostringstream str;

	if (table.size() > 0)
	{
		for (auto card : table)
		{
			if (dynamic_pointer_cast<CMinionCard>(card)) // Check the card is a minion card
				str << card->GetType() << "(" << dynamic_pointer_cast<CMinionCard>(card)->GetHealth() << ") ";
		}
	}
	else
		str << "None";

	str << "\n";

	return str.str();
}

/*
	Factory function to create correct class instance from an integer card type
*/
CardPtr CGame::CreateCard(int type, string name, vector<int> v)
{
	switch (type)
	{
		case 1:  return make_shared<CBasicMinionCard>   (name, v[0], v[1]);
		case 2:  return make_shared<CFireballSpell>     (name, v[0]);
		case 3:  return make_shared<CLightningSpell>    (name, v[0]);
		case 4:  return make_shared<CBlessSpell>        (name, v[0], v[1]);
		case 5:  return make_shared<CVampireMinionCard> (name, v[0], v[1], v[2]);
		case 6:  return make_shared<CWallMinionCard>    (name, v[0], v[1]);
		case 7:  return make_shared<CHordeMinionCard>   (name, v[0], v[1],    1);
		case 8:  return make_shared<CTrampleMinionCard> (name, v[0], v[1]);
		case 9:  return make_shared<CLeechMinionCard>   (name, v[0], v[1],    2);
		case 10: return make_shared<CSwordEquip>        (name, v[0]);
		case 11: return make_shared<CArmourEquip>       (name, v[0]);
	}

	throw exception("Invalid card type");

	return nullptr;
}

/*
	Free memory
*/
CGame::~CGame() {
	delete[] m_Players;
}