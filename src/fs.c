#include "include/fs.h"

int fs_create_file(char* path) {
    FILE* fptr;
    fptr = fopen(path, "w");

    fclose(fptr);

    printf("Created file at %s.\n", path);
    return 0;
}

int fs_create_dir(char *path) {
    // TODO: fs_create_dir
    return 0;
}

int fs_delete_file(char *path) {
    // TODO: fs_delete_file
    return 0;
}

int fs_delete_dir(char *path) {
    // TODO: fs_delete_dir
    return 0;
}

int fs_read_file(char *path) {
    // TODO: fs_read_file
    return 0;
}

int fs_rename_entry(char *path) {
    // TODO: fs_rename_entry
    return 0;
}