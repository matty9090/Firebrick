#pragma once

#include "Cards.hpp"

/*
	Spell cards
*/

class FireballSpell : public SpellCard
{
	public:
		FireballSpell(std::string type, int att) : SpellCard(type, att) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			std::ostringstream out;
			SpellCard::OnActivate(card, self, opp);

			std::vector<std::shared_ptr<Living>> targets;
			targets.push_back(std::dynamic_pointer_cast<Living>(opp));

			for (auto tblCard : opp->GetTable())
				targets.push_back(std::dynamic_pointer_cast<Living>(tblCard));

			if (targets.size() > 0)
			{
				int rand = Random(targets.size());
				CardPtr oppCard = (rand == targets.size() - 1) ? nullptr : opp->GetTable()[rand];
				out << Attack(card, targets[rand], opp, m_Attack, oppCard);
			}

			return out.str();
		}
};

class LightningSpell : public SpellCard
{
	public:
		LightningSpell(std::string type, int att) : SpellCard(type, att) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			std::ostringstream out;
			SpellCard::OnActivate(card, self, opp);

			for (auto c : opp->GetTable())
				out << Attack(card, std::dynamic_pointer_cast<Living>(c), opp, m_Attack, c);

			out << Attack(card, std::dynamic_pointer_cast<Living>(opp), opp, m_Attack, nullptr);

			return out.str();
		}
};

class BlessSpell : public SpellCard
{
	public:
		BlessSpell(std::string type, int att, int heal) : SpellCard(type, att) {}
};