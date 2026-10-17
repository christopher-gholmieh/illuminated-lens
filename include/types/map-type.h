// Written by: Christopher Gholmieh
// Guards:
#ifndef MAP_TYPE_H
#define MAP_TYPE_H

// Definitions:
#define MAP_INITIAL_CAPACITY 64

// Headers:
// Library:
#include <stdlib.h>
#include <stdint.h>

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


// Prototypes:
map_t*      initialize_map(void);

uint8_t     map_resize(map_t* map);
uint8_t     map_insert(map_t* map, string_t* key, void* value);

void*       map_get(map_t* map, string_t* key);

uint64_t    map_hash(string_t* key);

void        map_free(map_t* map, void (*callback)(void*));

// Guard:
#endif /** MAP_TYPE_H */