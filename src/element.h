#ifndef ELEMENT_H
#define ELEMENT_H

typedef struct {
    unsigned padding : 1;
    unsigned is_cursor_on : 1;
    unsigned is_wrong : 1;
    unsigned is_fixed : 1;
    unsigned number : 4;
} board_element;
#endif