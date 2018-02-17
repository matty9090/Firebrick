#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include "Player.hpp"

class Card;

// Create type for ease of use
typedef std::shared_ptr<Card> CardPtr;

/*
	General class card
*/

class Card
{
	public:
		Card(std::string type) : m_CardType(type) {}
		 
		virtual std::string OnPlay(std::shared_ptr<Player> self, std::shared_ptr<Player> opp) { return ""; } // TODO: Make pure
		virtual std::string OnActivate(std::shared_ptr<Player> self, std::shared_ptr<Player> opp) { return ""; }

		std::string GetType() { return m_CardType; }

	protected:
		std::string m_CardType;
};

/*
	The 3 types of card
*/

class MinionCard : public Card, public Living
{
	public:
		MinionCard(std::string type, int att, int health) : Card(type), Living(type, health), m_Attack(att) {}

		void TakeDamage(int damage) { m_Health -= damage; }

		std::string OnPlay(std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			std::ostringstream out;

			CardPtr card = nullptr;

			if (opp->GetTable().size() > 0 && m_Attack > 0) {
				card = opp->GetTable()[Random(opp->GetTable().size())];

				std::shared_ptr<Living> c;

				if (card == nullptr)
					c = std::dynamic_pointer_cast<Living>(opp);
				else if (!std::dynamic_pointer_cast<Living>(card))
					return "";
				else
					c = std::dynamic_pointer_cast<Living>(card);

				c->TakeDamage(m_Attack);

				out << GetType() << " attacks " << c->GetName() << ": " << c->GetName();

				if (c->GetHealth() <= 0)
				{
					out << " is killed";

					if (card != nullptr)
						opp->RemoveCardFromTable(card);
				}
				else
					out << " health now " << c->GetHealth();

				out << "\n";
			}

			return out.str();
		}

	protected:
		int m_Attack;
};

class SpellCard : public Card
{
	public:
		SpellCard(std::string type) : Card(type) {}

		std::string OnActivate(std::shared_ptr<Player> self, std::shared_ptr<Player> opp) {
			// TODO
			
			return "";
		}
};

class EquipmentCard : public Card
{
	public:
		EquipmentCard(std::string type) : Card(type) {}
};