// Written by: Christopher Gholmieh
// Headers:

// Utilities:
#include "utilities/memory-utilities.h"

// Types:
#include "types/string-type.h"
#include "types/map-type.h"


// Library:
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


// Definitions:
map_t* initialize_map(void) {
    // Variables (Assignment):
    // Map:
    map_t* map = allocate_memory(sizeof(map_t));

    if (map == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for map!\n");

        // Logic:
        return NULL;
    }

    // Capacity:
    map->capacity = MAP_INITIAL_CAPACITY;

    // Values:
    map->values = malloc(sizeof(void*) * map->capacity);

    if (map->values == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for map->values!\n");

        // Memory:
        free(map);

        // Logic:
        return NULL;
    }

    // Length:
    map->length = 0;

    // Keys:
    map->keys = malloc(sizeof(string_t) * map->capacity);

    if (map->keys == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for map->keys!\n");

        // Memory:
        free(map->values);
        free(map);

        // Logic:
        return NULL;
    }

    // Map:
    return map;
}

uint8_t map_resize(map_t* map) {
    // Validation:
    if (map == NULL) {
        // Message:
        fprintf(stderr, "[!] Map parameter supplied to map_resize is NULL!\n");

        // Logic:
        return 0;
    }

    // Variables (Assignment):
    // Capacity:
    size_t updated_capacity = map->capacity * 2;

    // Values:
    void** updated_values = malloc(sizeof(void*) * updated_capacity);

    if (updated_values == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for map's updated values!\n");

        // Logic:
        return 0;
    }

    // Keys:
    string_t** updated_keys = malloc(sizeof(string_t*) * updated_capacity);

    if (updated_keys == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for map's updated keys!\n");

        // Memory:
        free(updated_values);

        // Logic:
        return 0;
    }

    // Logic:
    for (size_t iterator = 0; iterator < map->capacity; iterator++) {
        // Variables (Assignment):
        // Key:
        string_t* key = map->keys[iterator];

        // Clause:
        if (key == NULL) {
            continue;
        }

        // Bucket:
        uint64_t bucket = map_hash(key) & (updated_capacity - 1);

        // Bucket:
        while (updated_keys[bucket] != NULL) {
            bucket++;
        }

        // Variables (Assignment):
        // Value:
        updated_values[bucket] = map->values[iterator];

        // Key:
        updated_keys[bucket] = key;
    }

    // Memory:
    free(map->values);
    free(map->keys);

    // Variables (Assignment):
    // Capacity:
    map->capacity = updated_capacity;

    // Values:
    map->values = updated_values;

    // Keys:
    map->keys = updated_keys;

    // Logic:
    return 1;
}

/**
 * @note This function assumes we own the key, which we will.
 */
uint8_t map_insert(map_t* map, string_t* key, void* value) {
    // Validation:
    if (map == NULL) {
        // Message:
        fprintf(stderr, "[!] Map parameter supplied to map_insert is NULL!\n");

        // Logic:
        return 0;
    }

    if (key == NULL) {
        // Message:
        fprintf(stderr, "[!] Key parameter supplied to map_insert is NULL!\n");

        // Logic:
        return 0;
    }

    if (value == NULL) {
        // Message:
        fprintf(stderr, "[!] Value parameter supplied to map_insert is NULL!\n");

        // Logic:
        return 0;
    }

    // Memory:
    if ((map->length / map->capacity) > 0.75) {
        if (map_resize(map) == 0) {
            // Message:
            fprintf(stderr, "[!] Failed to perform resize operation on map!\n");

            // Logic:
            return 0;
        }
    }

    // Variables (Assignment):
    // Bucket:
    uint64_t bucket = map_hash(key) & (map->capacity - 1);

    // Bucket:
    while (map->keys[bucket] != NULL) {
        bucket++;
    }

    // Values:
    map->values[bucket] = value;

    // Key:
    map->keys[bucket] = key;

    // Length:
    map->length++;

    // Logic:
    return 1;
}

void* map_get(map_t* map, string_t* key) {
    // Validation:
    if (map == NULL) {
        // Message:
        fprintf(stderr, "[!] Map parameter supplied to map_get is NULL!\n");

        // Logic:
        return NULL;
    }

    if (key == NULL) {
        // Message:
        fprintf(stderr, "[!] Key parameter supplied to map_hash is NULL!\n");

        // Logic:
        return NULL;
    }

    // Variables (Assignment):
    // Bucket:
    uint64_t bucket = map_hash(key) & (map->capacity - 1);

    // Validation:
    if (map->keys[bucket] == NULL) {
        // Message:
        fprintf(stderr, "[!] Key %s does not exist in the map!\n", key->buffer);

        // Logic:
        return NULL;
    }

    // Logic:
    while (map->keys[bucket] != NULL && string_compare(map->keys[bucket], key) != 1) {
        bucket++;
    }

    // Value:
    return map->values[bucket];
}

uint64_t map_hash(string_t* key) {
    // Validation:
    if (key == NULL) {
        // Message:
        fprintf(stderr, "[!] Key parameter supplied to map_hash is NULL!\n");

        // Logic:
        return 0;
    }

    // Variables (Assignment);
    // Hash:
    uint64_t hash = 14695981039346656037ULL;

    // Pointer:
    char* pointer = key->buffer;

    // Logic:
    while (*pointer != '\0') {
        // Variables (Assignment):
        // Prime:
        hash *= 1099511628211ULL;

        // XOR:
        hash ^= *pointer;

        // Pointer:
        pointer++;
    }

    // Hash:
    return hash;
}

/**
 * @note Supplying a callback parameter assumes you will also free the actual pointer as well.
 */
void map_free(map_t* map, void (*callback)(void*)) {
    // Validation:
    if (map == NULL) {
        // Message:
        fprintf(stderr, "[!] Map parameter supplied to map_free is NULL !\n");

        // Logic:
        return;
    }

    if (map->values == NULL) {
        // Message:
        fprintf(stderr, "[!] Map parameter supplied to map_free has NULL values!\n");

        // Logic:
        return;
    }

    if (map->keys == NULL) {
        // Message:
        fprintf(stderr, "[!] Map parameter supplied to map_free has NULL keys!\n");

        // Logic:
        return;
    }

    // Logic:
    for (size_t iterator = 0; iterator < map->capacity; iterator++) {
        // Variables (Assignment):
        // Key:
        string_t* key = map->keys[iterator];

        // Clause:
        if (key == NULL) {
            continue;
        }

        // Memory:
        if (callback == NULL) {
            free(map->values[iterator]);
        } else {
            callback(map->values[iterator]);
        }

        // Memory:
        free(key);
    }

    // Memory:
    free(map->values);
    free(map->keys);
    free(map);
}