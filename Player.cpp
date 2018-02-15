#include "Player.hpp"
#include "Util.hpp"

Player::Player(std::string name) : m_Name(name), m_Health(m_kMaxHealth)
{
	
}

void Player::TakeDamage(int damage)
{
	m_Health -= damage;
}

CardPtr Player::DrawCard()
{
	CardPtr card = m_Deck.front();
	m_Hand.push_back(card);
	m_Deck.pop();

	return card;
}

CardPtr Player::PlayCard()
{
	int n = Random(m_Hand.size());
	CardPtr card = m_Hand[n];
	m_Hand.erase(m_Hand.begin() + n);

	return card;
}