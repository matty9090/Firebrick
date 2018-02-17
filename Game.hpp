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
		bool ended;

		const int m_kMaxRounds = 10;
		const int m_kMaxHealth = 30;

		std::shared_ptr<Player> *m_Players;

		enum EPlayers { S, W };
		std::map<std::string, int> m_MinionCards;

		void Play(EPlayers player);
		void ReadDeck(std::string file, std::shared_ptr<Player> player);
		std::string OutputTable(std::vector<CardPtr> table);
		CardPtr CreateCard(int type, std::string name, std::vector<int> values);
};