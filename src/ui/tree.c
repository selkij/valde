#include "../include/tree.h"

/// @brief Initialize the tree window.
/// @param LINES Maximum Y dimension of the terminal.
/// @param COLS Maximum X dimension of the terminal.
/// @return The initialized tree window. NULL on failure.
WINDOW* tree_win_init(const int LINES, const int COLS) {
    WINDOW *tree_win = newwin(LINES - 1, COLS / 5, 1, 0);

    if(tree_win == NULL) {
        fprintf(stderr, "Error creating tree window.\n");
        return NULL;
    }

    refresh();
    wrefresh(tree_win);

    return tree_win;
}

/// @brief Add an entry to the tree window.
/// @param tree_win The tree window to add the entry to.
/// @param state The app state struct.
/// @param entry The entry to add.
/// @param index The index at which to add the entry.
void tree_add_entry(WINDOW* tree_win, const State* state, const struct entry* entry, const int index) {
    if(tree_win == NULL || entry == NULL) {
        fprintf(stderr, "tree_add_entry: Invalid parameters.\n");
        return;
    }

    const char* cwd = string_append_slash(state_get_cwd(state));
    const char* path = strcmp(strip_prefix(entry->path, cwd), "") == 0 ? cwd : strip_prefix(entry->path, cwd);

    if(entry_is_dir(entry)) {
        wattron(tree_win, A_BOLD);
        wattron(tree_win, COLOR_PAIR(2));
        mvwprintw(tree_win, index, 1, "%s\n", string_append_slash(path));
        wattroff(tree_win, COLOR_PAIR(2));
        wattroff(tree_win, A_BOLD);
    } else {
        mvwprintw(tree_win, index, 1, "%s\n", path);
    }

    refresh();
    wrefresh(tree_win);
}

void tree_list_entries(WINDOW* tree_win, const State* state, const struct entry* root_entry) {
    if(tree_win == NULL || root_entry == NULL) {
        fprintf(stderr, "tree_list_entries: Invalid parameters.\n");
        return;
    }

    if(entry_is_dir(root_entry) == false) {
        fprintf(stderr, "tree_list_entries: root_entry is not a directory.\n");
        return;
    }

    tree_add_entry(tree_win, state, root_entry, 0); // Add root entry first.

    for(size_t i = 1; i < root_entry->entry_count; i++) { // FIXME: makes the terminal go kaboom.
        tree_add_entry(tree_win, state, &root_entry->entries[i], (int) i);
    }
}

