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
  
  result = mkdir(path, 0777);
  
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

char* fs_read_file(struct entry* entry) {
  if (is_dir(entry)) {
    fprintf(stderr, "Entry is not a file: %s\n", entry->path);
    return NULL;
  }
  
  FILE* fptr = fopen(entry->path, "r");

  if(fptr == NULL) {
    fprintf(stderr, "File pointer is NULL\n");
    return NULL;
  }

  int count = entry->st.st_size;

  if(entry->st.st_size == 0) {
    fprintf(stderr, "File is empty: %s\n", entry->path);
    return NULL;
  }

  char* content = malloc(sizeof(char) * count);

  if(fptr == NULL) {
    fprintf(stderr, "file content is NULL: %s\n", entry->path);
    free(content);
    return NULL;
  }

  // Memory cleanup.
  fread(content, sizeof(char), count, fptr);
  fclose(fptr);

  return content;
  return 0;
}

int fs_rename_entry(char *path, char* new_path) {
  if(rename(path, new_path) != 0) {
    fprintf(stderr, "An error occured trying to rename %s to %s\n", path, new_path);
    return 1;
  }

  return 0;
}
