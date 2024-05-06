#ifndef CURSOR_H
#define CURSOR_H

typedef struct {
    uint8_t row;
    uint8_t col;
} board_cursor;

void set_cursor(uint8_t row, uint8_t col);
board_cursor* get_cursor();

#endif