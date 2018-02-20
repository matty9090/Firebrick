#include "Player.hpp"
#include "Util.hpp"
#include "Cards.hpp"

using namespace std;

Player::Player(std::string name, int maxHealth) : Living(name, maxHealth)
{

}

void Player::AddCardToDeck(CardPtr card)
{
	m_Deck.push(card);
}

void Player::RemoveCardFromTable(CardPtr card)
{
	for (size_t i = 0; i < m_Table.size(); ++i)
	{
		if (card == m_Table[i])
			m_Table.erase(m_Table.begin() + i);
	}
}

CardPtr Player::DrawCard()
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

CardPtr Player::PlayCard()
{
	int n = Random(m_Hand.size());
	CardPtr card = m_Hand[n];

	m_Hand.erase(m_Hand.begin() + n);
	m_Table.push_back(card);

	return card;
}

CardPtr Player::GetEnemy()
{
	for (auto c : m_Table)
		if (c->GetType() == "Wall")
			return c;

	return (m_Table.size() > 0) ? m_Table[Random(m_Table.size())] : nullptr;
}
