#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include "Player.hpp"

class CCard;
class CMinionCard;

// Create type for ease of use
typedef std::shared_ptr<CCard> CardPtr;

/*
	General class card
*/

class CCard
{
	public:
		CCard(std::string type) : m_CardType(type) {}
		 
		virtual std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp) { return ""; } // TODO: Make pure
		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp) { return ""; }

		std::string GetType() { return m_CardType; }

	protected:
		std::string m_CardType;
		int m_Excess;
		
		std::string Attack(CardPtr att, std::shared_ptr<CLiving> opp, std::shared_ptr<CPlayer> player, int damage, CardPtr remove = nullptr)
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

		std::string Heal(CardPtr att, std::shared_ptr<CLiving> opp, std::shared_ptr<CPlayer> player, int heal, CardPtr remove = nullptr)
		{
			std::ostringstream out;

			opp->TakeDamage(-heal);
			out << att->GetType() << " heals " << opp->GetName() << ": " << opp->GetName() << " health now " << opp->GetHealth() << "\n";

			return out.str();
		}
};

/*
	The 3 types of card
*/

class CMinionCard : public CCard, public CLiving
{
	public:
		CMinionCard(std::string type, int att, int health) : CCard(type), CLiving(type, health), m_Attack(att) {}

		void IncreaseAttack(int att) { m_Attack += att; }
		void TakeDamage(int damage) { m_Health -= damage; }

		std::string OnPlay(CardPtr curCard, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
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

	protected:
		int m_Attack;
};

class CSpellCard : public CCard
{
	public:
		CSpellCard(std::string type, int att, int heal = 0) : CCard(type), m_Attack(att), m_Heal(heal) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			self->RemoveCardFromTable(card);
			
			return "";
		}

	protected:
		int m_Attack, m_Heal;
};

class CEquipmentCard : public CCard
{
	public:
		CEquipmentCard(std::string type) : CCard(type) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			self->RemoveCardFromTable(card);

			return "";
		}
};