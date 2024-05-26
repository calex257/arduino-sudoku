#include "buttons.h"
#include "cursor.h"
#include "board.h"
#include "state.h"
#include "menu.h"
#include "timer.h"
#include "generator.h"
#include "led.h"
#include "buzzer.h"

#define ON_UP_BUTTON_PRESS ISR(INT1_vect)
#define ON_RIGHT_BUTTON_PRESS ISR(INT2_vect)
#define ON_LEFT_BUTTON_PRESS ISR(INT3_vect)
#define ON_DOWN_BUTTON_PRESS ISR(INT4_vect)
#define ON_CENTER_BUTTON_PRESS ISR(INT5_vect)



static bool (*actions[])() = {
	action_button_up,
	action_button_center,
	action_button_down,
	action_button_left,
	action_button_right,
};
static volatile int button_flags_register = 0;

bool action_button_up() {
	int state = get_state();
	switch (state) {
	case MENU_STATE:
		update_menu_cursor(MENU_UP);
		break;
	case GAME_STATE:
		board_move_cursor_up();
		break;
	case WIN_STATE:
	case LOSE_STATE:
		setup();
	default:
		break;
	}
}
bool action_button_center() {
	int state = get_state();

	switch (state) {
	case MENU_STATE:
		transition_to_game_state();
		break;
	case GAME_STATE:
		board_toggle_number_at_cursor();
		break;
	case WIN_STATE:
	case LOSE_STATE:
		setup();
	default:
		break;
	}
}
bool action_button_down() {
	int state = get_state();

	switch (state) {
	case MENU_STATE:
		update_menu_cursor(MENU_DOWN);
		break;
	case GAME_STATE:
		board_move_cursor_down();
		break;
	case WIN_STATE:
	case LOSE_STATE:
		setup();
	default:
		break;
	}
}
bool action_button_left() {

	int state = get_state();

	switch (state) {
	case MENU_STATE:
		break;
	case GAME_STATE:
		board_move_cursor_left();
		break;
	case WIN_STATE:
	case LOSE_STATE:
		setup();
	default:
		break;
	}
}
bool action_button_right() {

	int state = get_state();

	switch (state) {
	case MENU_STATE:
		break;
	case GAME_STATE:
		board_move_cursor_right();
		break;
	case WIN_STATE:
	case LOSE_STATE:
		setup();
	default:
		break;
	}
}

void transition_to_game_state() {
	board_difficulty difficulty = (board_difficulty) get_menu_cursor_position();
	set_state(GAME_STATE);
	set_counter(difficulty_times[difficulty]);
	set_led_increment(150.0 / missing_squares_per_difficulty[difficulty]);
	BLUE_VALUE = 0;
	RED_VALUE = 150;
	GREEN_VALUE = 0;
	timer_init();
	board_init(difficulty);
	board_render();
}

void transition_to_final_state(int state) {
	TFT_HX8357* scr = get_tft();
	disable_timer_interrupt();
	if (state == WIN_STATE) {
		scr->fillScreen(TFT_GREEN);
		int initial_time = get_second_counter_value();
		int actual_time = get_counter();
		set_counter(initial_time - actual_time);
		update_display();
		buzzer_victory_chant();
	} else {
		scr->fillScreen(TFT_RED);
		buzzer_defeat_cry();
	}
	set_state(state);
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
}

bool check_button_flag_is_set(int flag) {
	return (button_flags_register & flag) != 0;
}

void set_button_flag(int flag) {
	button_flags_register |= flag;
}

void clear_button_flag(int flag) {
	button_flags_register &= ~(flag);
}

void clear_button_flag_register() {
	button_flags_register = 0;
}

static inline void init_button_interrupts() {
	EICRA = 0;
	EICRB = 0;
	EICRA |= (1 << ISC10) | (1 << ISC20) | (1 << ISC30) | (1 << ISC11) | (1 << ISC21) | (1 << ISC31);
	EICRB |= (1 << ISC40) | (1 << ISC50) | (1 << ISC41) | (1 << ISC51);
	EIMSK |= (1 << INT1) | (1 << INT2) | (1 << INT3) | (1 << INT4) | (1 << INT5);
}

void buttons_init() {
	pinMode(UP_BUTTON_PIN, INPUT);
	pinMode(CENTER_BUTTON_PIN, INPUT);
	pinMode(DOWN_BUTTON_PIN, INPUT);
	pinMode(LEFT_BUTTON_PIN, INPUT);
	pinMode(RIGHT_BUTTON_PIN, INPUT);
	init_button_interrupts();
}

ON_UP_BUTTON_PRESS{
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[UP_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}

ON_RIGHT_BUTTON_PRESS{
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[RIGHT_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}

ON_LEFT_BUTTON_PRESS{
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[LEFT_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}

ON_DOWN_BUTTON_PRESS{
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[DOWN_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}

ON_CENTER_BUTTON_PRESS{
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[CENTER_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}