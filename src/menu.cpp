#include "menu.h"
#include "TFT_HX8357.h"
#include "generator.h"
#include "board.h"
#include "difficulty.h"

static TFT_HX8357* const scr = get_tft();
static char cursor = 0;
static char prev_cursor = 0;
static volatile char cursor_has_changed = 0;

static char difficulty_prompts[6][20] = {
"EASY",
"MEDIUM",
"HARD",
// "VERY HARD",
// "INSANE",
// "INHUMAN"
};

char get_menu_cursor_position() {
    return cursor;
}

void update_menu_cursor(int mode) {
    if (mode != MENU_UP && mode != MENU_DOWN) {
        return;
    }

    int increment = mode;
    prev_cursor = cursor;
    if ((cursor <= 0 && mode == MENU_UP) || (cursor >= 2 && mode == MENU_DOWN)) {
        return;
    }
    cursor += increment;
    cursor %= 3;
    cursor_has_changed = 1;
}

void handle_menu() {
    if (!cursor_has_changed) {
        return;
    }
    scr->setTextColor(TFT_RED, TFT_GREEN);
    scr->drawString(difficulty_prompts[prev_cursor], 20, 50 * prev_cursor + 100, 4);
    scr->setTextColor(TFT_RED, TFT_YELLOW);
    scr->drawString(difficulty_prompts[cursor], 20, 50 * cursor + 100, 4);
    cursor_has_changed = 0;
}

void display_menu() {
    scr->fillScreen(TFT_BLUE);
    for (int i = 0; i < 3; i++) {
        scr->setTextColor(TFT_RED, TFT_WHITE);
        scr->drawString(difficulty_prompts[i], 20, 50 * i + 100, 4);
    }
}