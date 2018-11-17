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

static void __check(char* s, void* p) {
    if (p)
        return;
        
    perror(s);
    exit(-1);
}

static int __indexOf(t_list list, int index) {
    return list->itemSize * index;
}

static void move(t_list list, int from, int to) {
    from = __indexOf(list, from);
    to = __indexOf(list, to);
    memcpy(&list->array[to], &list->array[from], list->itemSize);
}

// Moves elements around index to add an extra spot in array
static void __makeRoom(t_list list, int index) {
    for (int i = list->noItems; i > index; i--) {
        move(list, i-1, i);
    }
    list->noItems++;
}

static void __remove(t_list list, int index) {
    for (int i = index; i < list->noItems - 1; i++) {
        move(list, i+1, i);
    }
    list->noItems--;
}

void __insert(t_list list, int index, Item item) {
    int real_index = __indexOf(list, index);
    memcpy (&list->array[real_index], item, list->itemSize);
}


// Resize if noItems >= ARR_GROW_TRIGGER * arraySize
// Resize if noItems <= arraySize / ARR_GROW_TRIGGER
static void __resize(t_list list) {
    float arraySize = list->arraySize; 
    int newSize = arraySize;
    

    if (list->noItems >= ARR_GROW_TRIGGER * arraySize)
        newSize *= ARR_GROW_SCALE;
    else if (list->noItems <= arraySize / ARR_GROW_TRIGGER)
        newSize /= ARR_GROW_SCALE;
    else 
        return;
   
    if (newSize <= DEFAULT_ARR_SIZE) 
        return;

    // reallocarray __checks for integer overflow 
    char* newArray = (char*) reallocarray (list->array, list->itemSize, (int) newSize);
    __check("Resize", newArray);

    list->array = newArray;
    list->arraySize = (int) newSize;
}

/** Export Functions **/

t_list l_create(size_t type_size) {
    assert(type_size > 0);

    // Create list
    t_list new = calloc(sizeof(struct _list), 1);
    __check("Create list", new);

    // Create array
    new->array = calloc(type_size, DEFAULT_ARR_SIZE);
    __check("Create array", new->array);

    new->arraySize = DEFAULT_ARR_SIZE;
    new->itemSize = type_size;
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

int l_removeIndex(t_list list, int index) {
    if (index < 0 || index > list->noItems) 
        return 0;

    __remove(list, index);
    return 1;
}

int l_removeAll(t_list list, Item item) {
    if (list == NULL || item == NULL)
        return 0;
    
    int index;
    while ((index = l_indexOf(list, item)) != -1) {
        __remove(list, index);
    }

    return 1;
}

int l_indexOf(t_list list, Item item) {
    if (list == NULL)
        return -1;

    for (int i = 0; i < l_length(list); i++) {
        Item current = l_get(list, i);
        
        if (current == item || memcmp(current, item, list->itemSize)) {
            return i;
        }
    }

    return -1;
}

int l_contains(t_list list, Item item) {
    if (list == NULL)
        return 0;

    
    return l_indexOf(list, item) != -1;
}

int l_length(t_list list) {
    if (list == NULL)
        return 0;
    return list->noItems;
}

Item l_get(t_list list, int index) {
    if (index < 0 || index >= list->noItems)
        return NULL;

    index = __indexOf(list, index);
    
    return &list->array[index];
}

t_list l_clone(t_list list) {
    if (list == NULL)
        return NULL;

    t_list new = l_create(list->itemSize);

    for(int i = 0; i < 10; i++) {
        l_add(list, l_get(list, i));
    }   


    return new;
}

int l_equals(t_list lista, t_list listb) {
    if (l_length(lista) != l_length(listb)) 
        return 0;

    for (int i = 0; i < l_length(lista); i++) {
        Item current = l_get(listb, i);
        
        if (!l_contains(listb, current)) {
            return 0;
        }
    }


    for (int i = 0; i < l_length(listb); i++) {
        Item current = l_get(lista, i);
        
        if (!l_contains(lista, current)) {
            return 0;
        }
    }

    return 1;
}
