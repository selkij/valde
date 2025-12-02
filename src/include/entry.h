#ifndef ENTRY
#define ENTRY

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

struct entry {
  char* path;
  struct stat st;
  struct entry* entries; // NULL if is file or directory is empty
  size_t entry_count; // NULL if is file
};

bool is_dir(struct entry* entry);
struct entry populate_entry(char* path);
int populate_directory_entry(struct entry* entry);
void entry_info(struct entry* entry);

#endif /* ENTRY */
