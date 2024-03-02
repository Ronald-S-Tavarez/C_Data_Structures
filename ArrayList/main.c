/**
 * My own implementation of a basic arraylist in C
 * Missing Functionality Includes:
 *  Resize capacity to length, 
 *  Element Removal by Index, 
 *  Element Insertion at Index,
 *  Element Find,
 *  ArrayList Sort,
 *  ArrayList Foreach,
 *  ArrayList Clear
 *  
*/
#include <stdio.h>
#include "ArrayList.h"

struct Person {
    int age;
    char first_name [20];
};

void print_person_list(struct ArrayList * person_list);

int main(int argc, char ** argv) {
    struct Person person_one = { .age = 25, .first_name = "Ronald" };
    struct Person person_two = { .age = 23, .first_name = "Garry" };
    struct Person person_three = { .age = 27, .first_name = "Ari" };

    struct ArrayList * person_list = array_list_create(sizeof(struct Person), 3);

    array_list_push(person_list, &person_one);
    array_list_push(person_list, &person_two);
    array_list_push(person_list, &person_three);

    print_person_list(person_list);

    for (size_t i = person_list->length; i > 0; i--) {
        printf("\nPopping one person from ArrayList...\n\n");
        struct Person * removed_person = array_list_pop(person_list);
        print_person_list(person_list);
        printf("Removed Person { name: %s, age: %d }\n", removed_person->first_name, removed_person->age);
        free(removed_person);
    }

    array_list_destroy(person_list);
    return 0;
}

void print_person_list(struct ArrayList * person_list) {
    for (size_t i = 0; i < person_list->length; i++) {
        struct Person * person = (struct Person *)array_list_at(person_list, i);
        if (person) 
            printf("struct Person { name: %s, age: %d }\n", person->first_name, person->age);
    }
}