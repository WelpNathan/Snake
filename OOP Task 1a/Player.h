#pragma once
#include <vector>

#include "Trail.h"

class player
{
public:
	player();
	void reset();

	int get_x() const;
	int get_y() const;

	char get_symbol() const;
	bool is_at_position(int x_new, int y_new) const;
	
	int get_score() const;
	void set_score(int score);

	void add_fruit();
	
	void move(int key);
	void position_in_middle_of_grid();
	
	std::vector<trail>* get_trails();
	void add_trail(int x, int y);

private:
	int x_;
	int y_;
	char symbol_;
	int dx_;
	int dy_;
	int score_ = 0;
	int fruit_collected_ = 0;

	void update_position(int x_new, int y_new);
	std::vector<trail> trails_;
};
