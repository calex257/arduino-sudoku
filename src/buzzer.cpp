#include "buzzer.h"
#include "Arduino.h"


void buzzer_error_chime() {
    tone(BUZZER_PIN, 440, 100);
}

void buzzer_victory_chant() {
    tone(BUZZER_PIN, 330, 250);
    delay(112);
    tone(BUZZER_PIN, 350, 250);
    delay(112);
    tone(BUZZER_PIN, 330, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);

    tone(BUZZER_PIN, 330, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    tone(BUZZER_PIN, 350, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    
    tone(BUZZER_PIN, 350, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    tone(BUZZER_PIN, 392, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    
    tone(BUZZER_PIN, 392, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    tone(BUZZER_PIN, 350, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    
    tone(BUZZER_PIN, 350, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    tone(BUZZER_PIN, 220, 250);
    delay(112);
    tone(BUZZER_PIN, 261, 250);
    delay(112);
    
    tone(BUZZER_PIN, 330, 250);
    delay(112);
    tone(BUZZER_PIN, 350, 250);
    delay(112);
    tone(BUZZER_PIN, 330, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    
    tone(BUZZER_PIN, 330, 250);
    delay(112);
    tone(BUZZER_PIN, 193, 250);
    delay(112);
    tone(BUZZER_PIN, 330, 250);
    delay(112);
    tone(BUZZER_PIN, 350, 250);
    delay(112);
}
void buzzer_defeat_cry() {
    tone(BUZZER_PIN, 440, 260);
    delay(100);
    tone(BUZZER_PIN, 523, 260);
    delay(130);
    tone(BUZZER_PIN, 587, 100);
    delay(90);
    tone(BUZZER_PIN, 700, 100);
    delay(90);
    tone(BUZZER_PIN, 587, 100);
    delay(90);
    tone(BUZZER_PIN, 523, 150);
    delay(130);
    tone(BUZZER_PIN, 587, 300);
    delay(300);

    
    tone(BUZZER_PIN, 700, 350);
    delay(25);
    tone(BUZZER_PIN, 720, 350);
    delay(25);
    tone(BUZZER_PIN, 740, 350);
    delay(350);
    tone(BUZZER_PIN, 700, 260);
    delay(250);
    tone(BUZZER_PIN, 660, 260);
    delay(250);
    tone(BUZZER_PIN, 523, 250);
    delay(250);
    tone(BUZZER_PIN, 587, 300);
    delay(200);
}

void buzzer_intro_song() {
    tone(BUZZER_PIN, 700, 428);
	delay(214);
	tone(BUZZER_PIN, 524, 214);
	delay(642);
	tone(BUZZER_PIN, 800, 428);
	delay(214);
	tone(BUZZER_PIN, 524, 214);
	delay(642);
	tone(BUZZER_PIN, 780, 428);
	delay(214);
	tone(BUZZER_PIN, 524, 214);
	delay(642);
	tone(BUZZER_PIN, 700, 428);
	delay(214);
	tone(BUZZER_PIN, 524, 214);
	delay(214);
	tone(BUZZER_PIN, 1000, 214);
}