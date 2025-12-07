#ifndef FS
#define FS

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int fs_create_file(char* path);
int fs_create_dir(char* path);
int fs_delete_file(char* path);
int fs_delete_dir(char* path);
int fs_read_file(char* path);
int fs_rename_entry(char* path);

#endif /* FS */
