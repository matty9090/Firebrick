#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include "Player.hpp"


// Create type for ease of use
class CCard;
typedef std::shared_ptr<CCard> CardPtr;

/*
	General class card (abstract)
*/

class CCard
{
	public:
		CCard(std::string type) : m_CardType(type) {}
		 
		virtual std::string OnPlay(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp) { return ""; } // TODO: Make pure
		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp) { return ""; }

		std::string GetType() { return m_CardType; }

	protected:
		std::string m_CardType;
		int m_Excess;
		
		std::string Attack(CardPtr att, std::shared_ptr<CLiving> opp, std::shared_ptr<CPlayer> player, int damage, CardPtr remove = nullptr);
		std::string Heal(CardPtr att, std::shared_ptr<CLiving> opp, std::shared_ptr<CPlayer> player, int heal, CardPtr remove = nullptr);
};

/*
	The 3 types of card
*/

class CMinionCard : public CCard, public CLiving
{
	public:
		CMinionCard(std::string type, int att, int health) : CCard(type), CLiving(type, health), m_Attack(att) {}

		void IncreaseAttack(int att) { m_Attack += att; }
		void TakeDamage(int damage) { m_Health -= damage; }

		std::string OnPlay(CardPtr curCard, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);

	protected:
		int m_Attack;
};

class CSpellCard : public CCard
{
	public:
		CSpellCard(std::string type, int att, int heal = 0) : CCard(type), m_Attack(att), m_Heal(heal) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);

	protected:
		int m_Attack, m_Heal;
};

class CEquipmentCard : public CCard
{
	public:
		CEquipmentCard(std::string type) : CCard(type) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);
};