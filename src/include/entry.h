#ifndef ENTRY_H
#define ENTRY_H

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

struct entry {
  char* path;
  struct stat st;
  struct entry* entries; // NULL if is file or directory is empty
  size_t entry_count; // NULL if is file
};

bool is_dir(struct entry* entry);
struct entry entry_populate(char* path);
int entry_populate_dir(struct entry* entry);
void entry_info(struct entry* entry, bool include_subentries);

#endif /* ENTRY_H */
