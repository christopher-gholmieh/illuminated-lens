// Written by: Christopher Gholmieh
// Headers:

// Utilities:
#include "utilities/memory-utilities.h"

// Types:
#include "interpreter-implementation.h"


// Library:
#include <stdint.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>


// Definitions:
interpreter_t* initialize_interpreter(int argument_count, char** argument_vector) {
    // Variables (Assignment):
    // Interpreter:
    interpreter_t* interpreter = allocate_memory(sizeof(interpreter_t));

    if (interpreter == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for interpreter!\n");

        // Logic:
        return NULL;
    }

    // Count:
    interpreter->argument_count = argument_count;

    // Vector:
    interpreter->argument_vector = argument_vector;
    
    // Interpreter:
    return interpreter;
}

void interpreter_process(interpreter_t* interpreter) {
    // Validation:
    if (interpreter == NULL) {
        // Message:
        fprintf(stderr, "[!] Interpreter parameter passed to interpreter_process is NULL!\n");

        // Logic:
        return;
    }
}

void interpreter_free(interpreter_t* interpreter) {
    // Validation:
    if (interpreter == NULL) {
        // Message:
        fprintf(stderr, "[!] Interpreter parameter passeed to interpreter_free is NULL!\n");

        // Logic:
        return;
    }

    // Memory:
    if (interpreter->argument_vector == NULL) {
        // Message:
        fprintf(stderr, "[!] Interpreter parameter passed to interpreter_free has a NULL vector!\n");
    } else {
        // Memory:
        free(interpreter->argument_vector);
    }

    // Memory:
    free(interpreter);
}