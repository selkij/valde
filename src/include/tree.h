#ifndef VALDE_TREE_H
#define VALDE_TREE_H

#include <curses.h>
#include "state.h"
#include "entry.h"
#include "string_utils.h"

WINDOW* tree_win_init(int LINES, int COLS);
void tree_add_entry(WINDOW* tree_win, const State* state, const struct entry* entry, int index);
void tree_list_entries(WINDOW* tree_win, const State* state, const struct entry* root_entry);

#endif // VALDE_TREE_H
