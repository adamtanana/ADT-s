#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define DEFAULT_ARR_SIZE 32

// How much array should grow by
#define ARR_GROW_SCALE 2.0  

// When array should grow
#define ARR_GROW_TRIGGER 0.7

struct _list  {
    Item* array;
    int arraySize;
    int itemSize;
    int noItems;
}

void check(void* p) {
    if (p)
        return;
    
    perror("ArrayList");
    exit(-1);
}

t_list l_create(size_t type_size) {
    assert(type_size > 0);

    // Create list
    t_list new = calloc(sizeof struct _list, 1);
    check(new);

    // Create array
    new->array = calloc(type_size, DEFAULT_ARR_SIZE);
    check(new->array);

    return new;
}

void l_destroy(t_list list) {
    free(list->array);
    list->array = NULL;

    free(list);
}


