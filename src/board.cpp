#include <stdint.h>
#include "TFT_HX8357.h"
#include "board.h"
#include "cursor.h"
#include "difficulty.h"
#include "element.h"
#include "led.h"
#include "state.h"
#include "buttons.h"

const int x_padding = (SCREEN_WIDTH / 9 - TEXT_FONT_HEIGHT / 2) / 2;
const int y_padding = (SCREEN_WIDTH / 9 - TEXT_FONT_HEIGHT) / 2;

static TFT_HX8357 tft = TFT_HX8357();

TFT_HX8357* get_tft() {
    return &tft;
}

static board_element board[81];

board_element* get_board() {
    return (board_element*)board;
}

static board_element solution[81];

board_element* get_solution() {
    return (board_element*)solution;
}

void tft_init() {
    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
}

void board_init(board_difficulty difficulty) {
    generate_board(board, solution, difficulty);
    board_find_first_valid_cursor_position();
}

void board_set_tile_as_wrong() {
    board_cursor* current_cursor = get_cursor();
    uint8_t current_col = current_cursor->col;
    uint8_t current_row = current_cursor->row;
    board[current_row * BOARD_WIDTH + current_col].is_wrong = 1;
}

boolean board_check_tile_at_cursor() {
    board_cursor* current_cursor = get_cursor();
    uint8_t current_col = current_cursor->col;
    uint8_t current_row = current_cursor->row;
    return board[current_row * BOARD_WIDTH + current_col].number == 0 || board[current_row * BOARD_WIDTH + current_col].number == solution[current_row * BOARD_WIDTH + current_col].number;
}

bool board_move_cursor_left() {
    board_cursor* current_cursor = get_cursor();
    uint8_t current_col = current_cursor->col;
    uint8_t current_row = current_cursor->row;
    if (current_col == 0) {
        return false;
    }
    board[current_row * BOARD_WIDTH + current_col].is_cursor_on = 0;
    current_col --;
    board[current_row * BOARD_WIDTH + current_col].is_cursor_on = 1;
    if (current_col != current_cursor->col && !board_check_tile_at_cursor()) {
        board_set_tile_as_wrong();
    }
    set_cursor(current_row, current_col);
    board_update(true);
    return true;
}

bool board_move_cursor_right() {
    board_cursor* current_cursor = get_cursor();
    uint8_t current_col = current_cursor->col;
    uint8_t current_row = current_cursor->row;
    if (current_col == BOARD_WIDTH - 1) {
        return false;
    }
    board[current_row * BOARD_WIDTH + current_col].is_cursor_on = 0;
    current_col ++;
    board[current_row * BOARD_WIDTH + current_col].is_cursor_on = 1;
    if (current_col != current_cursor->col && !board_check_tile_at_cursor()) {
        board_set_tile_as_wrong();
    }
    set_cursor(current_row, current_col);
    board_update(true);
    return true;
}

bool board_move_cursor_up() {
    board_cursor* current_cursor = get_cursor();
    uint8_t current_col = current_cursor->col;
    uint8_t current_row = current_cursor->row;
    if (current_row == 0) {
        return false;
    }
    board[current_row * BOARD_WIDTH + current_col].is_cursor_on = 0;
    current_row --;
    board[current_row * BOARD_WIDTH + current_col].is_cursor_on = 1;
    if (current_row != current_cursor->row && !board_check_tile_at_cursor()) {
        board_set_tile_as_wrong();
    }
    set_cursor(current_row, current_col);
    board_update(true);
    return true;
}

bool board_move_cursor_down() {
    board_cursor* current_cursor = get_cursor();
    uint8_t current_col = current_cursor->col;
    uint8_t current_row = current_cursor->row;
    if (current_row == BOARD_WIDTH - 1) {
        return false;
    }
    board[current_row * BOARD_WIDTH + current_col].is_cursor_on = 0;
    current_row ++;
    board[current_row * BOARD_WIDTH + current_col].is_cursor_on = 1;
    if (current_row != current_cursor->row && !board_check_tile_at_cursor()) {
        board_set_tile_as_wrong();
    }
    set_cursor(current_row, current_col);
    board_update(true);
    return true;
}

