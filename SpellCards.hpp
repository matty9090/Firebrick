#pragma once

#include "Cards.hpp"

/*
	Spell cards
*/

class FireballSpell : public SpellCard
{
	public:
		FireballSpell(std::string type, int att) : SpellCard(type, att) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp) {
			std::ostringstream out;
			SpellCard::OnActivate(card, self, opp);

			std::vector<std::shared_ptr<Living>> targets;
			targets.push_back(std::dynamic_pointer_cast<Living>(opp));

			for (auto tblCard : opp->GetTable())
				targets.push_back(std::dynamic_pointer_cast<Living>(tblCard));

			if (targets.size() > 0)
			{
				std::shared_ptr<Living> target = targets[Random(targets.size())];
				target->TakeDamage(m_Attack);
				out << GetType() << " attacks " << target->GetName() << ": " << target->GetName();

				if(target->GetHealth() <= 0)
					out << " is killed";
				else
					out << " health now " << target->GetHealth();

				out << "\n";
			}

			return out.str();
		}
};

class LightningSpell : public SpellCard
{
	public:
		LightningSpell(std::string type, int att) : SpellCard(type, att) {}
};

class BlessSpell : public SpellCard
{
	public:
		BlessSpell(std::string type, int att, int heal) : SpellCard(type, att) {}
};