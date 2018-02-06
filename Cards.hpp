#pragma once

/*
	General class card
*/

class Card {
	public:
		Card(int type) : m_CardType(type) {}

	protected:
		int m_CardType;
};

/*
	The 3 types of card
*/

class MinionCard : public Card {
	public:
		MinionCard(int type) : Card(type) {}
};

class SpellCard : public Card {
	public:
		SpellCard(int type) : Card(type) {}
};

class EquipmentCard : public Card {
	public:
		EquipmentCard(int type) : Card(type) {}
};