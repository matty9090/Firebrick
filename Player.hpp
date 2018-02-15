#pragma once

#include <string>
#include <vector>
#include <stack>

#include "MinionCards.hpp"
#include "SpellCards.hpp"
#include "EquipCards.hpp"

class Player
{
	public:
		Player(std::string name);

		std::string GetName() { return m_Name; }

		void AddCardToDeck(CardPtr card) { m_Deck.push(card); }
		void DrawCard();
		void TakeDamage(int damage);

		int GetHealth() { return m_Health; }
		std::stack<CardPtr> GetDeck() const { return m_Deck; }
		CardPtr PlayCard();

	private:
		const int m_kMaxHealth = 30;
		int m_Health;

		std::string m_Name;
		std::stack<CardPtr> m_Deck;
		std::vector<CardPtr> m_Hand;
};