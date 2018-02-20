#pragma once

#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <vector>

class Card;
typedef std::shared_ptr<Card> CardPtr;

class Living {
	public:
		Living(std::string type, int health) : m_Name(type), m_Health(health) {}
		virtual ~Living() {}

		std::string GetName() { return m_Name; }
		int GetHealth() { return m_Health; }
		void TakeDamage(int damage) { m_Health -= damage; }

	protected:
		int m_Health;
		std::string m_Name;
};

class Player : public Living
{
	public:
		Player(std::string name, int maxHealth);
		virtual ~Player() {}

		void AddCardToDeck(CardPtr card);
		void RemoveCardFromTable(CardPtr card);

		CardPtr DrawCard();
		CardPtr PlayCard();

		std::queue<CardPtr>  GetDeck() const { return m_Deck; }
		std::vector<CardPtr> GetHand() const { return m_Hand; }
		std::vector<CardPtr> GetTable() const { return m_Table; }

	private:
		std::queue<CardPtr> m_Deck;
		std::vector<CardPtr> m_Hand, m_Table;
};