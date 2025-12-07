#include <stdio.h>
#include <stdlib.h>
#include "include/entry.h"
#include "include/fs.h"
#include "include/screen.h"

int test() {
  fs_create_file("test.allaa");
  getchar();
  fs_delete_file("test.allaa");
  getchar();
  fs_create_dir("test");
  getchar();
  fs_delete_dir("test");

  return 0;
}

int main() {
  printf("valde File manager\n\n");
  return test();
}
