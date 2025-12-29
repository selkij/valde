#include "../include/display.h"
#include "../include/tree.h"
#include "../include/content.h"

/// @brief Sets up color pairs for the terminal.
void screen_set_colors() {
  start_color();
  init_color(COLOR_RED, 1000, 596, 502); // Define a custom red color
  init_color(COLOR_CYAN, 502, 796, 1000); // Define a custom cyan color
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
}

/// @brief Clears and frees a window created with ncurses.
/// @param win The window to free.
void window_free(WINDOW* win) {
    wclear(win); // Also clear it's content.
    wrefresh(win);
    delwin(win);
}

/// @brief Initialize the main windows of the screen.
/// @param max_y Maximum Y dimension of the terminal.
/// @param max_x Maximum X dimension of the terminal.
Windows screen_init_windows(int max_y, int max_x) {
  WINDOW* tree = tree_win_init(max_y, max_x);

  Windows dummy = { .tree = NULL, .content = NULL };

  if(tree == NULL) {
      endwin();
      return dummy;
  }

  WINDOW* content = content_win_init(max_y, max_x);
  if(content == NULL) {
      window_free(tree);
      endwin();
      return dummy;
  }

  Windows windows = { .tree = tree, .content = content };
  return windows;
}

/// @brief Initialize the screen. Powered by ncurses.
/// @param state The app state struct.
/// @return Returns 0 on success, 1 on terminal color support failure, -1 on other failures.
int screen_init(State* state) {
  int max_y, max_x;

  // Initialize the screen
  if(initscr() == NULL) {
    fprintf(stderr, "Error initializing screen.\n");
    return TERMINAL_INIT_FAILURE;
  }

  if (!has_colors() || !can_change_color()) {
    endwin();
    printf("Your terminal does not support custom colors.\n");
    return TERMINAL_COLOR_UNSUPPORTED;
  }

  cbreak(); // Disable line buffering.
  noecho(); // Don't echo input characters.
  curs_set(0); // Hide cursor.
  keypad(stdscr, TRUE); // Enable function and arrow keys.

  getmaxyx(stdscr, max_y, max_x);

  screen_set_colors();
  Windows windows = screen_init_windows(max_y, max_x);
  
  attron(COLOR_PAIR(1));
  mvprintw(0,0,"valde File Manager - %s", state_get_cwd(state));
  attroff(COLOR_PAIR(1));

  struct entry test = entry_populate(state_get_cwd(state));
  entry_populate_dir(&test);
  tree_list_entries(windows.tree, state, &test);

  getch();

  window_free(windows.tree);
  window_free(windows.content);
  endwin();

  return 0;
}