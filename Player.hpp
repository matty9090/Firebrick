#pragma once

#include <string>
#include <vector>
#include <queue>

#include "SpellCards.hpp"
#include "EquipCards.hpp"
#include "BasicMinionCards.hpp"

class Player
{
	public:
		Player(std::string name);

		std::string GetName() { return m_Name; }

		void AddCardToDeck(CardPtr card) { m_Deck.push(card); }
		void TakeDamage(int damage);

		CardPtr DrawCard();
		CardPtr PlayCard();

		int GetHealth() { return m_Health; }

		std::queue<CardPtr>  GetDeck() const { return m_Deck; }
		std::vector<CardPtr> GetHand() const { return m_Hand; }

	private:
		const int m_kMaxHealth = 30;
		
		int m_Health;

		std::string m_Name;
		std::queue<CardPtr> m_Deck;
		std::vector<CardPtr> m_Hand;
};