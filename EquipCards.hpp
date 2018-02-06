#pragma once

#include "Cards.hpp"

/*
	Equipment Cards
*/

class SwordEquip : public EquipmentCard {
	public:
		SwordEquip() : EquipmentCard(10) {}
};

class ArmourEquip : public EquipmentCard {
	public:
		ArmourEquip() : EquipmentCard(11) {}
};