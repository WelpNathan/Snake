#include <cassert>
#include <iostream>

#include "Constants.h"
#include "raylib.h"
#include "Game.h"
#include "RandomNumberGenerator.h"

/// <summary>
/// Draws common data to the screen.
/// </summary>
/// <param name="score">Current player score.</param>
/// <param name="screen_height">Screen height.</param>
void draw_common(const int score, const int screen_height)
{
	DrawText(TextFormat("FPS: %i", GetFPS()), 610, 10, 20, LIGHTGRAY);
	DrawText(TextFormat("Score: %08i", score), 610, 30, 20, LIGHTGRAY);
	DrawText("Snake Game V1.1.0", 660, screen_height - 20, 20, LIGHTGRAY);
}

/// <summary>
/// Main game loop.
/// Starting point for program, uses ray-lib as
/// dependency for program.
/// </summary>
int main()
{
	// initialise the window and set fps
	InitWindow(900, 600, "OOP Assignment 1 - Snake Game");
	SetTargetFPS(60);

	// create a new instance of game and player
	game game;
	game.setup();
	auto* player = game.get_player();

	// speed limiting
	auto count_frames = 0;

	// getting the last key pressed
	auto key_pressed = KEY_DOWN;

	// getting screen resolution
	const auto screen_width = GetScreenWidth();
	const auto screen_height = GetScreenHeight();

	// main game loop
	while (!WindowShouldClose())
	{
		// get common game variables
		const auto game_running = game.is_running();
		const auto game_paused = game.is_paused();
		const auto score = player->get_score();

		// begin a new frame
		BeginDrawing();
		ClearBackground(DARKGRAY);

		// draw common login
		draw_common(score, screen_height);

		// get how big a single cell should be
		const auto cell_size = static_cast<int>(static_cast<float>(screen_height) / static_cast<float>((SIZE)));

		// check if the player wants to pause the game (only if running)
		if (IsKeyPressed(KEY_P) && game.is_running()) game.set_paused(!game.is_paused());
		if (game_paused) DrawText("Game\nPaused", screen_width / 2 + 175, screen_height / 2, 40, LIGHTGRAY);
		
		// whilst the game is running, process input events
		if (game_running && !game_paused)
		{
			DrawText("Press 'P'\nTo Pause", screen_width / 2 + 175, screen_height / 2, 40, LIGHTGRAY);

			// set which way the snake should move
			if (IsKeyPressed(KEY_RIGHT) && key_pressed != KEY_LEFT) key_pressed = KEY_RIGHT;
			if (IsKeyPressed(KEY_LEFT) && key_pressed != KEY_RIGHT) key_pressed = KEY_LEFT;
			if (IsKeyPressed(KEY_UP) && key_pressed != KEY_DOWN) key_pressed = KEY_UP;
			if (IsKeyPressed(KEY_DOWN) && key_pressed != KEY_UP) key_pressed = KEY_DOWN;
			
			// perform actions every 5 frames
			if (count_frames % MODE_HARD == 0)
			{
				player->update_trail();
				
				// process game input
				game.process_input(key_pressed);

				// if the player collides with a wall, end game
				if (game.is_player_collide_wall()) game.set_running(false);

				// if still running, check for fruit collision
				if (game.is_running())
				{
					// std::cout << "Player position | X: " << player->get_x() << " Y: " << player->get_y() << std::endl;
					
					// if the player collects fruit at the location
					const auto fruit_score = game.handle_fruit_at_position(player->get_x(), player->get_y());
					if (fruit_score > 0)
					{
						player->add_trail(player->get_x(), player->get_y());
						
						std::cout << "A fruit with a score of " << fruit_score << " was collected." << std::endl;
						
						// update player's score
						player->add_fruit();
						player->set_score(player->get_score() + fruit_score);
						
						// generate a new fruit on the board
						auto x = random_number_generator::get_random_value(SIZE) + 1;
						auto y = random_number_generator::get_random_value(SIZE) + 1;
						while (x >= SIZE || y >= SIZE || (player->get_x() == x && player->get_y() == y))
						{
							x = random_number_generator::get_random_value(SIZE) + 1;
							y = random_number_generator::get_random_value(SIZE) + 1;
						}
						
						game.spawn_fruit(x, y, 1000); // spawn fruit with score of 1000
					}
				}

				// reset frame
				count_frames = 0;
			}
			count_frames++;
		}
		else if(!game_running)
		{
			// if the game has ended
			DrawText(TextFormat("Game Ended\n\nFinal Score: %08i\n\nPress 'Enter' to restart", score),
			         screen_width / 2 + 175, screen_height / 2, 20, LIGHTGRAY);

			// restart the game
			if (IsKeyPressed(KEY_ENTER)) game.reset();
		}

		// prepare the grid for drawing
		const auto grid = game.prepare_grid();
		for (auto x = 0; x < SIZE; x++)
		{
			for (auto y = 0; y < SIZE; y++)
			{
				// calculate position on the screen
				const auto x_position = x * cell_size;
				const auto y_position = y * cell_size;

				// draw different colors depending on what type of square it is
				switch (grid[y][x])
				{
				case FLOOR: 
					DrawRectangle(x_position, y_position, cell_size, cell_size, DARKGREEN);
					break;
				case WALL: 
					DrawRectangle(x_position, y_position, cell_size, cell_size, LIGHTGRAY);
					break;
				case PLAYER: 
					DrawRectangle(x_position, y_position, cell_size, cell_size, GREEN);
					break;
				case TRAIL:
					DrawRectangle(x_position, y_position, cell_size, cell_size, BLUE);
					break;
				case FRUIT:
					DrawRectangle(x_position, y_position, cell_size, cell_size, ORANGE);
					break;
				default: assert(false); // no symbol specified
				}

				// draw lines around each tile, remove this if you don't like it!
				DrawRectangleLines(x * cell_size, y * cell_size, cell_size, cell_size, DARKGRAY);
			}
		}

		// ends the frame drawing
		EndDrawing();
	}

	// close the window and exit program
	CloseWindow();
	return 0;
}
