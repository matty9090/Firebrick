#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include "Player.hpp"

class Card;
class MinionCard;

// Create type for ease of use
typedef std::shared_ptr<Card> CardPtr;

/*
	General class card
*/

class Card
{
	public:
		Card(std::string type) : m_CardType(type) {}
		 
		virtual std::string OnPlay(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp) { return ""; } // TODO: Make pure
		virtual std::string OnActivate(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp) { return ""; }

		std::string GetType() { return m_CardType; }

	protected:
		std::string m_CardType;
		int m_Excess;
		
		std::string Attack(CardPtr att, std::shared_ptr<Living> opp, std::shared_ptr<Player> player, int damage, CardPtr remove = nullptr)
		{
			std::ostringstream out;

			m_Excess = damage - opp->GetHealth();
			opp->TakeDamage(damage);

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

		std::string Heal(CardPtr att, std::shared_ptr<Living> opp, std::shared_ptr<Player> player, int heal, CardPtr remove = nullptr)
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

class MinionCard : public Card, public Living
{
	public:
		MinionCard(std::string type, int att, int health) : Card(type), Living(type, health), m_Attack(att) {}

		void TakeDamage(int damage) { m_Health -= damage; }

		std::string OnPlay(CardPtr curCard, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			std::ostringstream out;

			CardPtr card = opp->GetEnemy();

			if (m_Attack > 0) {
				std::shared_ptr<Living> c;

				if (card == nullptr)
					c = std::dynamic_pointer_cast<Living>(opp);
				else if (!std::dynamic_pointer_cast<Living>(card))
					return "";
				else
					c = std::dynamic_pointer_cast<Living>(card);

				out << Attack(curCard, c, opp, m_Attack, card);
			}

			return out.str();
		}

	protected:
		int m_Attack;
};

class SpellCard : public Card
{
	public:
		SpellCard(std::string type, int att, int heal = 0) : Card(type), m_Attack(att), m_Heal(heal) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			self->RemoveCardFromTable(card);
			
			return "";
		}

	protected:
		int m_Attack, m_Heal;
};

class EquipmentCard : public Card
{
	public:
		EquipmentCard(std::string type) : Card(type) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			self->RemoveCardFromTable(card);

			return "";
		}
};