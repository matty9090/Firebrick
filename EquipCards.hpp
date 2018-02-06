#pragma once

#include "Cards.hpp"

/*
	Equipment Cards
*/

class SwordEquip : public EquipmentCard {
	public:
		SwordEquip(int type) : EquipmentCard(10) {}
};

class ArmourEquip : public EquipmentCard {
	public:
		ArmourEquip(int type) : EquipmentCard(11) {}
};