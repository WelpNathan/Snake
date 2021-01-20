#include "Game.h"

#include <algorithm>
#include <iostream>


#include "Constants.h"

/// <summary>
/// Sets up the game with some predefined
/// values for positions.
/// </summary>
void game::setup()
{
	// spawn initial fruit object
	this->spawn_fruit(4, 6, 1000);
	
	// draw the end of wall grid
	for (auto x = 0; x < SIZE + 1; x++)
	{
		for (auto y = 0; y < SIZE + 1; y++)
		{
			if (y == 1 || y == SIZE || x == 1 || x == SIZE)
			{
				walls_.emplace_back(wall(x, y));
			}
		}
	}
}

/// <summary>
/// Resets the game to default settings.
/// </summary>
void game::reset()
{
	walls_.clear();
	fruits_.clear();
	this->setup();
	this->set_running(true);
	player_.reset();
}

/// <summary>
/// Processes a keyboard input for the player.
/// </summary>
/// <param name="key">Integer keycode</param>
void game::process_input(int const key)
{
	player_.move(key);
}

/// <summary>
/// Builds up a 2D grid of characters representing
/// the current state of the game.
/// 
/// Characters are later used to decide which color
/// square to display, but you could display images instead.
/// </summary>
/// <returns>Grid to render</returns>
std::vector<std::vector<char>> game::prepare_grid()
{
	// create the 2D grid
	std::vector<std::vector<char>> grid;

	// for each row
	for (auto row = 1; row <= SIZE; ++row)
	{
		// create the inner vector to add to the 2D grid
		std::vector<char> line;

		// for each column, work out what's in that position and add the relevant char to the 2D grid
		for (auto col = 1; col <= SIZE; ++col)
		{
			if (row == player_.get_y() && col == player_.get_x())
			{
				// grid position is the player
				line.push_back(player_.get_symbol());
			}
			else if (is_wall_at_position(col, row))
			{
				// grid position is a wall
				line.push_back(WALL);
			}
			else
			{
				// grid position is the floor
				line.push_back(FLOOR);
			}
		}

		// now that the row is full, add it to the 2D grid
		grid.push_back(line);
	}

	// generate fruit on board
	for (auto &fruit : fruits_)
	{
		const auto x_pos = fruit.get_x() - 1;
		const auto y_pos = fruit.get_y() - 1;
		grid.at(y_pos).at(x_pos) = FRUIT;
	}

	// generate trail on board
	for (auto &trail : *player_.get_trails())
	{
		const auto x_pos = trail.get_x() - 1;
		const auto y_pos = trail.get_y() - 1;
		grid.at(y_pos).at(x_pos) = TRAIL;
	}

	// return grid object
	return grid;
}

/// <summary>
/// Checks if a grid position is a wall.
/// </summary>
/// <param name="x">X position of grid.</param>
/// <param name="y">Y position if grid.</param>
/// <returns>Boolean depending if a wall is at the location.</returns>
bool game::is_wall_at_position(const int x, const int y)
{
	// optimized for loop using std::any_of
	return std::any_of(walls_.begin(), walls_.end(),
	                   [x, y](const wall& wall)
	                   {
		                   return wall.is_at_position(x, y);
	                   });
}

/// <summary>
/// Handles the player collecting fruit.
/// </summary>
/// <param name="x">X position of grid.</param>
/// <param name="y">Y position if grid.</param>
/// <returns>Score of fruit.</returns>
int game::handle_fruit_at_position(const int x, const int y)
{
	for(auto it = fruits_.begin(); it != fruits_.end(); ++it)
	{
		if (it->is_at_position(x, y))
		{
			const auto fruit_score = it->get_score();
			fruits_.erase(it);
			return fruit_score;
		}
	}
	return 0;
}

/// <summary>
/// Spawns a fruit at a set position in the game.
/// </summary>
/// <param name="x">X position of fruit.</param>
/// <param name="y">Y position of fruit.</param>
/// <param name="score">Score of fruit.</param>
void game::spawn_fruit(const int x, const int y, const int score)
{
	const fruit fruit(x, y, score);
	fruits_.push_back(fruit);
}

/// <summary>
/// Returns if the player is colliding with a wall at
/// the current position.
/// </summary>
/// <returns>Boolean depending if player collides with wall.</returns>
bool game::is_player_collide_wall()
{
	if (is_wall_at_position(player_.get_x(), player_.get_y())) return true;
	return false;
}

/// <summary>
/// Checks if the game is running or not.
/// </summary>
/// <returns>Game running status.</returns>
bool game::is_running() const
{
	return running_;
}

/// <summary>
/// Sets if the game is running.
/// </summary>
/// <param name="running">Game running boolean.</param>
void game::set_running(const bool running)
{
	running_ = running;
}

/// <summary>
/// Sets if the game is paused.
/// </summary>
/// <param name="paused">Game paused boolean.</param>
void game::set_paused(const bool paused)
{
	paused_ = paused;
}

/// <summary>
/// Checks if the game is paused.
/// </summary>
/// <returns>Game paused status.</returns>
bool game::is_paused() const
{
	return paused_;
}

/// <summary>
/// Returns the snake game player object.
/// </summary>
/// <returns>Player object.</returns>
player* game::get_player()
{
	return &player_;
}