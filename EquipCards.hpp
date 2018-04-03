#pragma once

#include "Cards.hpp"

/*
	Equipment Cards
*/

class CSwordEquip : public CEquipmentCard
{
	public:
		CSwordEquip(std::string type, int attIncrement) : CEquipmentCard(type), m_AttIncrement(attIncrement) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);

	private:
		int m_AttIncrement;
};

class CArmourEquip : public CEquipmentCard
{
	public:
		CArmourEquip(std::string type, int protection) : CEquipmentCard(type), m_Protection(protection) {}

		virtual std::string OnActivate(CardPtr card, std::shared_ptr<CPlayer> self, std::shared_ptr<CPlayer> opp);

	private:
		int m_Protection;
};