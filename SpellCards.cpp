#include "SpellCards.hpp"
#include "Util.hpp"

/*
	Fireball spell causes damage to a minion or player
*/
std::string CFireballSpell::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;
	CSpellCard::OnActivate(card, self, opp);

	std::vector<std::shared_ptr<CLiving>> targets;

	// Add minions to targets
	for (auto tblCard : opp->GetTable())
		targets.push_back(std::dynamic_pointer_cast<CLiving>(tblCard));

	// Add player to target
	targets.push_back(std::dynamic_pointer_cast<CLiving>(opp));

	// Choose target at random
	if (targets.size() > 0)
	{
		int rand = Random(targets.size());
		CardPtr oppCard = (rand == targets.size() - 1) ? nullptr : opp->GetTable()[rand];
		out << Attack(card, targets[rand], opp, m_Attack, oppCard);
	}

	return out.str();
}

/*
	Lightning spell causes 1 damage to all enemies
*/
std::string CLightningSpell::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;
	CSpellCard::OnActivate(card, self, opp);

	// Damage all minions
	for (auto c : opp->GetTable())
		out << Attack(card, std::dynamic_pointer_cast<CLiving>(c), opp, m_Attack, c);

	// Damage player
	out << Attack(card, std::dynamic_pointer_cast<CLiving>(opp), opp, m_Attack, nullptr);

	return out.str();
}

/*
	Bless spell heals current player/minions or damages other player/minions
*/
std::string CBlessSpell::OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
{
	std::ostringstream out;
	CSpellCard::OnActivate(card, self, opp);

	std::vector<std::shared_ptr<CLiving>> targets;

	// Enemy minions, enemy player, friendly minions, friendly player added to targets
	for (auto minions : opp->GetTable())  targets.push_back(std::dynamic_pointer_cast<CLiving>(minions));
	targets.push_back(std::dynamic_pointer_cast<CLiving>(opp));
	for (auto minions : self->GetTable()) targets.push_back(std::dynamic_pointer_cast<CLiving>(minions));
	targets.push_back(std::dynamic_pointer_cast<CLiving>(self));

	if (targets.size() > 0)
	{
		int rand = Random(targets.size());
		CardPtr c = nullptr;

		// Attack/Heal depending on friendly/enemy
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