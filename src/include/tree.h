#ifndef TREE
#define TREE

#include <curses.h>
#include "state.h"
#include "entry.h"
#include "string_utils.h"

WINDOW* tree_win_init(int LINES, int COLS);
void tree_add_entry(WINDOW* tree_win, State* state, struct entry* entry, int index);
void tree_list_entries(WINDOW* tree_win, State* state, struct entry* root_entry);

#endif /* TREE */
