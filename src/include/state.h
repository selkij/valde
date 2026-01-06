#ifndef VALDE_STATE_H
#define VALDE_STATE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH_MAX 4096

typedef struct State {
    char* cwd;
    int selected_index;
} State;

State* state_init(const char* initial_working_directory);
void state_free(State* state);
void state_set_cwd(const State* state, const char* new_cwd);
const char* state_get_cwd(const State* state);

#endif /* VALDE_STATE_H */
