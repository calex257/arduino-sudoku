#ifndef STATE_H
#define STATE_H

#define MENU_STATE 0
#define GAME_STATE 1
#define WIN_STATE 2
#define LOSE_STATE 3

int get_state();
void set_state(int value);

#endif