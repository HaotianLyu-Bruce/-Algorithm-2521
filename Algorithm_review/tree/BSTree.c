#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "BSTree.h"

static int *insertionSortCopy(int *array, int arraySize);
static void insertionSort(int *array, int arraySize);


// create an empty Tree
Tree newTree() {
    return NULL;
}

// create a new node
Tree newNode(Item it) {
    Tree new_node = malloc(sizeof(struct Node));
    assert(new_node != NULL);
    new_node->data = it;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// free memory associated with Tree
void freeTree(Tree t) {
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        free(t);
    }
}

// check whether an item is in a Tree
bool TreeSearch(Tree t, Item it) {
    if (t == NULL) {
        return false;
    } else if (it > t->data) {
        return TreeSearch(t->right, it);
    } else if (it < t->data) {
        return TreeSearch(t->left, it);
    } else { // it == t->data
        return true;
    }
}

// find a node in the Tree, if not return NULL
Tree TreeFind(Tree t, Item it) {
    if (t == NULL) {
        return NULL;
    }
    if (t->data == it) {
        return t;
    } else if (t->data < it) {
        return TreeFind(t->right, it);
    } else {
        return TreeFind(t->left, it);
    }
}

// compute height of Tree
int TreeHeight(Tree t) {
    if (t == NULL) {
        return -1;
    }
    int leftHeight = 1 + TreeHeight(t->left);
    int rightHeight = 1 + TreeHeight(t->right);
    if (leftHeight > rightHeight) {
        return leftHeight;
    } else {
        return rightHeight;
    }
} 


// count #nodes in Tree
int  TreeNumNodes(Tree t) {
    if (t == NULL) {
        return 0;
    }
    return 1 + TreeNumNodes(t->left) + TreeNumNodes(t->right);
} 

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
    if (t == NULL) {
        t = newNode(it);
    } else if (it < t->data) {
        t->left = TreeInsert(t->left, it);
    } else if (it > t->data){
        t->right = TreeInsert(t->right, it);
    }
    return t;
}

//Tree travel:
//print the tree with preorder(NLR)
void TreePrintPreorder(Tree t) {
	if (t != NULL) {
		printf("%d ", t->data);
		TreePrintPreorder(t->left);
		TreePrintPreorder(t->right);
	}
}
//print the tree in-order(LNR)
void TreePrintInorder(Tree t) {
	if (t != NULL) {
		TreePrintInorder(t->left);
		printf("%d ", t->data);
		TreePrintInorder(t->right);
	}
}
//print the tree postorder(LRN)
void TreePrintPostorder(Tree t) {
	if (t != NULL) {
		TreePrintPostorder(t->left);
		TreePrintPostorder(t->right);
		printf("%d ", t->data);
	}
}

// join two trees t1 and t2
Tree joinTrees(Tree t1, Tree t2) {
	if (t1 == NULL) {
		return t2;
	} else if (t2 == NULL) {
		return t1;
	} else {
		Tree curr = t2;
		Tree parent = NULL;
		while (curr->left != NULL) {
			parent = curr;
			curr = curr->left;
		}
		if (parent != NULL) {
			parent->left = curr->right;
			curr->right = t2;
		}
		curr->left = t1;
		return curr;
	}
}


// delete an item from a Tree (use join)
Tree TreeDelete(Tree t, Item it) {
    if (t != NULL) {
		if (it > t->data) {
			t->right = TreeDelete(t->right, it);
		} else if(it < t->data) {
			t->left =  TreeDelete(t->left, it);
		} else {
			Tree new;
			if (t->left == NULL && t->right == NULL) {
				new = NULL;
			} else if (t->left == NULL) {
				new = t->right;
			} else if (t->right == NULL) {
				new = t->left;
			} else {
				new = joinTrees(t->left, t->right);
			}
			free(t);
			t = new;
		}
	}
	return t;
} 

//rotate Right at n1
Tree rotateRight(Tree n1) {
	if (n1 == NULL || n1->left == NULL) {
		return n1;
	}
	Tree n2 = n1->left;
	n1->left = n2->right;
	n2->right = n1;
	return n2;
}

//rotate Left at n2
Tree rotateLeft(Tree n2) {
	if (n2 == NULL || n2->right == NULL) {
		return n2;
	}
	Tree n1 = n2->right;
	n2->right = n1->left;
	n1->left = n2;
	return n1;
}

//insert item to the root of tree
Tree insertAtRoot(Tree t, Item it) {
	if (t == NULL) {
		t = newNode(it);
	} else if (it < t->data) {
		t->left = insertAtRoot(t->left, it);
		t = rotateRight(t);
	} else if (it > t->data) {
		t->right = insertAtRoot(t->right, it);
		t = rotateLeft(t);
	}
	return t;
}

