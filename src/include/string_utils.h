#ifndef VALDE_STRING_UTILS_H
#define VALDE_STRING_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char* strip_prefix(const char* str, const char* prefix);
bool string_ends_with(const char* str, const char* suffix);
const char* string_append_slash(const char* str);

#endif /* VALDE_STRING_UTILS_H */
