#ifndef FS_H
#define FS_H

#include <stdio.h>
#include <stdlib.h>

int fs_create_file(char* path);
int fs_create_dir(char* path);
int fs_delete_file(char* path);
int fs_delete_dir(char* path);
int fs_read_file(char* path);
int fs_rename_entry(char* path);

#endif /* FS_H */
