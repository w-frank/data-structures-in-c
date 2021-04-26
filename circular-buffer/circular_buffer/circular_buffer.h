#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdbool.h>
#include <stdint.h>

// Ring buffer
typedef struct circular_buffer_t circular_buffer_t;

// Handle type, the way users interact with the ring buffer
typedef circular_buffer_t* cbuf_handle_t;

// Pass in a storage buffer and size 
// Returns a circular buffer handle
cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size);

// Free a circular buffer structure.
// Does not free data buffer; owner is responsible for that
void circular_buf_free(cbuf_handle_t cbuf);

// Reset the buffer to empty, head == tail
void circular_buf_reset(cbuf_handle_t cbuf);

// Add data to the buffer (write) - overwrite if full or not?
void circular_buf_put(cbuf_handle_t cbuf, uint8_t data);

// Get a value from the buffer
// Returns 0 on success, -1 if the buffer is empty
int circular_buf_get(cbuf_handle_t cbuf, uint8_t * data);

// Check is buffer is full
bool circular_buf_full(cbuf_handle_t cbuf);

// Check if buffer is empty
// Returns true if the buffer is empty
bool circular_buf_empty(cbuf_handle_t cbuf);

/// Get the maximum capacity of the buffer
size_t circular_buf_capacity(cbuf_handle_t cbuf);

/// Get the current number of elements in the buffer
size_t circular_buf_size(cbuf_handle_t cbuf);

#endif //CIRCULAR_BUFFER_H_