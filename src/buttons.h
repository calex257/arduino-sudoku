#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

#define UP_BUTTON_PIN 20
#define CENTER_BUTTON_PIN 3
#define DOWN_BUTTON_PIN 2
#define LEFT_BUTTON_PIN 18
#define RIGHT_BUTTON_PIN 19

#define UP_BUTTON_FLAG 0
#define CENTER_BUTTON_FLAG 1
#define DOWN_BUTTON_FLAG 2
#define LEFT_BUTTON_FLAG 3
#define RIGHT_BUTTON_FLAG 4

const int button_flags[5] = {
    0x1, 0x2, 0x4, 0x8, 0x10
};

void handle_buttons();

bool action_button_up();

bool action_button_center();

bool action_button_down();

bool action_button_left();

bool action_button_right();

void transition_to_game_state();

bool check_button_flag_is_set(int flag);

void set_button_flag(int flag);

void clear_button_flag(int flag);

void clear_button_flag_register();

void buttons_init();

void transition_to_final_state(int state);

#endif