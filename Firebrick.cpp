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
	const string seedLocation	= "seed.txt";
	const string wizardDeck		= "wizard.txt";
	const string sorceressDeck	= "sorceress.txt";

	int seed;
	ifstream seedFile(seedLocation);

	// Read in seed
	if (seedFile.is_open())
	{
		seedFile >> seed;
		seedFile.close();
		srand(seed);
	}

	cout << "Matthew Lowe - Firebrick\n\n";

	// Create game class and run
	CGame firebrick(wizardDeck, sorceressDeck);
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