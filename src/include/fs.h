#ifndef FS
#define FS

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "entry.h"

int fs_create_file(char* path);
int fs_create_dir(char* path);
int fs_delete_file(char* path);
int fs_delete_dir(char* path);
char* fs_read_file(struct entry* entry);
int fs_rename_entry(char* path, char* new_path);

#endif /* FS */
