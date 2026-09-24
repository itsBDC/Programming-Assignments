// (Population projection) UBoS projects population based on the
// following assumptions:
// One birth every 7 seconds
// One death every 13 seconds
// One new immigrant every 45 seconds
// Write a program to display the population for each of the next five years. Assume the current population is 312032486 and one year has 365 days.

#include <iostream>
using namespace std;

int main()
{
    long currentPopulation = 312032486;
    const long secondsInAYear = 365 * 24 * 60 * 60;
    long birthsPerYear = secondsInAYear / 7;
    long deathsPerYear = secondsInAYear / 13;
    long immigrantsPerYear = secondsInAYear / 45;
    for (int year = 1; year <= 5; year++)
    {
        currentPopulation += birthsPerYear - deathsPerYear + immigrantsPerYear;
        cout << "Population after " << year << " year(s): " << currentPopulation << endl;
    }
    return 0;
}
