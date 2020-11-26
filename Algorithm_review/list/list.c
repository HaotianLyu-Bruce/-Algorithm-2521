#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

List newList(void) {
	List l = malloc(sizeof(struct list));
	if (l == NULL) {
		fprintf(stderr, "couldn't allocate list\n");
		exit(EXIT_FAILURE);
	}
	l->head = NULL;
	return l;
}

Node newNode(int value) {
	Node n = malloc(sizeof(struct node));
	if (n == NULL) {
		fprintf(stderr, "couldn't allocate node\n");
		exit(EXIT_FAILURE);
	}
	n->value = value;
	n->next = NULL;
	return n;
}

List insertIntoList(List l, int value) {
    assert(l != NULL);
    if (l->head == NULL) {
        Node new_node = newNode(value);
        l->head = new_node;
        return l;
    }
    Node curr = l->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode(value);
    return l;
}


List insertSortedList(List l, int value) {
    if (!listIsOrdered(l)) {
        fprintf(stderr, "array should be sorted\n");
		exit(EXIT_FAILURE);
    }
    assert(l != NULL);
    if (l->head == NULL) {
        l->head = newNode(value);
        return l;
    }
    if (value < l->head->value) {
        Node new_node = newNode(value);
        new_node->next = l->head;
        l->head = new_node;
        return l;
    }
    Node prev = l->head;
    Node curr = l->head->next;
    while (curr != NULL) {
        if (value <= curr->value) {
            break;
        }
        curr = curr->next;
        prev = prev->next;
    }
    Node new_node = newNode(value);
    new_node->next = curr;
    prev->next = new_node;
    return l;
}

List insertReversedList(List l, int value) {
    if (!listIsOrdered(l)) {
        fprintf(stderr, "array should be reversed\n");
		exit(EXIT_FAILURE);
    }
    assert(l != NULL);
    if (l->head == NULL) {
        l->head = newNode(value);
        return l;
    }
    if (value > l->head->value) {
        Node new_node = newNode(value);
        new_node->next = l->head;
        l->head = new_node;
        return l;
    }
    Node prev = l->head;
    Node curr = l->head->next;
    while (curr != NULL) {
        if (value >= curr->value) {
            break;
        }
        curr = curr->next;
        prev = prev->next;
    }
    Node new_node = newNode(value);
    new_node->next = curr;
    prev->next = new_node;
    return l;
}


bool listIsOrdered(List l) {
	if (l == NULL || l->head == NULL) {
		return true;
	}
	Node first = l->head;
	if (first->next == NULL) {
		return true;
	}
	int increase = 1;
	int decrease = 1;
	
	Node prev = l->head;
	Node curr = l->head->next;
	
	while (curr != NULL) {
		if (prev->value > curr->value) {
			increase = 0;
		}
		if (prev->value < curr->value) {
			decrease = 0;
		}
		prev = curr;
		curr = curr->next;
	}

	if (increase == 1 || decrease == 1) {
		return true;
	} else {
		return false;
	}
	
}


void printList(List l) {
	Node curr = l->head;
	while (curr != NULL) {
		printf("[%d] -> ", curr->value);
		curr = curr->next;
	}
	printf("X\n");
}