// Written by: Christopher Gholmieh
// Headers:

// Utilities:
#include "include/utilities/memory-utilities.h"

// Types:
#include "include/types/vector-type.h"


// Library:
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


// Definitions:
vector_t* initialize_vector(size_t bytes) {
    // Variables (Assignment):
    // Vector:
    vector_t* vector = allocate_memory(sizeof(vector_t));

    if (vector == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for vector!\n");

        // Logic:
        return NULL;
    }

    // Capacity:
    vector->capacity = VECTOR_INITIAL_CAPACITY;

    // Pointer:
    vector->pointer = allocate_memory(vector->capacity * bytes);

    if (vector->pointer == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for vector->pointer!\n");

        // Memory:
        free(vector);

        // Logic:
        return NULL;
    }

    // Length:
    vector->length = 0;

    // Bytes:
    vector->bytes = bytes;
}

void vector_free(vector_t* vector, void (*free_callback)(void*)) {
    // Validation:
    if (vector == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_free is NULL!\n");

        // Logic:
        return;
    }

    // Pointer:
    if (vector->pointer == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_free has a NULL pointer!\n");
    } else {
        // Memory:
        if (free_callback != NULL) {
            for (size_t iterator = 0; iterator < vector->length; iterator++) {
                free_callback((unsigned char*) vector->pointer + (iterator * vector->bytes));
            }
        }

        // Memory:
        free(vector->pointer);
    }

    // Memory:
    free(vector);
}