bool board_toggle_number_at_cursor() {
    board_cursor* current_cursor = get_cursor();
    uint8_t current_col = current_cursor->col;
    uint8_t current_row = current_cursor->row;
    if (board[current_row * BOARD_WIDTH + current_col].is_fixed == 1) {
        return false;
    }
    board[current_row * BOARD_WIDTH + current_col].number = (board[current_row * BOARD_WIDTH + current_col].number + 1) % 10;
    board[current_row * BOARD_WIDTH + current_col].is_wrong = 0;
    board_update(false);
    return true;
}

void board_draw_grid_outline() {
    for (int i = 0; i < 9; i++) {
        int value = i * SCREEN_WIDTH / BOARD_WIDTH;
        int color = i % 3 == 0 ? ACCENT_LINE_COLOR : NORMAL_LINE_COLOR;
        tft.drawFastVLine(value, 0, SCREEN_WIDTH, color);
        tft.drawFastHLine(0, value, SCREEN_WIDTH, color);
    }
    tft.drawFastVLine(SCREEN_WIDTH - 1, 0, SCREEN_WIDTH, ACCENT_LINE_COLOR);
    tft.drawFastHLine(0, SCREEN_WIDTH, SCREEN_WIDTH, ACCENT_LINE_COLOR);
}

void board_draw_numbers() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            draw_element_at_position(i, j);
            // uint8_t board_index = i * BOARD_WIDTH + j;
            // board_element elem = board[board_index];
            // uint16_t x_value = j * SCREEN_WIDTH / 9 + x_padding;
            // uint16_t y_value = i * SCREEN_WIDTH / 9 + y_padding;
            // uint16_t fgcolor = get_fgcolor_from_element(elem);
            // uint16_t bgcolor = elem.is_cursor_on ? CURSOR_COLOR : NO_CURSOR_COLOR;
            // tft.setTextColor(fgcolor, bgcolor);
            // if (elem.number != 0) {
            //     tft.drawNumber(elem.number, x_value, y_value, 4);
            // }
            // else if (!elem.is_fixed && elem.is_cursor_on == 1) {
            //     tft.drawChar('_', x_value, y_value, 4);
            // }
        }
    }
}

void board_find_first_valid_cursor_position() {
    board_cursor* current_cursor = get_cursor();
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i * BOARD_WIDTH + j].is_fixed == 0) {
                board[i * BOARD_WIDTH + j].is_cursor_on = 1;
                current_cursor->row = i;
                current_cursor->col = j;
                return;
            }
        }
    }
}

int board_count_wrong_numbers() {
    int counter = 0;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            int index = i * BOARD_WIDTH + j;
            if (board[index].is_fixed == 0 && board[index].number != solution[index].number) {
                counter ++;
            }
        }
    }
    return counter;
}

void draw_element_at_position(int row, int col) {
    uint8_t board_index = row * BOARD_WIDTH + col;
    board_element elem = board[board_index];
    uint16_t x_value = col * SCREEN_WIDTH / 9 + x_padding;
    uint16_t y_value = row * SCREEN_WIDTH / 9 + y_padding;
    uint16_t fgcolor = get_fgcolor_from_element(elem);
    uint16_t bgcolor = elem.is_cursor_on ? CURSOR_COLOR : NO_CURSOR_COLOR;
    tft.setTextColor(fgcolor, bgcolor);
    if (elem.number != 0) {
        tft.drawNumber(elem.number, x_value, y_value, 4);
    }
    else if (!elem.is_fixed && elem.is_cursor_on == 1) {
        tft.drawChar('_', x_value, y_value, 4);
    } else {
        tft.setTextColor(fgcolor, TFT_WHITE);
        tft.drawString("   ", x_value, y_value, 4);
    }
}

void board_update(boolean count_wrong_numbers) {
    int prev_row, prev_col, row, col;
    board_cursor* prev_cursor = get_prev_cursor();
    prev_row = prev_cursor->row;
    prev_col = prev_cursor->col;
    draw_element_at_position(prev_row, prev_col);
    board_cursor* cursor = get_cursor();
    row = cursor->row;
    col = cursor->col;
    draw_element_at_position(row, col);
    if (count_wrong_numbers) {
        int wrong_count = board_count_wrong_numbers();
        set_wrong_count(wrong_count);
        if (wrong_count == 0) {
            // set_state(WIN_STATE);
            transition_to_final_state(WIN_STATE);
        }
    }
}

void board_show_winning_screen() {
    tft.fillScreen(TFT_GREEN);
}

void board_render() {
    tft.fillScreen(TFT_WHITE);
    board_draw_grid_outline();
    board_draw_numbers();
}