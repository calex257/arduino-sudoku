#ifndef TIMER_H

#define TIMER_H
#include "TM1637Display.h"

#define CLK 8
#define DIO 9

TM1637Display* get_display();

int get_counter();

int get_second_counter_value();

void timer_init();

void set_counter(int seconds);

bool get_timer_is_modified();

void set_timer_is_modified(bool value);

void update_display();

#endif