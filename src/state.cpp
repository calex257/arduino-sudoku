#include "state.h"

static volatile int state = 0;

int get_state() {
    return state;
}

void set_state(int value) {
    state = value;
}