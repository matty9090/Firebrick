#pragma once

#include "Cards.hpp"

/*
	Minion Cards
*/

// No special abilities so will use standard CMinionCard's attack function
class CBasicMinionCard : public CMinionCard
{
	public:
		CBasicMinionCard(std::string type, int att, int health) : CMinionCard(type, att, health) {}
};

class CVampireMinionCard : public CMinionCard
{
	public:
		CVampireMinionCard(std::string type, int att, int health, int heal) : CMinionCard(type, att, health), m_Heal(heal) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);

	private:
		int m_Heal;
};

// No special abilities (however, will be picked as the first enemy)
class CWallMinionCard : public CMinionCard
{
	public:
		CWallMinionCard(std::string type, int att, int health) : CMinionCard(type, att, health) {}
};

class CHordeMinionCard : public CMinionCard
{
	public:
		CHordeMinionCard(std::string type, int att, int health, int attIncrement) : CMinionCard(type, att, health), m_InitialAtt(att), m_AttIncrement(attIncrement) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);

	private:
		int m_AttIncrement;
		int m_InitialAtt;
};

class CTrampleMinionCard : public CMinionCard
{
	public:
		CTrampleMinionCard(std::string type, int att, int health) : CMinionCard(type, att, health), m_InitialAtt(att) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);

	private:
		int m_InitialAtt;
};

class CLeechMinionCard : public CMinionCard
{
	public:
		CLeechMinionCard(std::string type, int att, int health, int heal) : CMinionCard(type, att, health), m_Heal(heal) {}

		std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);

	protected:
		int m_Heal;
};
