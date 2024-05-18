#include "Arduino.h"
#include "timer.h"


static TM1637Display display(CLK, DIO);
static volatile int second_counter;
static int set_second_counter_value;
static volatile bool timer_is_modified;

static inline void enable_timer_interrupts() {
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

void timer_init() {
	display.setBrightness(0x0f);
    enable_timer_interrupts();
}

TM1637Display* get_display() {
    return &display;
}

int get_counter() {
    return second_counter;
}

ISR(TIMER1_COMPA_vect) {
	if (second_counter >= 0) {
		second_counter --;
        timer_is_modified = true;
	}
}

void set_counter(int seconds) {
    second_counter = seconds;
    set_second_counter_value = seconds;
}

int get_second_counter_value() {
    return set_second_counter_value;
}

bool get_timer_is_modified() {
    return timer_is_modified;
}

void set_timer_is_modified(bool value) {
    timer_is_modified = value;
}

void update_display() {
    int mins = second_counter / 60;
    int secs = second_counter % 60;
    display.showNumberDecEx(mins * 100 + secs,0b01000000, true);
}
