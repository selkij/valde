#include "include/fs.h"

int fs_create_file(char* path) {
  FILE* fptr;
  fptr = fopen(path, "w");

  fclose(fptr);

  if(fptr == NULL) {
    fprintf(stderr, "An error occured trying to create file %s\n", path);
    return 1;
  }

  printf("Created file at %s.\n", path);
  return 0;
}

int fs_create_dir(char *path) {
  // TODO: Folder permissions.
  int result;
  
  result = mkdir(path);
  
  if(result) {
    fprintf(stderr, "An error occured trying to create folder %s\n", path);
    return 1;
  }

  printf("Created folder at %s\n", path);
  return 0;
}

int fs_delete_file(char *path) {
  int result;
  result = remove(path);

  if(result != 0) {
    fprintf(stderr, "An error occured trying to delete file %s\n", path);
  }

  printf("Deleted file at %s\n", path);
  return 0;
}

int fs_delete_dir(char *path) {
  // TODO: Delete non empty directories.
  int result;
  result = rmdir(path);

  if(result != 0) {
    fprintf(stderr, "An error occured trying to delete folder %s\n", path);
  }

  printf("Deleted directory at %s\n", path);
  return 0;
}

int fs_read_file(char *path) {
  
  return 0;
}

int fs_rename_entry(char *path) {
  // TODO: fs_rename_entry
  return 0;
}
