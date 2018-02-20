#pragma once

#include "Cards.hpp"

/*
	Minion Cards
*/

class BasicMinionCard : public MinionCard
{
	public:
		BasicMinionCard(std::string type, int att, int health) : MinionCard(type, att, health) {}
};

class VampireMinionCard : public MinionCard
{
	public:
		VampireMinionCard(std::string type, int att, int health, int heal) : MinionCard(type, att, health), m_Heal(heal) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			std::ostringstream out;
			
			if (MinionCard::OnPlay(card, self, opp) != "")
				m_Health += m_Heal;

			return out.str();
		}

	private:
		int m_Heal;
};

class WallMinionCard : public MinionCard
{
	public:
		WallMinionCard(std::string type, int att, int health) : MinionCard(type, att, health) {}
};

class HordeMinionCard : public MinionCard
{
	public:
		HordeMinionCard(std::string type, int att, int health, int attIncrement) : MinionCard(type, att, health) {}
};

class TrampleMinionCard : public MinionCard
{
	public:
		TrampleMinionCard(std::string type, int att, int health) : MinionCard(type, att, health) {}
};

class LeechMinionCard : public MinionCard
{
	public:
		LeechMinionCard(std::string type, int att, int health, int heal) : MinionCard(type, att, health) {}
};
