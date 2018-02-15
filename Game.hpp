#pragma once

#include <string>
#include <map>
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
		std::map<std::string, int> m_MinionCards;

		void ReadDeck(std::string file, Player *player);
		CardPtr CreateCard(int type, std::string name, std::vector<int> values);
};