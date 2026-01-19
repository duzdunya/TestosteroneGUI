#ifndef DSTRUCTURES_H
#define DSTRUCTURES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_INITIAL_CAPACITY 16
#define array(T, a) array_init(sizeof(T), ARRAY_INITIAL_CAPACITY, a)
#define array_append(a, v)                                                     \
    ((a) = array_ensure_capacity(a, 1, sizeof(v)),                             \
     (a)[array_header(a)->length] = (v), &(a)[array_header(a)->length++])
#define array_header(a) ((ArrayHeader *)(a) - 1)
#define array_length(a) (array_header(a)->length)
#define array_capacity(a) (array_header(a)->capacity)
#define array_remove(a, i)                                                     \
    (do {                                                                      \
	ArrayHeader *h = array_header(a);                                      \
	if (i == h->length - 1) {                                              \
	    h->length -= 1;                                                    \
	} else if (h->length > 1) {                                            \
	    void *ptr = &a[i];                                                 \
	    void *last = &a[h->length - 1];                                    \
	    h->length -= 1;                                                    \
	    memcpy(ptr, last, sizeof(*a));                                     \
	}                                                                      \
    } while (0);)
#define array_pop_back(a) (array_header(a)->length -= 1)

typedef struct {
    void *(*alloc)(size_t bytes, void *context);
    void (*free)(size_t bytes, void *ptr, void *context);
    void *context;
} Allocator;

typedef struct {
    size_t length;
    size_t capacity;
    size_t padding_or_something; // prefer 16-byte alignment
    Allocator *a;
} ArrayHeader;

void *array_init(size_t item_size, size_t capacity, Allocator *a);
void *my_alloc(size_t bytes, void *context);
void my_free(size_t bytes, void *ptr, void *context);
void *array_ensure_capacity(void *a, size_t item_count, size_t item_size);

#endif
