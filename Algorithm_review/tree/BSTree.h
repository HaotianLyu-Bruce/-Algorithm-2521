// Binary search tree.....COMP2521

#include <stdbool.h>

typedef int Item;

typedef struct Node *Tree;

struct Node {
   int  data;
   Tree left, right;
};

Tree newTree();        // create an empty Tree
Tree newNode(Item it); // create a new node
void freeTree(Tree t);   // free memory associated with Tree

bool TreeSearch(Tree t, Item it);   // check whether an item is in a Tree
Tree TreeFind(Tree t, Item it);  // find a node in the Tree, if not return NULL
int  TreeHeight(Tree t);         // compute height of Tree
int  TreeNumNodes(Tree t);       // count #nodes in Tree
Tree TreeInsert(Tree t, Item it);   // insert a new item into a Tree
Tree TreeDelete(Tree t, Item it);   // delete an item from a Tree
Tree joinTrees(Tree t1, Tree t2);   // join two trees t1 and t2

//Tree travel
void TreePrintPreorder(Tree t);
void TreePrintInorder(Tree t);
void TreePrintPostorder(Tree t);

Tree rotateRight(Tree n1);
Tree rotateLeft(Tree n2);
Tree insertAtRoot(Tree t, Item it);

//AVL Tree
Tree insertAVL(Tree t, Item it);

//Splay Tree
Tree InsertSplay(Tree t, Item it);
Tree Splay(Tree t, Item it);// move item to root, if not exist, move nearst node.

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
void printTree(Tree t);


