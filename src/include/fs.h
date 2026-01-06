#ifndef VALDE_FS_H
#define VALDE_FS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "entry.h"

int fs_create_file(const char* path);
int fs_create_dir(const char* path, mode_t mode);
int fs_delete_file(const char* path);
int fs_delete_dir(const char* path);
int fs_delete_dir_recursive(const char* path);
char* fs_read_file(const struct entry* entry);
int fs_rename_entry(const char* path, const char* new_path);

#endif /* VALDE_FS_H */
