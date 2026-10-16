// Written by: Christopher Gholmieh
// Guards:
#ifndef STRING_TYPE_H
#define STRING_TYPE_H

// Constants:
#define STRING_INITIAL_CAPACITY 64

// Headers:
// Library:
#include <stdlib.h>
#include <stdint.h>

// Structures:
typedef struct {
    /* Capacity: */
    size_t capacity;

    /* Length: */
    size_t length;

    /* Buffer: */
    char* buffer;
} string_t;

// Prototypes:
string_t* initialize_string(void);
string_t* initialize_string_from(const char* buffer);

uint8_t   string_reserve(string_t* string, size_t capacity);
uint8_t   string_compare(string_t* string, string_t* other);

void      string_free(string_t* string);

// Guard:
#endif /** STRING_TYPE_H */