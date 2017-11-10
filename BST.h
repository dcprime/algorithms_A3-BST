#pragma once
/* BST.h: Header file for BST functions and definitions */

#include "nodes.h"  // Header file includes Prototypes defined in nodes.cpp

/******************* structure definitions ********************/

// BST_link is a pointer to a BSTNode
typedef struct BSTNode* BST_link;

// BSTNode contains a Message structure and pointers to left and right child nodes
struct BSTNode { Message message; BST_link pLeft, pRight; };

/******************** function prototypes ***********************/

void BSTInit(void);

BST_link NEW(Message message, BST_link left, BST_link right);

void BSTPrint(BST_link h);

Message BSTSearch(BST_link h, char *textSearchKey);

Message Search(char *textSearchKey);

BST_link BSTInsert(BST_link h, Message message);

BST_link Insert(Message message);

int count(BST_link h);

int height(BST_link h);