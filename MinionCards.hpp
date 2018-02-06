#pragma once

#include "Cards.hpp"

/*
	Minion Cards
*/

class BasicMinionCard : public MinionCard {
	public:
		BasicMinionCard(int type) : MinionCard(1) {}
};

class VampireMinionCard : public MinionCard {
	public:
		VampireMinionCard(int type) : MinionCard(5) {}
};

class WallMinionCard : public MinionCard {
	public:
		WallMinionCard(int type) : MinionCard(6) {}
};

class HordeMinionCard : public MinionCard {
	public:
		HordeMinionCard(int type) : MinionCard(7) {}
};

class TrampleMinionCard : public MinionCard {
	public:
		TrampleMinionCard(int type) : MinionCard(8) {}
};

class LeechMinionCard : public MinionCard {
	public:
		LeechMinionCard(int type) : MinionCard(9) {}
};