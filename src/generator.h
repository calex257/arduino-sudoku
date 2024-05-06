#define SOLUTIONS
#define NR_BOARDS 30
#include "board.h"

enum board_difficulty{
    DIFF_EASY,
    DIFF_MEDIUM,
    DIFF_HARD,
    DIFF_VERY_HARD,
    DIFF_INSANE,
    DIFF_INHUMAN
};

void generate_board(board_element *board, board_element *solution, board_difficulty diff);