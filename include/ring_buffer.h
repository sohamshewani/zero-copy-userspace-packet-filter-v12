```c
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>

typedef struct RingBuffer RingBuffer;

RingBuffer* ring_buffer_create(size_t size);
void ring_buffer_destroy(RingBuffer* buffer);

void ring_buffer_push(RingBuffer* buffer, uint8_t* data, size_t size);
size_t ring_buffer_pop(RingBuffer* buffer, uint8_t* data, size_t max_size);
size_t ring_buffer_available(RingBuffer* buffer);

#endif // RING_BUFFER_H
