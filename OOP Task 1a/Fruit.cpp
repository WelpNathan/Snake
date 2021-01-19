#include "Fruit.h"

#include "Constants.h"

/// <summary>
/// Create a new instance of fruit.
/// </summary>
/// <param name="x">X position of fruit.</param>
/// <param name="y">Y position of fruit.</param>
fruit::fruit(const int x, const int y, const int score)
{
	x_ = x;
	y_ = y;
	score_ = score;
	symbol_ = FRUIT;
}

/// <summary>
/// Gets the score of the fruit when collected.
/// </summary>
/// <returns>Score of fruit.</returns>
int fruit::get_score() const
{
	return score_;
}

/// <summary>
/// Checks to see if the fruit is at position x and y.
/// </summary>
/// <param name="x_check">X location</param>
/// <param name="y_check">Y location</param>
/// <returns>Boolean depending on position</returns>
bool fruit::is_at_position(const int x_check, const int y_check) const
{
	return this->x_ == x_check && this->y_ == y_check;
}

/// <summary>
/// Gets the x position of the fruit.
/// </summary>
/// <returns>X position of fruit.</returns>
int fruit::get_x() const
{
	return x_;
}

/// <summary>
/// Gets the y position of the fruit.
/// </summary>
/// <returns>Y position of fruit.</returns>
int fruit::get_y() const
{
	return y_;
}
