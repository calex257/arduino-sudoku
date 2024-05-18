#include "state.h"

static int state = 0;

int get_state() {
    return state;
}

void set_state(int value) {
    state = value;
}