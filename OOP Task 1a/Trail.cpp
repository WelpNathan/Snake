#include "Trail.h"

#include "Constants.h"

/// <summary>
/// Creates a new instance of trail.
/// </summary>
/// <param name="x">X position of trail.</param>
/// <param name="y">Y position of trail.</param>
trail::trail(const int x, const int y)
{
	x_ = x;
	y_ = y;
	symbol_ = TRAIL;
}

/// <summary>
/// Gets the x position of the trail.
/// </summary>
/// <returns>X position.</returns>
int trail::get_x() const
{
	return x_;
}

/// <summary>
/// Gets the y position of the trail.
/// </summary>
/// <returns>Y position.</returns>
int trail::get_y() const
{
	return x_;
}