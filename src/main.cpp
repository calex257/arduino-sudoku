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
#include "buttons.h"
#include "timer.h"

#define BUZZER_PIN A0

#define RED_PIN A1

#define GREEN_PIN A2

#define BLUE_PIN A3

bool (*actions[])() = {
	board_move_cursor_up,
	board_toggle_number_at_cursor,
	board_move_cursor_down,
	board_move_cursor_left,
	board_move_cursor_right,
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

void setup(void) {
	randomSeed(analogRead(PA2));
	board_element* board = get_board();
	board_element* solution = get_solution();
	generate_board(board, solution, DIFF_HARD);
	board_find_first_valid_cursor_position();
	board_init();
	board_render();
	timer_init();
	buttons_init();
	Serial.begin(9600);
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);
	set_counter(300);
}

void handle_timer() {
	if (get_timer_is_modified()) {
		if (get_counter() < 0) {
			scr->fillScreen(TFT_RED);
			set_timer_is_modified(false);
		}
		else {
			update_display();
			set_timer_is_modified(false);
		}
	}
}

void handle_buttons() {
	bool button_action_performed = false;

	for (int i = 0; i < 5; i++) {
		if (check_button_flag_is_set(button_flags[i])) {
			clear_button_flag(button_flags[i]);
			button_action_performed = actions[i]();
			break;
		}
	}

	if(button_action_performed) {
		board_render();
	}
}

void loop() {
	analogWrite(RED_PIN, 255);
	analogWrite(GREEN_PIN, 255);
	analogWrite(BLUE_PIN, 255);

	handle_timer();
	handle_buttons();
}