#include <stdlib.h>
#include "board.h"
#include "generator.h"
#include "boards/games.h"
#include "boards/solutions.h"

void generate_easy_board(board_element *board, board_element *solution)
{
    int index = rand() % NR_BOARDS;
    board_element *selected_board = easy_boards[index];
    memcpy(board, selected_board, 81 * sizeof(board_element));
    board_element *selected_solution = easy_boards_solutions[index];
    memcpy(solution, selected_solution, 81 * sizeof(board_element));
}

void generate_medium_board(board_element *board, board_element *solution)
{
    int index = rand() % NR_BOARDS;
    board_element *selected_board = medium_boards[index];
    memcpy(board, selected_board, 81 * sizeof(board_element));
    board_element *selected_solution = medium_boards_solutions[index];
    memcpy(solution, selected_solution, 81 * sizeof(board_element));
}

void generate_hard_board(board_element *board, board_element *solution)
{
    int index = random(0, NR_BOARDS);
    board_element *selected_board = hard_boards[index];
    memcpy(board, selected_board, 81 * sizeof(board_element));
    board_element *selected_solution = hard_boards_solutions[index];
    memcpy(solution, selected_solution, 81 * sizeof(board_element));
}

// void generate_very_hard_board(board_element *board, board_element *solution)
// {
//     int index = random(0, NR_BOARDS);
//     board_element *selected_board = very_hard_boards[index];
//     memcpy(board, selected_board, 81 * sizeof(board_element));
//     board_element *selected_solution = very_hard_boards_solutions[index];
//     memcpy(solution, selected_solution, 81 * sizeof(board_element));
// }

// void generate_insane_board(board_element *board, board_element *solution)
// {
//     int index = random(0, NR_BOARDS);
//     board_element *selected_board = insane_boards[index];
//     memcpy(board, selected_board, 81 * sizeof(board_element));
//     board_element *selected_solution = insane_boards_solutions[index];
//     memcpy(solution, selected_solution, 81 * sizeof(board_element));
// }

// void generate_inhuman_board(board_element *board, board_element *solution)
// {
//     int index = random(0, NR_BOARDS);
//     board_element *selected_board = inhuman_boards[index];
//     memcpy(board, selected_board, 81 * sizeof(board_element));
//     board_element *selected_solution = inhuman_boards_solutions[index];
//     memcpy(solution, selected_solution, 81 * sizeof(board_element));
// }

void generate_board(board_element *board, board_element *solution, board_difficulty diff)
{
    switch (diff)
    {
    case DIFF_EASY:
        generate_easy_board(board, solution);
        break;
    case DIFF_MEDIUM:
        generate_medium_board(board, solution);
        break;
    case DIFF_HARD:
        generate_hard_board(board, solution);
        break;
    // case DIFF_VERY_HARD:
    //     generate_very_hard_board(board, solution);
    //     break;
    // case DIFF_INSANE:
    //     generate_insane_board(board, solution);
    //     break;
    // case DIFF_INHUMAN:
    //     generate_inhuman_board(board, solution);
    //     break;
    default:
        break;
    }
}