#pragma once

#include "Cards.hpp"

/*
	Spell cards
*/

class FireballSpell : public SpellCard {
	public:
		FireballSpell(int type) : SpellCard(2) {}
};

class LightningSpell : public SpellCard {
	public:
		LightningSpell(int type) : SpellCard(3) {}
};

class BlessSpell : public SpellCard {
	public:
		BlessSpell(int type) : SpellCard(4) {}
};