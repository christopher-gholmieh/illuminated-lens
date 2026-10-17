// Written by: Christopher Gholmieh
// Guards:
#ifndef MAP_TYPE_H
#define MAP_TYPE_H

// Headers:
// Library:
#include <stdlib.h>

// Types:
#include "types/string-type.h"

// Structures:
typedef struct {
    /* Capacity: */
    size_t capacity;

    /* Values: */
    void** values;

    /* Length: */
    size_t length;

    /* Keys: */
    string_t** keys;
} map_t;

// Guard:
#endif /** MAP_TYPE_H */