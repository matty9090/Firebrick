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

/* Unused? */
class WallMinionCard : public MinionCard
{
	public:
		WallMinionCard(std::string type, int att, int health) : MinionCard(type, att, health) {}
};

class HordeMinionCard : public MinionCard
{
	public:
		HordeMinionCard(std::string type, int att, int health, int attIncrement) : MinionCard(type, att, health), m_InitialAtt(att), m_AttIncrement(attIncrement) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			int extra = 0;

			for (CardPtr c : self->GetTable())
				if (c->GetType() == GetType() && c != card)
					extra += m_AttIncrement;

			m_Attack = m_InitialAtt + extra;

			return MinionCard::OnPlay(card, self, opp);
		}

	private:
		int m_AttIncrement;
		int m_InitialAtt;
};

class TrampleMinionCard : public MinionCard
{
	public:
		TrampleMinionCard(std::string type, int att, int health) : MinionCard(type, att, health), m_InitialAtt(att) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<Player> self, std::shared_ptr<Player> opp)
		{
			std::ostringstream out;
			m_Attack = m_InitialAtt;

			do
			{
				out << MinionCard::OnPlay(card, self, opp);
				m_Attack = m_Excess;
			}
			while (m_Excess > 0);

			return out.str();
		}

	private:
		int m_InitialAtt;
};

class LeechMinionCard : public MinionCard
{
	public:
		LeechMinionCard(std::string type, int att, int health, int heal) : MinionCard(type, att, health) {}
};
