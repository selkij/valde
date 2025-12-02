#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "include/entry.h"

int main() {
  struct entry entry_test;

  entry_test = populate_entry("/home/lain/");
  int dir_result = populate_directory_entry(&entry_test);

  if(dir_result == 1) return 1;
  entry_info(&entry_test);

  free(entry_test.entries);

  return 0;
}
