#include "Cards.hpp"

std::string CCard::Attack(CardPtr att, std::shared_ptr<CLiving> opp, std::shared_ptr<CPlayer> player, int damage, CardPtr remove)
{
	std::ostringstream out;

	damage -= opp->GetProtection();

	m_Excess = damage - opp->GetHealth();
	opp->TakeDamage(damage);

	if (opp->GetHealth() < 0)
		m_Excess = 0;

	out << att->GetType() << " attacks " << opp->GetName() << ": " << opp->GetName();

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

std::string CCard::Heal(CardPtr att, std::shared_ptr<CLiving> opp, std::shared_ptr<CPlayer> player, int heal, CardPtr remove)
{
	std::ostringstream out;

	opp->TakeDamage(-heal);
	out << att->GetType() << " heals " << opp->GetName() << ": " << opp->GetName() << " health now " << opp->GetHealth() << "\n";

	return out.str();
}

std::string CMinionCard::OnPlay(CardPtr curCard, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;

	CardPtr card = opp->GetEnemy();

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

std::string CSpellCard::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	self->RemoveCardFromTable(card);

	return "";
}

std::string CEquipmentCard::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	self->RemoveCardFromTable(card);

	return "";
}