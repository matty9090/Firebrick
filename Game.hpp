#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "Util.hpp"
#include "Player.hpp"

class Game
{
	public:
		Game(std::string wizFile, std::string sorFile);
		~Game();

		void Run();

	private:
		int m_Round;
		Player **m_Players;

		enum EPlayers { S, W };
		std::map<std::string, int> m_MinionCards;

		void Play(EPlayers player);
		void ReadDeck(std::string file, Player *player);
		std::string OutputHand(std::vector<CardPtr> hand);
		CardPtr CreateCard(int type, std::string name, std::vector<int> values);
};