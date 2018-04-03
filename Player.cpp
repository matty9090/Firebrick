#include "Player.hpp"
#include "Util.hpp"
#include "Cards.hpp"

using namespace std;

CPlayer::CPlayer(std::string name, int maxHealth) : CLiving(name, maxHealth)
{

}

void CPlayer::AddCardToDeck(CardPtr card)
{
	m_Deck.push(card);
}

void CPlayer::RemoveCardFromTable(CardPtr card)
{
	for (size_t i = 0; i < m_Table.size(); ++i)
	{
		if (card == m_Table[i])
			m_Table.erase(m_Table.begin() + i);
	}
}

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

CardPtr CPlayer::PlayCard()
{
	int n = Random(m_Hand.size());
	CardPtr card = m_Hand[n];

	m_Hand.erase(m_Hand.begin() + n);
	m_Table.push_back(card);

	return card;
}

CardPtr CPlayer::GetEnemy()
{
	for (auto c : m_Table)
		if (c->GetType() == "Wall")
			return c;

	return (m_Table.size() > 0) ? m_Table[Random(m_Table.size())] : nullptr;
}
