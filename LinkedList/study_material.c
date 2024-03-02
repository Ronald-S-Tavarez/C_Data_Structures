/**
 * Implementation from Daniel McCarthy's Data Structures and Algorithms In the C Programming Language Course.
 * User is responsible for memory of the head, free_linked_list frees succeeding list elements.
 * LinkedList itself is not a struct, it is a descriptor of pointer-linked list_elements.
 * This file describes single linked list, 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct list_element {
    void * data;
    struct list_element * next;
};

void init_list_element(struct list_element * element);
void add_list_element(struct list_element * head, void * data);
struct list_element * get_last_list_element(struct list_element * head);
void free_linked_list(struct list_element * head);

int main(int argc, char ** argv) {

    struct list_element head;
    init_list_element(&head);   // Initialize the list head.
    add_list_element(&head, "This is the first element");   // Add the first element to the list.
    add_list_element(&head, "This is the second element");  // Add the second element to the list
    add_list_element(&head, "This is the third element");   // Add the third element

    struct list_element * current = &head;
    while (current != NULL) {
        printf("%s\n", (const char *)current->data);
        current = current->next;
    }
    free_linked_list(&head);
    return 0;
}

void init_list_element(struct list_element * element) {
    element->data = NULL;
    element->next = NULL;
}

void add_list_element(struct list_element * head, void * data) { 
    if (head->data == NULL) {
        head->data = data;
    } else {
        struct list_element * tail = get_last_list_element(head);
        struct list_element * element = (struct list_element *) malloc(sizeof(struct list_element));
        init_list_element(element);
        element->data = data;
        tail->next = element;
    }
}

struct list_element * get_last_list_element(struct list_element * head) {
    struct list_element * current = head;
    while (current != NULL) {
        if (current->next == NULL) break;
        current = current->next;
    }
    return current;
}

void free_linked_list(struct list_element * head) {
    struct list_element * current = head->next;
    while (current != NULL) {
        struct list_element * next = current->next;
        free(current);
        current = next;
    }
}