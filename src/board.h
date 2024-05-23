#ifndef BOARD_H
#define BOARD_H

#include "TFT_HX8357.h"
#include "difficulty.h"
#include "element.h"

#define SCREEN_WIDTH 320
#define BOARD_WIDTH  9
#define NORMAL_LINE_COLOR TFT_DARKGREY
#define ACCENT_LINE_COLOR TFT_BLACK
#define FIXED_TEXT_COLOR TFT_BLACK
#define CURSOR_TEXT_COLOR TFT_CYAN
#define ADDED_TEXT_COLOR TFT_BLUE
#define CURSOR_COLOR TFT_ORANGE
#define NO_CURSOR_COLOR TFT_WHITE
#define TEXT_FONT_HEIGHT 26
#define WRONG_TEXT_COLOR TFT_RED

// #define SOLUTIONS
// #define NR_BOARDS 30
// #include "board.h"

// enum board_difficulty{
//     DIFF_EASY,
//     DIFF_MEDIUM,
//     DIFF_HARD,
//     DIFF_VERY_HARD,
//     DIFF_INSANE,
//     DIFF_INHUMAN
// };

// typedef struct {
//     unsigned padding : 1;
//     unsigned is_cursor_on : 1;
//     unsigned is_wrong : 1;
//     unsigned is_fixed : 1;
//     unsigned number : 4;
// } board_element;



static inline uint16_t get_fgcolor_from_element(board_element elem) {
    return elem.is_fixed ? FIXED_TEXT_COLOR : (elem.is_wrong ? WRONG_TEXT_COLOR : (elem.is_cursor_on ? CURSOR_TEXT_COLOR : ADDED_TEXT_COLOR));
}

board_element* get_board();
board_element* get_solution();
TFT_HX8357* get_tft();
void tft_init();
void board_init(board_difficulty diff);
void generate_board(board_element *board, board_element *solution, board_difficulty diff);
void board_draw_grid_outline();
void board_draw_numbers();
void board_render();
bool board_move_cursor_left();
bool board_move_cursor_right();
bool board_move_cursor_up();
bool board_move_cursor_down();
bool board_toggle_number_at_cursor();
void board_find_first_valid_cursor_position();
void board_show_winning_screen();
boolean board_check_game_complete();
#endif