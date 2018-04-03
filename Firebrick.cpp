#include <iostream>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

#include "Game.hpp"

using namespace std;

/*
	Entry point of program
*/
int main()
{
	// Declare files
	const string g_SeedFile = "seed.txt";
	const string g_WizardDeck = "wizard.txt";
	const string g_SorceressDeck = "sorceress.txt";

	int seed;
	ifstream seedFile(g_SeedFile);

	// Read in seed
	if (seedFile.is_open())
	{
		seedFile >> seed;
		seedFile.close();
		srand(seed);
	}

	cout << "Matthew Lowe - Firebrick\n\n";

	// Create game class and run
	CGame firebrick(g_WizardDeck, g_SorceressDeck);
	firebrick.Run();

    return 0;
}

/*
	Generate a random number between 0 and n
*/
int Random(const int n)
{
	return rand() % n;
}