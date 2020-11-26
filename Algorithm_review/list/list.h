#ifndef LIST_H
#define LIST_H

#include <stdbool.h> // Provides the constants 'true' and 'false'
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 1024

typedef struct node *Node;
struct node {
    int value;
    Node next;
};

typedef struct list *List;
struct list {
	Node head;
};

/**
 * Creates an empty list
 */
List newList(void);

/**
 * Creates a new node containing the given value.
 */
Node newNode(int value);

/**
 * insert a new node to the end of list
 */
List insertIntoList(List l, int value);

/**
 * insert a new node into a sorted list
 */
List insertSortedList(List l, int value);

/**
 * insert a new node into a sorted list
 */
List insertReversedList(List l, int value);

/**
 * check list is sorted and reversed or not
 */
bool listIsOrdered(List l);

/**
 * print the list
 */
void printList(List l);

#endif