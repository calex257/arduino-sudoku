#ifndef MENU_H
#define MENU_H

#define MENU_UP -1
#define MENU_DOWN 1

void display_menu();
void update_menu_cursor(int mode);
void handle_menu();
char get_menu_cursor_position();

#endif