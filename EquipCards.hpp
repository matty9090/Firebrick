#pragma once

#include "Cards.hpp"

/*
	Equipment Cards
*/

class SwordEquip : public EquipmentCard
{
	public:
		SwordEquip(std::string type, int attIncrement) : EquipmentCard(type), m_AttIncrement(attIncrement) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			std::ostringstream out;
			EquipmentCard::OnActivate(card, self, opp);
			std::vector<std::shared_ptr<MinionCard>> cards;

			for (auto c : self->GetTable())
				if (std::dynamic_pointer_cast<MinionCard>(c))
					cards.push_back(std::dynamic_pointer_cast<MinionCard>(c));

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

	private:
		int m_AttIncrement;
};

class ArmourEquip : public EquipmentCard
{
	public:
		ArmourEquip(std::string type, int protection) : EquipmentCard(type), m_Protection(protection) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			std::ostringstream out;
			EquipmentCard::OnActivate(card, self, opp);
			std::vector<std::shared_ptr<MinionCard>> cards;

			for (auto c : self->GetTable())
				if (std::dynamic_pointer_cast<MinionCard>(c))
					cards.push_back(std::dynamic_pointer_cast<MinionCard>(c));

			if (cards.size() > 0)
			{
				int rand = Random(cards.size());
				cards[rand]->AddArmour(m_Protection);
				out << cards[rand]->GetType() << "(" << cards[rand]->GetHealth() << ") equipped with " << GetType() << "\n";
			}

			return out.str();
		}

	private:
		int m_Protection;
};