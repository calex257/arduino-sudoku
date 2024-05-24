#ifndef LED_H
#define LED_H

#define GREEN_VALUE OCR3A

#define RED_VALUE OCR4A

#define BLUE_VALUE OCR4B

void init_led_pwm();
void set_led_increment(float val);
float get_led_increment();
void set_wrong_count(int correct_count);

#endif