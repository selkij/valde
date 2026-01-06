#include "../include/content.h"

/// @brief Initialize the content window.
/// @param LINES Maximum Y dimension of the terminal.
/// @param COLS Maximum X dimension of the terminal.
/// @return The initialized content window. NULL on failure.
WINDOW* content_win_init(const int LINES, const int COLS) {
    WINDOW *content_win = newwin(LINES - 1, COLS - COLS / 5, 1, COLS / 5);

    if(content_win == NULL) {
        fprintf(stderr, "Error creating content window.\n");
        return NULL;
    }

    wattron(content_win, COLOR_PAIR(1));
    box(content_win, 0 , 0);
    wattroff(content_win, COLOR_PAIR(1));

    refresh();
    wrefresh(content_win);

    return content_win;
}