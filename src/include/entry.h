#ifndef ENTRY
#define ENTRY

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include "string_utils.h"

#define NOT_A_DIRECTORY 1
#define ALLOCATION_FAILURE 2
#define POPULATE_FAILURE 3

struct entry {
  const char* path;
  struct stat st;
  struct entry* entries; // NULL if is file or directory is empty
  size_t entry_count; // NULL if is a file
};

bool entry_is_dir(const struct entry* entry);
struct entry entry_populate(const char* path);
int entry_populate_dir(struct entry* entry);
void entry_info(const struct entry* entry, bool include_subentries);

#endif /* ENTRY */
