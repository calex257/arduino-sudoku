#include "led.h"
#include "board.h"

static float led_increment = 0;

void init_led_pwm() {
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	TCCR3A = 0;
    TCCR3B = 0;
	TCCR3A |= (1 << WGM30);
	TCCR3B |= (1 << WGM32);
	TCCR3A |= (1 << COM3A1);
	TCCR3B |= (1 << CS31) | (1 << CS30);
	OCR3A = 0;
	TCCR4A = 0;
    TCCR4B = 0;
	TCCR4A |= (1 << WGM40);
	TCCR4B |= (1 << WGM42);
	TCCR4A |= (1 << COM4A1);
	TCCR4A |= (1 << COM4B1);
	TCCR4B |= (1 << CS41) | (1 << CS40);
	OCR4A = 0;
	OCR4B = 0;
}

void set_led_increment(float val) {
    led_increment = val;
}

float get_led_increment() {
    return led_increment;
}

void set_wrong_count(int correct_count) {
    RED_VALUE = (int)(led_increment * correct_count);
    GREEN_VALUE = (int)(150 - led_increment * correct_count);
    // Serial.print(GREEN_VALUE);
    // Serial.print(" ");
    // Serial.print(RED_VALUE);
    // Serial.print("\n");
}