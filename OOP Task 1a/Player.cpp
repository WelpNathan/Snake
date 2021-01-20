#include "Player.h"

#include <raylib.h>

#include "Constants.h"

/// <summary>
/// Creates a new instance of player.
/// </summary>
player::player() : x_(0), y_(0), symbol_(PLAYER), dx_(0), dy_(0)
{
	position_in_middle_of_grid();
}

/// <summary>
/// Reset's the player's data for a new game.
/// </summary>
void player::reset()
{
	fruit_collected_ = 0;
	this->position_in_middle_of_grid();
	this->set_score(0);
}

/// <summary>
/// Returns the X position of the player.
/// </summary>
/// <returns>X location</returns>
int player::get_x() const
{
	return x_;
}

/// <summary>
/// Returns the Y position of the player.
/// </summary>
/// <returns>Y location</returns>
int player::get_y() const
{
	return y_;
}

/// <summary>
/// Returns the symbol of the player.
/// A symbol is a game object, i.e wall, floor, player.
/// </summary>
/// <returns>Symbol of player</returns>
char player::get_symbol() const
{
	return symbol_;
}

/// <summary>
/// Checks to see if a player is at the specified location.
/// </summary>
/// <param name="x_new">X location</param>
/// <param name="y_new">Y location</param>
/// <returns>Boolean depending on player location</returns>
bool player::is_at_position(const int x_new, const int y_new) const
{
	return this->x_ == x_new && this->y_ == y_new;
}

/// <summary>
/// Gets the player's score.
/// </summary>
/// <returns>Player score.</returns>
int player::get_score() const
{
	return score_;
}

/// <summary>
/// Sets the player's score.
/// </summary>
/// <param name="score">New score value.</param>
void player::set_score(const int score)
{
	score_ = score;
}

/// <summary>
/// Moves the player's position depending
/// on the key.
/// </summary>
/// <param name="key">Integer keycode</param>
void player::move(const int key)
{
	switch (key)
	{
	case KEY_LEFT:
		dx_ = -1;
		dy_ = 0;
		break;
	case KEY_RIGHT:
		dx_ = +1;
		dy_ = 0;
		break;
	case KEY_UP:
		dx_ = 0;
		dy_ = -1;
		break;
	case KEY_DOWN:
		dx_ = 0;
		dy_ = +1;
		break;
	default:
		// not a key we care about, so do nothing
		break;
	}

	// update mouse coordinates if move is possible
	if (((x_ + dx_) >= 1) && ((x_ + dx_) <= SIZE) && ((y_ + dy_) >= 1) && ((y_ + dy_) <= SIZE))
	{
		update_position(dx_, dy_);
	}
}

/// <summary>
/// Update the player's position a few blocks.
/// </summary>
/// <param name="x_new">Incremented x value</param>
/// <param name="y_new">Incremented y value</param>
void player::update_position(const int x_new, const int y_new)
{
	x_ += x_new;
	y_ += y_new;
}

/// <summary>
/// Moves the player to be in the middle of the grid.
/// </summary>
void player::position_in_middle_of_grid()
{
	x_ = SIZE / 2;
	y_ = SIZE / 2;
}

/// <summary>
/// Gets the player's trails.
/// </summary>
/// <returns>Player trails.</returns>
std::vector<trail>* player::get_trails()
{
	return &trails_;
}

/// <summary>
/// Adds a new trail to the player.
/// </summary>
void player::add_trail(const int x, const int y)
{
	const trail trail(x, y);
	trails_.push_back(trail);
}

/// <summary>
/// Notifies the player that a fruit
/// was collected.
/// </summary>
void player::add_fruit()
{
	fruit_collected_++;
}