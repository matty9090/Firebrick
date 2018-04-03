#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "Util.hpp"
#include "Player.hpp"

class CGame
{
	public:
		CGame(std::string wizFile, std::string sorFile);
		~CGame();

		void Run();

	private:
		int m_Round;
		bool ended;

		const int m_kMaxRounds = 30;
		const int m_kMaxHealth = 30;

		std::shared_ptr<CPlayer> *m_Players;

		enum EPlayers { S, W };
		std::map<std::string, int> m_MinionCards;

		void Play(EPlayers player);
		void ReadDeck(std::string file, std::shared_ptr<CPlayer> player);
		std::string OutputTable(std::vector<CardPtr> table);
		CardPtr CreateCard(int type, std::string name, std::vector<int> values);
};