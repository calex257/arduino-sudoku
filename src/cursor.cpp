#include <stdint.h>
#include "cursor.h"

static board_cursor cursor = {.row = 0, .col = 0};

board_cursor* get_cursor() {
    return &cursor;
}

void set_cursor(uint8_t row, uint8_t col) {
    cursor.row = row;
    cursor.col = col;
}