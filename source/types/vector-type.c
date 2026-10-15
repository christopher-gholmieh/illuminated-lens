// Written by: Christopher Gholmieh
// Headers:

// Utilities:
#include "include/utilities/memory-utilities.h"

// Types:
#include "include/types/vector-type.h"


// Library:
#include <stdint.h>
#include <string.h>

#include <stdlib.h>
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

/**
 * @note The vector is defined to only have a capacity that is a multiple of 2 for simplicity.
 * @note You could also worry about the maximum limit, e.g if parameter desired_capacity is extremely high, but it's unlikely.
 */
uint8_t vector_reserve(vector_t* vector, size_t desired_capacity) {
    // Validation:
    if (vector == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed into vector_reserve is NULL!\n");

        // Logic:
        return 0;
    }

    // Variables (Assignment):
    // Capacity:
    size_t updated_capacity = VECTOR_INITIAL_CAPACITY;
    
    while (updated_capacity < desired_capacity) {
        updated_capacity <<= 1;
    }

    // Pointer:
    void* updated_pointer = realloc(vector->pointer, updated_capacity * vector->bytes);

    if (updated_pointer == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to reallocate memory for vector->pointer of size %zu bytes!", updated_capacity * vector->bytes);

        // Logic:
        return 0;
    } else {
        vector->pointer = updated_pointer;
    }

    // Capacity:
    vector->capacity = updated_capacity;

    // Logic:
    return 1;
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