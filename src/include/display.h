#ifndef VALDE_DISPLAY_H
#define VALDE_DISPLAY_H

#include <curses.h>
#include "state.h"
#include "entry.h"

#define TERMINAL_COLOR_UNSUPPORTED 1
#define TERMINAL_INIT_FAILURE (-1)

typedef struct Windows {
    WINDOW* tree;
    WINDOW* content;
} Windows;

int screen_init(State* state);

#endif /* VALDE_DISPLAY_H */
