#include "include/entry.h"

// TODO: Better error messages.
// TODO: Comment.

bool is_dir(struct entry* entry) {
  return S_ISDIR(entry->st.st_mode);
}

struct entry entry_populate(char* path) {
  struct stat st;
  struct entry entry;
  struct entry dummy;
  dummy.path = NULL;
  
  if(stat(path, &st) != 0) {
    if(errno == ENOENT || errno == ELOOP || errno == ENOTDIR) { // Conditions to determine if it's a symlink.
      if(lstat(path, &st) != 0) { // If stat fails, it's a symlink, and using lstat also fails.
        fprintf(stderr, "Got lstat error, can't proceed.\n");
        return dummy;
      }
    } else { // If using stat fails and it isn't because it is a symlink.
      fprintf(stderr, "Got stat error trying to populate entry %s.\n", path);
      return dummy;
    }
  }

  entry.path = path; // FIXME: populate real path, for example if its set to "../", it will be "../", not the real path
  entry.st = st;

  return entry; // The dummy struct is returned if something went wrong.
}

int entry_populate_dir(struct entry* entry) { // TODO: Move to directory.c, maybe remove entries from the struct.
  if(!S_ISDIR(entry->st.st_mode)) { // Entry is not a directory.
    fprintf(stderr, "Entry is not a directory.");
    return 1;
  }

  struct dirent* de;
  DIR* dir = opendir(entry->path);

  if(dir == NULL) { // Error trying to open dir
    fprintf(stderr, "Could not open dir.\n");
    return 1;
  }

  struct entry* entries = NULL;
  size_t count = 0;

  // Populate entry for each entries in current directory.
  while((de = readdir(dir)) != NULL) {
    if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue; // Omit ./ and ../ directories by default.

    struct entry* temp = realloc(entries, (count+1) * sizeof(struct entry));

    if(!temp) { // If allocating temp fails.
      free(entries);
      closedir(dir);

      fprintf(stderr, "An error occured trying to realloc entries.\n");
      return 1;
    }

    entries = temp; // Update the entries object.

    struct entry temp_entry;
    size_t length = strlen(entry->path) + strlen(de->d_name) + 1;
    char* path = malloc(length);
    snprintf(path, length, "%s%s", entry->path, de->d_name);
    
    temp_entry = entry_populate(path);
    
    if(temp_entry.path == NULL) {
      fprintf(stderr, "Got an error trying to populate %s\n", entry->path);
      return 1;
    }
     
    entries[count] = temp_entry;
    
    count++;
  }
  entry->entries = entries;
  entry->entry_count = count;

  // Memory cleanup
  closedir(dir);

  return 0;
}

void entry_info(struct entry* entry, bool include_subentries) {
  printf("File: %s\n", entry->path);
  printf("Size: %ld bytes\n", entry->st.st_size);
  printf("Permissions: %o (octal)\n", entry->st.st_mode & 0777);
  printf("Last modified: %s", ctime(&entry->st.st_mtime));
  printf("Last access: %s", ctime(&entry->st.st_atime));
  printf("Is directory? %s\n", S_ISDIR(entry->st.st_mode) ? "Yes" : "No");
  printf("Is regular file? %s\n", S_ISREG(entry->st.st_mode) ? "Yes" : "No");

  if(!S_ISDIR(entry->st.st_mode) || !include_subentries) return;

  printf("-------------------\n");
  printf("Getting sub-entries...\n");

  struct entry sub_entry;

  for(size_t i = 0; i < entry->entry_count; i++) {
    sub_entry = entry->entries[i];
    printf("File: %s\n", sub_entry.path);
    printf("Size: %ld bytes\n", sub_entry.st.st_size);
    printf("Permissions: %o (octal)\n", sub_entry.st.st_mode & 0777);
    printf("Last modified: %s", ctime(&sub_entry.st.st_mtime));
    printf("Last access: %s", ctime(&sub_entry.st.st_atime));
    printf("Is directory? %s\n", S_ISDIR(sub_entry.st.st_mode) ? "Yes" : "No");
    printf("Is regular file? %s\n", S_ISREG(sub_entry.st.st_mode) ? "Yes" : "No");
    printf("---\n");
  }

}
