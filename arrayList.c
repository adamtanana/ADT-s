#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include "list.h"

#define DEFAULT_ARR_SIZE 32

// How much array should grow by
#define ARR_GROW_SCALE 2.0  

// When array should grow
#define ARR_GROW_TRIGGER 0.7

struct _list  {
    char* array;
    int arraySize;
    size_t itemSize;
    int noItems;
};

/** Static Functions **/

static void __check(void* p) {
    if (p)
        return;
    
    perror("ArrayList");
    exit(-1);
}

static int __indexOf(t_list list, int index) {
    return list->itemSize * index;
}

// Moves elements around index to add an extra spot in array
static void __makeRoom(t_list list, int index) {

    // Sanity check, i is at least 1. if index is 0, 0 !> 0, so loop wont run on index 0.
    for (int i = list->noItems+1; i > index; i--) {
        list->array[i] = list->array[i-1];
    }
    list->noItems++;
}

void __insert(t_list list, int index, Item item) {
    int real_index = __indexOf(list, index);
    memcpy (&list->array[real_index], item, list->itemSize);
}

// Resize if noItems >= ARR_GROW_TRIGGER * arraySize
// Resize if noItems <= arraySize / ARR_GROW_TRIGGER
static void __resize(t_list list) {
    int arraySize = list->arraySize; 
    int newSize = arraySize;
    
    if (list->noItems < ARR_GROW_TRIGGER * arraySize &&
            list->noItems > arraySize / ARR_GROW_TRIGGER) 
        return;
    
    if (list->noItems >= ARR_GROW_TRIGGER * arraySize)
        newSize *= ARR_GROW_SCALE;
    else if (list->noItems <= arraySize / ARR_GROW_TRIGGER)
        newSize /= ARR_GROW_SCALE;
    else 
        return;

    // reallocarray __checks for integer overflow 
    char* newArray = (char*) reallocarray (list->array, list->itemSize, newSize);
    __check(newArray);

    list->array = newArray;
    list->arraySize = newSize;
}

/** Export Functions **/

t_list l_create(size_t type_size) {
    assert(type_size > 0);

    // Create list
    t_list new = calloc(sizeof(struct _list), 1);
    __check(new);

    // Create array
    new->array = calloc(type_size, DEFAULT_ARR_SIZE);
    __check(new->array);

    return new;
}

void l_destroy(t_list list) {
    free(list->array);
    list->array = NULL;

    free(list);
}



int l_add(t_list list, Item item) {
    l_addIndex(list, item, list->noItems);
}

int l_addIndex(t_list list, Item item, int index) {
    __resize(list);

    if (item == NULL) 
        return 0;

    if (index < 0 || index > list->noItems) 
        return 0;
   

    // Make room around the index
    __makeRoom(list, index);
    __insert(list, index, item); 
    
    return 1;
}
