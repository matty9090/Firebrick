#include <iostream>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

#include "Game.hpp"

using namespace std;

const string g_SeedFile      = "seed.txt";
const string g_WizardDeck    = "wizard.txt";
const string g_SorceressDeck = "sorceress.txt";

int main()
{
	int seed;
	ifstream seedFile(g_SeedFile);

	if (seedFile.is_open()) {
		seedFile >> seed;
		seedFile.close();
		srand(seed);
	}

	cout << "Matthew Lowe - Firebrick\n\n\n";

	Game firebrick(g_WizardDeck, g_SorceressDeck);
	firebrick.Run();

    return 0;
}

/*
	Generate a random number between 0 and n
*/
int Random(const float n)
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1));
}