#include <Arduino.h>
#include <SoftwareSerial.h>
#include <time.h>
#include "User_Setup.h"
#include "TFT_HX8357.h"
#include "board.h"
#include "cursor.h"
#include "buzzer.h"
#define EASY
#define MEDIUM
#define HARD
// #define VERY_HARD
// #define INSANE
// #define INHUMAN
#define SOLUTIONS
#include "generator.h"
#include "buttons.h"
#include "timer.h"
#include "menu.h"
#include "state.h"
#include "led.h"
#define BUZZER_PIN A0

#define RED_PIN A1

#define GREEN_PIN A2

#define BLUE_PIN A3

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
	pinMode(BUZZER_PIN, OUTPUT);
	buzzer_intro_song();
	randomSeed(analogRead(PA2));
	srand(analogRead(PA2));
	// board_element* board = get_board();
	// board_element* solution = get_solution();
	// generate_board(board, solution, DIFF_HARD);
	// board_find_first_valid_cursor_position();
	tft_init();
	// board_render();
	// timer_init();
	timer_clear();
	init_led_pwm();
	BLUE_VALUE = 255;
	RED_VALUE = 0;
	GREEN_VALUE = 0;
	buttons_init();
	display_menu();
	set_state(MENU_STATE);
	Serial.begin(9600);
	// pinMode(RED_PIN, OUTPUT);
	// pinMode(GREEN_PIN, OUTPUT);
	// pinMode(BLUE_PIN, OUTPUT);
	// set_counter(300);
}

void loop() {
	// analogWrite(RED_PIN, 255);
	// analogWrite(GREEN_PIN, 255);
	// analogWrite(BLUE_PIN, 255);

	int state = get_state();
	handle_buttons();
	switch (state) {
		case MENU_STATE:
			handle_menu();
			break;
		case GAME_STATE:
			if (get_wrong_flag()) {
				buzzer_error_chime();
				set_wrong_flag(0);
			}
			handle_timer();
			break;
		case LOSE_STATE:
		case WIN_STATE:
			break;
	}
}