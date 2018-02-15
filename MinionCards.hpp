#pragma once

#include "Cards.hpp"

/*
	Minion Cards
*/

class BasicMinionCard : public MinionCard
{
	public:
		BasicMinionCard(std::string type) : MinionCard(type) {}
};

class VampireMinionCard : public MinionCard
{
	public:
		VampireMinionCard(std::string type) : MinionCard(type) {}
};

class WallMinionCard : public MinionCard
{
	public:
		WallMinionCard(std::string type) : MinionCard(type) {}
};

class HordeMinionCard : public MinionCard
{
	public:
		HordeMinionCard(std::string type) : MinionCard(type) {}
};

class TrampleMinionCard : public MinionCard
{
	public:
		TrampleMinionCard(std::string type) : MinionCard(type) {}
};

class LeechMinionCard : public MinionCard
{
	public:
		LeechMinionCard(std::string type) : MinionCard(type) {}
};
