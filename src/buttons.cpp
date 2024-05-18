#include "buttons.h"
#include "cursor.h"
#include "board.h"
#include "state.h"

#define ON_UP_BUTTON_PRESS ISR(INT1_vect)
#define ON_RIGHT_BUTTON_PRESS ISR(INT2_vect)
#define ON_LEFT_BUTTON_PRESS ISR(INT3_vect)
#define ON_DOWN_BUTTON_PRESS ISR(INT4_vect)
#define ON_CENTER_BUTTON_PRESS ISR(INT5_vect)

static volatile int button_flags_register = 0;

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

ON_UP_BUTTON_PRESS {
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[UP_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}

ON_RIGHT_BUTTON_PRESS {
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[RIGHT_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}

ON_LEFT_BUTTON_PRESS {
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[LEFT_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}

ON_DOWN_BUTTON_PRESS {
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[DOWN_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}

ON_CENTER_BUTTON_PRESS {
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 150) {
		set_button_flag(button_flags[CENTER_BUTTON_FLAG]);
	}
	last_interrupt_time = interrupt_time;
}