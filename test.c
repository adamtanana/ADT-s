#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    t_list list = l_create(sizeof(int));

    // Init list with 40 numbers
    int i = 0;
    for (i = 0; i < 40; i++) {
        l_add(list, &i);
    }
   
   

    // Print each int with a single function
    void printints(Item item) {
        printf("%d, ", *(int*) item);
    }

    l_foreach(list, printints);



    // Create a new list based on the values of another list
    Item mapper(Item item) {
        int val = * (int*) item;

        return val % 2 == 0 ? "Even" : "Odd";
    }

    t_list lol = l_map(list, sizeof(char*), mapper);
    
     
    puts("\n");
    
    // Print the list out
    void printstrings(Item item) {
        printf("%s, ", (char*) item);
    }
    
    l_foreach(lol, printstrings);
    
    
    puts("\n");
    l_destroy(lol);
    l_destroy(list);
}

