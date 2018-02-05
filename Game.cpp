#include "Game.hpp"

Game::Game(std::string wizFile, std::string sorFile)
{
	players = new Player*[2];

	players[0] = new Player("Sorceress");
	players[1] = new Player("Wizard");
}

void Game::Run()
{

}

Game::~Game() {
	delete[] players;
}