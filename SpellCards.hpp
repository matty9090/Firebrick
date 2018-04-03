#pragma once

#include "Cards.hpp"

/*
	Spell cards
*/

class CFireballSpell : public CSpellCard
{
	public:
		CFireballSpell(std::string type, int att) : CSpellCard(type, att) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			std::ostringstream out;
			CSpellCard::OnActivate(card, self, opp);

			std::vector<std::shared_ptr<CLiving>> targets;

			for (auto tblCard : opp->GetTable())
				targets.push_back(std::dynamic_pointer_cast<CLiving>(tblCard));

			targets.push_back(std::dynamic_pointer_cast<CLiving>(opp));

			if (targets.size() > 0)
			{
				int rand = Random(targets.size());
				CardPtr oppCard = (rand == targets.size() - 1) ? nullptr : opp->GetTable()[rand];
				out << Attack(card, targets[rand], opp, m_Attack, oppCard);
			}

			return out.str();
		}
};

class CLightningSpell : public CSpellCard
{
	public:
		CLightningSpell(std::string type, int att) : CSpellCard(type, att) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			std::ostringstream out;
			CSpellCard::OnActivate(card, self, opp);

			for (auto c : opp->GetTable())
				out << Attack(card, std::dynamic_pointer_cast<CLiving>(c), opp, m_Attack, c);

			out << Attack(card, std::dynamic_pointer_cast<CLiving>(opp), opp, m_Attack, nullptr);

			return out.str();
		}
};

class CBlessSpell : public CSpellCard
{
	public:
		CBlessSpell(std::string type, int att, int heal) : CSpellCard(type, att, heal) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			std::ostringstream out;
			CSpellCard::OnActivate(card, self, opp);

			std::vector<std::shared_ptr<CLiving>> targets;

			// Enemy minions, enemy player, friendly minions, friendly player
			for (auto minions : opp->GetTable())  targets.push_back(std::dynamic_pointer_cast<CLiving>(minions));
			targets.push_back(std::dynamic_pointer_cast<CLiving>(opp));
			for (auto minions : self->GetTable()) targets.push_back(std::dynamic_pointer_cast<CLiving>(minions));
			targets.push_back(std::dynamic_pointer_cast<CLiving>(self));

			if (targets.size() > 0)
			{
				int rand = Random(targets.size());
				CardPtr c = nullptr;

				if (std::dynamic_pointer_cast<CPlayer>(targets[rand]) == self)
				{
					CardPtr isPlayer = std::dynamic_pointer_cast<CCard>(targets[rand]);
					c = (isPlayer) ? nullptr : isPlayer;
					out << Attack(card, targets[rand], opp, m_Attack, c);
				}
				else
				{
					CardPtr isPlayer = std::dynamic_pointer_cast<CCard>(targets[rand]);
					c = (isPlayer) ? nullptr : isPlayer;
					out << Heal(card, targets[rand], opp, m_Heal, c);
				}
			}

			return out.str();
		}
};