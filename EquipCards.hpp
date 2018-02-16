#pragma once

#include "Cards.hpp"

/*
	Equipment Cards
*/

class SwordEquip : public EquipmentCard
{
	public:
		SwordEquip(std::string type, int attIncrement) : EquipmentCard(type) {}
};

class ArmourEquip : public EquipmentCard
{
	public:
		ArmourEquip(std::string type, int protection) : EquipmentCard(type) {}
};