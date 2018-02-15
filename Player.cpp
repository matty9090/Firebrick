#include "Player.hpp"
#include "Util.hpp"

Player::Player(std::string name) : m_Name(name), m_Health(m_kMaxHealth)
{
	
}

void Player::TakeDamage(int damage)
{
	m_Health -= damage;
}

void Player::DrawCard()
{
	m_Hand.push_back(m_Deck.top());
	m_Deck.pop();
}

CardPtr Player::PlayCard()
{
	int n = Random(m_Hand.size());
	CardPtr card = m_Hand[n];
	m_Hand.erase(m_Hand.begin() + n);

	return card;
}