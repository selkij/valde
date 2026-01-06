#include "include/state.h"

/// @brief Initialize the app's state struct.
/// @param initial_working_directory Initial working directory. If NULL, uses system's current working directory.
/// @return The initialized State struct. NULL on failure.
State* state_init(const char* initial_working_directory) {
    State* state = malloc(sizeof(State));
    state->cwd = malloc(sizeof(char) * strlen(initial_working_directory ? initial_working_directory : ""));

    if(state == NULL) {
        fprintf(stderr, "Error allocating memory for state.\n");
        return NULL;
    }

    if(initial_working_directory != NULL) { // Set to provided directory.
        state_set_cwd(state, initial_working_directory);
    } else {
        state_set_cwd(state, getcwd(NULL, 0));
        if(state_get_cwd(state) == NULL) { // Else use system current working directory.
            fprintf(stderr, "Error getting current working directory.\n");
            free(state);
            return NULL;
        }
    }

    return state;
}

/// @brief To be called after being done using the state struct to free allocated memory.
/// @param state The state struct to free.
void state_free(State* state) {
    if(state != NULL) {
        free(state->cwd);
        free(state);
    }
}

/// @brief Change the current working directory.
/// @param state The state struct to update.
/// @param new_cwd The new current working directory.
void state_set_cwd(const State* state, const char* new_cwd) {
    if(state != NULL && new_cwd != NULL) {
        snprintf(state->cwd, PATH_MAX, "%s", new_cwd);
    }
}

/// @brief Get the current working directory from the state struct.
/// @param state The state struct to get the current working directory from.
/// @return The current working directory. NULL on failure.
const char* state_get_cwd(const State* state) {
    if(state != NULL) {
        return state->cwd;
    }

    return NULL;
}