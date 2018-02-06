#pragma once

#include <string>
#include <set>
#include <memory>

#include "Util.hpp"
#include "Player.hpp"

class Game
{
	public:
		Game(std::string wizFile, std::string sorFile);
		~Game();

		void Run();

	private:
		Player **m_Players;

		enum EPlayers { S, W };

		void ReadDeck(std::string file, Player *player);
		CardPtr CreateCard(int type, std::vector<int> values);
};