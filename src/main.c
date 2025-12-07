#include <stdio.h>
#include <stdlib.h>
#include "include/entry.h"
#include "include/fs.h"
#include "include/screen.h"

int test() {
  struct entry entry_test;

  entry_test = entry_populate("/home/lain/");
  int dir_result = entry_populate_dir(&entry_test);

  entry_info(&entry_test, false);

  if(dir_result == 1) return 1;
  free(entry_test.entries);
  return 0;
}

int main() {
  printf("valde File manager\n\n");
  return test();
}
