#include "EquipCards.hpp"
#include "Util.hpp"

/*
	Increase attack value of a minion / heal player if no minions on table
*/
std::string CSwordEquip::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;
	CEquipmentCard::OnActivate(card, self, opp);
	std::vector<std::shared_ptr<CMinionCard>> cards;

	// Add all minions on table to list
	for (auto c : self->GetTable())
		if (std::dynamic_pointer_cast<CMinionCard>(c))
			cards.push_back(std::dynamic_pointer_cast<CMinionCard>(c));

	// Increase attack of random minion, or heal player
	if (cards.size() > 0)
	{
		int rand = Random(cards.size());
		cards[rand]->IncreaseAttack(m_AttIncrement);
		out << cards[rand]->GetType() << "(" << cards[rand]->GetHealth() << " equipped with " << GetType() << "\n";
	}
	else
		self->TakeDamage(-m_AttIncrement);

	return out.str();
}

/*
	Increase defense of minion
*/
std::string CArmourEquip::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;
	CEquipmentCard::OnActivate(card, self, opp);
	std::vector<std::shared_ptr<CMinionCard>> cards;

	// Add all minions on table to list
	for (auto c : self->GetTable())
		if (std::dynamic_pointer_cast<CMinionCard>(c))
			cards.push_back(std::dynamic_pointer_cast<CMinionCard>(c));

	// Add protection to a random minion if there is one
	if (cards.size() > 0)
	{
		int rand = Random(cards.size());
		cards[rand]->AddArmour(m_Protection);
		out << cards[rand]->GetType() << "(" << cards[rand]->GetHealth() << ") equipped with " << GetType() << "\n";
	}

	return out.str();
}