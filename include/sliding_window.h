```c
#ifndef SLIDING_WINDOW_H
#define SLIDING_WINDOW_H

#include <stdint.h>
#include <stdbool.h>

// Structure to represent a sliding window flow control mechanism
struct SlidingWindow {
    uint32_t read_index;
    uint32_t write_index;
    uint32_t window_size;
    bool full;
};

// Initialize the sliding window
void sliding_window_init(struct SlidingWindow* window, uint32_t window_size);

// Update the sliding window
void sliding_window_update(struct SlidingWindow* window, bool full);

#endif // SLIDING_WINDOW_H
