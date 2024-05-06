#include <Arduino.h>
#include <SoftwareSerial.h>
#include <time.h>
#include "User_Setup.h"
#include "TFT_HX8357.h"
#include "board.h"
#include "cursor.h"
#define EASY
#define MEDIUM
#define HARD
#define VERY_HARD
#define INSANE
#define INHUMAN
#define SOLUTIONS
#include "generator.h"

void (*actions[])() = {
	board_move_cursor_down,
	board_move_cursor_left,
	board_move_cursor_right,
	board_move_cursor_up,
	board_toggle_number_at_cursor,
};

void setup(void) {
	randomSeed(analogRead(PA2));
	board_element* board = get_board();
	board_element* solution = get_solution();
	generate_board(board, solution, DIFF_HARD);
	// memcpy(board, solution, 81 * sizeof(board_element));
	board_find_first_valid_cursor_position();
	board_init();
	board_render();
}

void loop() {
	delay(1000);
	int choice = rand() % 5;
	void (*action)() = actions[choice];
	action();
	if (board_check_game_complete()) {
		board_show_winning_screen();
	} else {
		board_render();
	}
}