#pragma once

#include "Cards.hpp"

/*
	Spell cards
*/

class CFireballSpell : public CSpellCard
{
	public:
		CFireballSpell(std::string type, int att) : CSpellCard(type, att) {}

		std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);
};

class CLightningSpell : public CSpellCard
{
	public:
		CLightningSpell(std::string type, int att) : CSpellCard(type, att) {}

		std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);
};

class CBlessSpell : public CSpellCard
{
	public:
		CBlessSpell(std::string type, int att, int heal) : CSpellCard(type, att, heal) {}

		std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);
};