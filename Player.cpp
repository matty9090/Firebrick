#include "Player.hpp"
#include "Util.hpp"
#include "Cards.hpp"

using namespace std;

/*
	Constructor which calls Living class to initialise members
*/
CPlayer::CPlayer(std::string name, int maxHealth) : CLiving(name, maxHealth)
{

}

/*
	Add card to deck (used when loading in cards from file)
*/
void CPlayer::AddCardToDeck(CardPtr card)
{
	m_Deck.push(card);
}

/*
	Remove a card from the players table. e.g. When a minion dies
*/
void CPlayer::RemoveCardFromTable(CardPtr card)
{
	for (size_t i = 0; i < m_Table.size(); ++i)
	{
		if (card == m_Table[i])
			m_Table.erase(m_Table.begin() + i);
	}
}

/*
	Draw a card off the top of the deck
*/
CardPtr CPlayer::DrawCard()
{
	CardPtr card = nullptr;

	if (m_Deck.size() > 0)
	{
		card = m_Deck.front();
		m_Hand.push_back(card);
		m_Deck.pop();
	}

	return card;
}

/*
	Play a random card from hand onto the table
*/
CardPtr CPlayer::PlayCard()
{
	int n = Random(m_Hand.size());
	CardPtr card = m_Hand[n];

	m_Hand.erase(m_Hand.begin() + n);
	m_Table.push_back(card);

	return card;
}

/*
	Get a random enemy from players table to attack (always attacks wall first)
*/
CardPtr CPlayer::GetEnemy()
{
	for (auto c : m_Table)
		if (c->GetType() == "Wall")
			return c;

	return (m_Table.size() > 0) ? m_Table[Random(m_Table.size())] : nullptr;
}
