// Written by: Christopher Gholmieh
// Headers:

// Utilities:
#include "utilities/memory-utilities.h"

// Types:
#include "miner-implementation.h"


// Library:
#include <stdint.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>


// Definitions:
miner_t* initialize_miner(void) {
    // Variables (Assignment):
    // Miner:
    miner_t* miner = allocate_memory(sizeof(miner_t));

    if (miner == NULL) {
        // Message:
        fprintf(stderr, "[!] Failed to allocate memory for miner!\n");

        // Logic:
        return;
    }

    // Miner:
    return miner;
}