#pragma once

class random_number_generator
{
public:
	random_number_generator();

	static int get_random_value(int);

private:
	static void seed();
};
