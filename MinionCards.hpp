#pragma once

#include "Cards.hpp"

/*
	Minion Cards
*/

class CBasicMinionCard : public CMinionCard
{
	public:
		CBasicMinionCard(std::string type, int att, int health) : CMinionCard(type, att, health) {}
};

class CVampireMinionCard : public CMinionCard
{
	public:
		CVampireMinionCard(std::string type, int att, int health, int heal) : CMinionCard(type, att, health), m_Heal(heal) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			std::ostringstream out;
			std::string res = CMinionCard::OnPlay(card, self, opp);
			out << res;
			
			if (res != "")
				m_Health += m_Heal;

			return out.str();
		}

	private:
		int m_Heal;
};

class CWallMinionCard : public CMinionCard
{
	public:
		CWallMinionCard(std::string type, int att, int health) : CMinionCard(type, att, health) {}
};

class CHordeMinionCard : public CMinionCard
{
	public:
		CHordeMinionCard(std::string type, int att, int health, int attIncrement) : CMinionCard(type, att, health), m_InitialAtt(att), m_AttIncrement(attIncrement) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			int extra = 0;

			for (CardPtr c : self->GetTable())
				if (c->GetType() == GetType() && c != card)
					extra += m_AttIncrement;

			m_Attack = m_InitialAtt + extra;

			return CMinionCard::OnPlay(card, self, opp);
		}

	private:
		int m_AttIncrement;
		int m_InitialAtt;
};

class CTrampleMinionCard : public CMinionCard
{
	public:
		CTrampleMinionCard(std::string type, int att, int health) : CMinionCard(type, att, health), m_InitialAtt(att) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			std::ostringstream out;
			m_Attack = m_InitialAtt;

			do
			{
				out << CMinionCard::OnPlay(card, self, opp);
				m_Attack = m_Excess;
			}
			while (m_Excess > 0);

			return out.str();
		}

	private:
		int m_InitialAtt;
};

class CLeechMinionCard : public CMinionCard
{
	public:
		CLeechMinionCard(std::string type, int att, int health, int heal) : CMinionCard(type, att, health), m_Heal(heal) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp)
		{
			std::ostringstream out;
			std::string res = CMinionCard::OnPlay(card, self, opp);
			out << res;

			if (res != "")
			{
				self->TakeDamage(-m_Heal);
				out << "Leech heals " << self->GetName() << ": " << self->GetName() << " health now " << self->GetHealth();
			}

			return out.str();
		}

	protected:
		int m_Heal;
};
