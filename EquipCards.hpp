#pragma once

#include "Cards.hpp"

/*
	Equipment Cards
*/

class SwordEquip : public EquipmentCard
{
	public:
		SwordEquip(std::string type, int attIncrement) : EquipmentCard(type) {}

		std::string GetHealthStr() { return ""; }
};

class ArmourEquip : public EquipmentCard
{
	public:
		ArmourEquip(std::string type, int protection) : EquipmentCard(type) {}

		std::string GetHealthStr() { return ""; }
};