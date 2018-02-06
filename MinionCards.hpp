#pragma once

#include "Cards.hpp"

/*
	Minion Cards
*/

class BasicMinionCard : public MinionCard {
	public:
		BasicMinionCard() : MinionCard(1) {}
};

class VampireMinionCard : public MinionCard {
	public:
		VampireMinionCard() : MinionCard(5) {}
};

class WallMinionCard : public MinionCard {
	public:
		WallMinionCard() : MinionCard(6) {}
};

class HordeMinionCard : public MinionCard {
	public:
		HordeMinionCard() : MinionCard(7) {}
};

class TrampleMinionCard : public MinionCard {
	public:
		TrampleMinionCard() : MinionCard(8) {}
};

class LeechMinionCard : public MinionCard {
	public:
		LeechMinionCard() : MinionCard(9) {}
};