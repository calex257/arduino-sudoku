#include <stdint.h>
#include "cursor.h"

static board_cursor cursor = {.row = 0, .col = 0};
static board_cursor prev_cursor = {.row = 0, .col = 0};

board_cursor* get_cursor() {
    return &cursor;
}

board_cursor* get_prev_cursor() {
    return &prev_cursor;
}

void set_cursor(uint8_t row, uint8_t col) {
    prev_cursor.row = cursor.row;
    prev_cursor.col = cursor.col;
    cursor.row = row;
    cursor.col = col;
}