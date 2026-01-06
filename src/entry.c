#include "include/entry.h"

/// @brief Tells if the entry is a directory.
/// @param entry The entry to check.
/// @return returns true if entry is a directory, false otherwise.
bool entry_is_dir(const struct entry* entry) {
  return S_ISDIR(entry->st.st_mode);
}

/// @brief Populates an entry struct for the given path.
/// @param path The path to populate the entry for.
/// @return The populated entry struct. If an error occurs, a dummy struct with path set to NULL is returned.
struct entry entry_populate(const char* path) {
  struct stat st;
  struct entry entry;
  struct entry dummy; // Used when an error occurs.
  dummy.path = NULL;

  if(lstat(path, &st) != 0) {
    printf("TEST %s\n", path);
    fprintf(stderr, "Could not populate entry %s: %s\n", path, strerror(errno));
    return dummy;
  }
  
  if(S_ISLNK(st.st_mode)) {
    struct stat target;

    if(stat(path, &target) != 0) {
      fprintf(stderr, "Could not populate entry %s: %s\n", path, strerror(errno));
      return dummy;
    }
    
    entry.st = target; // Use target stat info for symlinks.
  } else {
    entry.st = st;
  }

  entry.path = path;

  return entry; // The dummy struct is returned if something went wrong.
}

/// @brief Populates the entries of a directory entry.
/// @param entry The directory entry to populate.
/// @return Returns EXIT_SUCCESS on success, error code otherwise.
int entry_populate_dir(struct entry* entry) {
  if(!S_ISDIR(entry->st.st_mode)) { // Entry is not a directory.
    fprintf(stderr, "Entry is not a directory for %s.", entry->path);
    return NOT_A_DIRECTORY;
  }

  struct dirent* de;
  DIR* dir = opendir(entry->path);

  if(dir == NULL) { // Error trying to open dir
    fprintf(stderr, "Could not open dir %s: %s\n", entry->path, strerror(errno));
    return 1;
  }

  struct entry* entries = NULL;
  size_t count = 0;

  // Populate entry for each entry in current directory.
  while((de = readdir(dir)) != NULL) {
    if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue; // Omit ./ and ../ directories by default.

    struct entry* temp = realloc(entries, (count+1) * sizeof(struct entry));

    if(!temp) { // If allocating temp fails.
      free(entries);
      closedir(dir);

      fprintf(stderr, "An error occurred trying to realloc entries: %s\n", strerror(errno));
      return ALLOCATION_FAILURE;
    }

    entries = temp; // Update the entries object.



    struct entry temp_entry;

    if(string_ends_with(entry->path, "/")) { // Whether the entry path already ends with a '/' or not.
      const size_t length = strlen(entry->path) + strlen(de->d_name) + 1; // +1 for null terminator.
      char* path = malloc(length);

      snprintf(path, length, "%s%s", entry->path, de->d_name);
      temp_entry = entry_populate(path);
    } else {
      const size_t length = strlen(entry->path) + strlen(de->d_name) + 2; // +2 for '/' and null terminator.
      char* path = malloc(length);

      snprintf(path, length, "%s/%s", entry->path, de->d_name);
      temp_entry = entry_populate(path);
    }
    
    if(temp_entry.path == NULL) {
      fprintf(stderr, "Got an error trying to populate %s: %s\n", entry->path, strerror(errno));
      return POPULATE_FAILURE;
    }
     
    entries[count] = temp_entry;
    
    count++;
  }

  entry->entries = entries;
  entry->entry_count = count;

  // Memory cleanup
  closedir(dir);

  return EXIT_SUCCESS;
}

/// @brief Prints information about an entry.
/// @param entry The entry to print information about.
/// @param include_subentries Whether to include subentries information (if directory) or not.
void entry_info(const struct entry* entry, const bool include_subentries) {
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
