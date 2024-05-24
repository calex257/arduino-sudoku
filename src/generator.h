#ifndef GENERATOR_H
#define GENERATOR_H
#define SOLUTIONS
#define NR_BOARDS 10
// #include "board.h"
#include "element.h"
#include "difficulty.h"

const int difficulty_times[] = {
    300,
    600,
    900,
};

const int missing_squares_per_difficulty[] = {
    19,
    28,
    37,
};

void generate_board(board_element *board, board_element *solution, board_difficulty diff);

#endif