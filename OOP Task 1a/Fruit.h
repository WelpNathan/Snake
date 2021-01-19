#pragma once
class fruit
{
public:
	fruit(int x, int y, int score);
	
	int get_score() const;
	bool is_at_position(int x_check, int y_check) const;

	int get_x() const;
	int get_y() const;
private:
	int x_;
	int y_;
	int score_ = 10;
	char symbol_;
};

