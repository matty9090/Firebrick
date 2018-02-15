#pragma once

#include <memory>
#include <string>

/*
	General class card
*/

class Card
{
	public:
		Card(std::string type) : m_CardType(type) {}

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
		MinionCard(std::string type) : Card(type) {}
};

class SpellCard : public Card
{
	public:
		SpellCard(std::string type) : Card(type) {}
};

class EquipmentCard : public Card
{
	public:
		EquipmentCard(std::string type) : Card(type) {}
};