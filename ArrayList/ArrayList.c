#include "ArrayList.h"
#include <string.h>
#include <stdio.h>

// Helper function, returns true on successful realloc, and returns false on failure.
static bool _array_list_resize(struct ArrayList * array_list) {
    size_t new_capacity = array_list->capacity * 2;
    void * new_array = realloc(array_list->array, new_capacity * array_list->element_size);
    if (new_array != NULL) {
        array_list->array = new_array;
        array_list->capacity = new_capacity;
        return true;
    }
    return false; 
}

// Helper function, copies the element into the array memory at the end of the array. Does no bounds checking.
static void _array_list_insert(struct ArrayList * array_list, void * element) {
    void * target = (char *)array_list->array + array_list->length * array_list->element_size;
    memcpy(target, element, array_list->element_size);
    array_list->length++;
}

void array_list_initialize(struct ArrayList * array_list, size_t element_size, size_t capacity) { 
    array_list->array = malloc(capacity * element_size);
    if (array_list->array == NULL) {
        perror("Failure to allocate ArrayList->array.");
        return;
    }

    array_list->length = 0;
    array_list->element_size = element_size;
    array_list->capacity = capacity;
}

void * array_list_at(struct ArrayList * array_list, size_t index) {
    if (index >= array_list->length) return NULL;
    return (char *)array_list->array + index * array_list->element_size;
}

struct ArrayList * array_list_create(size_t element_size, size_t capacity) {
    struct ArrayList * array_list = (struct ArrayList *)malloc(sizeof(struct ArrayList));
    if (array_list == NULL) {
        perror("Failure to create ArrayList.");
        return NULL;
    }

    array_list_initialize(array_list, element_size, capacity);
    return array_list;
}

void array_list_push(struct ArrayList * array_list, void * element) {
    if (array_list->length == array_list->capacity) {
        bool resize_success = _array_list_resize(array_list); 
        if (!resize_success) {
            perror("Failure to resize ArrayList.");
            return;
        }
    }
    _array_list_insert(array_list, element);
}

void * array_list_pop(struct ArrayList * array_list) {
    if (array_list->length == 0) {
        perror("Cannot pop from empty ArrayList");
        return NULL;
    }

    void * last_element = array_list_at(array_list, array_list->length - 1);
    void * element_copy = malloc(array_list->element_size);
    if (element_copy == NULL) {
        perror("Failure to create element copy");
        return NULL;
    }

    // Copy the element and return the copy, clear the original from memory, adjust the list length to represent the change.
    memcpy(element_copy, last_element, array_list->element_size);
    array_list->length--;
    memset(last_element, 0, array_list->element_size);

    return element_copy;
}

void array_list_destroy(struct ArrayList * array_list) {
    free(array_list->array);
    free(array_list);
}