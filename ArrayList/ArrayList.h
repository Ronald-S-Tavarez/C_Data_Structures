#ifndef RON_ARRAYLIST_H
#define RON_ARRAYLIST_H

#include <stdlib.h>
#include <stdbool.h>

struct ArrayList {
    void * array;        // Pointer to underlying array
    size_t length;       // Number of elements in use
    size_t capacity;     // Total available capacity
    size_t element_size; // Size of each individual element in bytes
};

// Initialize an existing ArrayList
void array_list_initialize(struct ArrayList * array_list, size_t element_size, size_t capacity);

// Create a new ArrayList
struct ArrayList * array_list_create(size_t element_size, size_t capacity);

// Append an element to an ArrayList
void array_list_push(struct ArrayList * array_list, void * element);

// Allocates new memory for the element outside the arraylist and clears the memory within.
void * array_list_pop(struct ArrayList * array_list);

// Returns an element at the index or NULL when element not found / out of bounds.
void * array_list_at(struct ArrayList * array_list, size_t index);

// Free the ArrayList and its underlying array
void array_list_destroy(struct ArrayList * array_list);

#endif  //RON_ARRAYLIST_H