#pragma once

#include <string>

#include "Util.hpp"
#include "Player.hpp"

class Game
{
	public:
		Game(std::string wizFile, std::string sorFile);
		~Game();

		void Run();

	private:
		Player **players;

		enum EPlayers { S, W };

		void ReadDeck(std::string file, Player *player);
};