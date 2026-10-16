// Written by: Christopher Gholmieh
// Guards:
#ifndef INTERPRETER_IMPLEMENTATION_H
#define INTERPRETER_IMPLEMENTATION_H

// Structures:
typedef struct {
    /* Count: */
    int argument_count;

    /* Vector: */
    char** argument_vector;
} interpreter_t;

// Prototypes:
interpreter_t* initialize_interpreter(int argument_count, char** argument_vector);

void           interpreter_free(interpreter_t* interpreter);

// Guard:
#endif /** INTERPRETER_IMPLEMENTATION_H */