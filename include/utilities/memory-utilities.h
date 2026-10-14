// Written by: Christopher Gholmieh
// Guards:
#ifndef MEMORY_UTILITIES_H
#define MEMORY_UTILITIES_H

// Headers:
// Library:
#include <stdlib.h>
#include <stdio.h>

// Functions:
static inline void* allocate_memory(size_t bytes) {
    // Variables (Assignment):
    // Pointer:
    void* pointer = malloc(bytes);

    // Validation:
    if (pointer == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for %zu bytes!\n", bytes);

        // Logic:
        return NULL;
    }

    // Pointer:
    return pointer;
}

// Guard:
#endif /** MEMORY_UTILITIES_H */