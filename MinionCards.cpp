#include "MinionCards.hpp"

/*
	Vampire minion increases it's health when it attacks
*/
std::string CVampireMinionCard::OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;
	std::string res = CMinionCard::OnPlay(card, self, opp);
	out << res;

	// If it had something to attack, increase health
	if (res != "")
		m_Health += m_Heal;

	return out.str();
}

/*
	Horde minion increases it's attack for each other horde on the table
*/
std::string CHordeMinionCard::OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	int extra = 0;

	// Total up other horde minions (excluding itself)
	for (CardPtr c : self->GetTable())
		if (c->GetType() == GetType() && c != card)
			extra += m_AttIncrement;

	// Add extra attack
	m_Attack = m_InitialAtt + extra;

	return CMinionCard::OnPlay(card, self, opp);
}

/*
	For every kill, use excess damage on new target
*/
std::string CTrampleMinionCard::OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;
	m_Attack = m_InitialAtt; // Reset attack value

	// Set attack value to excess on every kill, keep looping until no kills / no excess damage left
	do
	{
		out << CMinionCard::OnPlay(card, self, opp);
		m_Attack = m_Excess;
	} while (m_Excess > 0);

	return out.str();
}

/*
	Leech heals player for every attack on an enemy
*/
std::string CLeechMinionCard::OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;
	std::string res = CMinionCard::OnPlay(card, self, opp);
	out << res;

	// If it attacked, heal player
	if (res != "")
	{
		self->TakeDamage(-m_Heal);
		out << "Leech heals " << self->GetName() << ": " << self->GetName() << " health now " << self->GetHealth();
	}

	return out.str();
}