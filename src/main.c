#include <stdio.h>
#include <stdlib.h>
#include "include/entry.h"
#include "include/fs.h"
#include "include/display.h"
#include "include/state.h"

int main(int argc, char* argv[]) {
  printf("valde file manager\n\n");

  State* state = state_init(argv[1]);
  screen_init(state);
  state_free(state);

  return EXIT_SUCCESS;
}