Tree insertAVL(Tree t, Item it) {
	if (t == NULL) {
		return newNode(it);
	}
	if (it == t->data) {
		return t;
	}
	if (it > t->data) {
		t->right = insertAVL(t->right, it);
	} else if (it < t->data) {
		t->left = insertAVL(t->left, it);
	}
	int LHeight = TreeHeight(t->left);
	int RHeight = TreeHeight(t->right);
	if ((LHeight - RHeight) > 1) {
		if (it > t->left->data) {
			t->left = rotateLeft(t->left);
		}
		t = rotateRight(t);
	} else if ((RHeight - LHeight) > 1) {
		if (it < t->right->data) {
			t->right = rotateRight(t->right);
		}
		t = rotateLeft(t);
	}
	return t;
}

Tree InsertSplay(Tree t, Item it) {
	if (t == NULL) {
		return newNode(it);
	}
	if (it == t->data) {
		return t;
	}
	if (it < t->data) {
		if (t->left == NULL) {
			t->left = newNode(it);
		} else if (it < t->left->data) {
			t->left->left = InsertSplay(t->left->left, it);
			t = rotateRight(t);
		} else {
			t->left->right = InsertSplay(t->left->right, it);
			t->left = rotateLeft(t->left);
		}
		return rotateRight(t);
	} else if (it > t->data) {
		if (t->right == NULL) {
			t->right = newNode(it);
		} else if (it > t->right->data) {
			t->right->right = InsertSplay(t->right->right, it);
			t = rotateLeft(t);
		} else {
			t->right->left = InsertSplay(t->right->left, it);
			t->right = rotateRight(t->right);
		}
		return rotateLeft(t);
	}
}


Tree Splay(Tree t, Item it) {
	if (t == NULL) {
		return t;
	}
	if (it == t->data) {
		return t;
	}
	if (it < t->data) {
		if (t->left == NULL) {
			return t;
		} else if (it < t->left->data) {
			t->left->left = Splay(t->left->left, it);
			t = rotateRight(t);
		} else {
			t->left->right = Splay(t->left->right, it);
			t->left = rotateLeft(t->left);
		}
		return rotateRight(t);
		//return (t->left == NULL)? t: rotateRight(t);
	} else if (it > t->data) {
		if (t->right == NULL) {
			return t;
		} else if (it > t->right->data) {
			t->right->right = Splay(t->right->right, it);
			t = rotateLeft(t);
		} else {
			t->right->left = Splay(t->right->left, it);
			t->right = rotateRight(t->right);
		}
		return rotateLeft(t);
		//return (t->right == NULL)? t:rotateLeft(t);
	}
}



////////////////////////////////////////////////////////////////////////
// Printing a Tree
//
// The following section contains code to display a tree.
// This code is very complicated. You do not need to understand these
// functions.
//
// ASCII tree printer
// Courtesy: ponnada
// Via: http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/

#include <string.h>

static int max(int x, int y) {
	if (x > y) {
		return x;
	} else {
		return y;
	}
}

// Data structures
typedef struct asciinode_struct asciinode;
struct asciinode_struct
{
	asciinode *left, *right;
	// Length of the edge from this node to its children
	int edge_length;
	int height;
	int lablen;
	// -1 = I am left, 0 = I am root, 1 = I am right
	int parent_dir;
	// Max supported unit32 in dec, 10 digits max
	char label[11];
};

static void print_level(asciinode *node, int x, int level);
static void compute_edge_lengths(asciinode *node);
static asciinode *build_ascii_tree_recursive(Tree t);
static asciinode *build_ascii_tree(Tree t);
static void free_ascii_tree(asciinode *node);
static void compute_lprofile(asciinode *node, int x, int y);
static void compute_rprofile(asciinode *node, int x, int y);

#define MAX_HEIGHT 1000
static int lprofile[MAX_HEIGHT];
static int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

static int gap = 3; // Gap between left and right nodes

// Used for printing the next node in the same level
// This is the x coordinate of the next char printed
static int print_next;

// Prints ascii tree for given Tree structure
void printTree(Tree t)
{
	printf("\n");
	asciinode *proot;
	int xmin, i;
	if (t == NULL) {
		printf("X\n\n");
		return;
	}
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
		lprofile[i] = INFINITY;
	}
	
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
		xmin = MIN(xmin, lprofile[i]);
	}
	
	for (i = 0; i < proot->height; i++) {
		print_next = 0;
		print_level(proot, -xmin, i);
		printf("\n");
	}
	
	if (proot->height >= MAX_HEIGHT) {
		printf("(Tree is taller than %d; may be drawn incorrectly.)\n",
		       MAX_HEIGHT);
	}
	
	free_ascii_tree(proot);
	printf("\n");
}

