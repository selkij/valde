#include "include/string_utils.h"

/// @brief Strips the given prefix from the string if it exists.
/// @param str The string to strip the prefix from.
/// @param prefix The prefix to strip.
const char* strip_prefix(const char* str, const char* prefix) {
    const size_t len_prefix = strlen(prefix);
    const size_t len_str = strlen(str);

    if (!str || !prefix) return NULL;

    if(len_str < len_prefix) {
        return str; // Prefix longer than string, nothing to do.
    }

    if(strncmp(str, prefix, len_prefix) == 0) {
        return str + len_prefix; // Shifts the pointer the number of the prefix has to omit it.
    }

    return str; // Prefix not found, return original string.
}

bool string_ends_with(const char* str, const char* suffix) {
    const size_t len_suffix = strlen(suffix);
    const size_t len_str = strlen(str);

    if (!str || !suffix) return false;

    if(len_str < len_suffix) {
        return false; // Prefix longer than string, nothing to do.
    }

    return strncmp(str + len_str - len_suffix, suffix, len_suffix) == 0;
}

const char* string_append_slash(const char* str) {
    const size_t len_str = strlen(str);

    if(string_ends_with(str, "/")) {
        return str; // Already ends with slash.
    }

    char* new_str = malloc(len_str + 2); // +1 for '/' and +1 for null terminator.
    snprintf(new_str, len_str + 2, "%s/", str);

    return new_str;
}