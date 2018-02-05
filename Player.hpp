#pragma once

#include <string>

class Player
{
	public:
		Player(std::string name);

		std::string getName() { return m_Name; }

	private:
		std::string m_Name;
};