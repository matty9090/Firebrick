#include "Cards.hpp"

/*
	Helper function to attack an enemy
*/
std::string CCard::Attack(CardPtr att, std::shared_ptr<CLiving> opp, std::shared_ptr<CPlayer> player, int damage, CardPtr remove)
{
	std::ostringstream out;

	// Reduce damage if the enemy has armour
	damage -= opp->GetProtection();

	// Damage the enemy
	opp->TakeDamage(damage);

	// Set excess damage for minions which have the horde property
	if (opp->GetHealth() < 0)
		m_Excess = abs(opp->GetHealth());
	else
		m_Excess = 0;

	out << att->GetType() << " attacks " << opp->GetName() << ": " << opp->GetName();

	// Check if enemy was killed
	if (opp->GetHealth() <= 0)
	{
		out << " is killed";

		if (remove != nullptr)
			player->RemoveCardFromTable(remove);
	}
	else
		out << " health now " << opp->GetHealth();

	out << "\n";

	return out.str();
}

/*
	Helper function to heal player and output to console
*/
std::string CCard::Heal(CardPtr att, std::shared_ptr<CLiving> opp, std::shared_ptr<CPlayer> player, int heal, CardPtr remove)
{
	std::ostringstream out;

	opp->TakeDamage(-heal);
	out << att->GetType() << " heals " << opp->GetName() << ": " << opp->GetName() << " health now " << opp->GetHealth() << "\n";

	return out.str();
}

/*
	General minion play function
*/
std::string CMinionCard::OnPlay(CardPtr curCard, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;

	// Get a random enemy
	CardPtr card = opp->GetEnemy();

	// Attack the enemy
	if (m_Attack > 0) {
		std::shared_ptr<CLiving> c;

		if (card == nullptr)
			c = std::dynamic_pointer_cast<CLiving>(opp);
		else if (!std::dynamic_pointer_cast<CLiving>(card))
			return "";
		else
			c = std::dynamic_pointer_cast<CLiving>(card);

		out << Attack(curCard, c, opp, m_Attack, card);
	}

	return out.str();
}

/*
	Spell cards remove themselves when used
	This function is called alongside the derived class' special ability
*/
std::string CSpellCard::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	self->RemoveCardFromTable(card);

	return "";
}

/*
	Equipment cards remove themselves when used
	This function is called alongside the derived class' special ability
*/
std::string CEquipmentCard::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	self->RemoveCardFromTable(card);

	return "";
}