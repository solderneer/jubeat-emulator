/*
 * ringbuffer.h
 *
 *  Created on: 30 May 2017
 *      Author: User
 */

#include <inttypes.h>

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#define RING_BUFFER_SIZE 8

#if (RING_BUFFER_SIZE & (RING_BUFFER_SIZE - 1)) != 0
#error "RING_BUFFER_SIZE must be a power of two"
#endif

typedef uint8_t ring_buffer_size_t;

#define RING_BUFFER_MASK (RING_BUFFER_SIZE-1)

typedef struct ring_buffer_t ring_buffer_t;

struct ring_buffer_t {
  /** Buffer memory. */
  char buffer[RING_BUFFER_SIZE];
  /** Index of tail. */
  ring_buffer_size_t tail_index;
  /** Index of head. */
  ring_buffer_size_t head_index;
};

void ring_buffer_init(ring_buffer_t *buffer);
void ring_buffer_queue(ring_buffer_t *buffer, char data);
void ring_buffer_queue_arr(ring_buffer_t *buffer, const char *data, ring_buffer_size_t size);
uint8_t ring_buffer_dequeue(ring_buffer_t *buffer, char *data);
uint8_t ring_buffer_dequeue_arr(ring_buffer_t *buffer, char *data, ring_buffer_size_t len);
uint8_t ring_buffer_peek(ring_buffer_t *buffer, char *data, ring_buffer_size_t index);

inline uint8_t ring_buffer_is_empty(ring_buffer_t *buffer) {
  return (buffer->head_index == buffer->tail_index);
}

inline uint8_t ring_buffer_is_full(ring_buffer_t *buffer) {
  return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK) == RING_BUFFER_MASK;
}

inline ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *buffer) {
  return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK);
}

#endif /* RINGBUFFER_H */
