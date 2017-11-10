/******************* BST.cpp *************************
*                                                    *
*  Functions adapted from ESE lecture slides         *
*  on creating BST functions                         *
*                                                    *
*****************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "nodes.h"
#include "BST.h"

// ‘head’ points to root (private var)
static BST_link head;

// empty message for initializing an empty BSTNode
static Message NullMessage = {};

// Create an empty Binary Search Tree
void BSTInit(void) {
    head = NEW(NullMessage, NULL, NULL);  // start with empty
}

// NEW() function creates a new tree node using malloc()
BST_link NEW(Message message, BST_link left, BST_link right) {
    BST_link pNew = (BST_link)malloc(sizeof(*pNew));
    pNew->message = message;
    pNew->pLeft = left;
    pNew->pRight = right;
    return(pNew);
}

// print BST message content using inorder traversal
void BSTPrint(BST_link h)
{
    if (h == NULL) return;	// reached leaf
    BSTPrint(h->pLeft);
    printf("Key: %s\n", h->message.text);
    BSTPrint(h->pRight);
    return;
}

// Search for a key in the BST (using message in struct Message)
Message BSTSearch(BST_link h, char *textSearchKey) {
    int	 rc;
    if (h == NULL) return(NullMessage); // Got to end & not found
    rc = strcmp(textSearchKey, h->message.text);
    if (rc == 0) return(h->message); // Found it
    if (rc < 0) return(BSTSearch(h->pLeft, textSearchKey));
    else		   return(BSTSearch(h->pRight, textSearchKey));
}

// call BSTSearch without having to worry about main having access to "head"
Message Search(char *textSearchKey) { return(BSTSearch(head, textSearchKey)); }

// Insert a key in the BST. Uses message as before. 
BST_link BSTInsert(BST_link h, Message message) {
    int	 rc;
    if (h == NULL) return(NEW(message, NULL, NULL));//make leaves
    rc = strcmp(message.text, h->message.text); // Go left or right?
    if (rc < 0)
        h->pLeft = BSTInsert(h->pLeft, message);
    else
        h->pRight = BSTInsert(h->pRight, message);
    return(h);  // pointer to newly added node
}

// call Insert without having to worry about main having access to "head"
BST_link Insert(Message message)
{
    head = BSTInsert(head, message);
    return(head);
}

// count the number of nodes in a tree
int count(BST_link h) {
    if (h == NULL) return(0);
    return(count(h->pLeft) + count(h->pRight) + 1);
}

// determine greatest height of tree
int height(BST_link h) {
    int	iLeftH, iRightH;
    if (h == NULL) return(-1);
    iLeftH = height(h->pLeft);
    iRightH = height(h->pRight);
    if (iLeftH > iRightH)
        return(iLeftH + 1);
    else
        return(iRightH + 1);
}
