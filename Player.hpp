#pragma once

#include <string>
#include <vector>

#include "MinionCards.hpp"
#include "SpellCards.hpp"
#include "EquipCards.hpp"

class Player
{
	public:
		Player(std::string name);

		std::string GetName() { return m_Name; }

		void AddCardToDeck(CardPtr card) { m_Deck.push_back(card); }

		std::vector<CardPtr> GetDeck() const { return m_Deck; }
		std::vector<CardPtr> GetHand() const { return m_Hand; }

	private:
		std::string m_Name;
		std::vector<CardPtr> m_Deck;
		std::vector<CardPtr> m_Hand;
};