// This function prints the given level of the given tree, assuming
// that the node has the given x coordinate.
static void print_level(asciinode *node, int x, int level)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	
	if (level == 0) {
		for (i = 0; i < (x - print_next - ((node->lablen - isleft)/2)); i++) {
			printf(" ");
		}
		print_next += i;
		printf("%s", node->label);
		print_next += node->lablen;
		
	} else if (node->edge_length >= level) {
		if (node->left != NULL) {
			for (i = 0; i < (x - print_next - (level)); i++) {
				printf(" ");
			}
			print_next += i;
			printf("/");
			print_next++;
		}
		
		if (node->right != NULL) {
			for (i = 0; i < (x - print_next + (level)); i++) {
				printf(" ");
			}
			print_next += i;
			printf("\\");
			print_next++; 
		}
		
	} else {
		print_level(node->left,
		            x - node->edge_length - 1,
		            level - node->edge_length - 1);
		print_level(node->right,
		            x + node->edge_length + 1,
		            level - node->edge_length - 1);
	}
}

// This function fills in the edge_length and
// height fields of the specified tree
static void compute_edge_lengths(asciinode *node)
{
	int h, hmin, i, delta;
	if (node == NULL) return;
	compute_edge_lengths(node->left);
	compute_edge_lengths(node->right);
	
	// First fill in the edge_length of node
	if (node->right == NULL && node->left == NULL) {
		node->edge_length = 0;
	
	} else {
		if (node->left == NULL) {
			hmin = 0;
		} else {
			for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++) {
				rprofile[i] = -INFINITY;
			}
			compute_rprofile(node->left, 0, 0);
			hmin = node->left->height;
		}
		
		if (node->right == NULL) {
			hmin = 0;
		} else {
			for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++) {
				lprofile[i] = INFINITY;
			}
			compute_lprofile(node->right, 0, 0);
			hmin = MIN(node->right->height, hmin);
		}
		
		delta = 4;
		for (i = 0; i < hmin; i++) {
			delta = max(delta, gap + 1 + rprofile[i] - lprofile[i]);
		}
		
		// If the node has two children of height 1, then we allow the
		// two leaves to be within 1, instead of 2
		if (delta > 4 &&
			((node->left != NULL && node->left->height == 1) ||
			(node->right != NULL && node->right->height == 1))) {
			delta--;
		}
		node->edge_length = ((delta + 1)/2) - 1;
	}
	
	// Now fill in the height of the node
	h = 1;

	if (node->left != NULL) {
		h = MAX(node->left->height + node->edge_length + 1, h);
	}
	if (node->right != NULL) {
		h = MAX(node->right->height + node->edge_length + 1, h);
	}
	
	node->height = h;
}

static asciinode *build_ascii_tree_recursive(Tree t)
{
	asciinode *node;
	
	if (t == NULL) return NULL;
	
	node = malloc(sizeof(asciinode));
	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);
	
	if (node->left != NULL) node->left->parent_dir = -1;
	if (node->right != NULL) node->right->parent_dir = 1;
	
	sprintf(node->label, "%d", t->data);
	
	node->lablen = (int)strlen(node->label);
	return node;
}

// Copy the tree into the ascii node structre
static asciinode *build_ascii_tree(Tree t)
{
	asciinode *node;
	if (t == NULL) return NULL;
	node = build_ascii_tree_recursive(t);
	node->parent_dir = 0;
	return node;
}

// Free all the nodes of the given tree
static void free_ascii_tree(asciinode *node)
{
	if (node == NULL) return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

// It assumes that the center of the label of the root of this tree
// is located at a position (x, y). It assumes that the edge_length
// fields have been computed for this tree.
static void compute_lprofile(asciinode *node, int x, int y)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft)/2));
	if (node->left != NULL) {
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
			lprofile[y + i] = MIN(lprofile[y + i], x - i);
		}
	}
	compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
	compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

static void compute_rprofile(asciinode *node, int x, int y)
{
	int i, notleft;
	if (node == NULL) return;
	notleft = (node->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft)/2));
	if (node->right != NULL) {
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
			rprofile[y + i] = MAX(rprofile[y + i], x + i);
		}
	}
	compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
	compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}


////////////////////////////////////////////////////////////////////////
// Insertion Sort

static int *insertionSortCopy(int *array, int arraySize) {
	int *copy = malloc(arraySize * sizeof(int));
	if (copy == NULL) {
		fprintf(stderr, "Insufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	
	for (int i = 0; i < arraySize; i++) {
		copy[i] = array[i];
	}
	insertionSort(copy, arraySize);
	return copy;
}

static void insertionSort(int *array, int arraySize) {
	for (int i = 1; i < arraySize; i++) {
		int temp = array[i];
		while (i > 0 && array[i - 1] > temp) {
			array[i] = array[i - 1];
			i--;
		}
		array[i] = temp;
	}	
}
