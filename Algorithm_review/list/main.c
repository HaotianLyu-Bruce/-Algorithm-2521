#include <stdio.h>
#include "list.h"

int main(void) {
    
    printf("==test insert at end==\n");
    List list_random = newList();
    insertIntoList(list_random, 2);
    insertIntoList(list_random, 3);
    insertIntoList(list_random, 6);
    insertIntoList(list_random, 4);
    insertIntoList(list_random, 5);
    insertIntoList(list_random, 7);
    insertIntoList(list_random, 1);
    printList(list_random);
    
    
    printf("==test insert sorted==\n");
    List list_sorted = newList();
    insertSortedList(list_sorted, 2);
    insertSortedList(list_sorted, 3);
    insertSortedList(list_sorted, 6);
    insertSortedList(list_sorted, 4);
    insertSortedList(list_sorted, 5);
    insertSortedList(list_sorted, 7);
    insertSortedList(list_sorted, 1);
    printList(list_sorted);

    printf("==test insert reversed==\n");
    List list_reversed = newList();
    insertReversedList(list_reversed, 2);
    insertReversedList(list_reversed, 3);
    insertReversedList(list_reversed, 6);
    insertReversedList(list_reversed, 4);
    insertReversedList(list_reversed, 5);
    insertReversedList(list_reversed, 7);
    insertReversedList(list_reversed, 1);
    printList(list_reversed);

}