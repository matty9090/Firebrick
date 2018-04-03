#pragma once

#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <vector>

// Predeclare the abstract card class
class CCard;

// Create type for ease of use
typedef std::shared_ptr<CCard> CardPtr;

/*
	Living class
	Players and Minions share properties e.g. Health
*/
class CLiving
{
	public:
		CLiving(std::string type, int health) : m_Name(type), m_Health(health), m_Armour(0) {}
		virtual ~CLiving() {}

		std::string GetName() { return m_Name; }

		int GetHealth() { return m_Health; }
		int GetProtection() { return m_Armour; }

		void TakeDamage(int damage) { m_Health -= damage; }
		void AddArmour(int protection) { m_Armour += protection; }

	protected:
		int m_Health, m_Armour;
		std::string m_Name;
};

/*
	Player class
	A player has a deck, hand and table
*/
class CPlayer : public CLiving
{
	public:
		CPlayer(std::string name, int maxHealth);
		virtual ~CPlayer() {}

		void AddCardToDeck(CardPtr card);
		void RemoveCardFromTable(CardPtr card);

		CardPtr DrawCard();
		CardPtr PlayCard();
		CardPtr GetEnemy();

		std::queue<CardPtr>  GetDeck() const { return m_Deck; }
		std::vector<CardPtr> GetHand() const { return m_Hand; }
		std::vector<CardPtr> GetTable() const { return m_Table; }

	private:
		std::queue<CardPtr> m_Deck;
		std::vector<CardPtr> m_Hand, m_Table;
};