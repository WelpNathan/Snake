#include "RandomNumberGenerator.h"

#include <cstdlib>
#include <ctime>

/// <summary>
/// Creates a new instance of RandomNumberGenerator.
/// </summary>
random_number_generator::random_number_generator()
{
	seed();
}

/// <summary>
/// Returns a new random value.
/// </summary>
/// <param name="max">Maximum value to create.</param>
/// <returns>Random number</returns>
int random_number_generator::get_random_value(const int max)
{
	// produce a random number in range [1..max]
	return (rand() % max) + 1;
}

/// <summary>
/// Create a new seed for the generator.
///
/// TODO: Potentially add a new unique way of seeding?
/// </summary>
void random_number_generator::seed()
{
	// seed the random number generator from current system time
	// so that the numbers will be different every time we run
	srand(static_cast<unsigned>(time(nullptr)));
}
