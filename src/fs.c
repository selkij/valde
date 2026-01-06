#include "include/fs.h"

int fs_create_file(const char* path) {
  FILE *fptr = fopen(path, "w");

  fclose(fptr);

  if(fptr == NULL) {
    fprintf(stderr, "An error occurred trying to create file %s: %s\n", path, strerror(errno));
    return 1;
  }

  printf("Created file at %s.\n", path);
  return 0;
}

int fs_create_dir(const char *path, const mode_t mode) {
  if(mkdir(path, mode)) {
    fprintf(stderr, "An error occurred trying to create folder %s: %s\n", path, strerror(errno));
    return 1;
  }

  return 0;
}

int fs_delete_file(const char *path) {
  if(remove(path)) {
    fprintf(stderr, "An error occurred trying to delete file %s: %s\n", path, strerror(errno));
  }

  printf("Deleted file at %s\n", path);
  return 0;
}

int fs_delete_dir(const char *path) {
  // TODO: Delete non empty directories.
  if(rmdir(path)) {
    fprintf(stderr, "An error occurred trying to delete folder %s: %s\n", path, strerror(errno));
  }

  printf("Deleted directory at %s\n", path);
  return 0;
}

int fs_delete_dir_recursive(const char *path) {
  // TODO
  
  return 0;
}

char* fs_read_file(const struct entry* entry) {
  if (entry_is_dir(entry)) {
    fprintf(stderr, "Cannot read entry %s: Entry is not a file.\n", entry->path);
    return NULL;
  }
  
  FILE* fptr = fopen(entry->path, "r");

  if(fptr == NULL) {
    fprintf(stderr, "Could not read entry %s: %s\n", entry->path, strerror(errno));
    return NULL;
  }

  const int count = (int) entry->st.st_size;

  if(entry->st.st_size == 0) {
    fprintf(stderr, "Could not read entry %s: File is empty.\n", entry->path);
    return NULL;
  }

  char* content = malloc(sizeof(char) * count);

  fread(content, sizeof(char), count, fptr);

  // Memory cleanup.
  fclose(fptr);

  return content;
}

int fs_rename_entry(const char *path, const char* new_path) {
  if(rename(path, new_path)) {
    fprintf(stderr, "An error occurred trying to rename %s to %s: %s\n", path, new_path, strerror(errno));
    return 1;
  }

  return 0;
}
