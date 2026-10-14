// Written by: Christopher Gholmieh
// Guards:
#ifndef FILESYSTEM_UTILITIES_H
#define FILESYSTEM_UTILITIES_H

// Headers:
// Library:
#include <unistd.h>
#include <stdint.h>

// Functions:
static inline uint8_t file_readable(const char* file_path) {
    return access(file_path, R_OK) == 0;
}

static inline uint8_t file_exists(const char* file_path) {
    return access(file_path, F_OK) == 0;
}

// Guard:
#endif /* FILESYSTEM_UTILITIES_H */