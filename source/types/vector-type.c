// Written by: Christopher Gholmieh
// Headers:

// Utilities:
#include "utilities/memory-utilities.h"

// Types:
#include "types/vector-type.h"


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

    // Vector:
    return vector;
}

/**
 * @note The vector is defined to only have a capacity that is a power of two for simplicity.
 * @note You could also worry about the maximum limit, e.g if parameter capacity is extremely high, but it's unlikely.
 */
uint8_t vector_reserve(vector_t* vector, size_t capacity) {
    // Validation:
    if (vector == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed into vector_reserve is NULL!\n");

        // Logic:
        return 0;
    }

    if (vector->capacity >= capacity) {
        // Message:
        fprintf(stderr, "[!] Capacity parameter passed into vector_reserve must be greater than the current capacity!\n");

        // Logic:
        return 0;
    }

    // Variables (Assignment):
    // Capacity:
    size_t updated_capacity = VECTOR_INITIAL_CAPACITY;
    
    while (updated_capacity < capacity) {
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
        // Variables (Assignment):
        // Pointer:
        vector->pointer = updated_pointer;
    }

    // Capacity:
    vector->capacity = updated_capacity;

    // Logic:
    return 1;
}

uint8_t vector_append(vector_t* vector, void* pointer) {
    // Validation:
    if (vector == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_append is NULL!\n");

        // Logic:
        return 0;
    }

    if (pointer == NULL) {
        // Message:
        fprintf(stderr, "[!] Pointer parameter passed to vector_append is NULL!\n");

        // Logic:
        return 0;
    }

    // Boundary:
    if (vector->length == vector->capacity) {
        // Memory:
        if (vector_reserve(vector, vector->capacity << 1) == 0) {
            // Message:
            fprintf(stderr, "[!] Failed to reserve memory for vector!\n");

            // Logic:
            return 0;
        }
    }

    // Memory:
    memcpy((unsigned char*) vector->pointer + (vector->bytes * vector->length), pointer, vector->bytes);

    // Variables (Assignment):
    // Length:
    vector->length++;

    // Logic:
    return 1;
}

void* vector_get(vector_t* vector, size_t index) {
    // Validation:
    if (vector == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_get is NULL!\n");

        // Logic:
        return NULL;
    }

    if (vector->length == 0) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_get has a length of zero!\n");

        // Logic:
        return NULL;
    }

    if (vector->pointer == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_get has a NULL pointer!\n");

        // Logic:
        return NULL;
    }

    if (vector->length <= index) {
        // Message:
        fprintf(stderr, "[!] Index parameter passed to vector_get is invalid!\n");

        // Logic:
        return NULL;
    }

    // Variables (Assignment):
    // Pointer:
    void* pointer = (unsigned char*) vector->pointer + (index * vector->bytes);

    // Pointer:
    return pointer;
}

void* vector_pop(vector_t* vector) {
    // Validation:
    if (vector == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_pop is NULL!\n");

        // Logic:
        return NULL;
    }

    if (vector->length == 0) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_pop has a length of zero!\n");

        // Logic:
        return NULL;
    }

    if (vector->pointer == NULL) {
        // Message:
        fprintf(stderr, "[!] Vector parameter passed to vector_pop has a NULL pointer!\n");

        // Logic:
        return NULL;
    }

    // Variables (Assignment):
    // Length:
    vector->length--;

    // Pointer:
    void* pointer = (unsigned char*) vector->pointer + (vector->bytes * vector->length);

    // Pointer:
    return pointer;
}

void vector_free(vector_t* vector, void (*callback)(void*)) {
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
        if (callback != NULL) {
            for (size_t iterator = 0; iterator < vector->length; iterator++) {
                callback((unsigned char*) vector->pointer + (iterator * vector->bytes));
            }
        }

        // Memory:
        free(vector->pointer);
    }

    // Memory:
    free(vector);
}