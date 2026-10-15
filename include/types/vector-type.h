// Written by: Christopher Gholmieh
// Guards:
#ifndef VECTOR_TYPE_H
#define VECTOR_TYPE_H

// Constants:
#define VECTOR_INITIAL_CAPACITY 32

// Headers:
// Library:
#include <stdlib.h>
#include <stdint.h>

// Structures:
typedef struct {
    /* Capacity: */
    size_t capacity;

    /* Pointer: */
    void* pointer;

    /* Length: */
    size_t length;

    /* Bytes: */
    size_t bytes;
} vector_t;

// Prototypes:
vector_t* initialize_vector(size_t bytes);

uint8_t   vector_reserve(vector_t* vector, size_t desired_capacity);

void      vector_free(vector_t* vector, void (*free_callback)(void*));

// Guard:
#endif /** VECTOR_TYPE_H */