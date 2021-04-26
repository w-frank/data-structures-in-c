#include <stdio.h>
#include <stdlib.h>

#include "circular_buffer/circular_buffer.h"

#define EXAMPLE_BUFFER_SIZE 10

void print_buffer_status(cbuf_handle_t cbuf);

int main(void)
{
    uint8_t * buffer = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));

    printf("=== Circular Buffer Example ===\n");

    cbuf_handle_t cbuf = circular_buf_init(buffer, EXAMPLE_BUFFER_SIZE);

    printf("Buffer initialised\n");
    print_buffer_status(cbuf);

    printf("Adding %d values\n", EXAMPLE_BUFFER_SIZE - 1);
    for (uint8_t i = 0; i < (EXAMPLE_BUFFER_SIZE - 1); i++)
    {
        circular_buf_put(cbuf, i);
        printf("Added %u, size now: %zu\n", i, circular_buf_size(cbuf));
    }

    print_buffer_status(cbuf);

    printf("Adding %d values\n", EXAMPLE_BUFFER_SIZE);
    for (uint8_t i = 0; i < EXAMPLE_BUFFER_SIZE; i++)
    {
        circular_buf_put(cbuf, i);
        printf("Added %u, size now: %zu\n", i, circular_buf_size(cbuf));
    }

    print_buffer_status(cbuf);

    printf("Reading back values: ");
    while(!circular_buf_empty(cbuf))
    {
        uint8_t data;
        circular_buf_get(cbuf, &data);
        printf("%u ", data);
    }
    printf("\n");
    
    print_buffer_status(cbuf);

    free(buffer);
    circular_buf_free(cbuf);

}

void print_buffer_status(cbuf_handle_t cbuf)
{
    printf("Full: %d, empty: %d, size: %zu\n",
        circular_buf_full(cbuf),
        circular_buf_empty(cbuf),
        circular_buf_size(cbuf));
}