#include <stdio.h>
#include "BSTree.h"

int main(void) {
    
    printf("===test BST insert===\n");
    Tree bst = newTree();
    bst = TreeInsert(bst, 5);
    bst = TreeInsert(bst, 3);
    bst = TreeInsert(bst, 7);
    bst = TreeInsert(bst, 8);
    bst = TreeInsert(bst, 2);
    bst = TreeInsert(bst, 4);
    bst = TreeInsert(bst, 6);
    printTree(bst);
    
    printf("===test BST height and Number of nodes===\n");
    int height = TreeHeight(bst);
    int number = TreeNumNodes(bst);
    printf("The height of bst is %d\n", height);
    printf("The number of bst's nodes is %d\n\n", number);

    printf("===test BST travel===\n");
    printf("Preorder: ");
    TreePrintPreorder(bst);
    printf("\n");
    printf("Inorder: ");
    TreePrintInorder(bst);
    printf("\n");
    printf("Postorder: ");
    TreePrintPostorder(bst);
    printf("\n\n");

    printf("===test BST search and find===\n");
    printf("Enter a node you want find: ");
    Item key;
    scanf("%d", &key);
    if (TreeSearch(bst, key)) {
        printf("Node with data %d exists\n", key);
        Tree sub = TreeFind(bst, key);
        int subHeight = TreeHeight(sub);
        int subNumber = TreeNumNodes(sub);
        printf("The height of subtree on this node is %d\n", subHeight);
        printf("The number of subtree's nodes on this node is %d\n\n", subNumber);
    } else {
        printf("Node with data %d doesn't exist\n\n", key);
    }

    printf("===test BST delete===\n");
    printf("Enter a node you want delete: ");
    Item delete_key;
    scanf("%d", &delete_key);
    bst = TreeDelete(bst, delete_key);
    printTree(bst);
    freeTree(bst);

    printf("===test insert at root===\n");
    Tree bst_two = newTree();
    bst_two = TreeInsert(bst_two, 10);
    bst_two = TreeInsert(bst_two, 5);
    bst_two = TreeInsert(bst_two, 14);
    bst_two = TreeInsert(bst_two, 30);
    bst_two = TreeInsert(bst_two, 29);
    bst_two = TreeInsert(bst_two, 32);
    printTree(bst_two);
    
    printf("Enter a number you want insert at root: ");
    Item key_root;
    scanf("%d", &key_root);

    bst_two = insertAtRoot(bst_two, key_root);
    printTree(bst_two);
    freeTree(bst_two);

    printf("Choose type of tree: \n");
    printf("AVL Tree insert: 1\n");
    printf("Splay Tree insert: 2\n");
    printf("Splay Tree seach: 3\n");
    printf("Enter type index: ");
    int type;
    scanf("%d", &type);
    if (type == 1) {
        printf("===test insert into a AVL Tree===\n");
        Tree AVLt = newTree();
        // AVLt = TreeInsert(AVLt, 14);
        Item key_avl;
        printf("Enter a number: ");
        while (scanf("%d", &key_avl) == 1) {
            AVLt = insertAVL(AVLt, key_avl);
            printTree(AVLt);
            printf("Enter a number: ");
        }
        freeTree(AVLt);

        printf("\n"); 
    } else if (type == 2) {
        printf("===test insert into a splay Tree===\n");
        Tree SplayT = newTree();
        // SplayT = TreeInsert(SplayT, 14);
        Item key_splay;
        printf("Enter a number: ");
        while (scanf("%d", &key_splay) == 1) {
            SplayT = InsertSplay(SplayT, key_splay);
            printTree(SplayT);
            printf("Enter a number: ");
        }
        freeTree(SplayT);  

        printf("\n");
    } else if (type == 3) {
        printf("===test search a splay Tree===\n");
        Tree SplayT = newTree();
        SplayT = TreeInsert(SplayT, 80);
        SplayT = TreeInsert(SplayT, 9);
        SplayT = TreeInsert(SplayT, 56);
        SplayT = TreeInsert(SplayT, 24);
        SplayT = TreeInsert(SplayT, 4);
        SplayT = TreeInsert(SplayT, -1);
        SplayT = TreeInsert(SplayT, 5);
        SplayT = TreeInsert(SplayT, 7);
        SplayT = TreeInsert(SplayT, 8);
        printTree(SplayT);
        Item key_splay;
        printf("Enter a number: ");
        scanf("%d", &key_splay);
        SplayT = Splay(SplayT, key_splay);
        printTree(SplayT);
        if (SplayT->data == key_splay) {
            printf("Item %d is in the splay tree\n\n", key_splay);
        } else {
            printf("Item %d is not in the splay tree\n\n", key_splay);
        }
        freeTree(SplayT);
    }
}