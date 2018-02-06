#pragma once

#include "Cards.hpp"

/*
	Spell cards
*/

class FireballSpell : public SpellCard {
	public:
		FireballSpell() : SpellCard(2) {}
};

class LightningSpell : public SpellCard {
	public:
		LightningSpell() : SpellCard(3) {}
};

class BlessSpell : public SpellCard {
	public:
		BlessSpell() : SpellCard(4) {}
};