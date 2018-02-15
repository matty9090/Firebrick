#pragma once

#include "Cards.hpp"

/*
	Spell cards
*/

class FireballSpell : public SpellCard
{
	public:
		FireballSpell(std::string type, int att) : SpellCard(type) {}

		std::string GetHealthStr() { return ""; }
};

class LightningSpell : public SpellCard
{
	public:
		LightningSpell(std::string type, int att) : SpellCard(type) {}

		std::string GetHealthStr() { return ""; }
};

class BlessSpell : public SpellCard
{
	public:
		BlessSpell(std::string type, int att, int heal) : SpellCard(type) {}

		std::string GetHealthStr() { return ""; }
};