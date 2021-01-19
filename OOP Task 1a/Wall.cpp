#include "Wall.h"

#include "Constants.h"

/// <summary>
/// Creates a new instance of wall with set
/// x and y positions.
/// </summary>
/// <param name="x">X position</param>
/// <param name="y">Y position</param>
wall::wall(const int x, const int y)
{
	symbol_ = WALL;
	this->x_ = x;
	this->y_ = y;
}

/// <summary>
/// Returns the x position of the wall.
/// </summary>
/// <returns>X position of wall</returns>
int wall::get_x() const
{
	return x_;
}

/// <summary>
/// Returns the y position of the wall.
/// </summary>
/// <returns>Y position of wall</returns>
int wall::get_y() const
{
	return y_;
}

/// <summary>
/// Returns the symbol of the wall.
/// Remember, a symbol is wall, player, floor etc.
/// </summary>
/// <returns>Symbol of wall</returns>
char wall::get_symbol() const
{
	return symbol_;
}

/// <summary>
/// Checks to see if the wall is at position x and y.
/// </summary>
/// <param name="x_check">X location</param>
/// <param name="y_check">Y location</param>
/// <returns>Boolean depending on position</returns>
bool wall::is_at_position(const int x_check, const int y_check) const
{
	return this->x_ == x_check && this->y_ == y_check;
}
