#pragma once

class wall
{
public:
	wall(int x, int y);

	int get_x() const;
	int get_y() const;
	char get_symbol() const;
	bool is_at_position(int x_check, int y_check) const;

private:
	char symbol_;
	int x_{}, y_{};
};
