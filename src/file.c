#include "include/file.h"

// TODO: Comment.
char* file_content(struct entry* entry) {
  if (is_dir(entry)) {
    perror("entry is not a file.\n");
    return NULL;
  }
  
  FILE* fptr = fopen(entry->path, "r");
  int count = entry->st.st_size;
  char* content = malloc(sizeof(char) * count);

  if(fptr == NULL) {
    perror("file content is NULL\n");
    return NULL;
  }

  // Memory cleanup.
  fread(content, sizeof(char), count, fptr);
  fclose(fptr);

  return content;
}
