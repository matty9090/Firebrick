#pragma once

#include <memory>
#include <string>
#include <sstream>

/*
	General class card
*/

class Card
{
	public:
		Card(std::string type) : m_CardType(type) {}
		 
		virtual void Play() {}
		virtual std::string GetHealthStr() = 0;

		std::string GetType() { return m_CardType; }

	protected:
		std::string m_CardType;
};

// Create type for ease of use
typedef std::shared_ptr<Card> CardPtr;

/*
	The 3 types of card
*/

class MinionCard : public Card
{
	public:
		MinionCard(std::string type, int att, int health) : Card(type), m_Attack(att), m_Health(health) {}

		std::string GetHealthStr() {
			std::ostringstream str;
			str << "(" << m_Health << ")";
			return str.str();
		}

	protected:
		int m_Attack, m_Health;
};

class SpellCard : public Card
{
	public:
		SpellCard(std::string type) : Card(type) {}

		std::string GetHealthStr() { return ""; }
};

class EquipmentCard : public Card
{
	public:
		EquipmentCard(std::string type) : Card(type) {}

		std::string GetHealthStr() { return ""; }
};