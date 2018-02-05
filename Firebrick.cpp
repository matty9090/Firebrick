#include <iostream>
#include <ctime>

using namespace std;

int Random(const float n);

int main()
{
    return 0;
}

int Random(const float n)
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1));
}