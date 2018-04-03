#pragma once

#include "Cards.hpp"

/*
	Equipment Cards
*/

class CSwordEquip : public CEquipmentCard
{
	public:
		CSwordEquip(std::string type, int attIncrement) : CEquipmentCard(type), m_AttIncrement(attIncrement) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			std::ostringstream out;
			CEquipmentCard::OnActivate(card, self, opp);
			std::vector<std::shared_ptr<CMinionCard>> cards;

			for (auto c : self->GetTable())
				if (std::dynamic_pointer_cast<CMinionCard>(c))
					cards.push_back(std::dynamic_pointer_cast<CMinionCard>(c));

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

class CArmourEquip : public CEquipmentCard
{
	public:
		CArmourEquip(std::string type, int protection) : CEquipmentCard(type), m_Protection(protection) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			std::ostringstream out;
			CEquipmentCard::OnActivate(card, self, opp);
			std::vector<std::shared_ptr<CMinionCard>> cards;

			for (auto c : self->GetTable())
				if (std::dynamic_pointer_cast<CMinionCard>(c))
					cards.push_back(std::dynamic_pointer_cast<CMinionCard>(c));

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