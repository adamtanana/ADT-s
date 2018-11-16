// Abstract List Class
// TODO: Implement ArrayList, LinkedList
// Author: Adam Tanana

// Header guard
#ifndef LIST_H
#define LIST_H

// A list contains void* Pointers.
// A list is ordered.
// It is the callers responsibility to deference the pointer and ensure the pointer is valid
// On adding to a list, the memory is copied and malloc'ed seperately.
// There is no need to malloc the memory yourself.
// On creation of a list you must specify the length of the list type

typedef struct _list* t_list;
typedef void* Item;

/*
    Creates a new list of default size.
    Size of each element must be exactly `type_size`.
*/
t_list l_create(size_t type_size);

/*
    Destroys a list, freeing up all memory from the list
*/
void l_destroy(t_list);

/* 
     Add an item to the end of the list
     Returns index of item after added into the list.
     On creation of a list you must specify the length of the list type
*/
int l_add(t_list list, Item item);

/*
    Add an item at index `index` into the list. Moves elements to make room
    if index < 0 or index > len list. Will fail and return false
    On creation of a list you must specify the length of the list type
*/
int l_addIndex(t_list list, Item item, int index);

/* 
    Remove item from index `index`.
    Returns 1 if success, 0 otherwise.
*/
int l_removeIndex(t_list list, int index);

/* 
    Remove first occurence of item in the list.
    Returns 1 if success, 0 otherwise.
*/
int l_removeItem(t_list list, Item item);

/* 
    Remove All occurences of item in the list.
    Returns 1 if success, 0 otherwise.
*/
int l_removeAll(t_list list, Item item);

/*
    Returns length of list
*/
int l_length(t_list list);

/*
    Returns item at index `index`
*/
Item l_getList(t_list list, int index);

/*
    Returns item at index `index`
*/
Item l_union(t_list list, int index);

/*
    Returns if each list contains both;
      the same items
      the same number of items 
      the same item type
  
    1 if equal
    0 otherwise
*/
int l_equals(t_list lista, t_list listb);

/*
    Apply function `void apply(Item item)` to each element in list
*/
void l_foreach(t_list list, void (*apply)(Item));

/*
    Map each element from one type to another (types are arbritrary).
    Items are passed into `Item map(Item)` function, a new list is created 
    and returned. The new list contains all Items returned by map function.
    ie. 
    
    new_size should be the sizeof of the new list type.

    Item mapToHalf(Item item) {
        int number = *((int*) item);
        
        int new_value = number / 2;
        return &new_value;
    }


*/
t_list l_map(t_list list, size_t new_size, Item (*map)(Item));

#endif
