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

int counter = 0;
unsigned int colors[] = {
	TFT_BLUE,
	TFT_GREEN, 
	TFT_RED,
	TFT_WHITE,
	TFT_YELLOW,
	TFT_PURPLE,
	TFT_PINK
};
const int limit = sizeof(colors) / sizeof(int);
TFT_HX8357* scr = get_tft();

void init_timer() {
	sei();
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1C = 0;
	TCNT1 = 0;
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
	TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << WGM12);
	OCR1A = 15625;
	TIMSK1 = 0;
	TIMSK1 |= (1 << OCIE1A);
}

void setup(void) {
	randomSeed(analogRead(PA2));
	board_element* board = get_board();
	board_element* solution = get_solution();
	generate_board(board, solution, DIFF_HARD);
	// memcpy(board, solution, 81 * sizeof(board_element));
	board_find_first_valid_cursor_position();
	board_init();
	board_render();
    // scr->begin();
	// init_timer();
	// scr->fillScreen(TFT_CYAN);
}

ISR(TIMER1_COMPA_vect) {
	scr->fillScreen(colors[counter]);
	counter ++;
	counter %= limit;
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