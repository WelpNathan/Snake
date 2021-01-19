#pragma once

#include <vector>

#include "Fruit.h"
#include "Player.h"
#include "Wall.h"

class game
{
public:
	void setup();
	void reset();
	void process_input(int key);
	std::vector<std::vector<char>> prepare_grid();
	void spawn_fruit(int x, int y, int score);
	
	bool is_running() const;
	void set_running(bool running);

	bool is_paused() const;
	void set_paused(bool paused);

	bool is_player_collide_wall();
	int handle_fruit_at_position(int x, int y);

	player* get_player();
private:
	player player_;
	std::vector<wall> walls_;
	std::vector<fruit> fruits_;
	
	bool running_ = true;
	bool paused_ = false;
	
	bool is_wall_at_position(int x, int y);
};
