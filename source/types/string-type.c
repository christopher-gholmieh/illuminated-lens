// Written by: Christopher Gholmieh
// Headers:

// Utilities:
#include "include/utilities/memory-utilities.h"

// Types:
#include "include/types/string-type.h"


// Library:
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


// Definitions:
string_t* initialize_string(void) {
    // Variables (Assignment):
    // String:
    string_t* string = (string_t*) allocate_memory(sizeof(string_t));

    if (string == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for string_t!\n");

        // Logic:
        return NULL;
    }

    // Capacity:
    string->capacity = STRING_INITIAL_CAPACITY;

    // Length:
    string->length = 0;

    // Buffer:
    string->buffer = allocate_memory(string->capacity);

    if (string->buffer == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for string_t->buffer!\n");

        // Memory:
        free(string);

        // Logic:
        return NULL;
    }

    // Terminator:
    string->buffer[string->length] = '\0';

    // String:
    return string;
}

uint8_t string_reserve(string_t* string, size_t capacity) {
    // Validation:
    if (string == NULL) {
        // Message:
        fprintf(stderr, "[!] String parameter passed to string_reserve is NULL!\n");

        // Logic:
        return 0;
    }

    if (string->capacity >= capacity) {
        // Message:
        fprintf(stderr, "[!] Capacity parameter passed into string_reserve must be greater than the current capacity!\n");

        // Logic:
        return 0;
    }

    // Variables (Assignment):
    // Capacity:
    size_t updated_capacity = STRING_INITIAL_CAPACITY;
    
    while (updated_capacity < capacity) {
        updated_capacity <<= 1;
    }

    // Buffer:
    void* updated_buffer = realloc(string->buffer, updated_capacity);

    if (updated_buffer == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to reallocate memory for string->buffer of size %zu bytes!", updated_capacity);

        // Logic:
        return 0;
    } else {
        // Variables (Assignment):
        // Buffer:
        string->buffer = updated_buffer;
    }

    // Capacity:
    string->capacity = updated_capacity;

    // Logic:
    return 1;
}

void string_free(string_t* string) {
    // Validation:
    if (string == NULL) {
        // Message:
        fprintf(stderr, "[!] String parameter passed to string_free is NULL!\n");

        // Logic:
        return;
    }

    // Buffer:
    if (string->buffer == NULL) {
        // Message:
        fprintf(stderr, "[!] String parameter passed to string_free has a NULL buffer!\n");
    } else {
        // Memory:
        free(string->buffer);
    }

    // Memory:
    free(string);
}