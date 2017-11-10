/******************* BST_main.cpp ************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "get_message.h"    // Header file includes Prototypes defined in get_message.cpp
#include "queues.h"         // Header file includes Prototypes defined in queues.cpp
#include "nodes.h"          // Header file includes Prototypes defined in nodes.cpp
#include "BST.h"            // Header file includes Prototypes defined in BST.cpp

void main(int argc, char *argv[])
{
    FILE *fp;
    char szBuf[BUFFER_LENGTH] = { NULL };   // array to store retrieved message content
    int iLen = BUFFER_LENGTH;               // number of characters in szBuf
    int mNumber = atoi(argv[1]);            // number of quotes to retrieve
    int q_count = 0;                        // number of quotes in file
    char next_char = '1';                   // manages while loop for file analysis
    int i = 0;                              // int for loop counting
    Node *pNode, *pHead;                    // Node pointers for node creation
    Message BST_node_Q = { NULL };          // Empty Message to hold quote text for BST
    BST_link BST_Q_ptr;                     // Pointer to BST node holding Fortune quote

    //seed random number generator
    time_t seed;
    seed = time(NULL);
    srand(time(NULL));

    // open quote file and print error if file not found
    if (fopen_s(&fp, "FortuneCookies.txt", "r") != 0) {
        printf("Error opening quote list. Check reference file.");
    }

    // set q_count to be number of quotes in file
    while (next_char != EOF) {
        next_char = fgetc(fp);
        if (next_char == '%') {
            if (fgetc(fp) == '%') {
                q_count++;
            }
        }
    }

    // create an array of q_count size to store start position of each quote
    long* q_start;
    q_start = (long *)calloc(q_count, sizeof(long));

    // move file pointer back to start of file and reset next_char and q_count
    fseek(fp, 0, SEEK_SET);
    next_char = '1';
    q_count = 0;

    // populate q_start with the starting position of each quote
    while (next_char != EOF) {
        next_char = fgetc(fp);
        if (next_char == '%') {
            if (fgetc(fp) == '%') {
                q_start[q_count] = ftell(fp);
                q_count++;
            }
        }
    }

    fclose(fp); // close the file pointer
    
    // create 5 Message structures
    Message BTS_node_A = { "And this is crazy, ", 0, 0, 'x', 0, "nothing" };
    Message BTS_node_B = { "But here's my number, so", 0, 0, 'x', 0, "nothing" };
    Message BTS_node_C = { "Call me maybe.", 0, 0, 'x', 0, "nothing" };
    Message BTS_node_D = { "Don't need to type", 0, 0, 'x', 0, "nothing" };
    Message BTS_node_E = { "Every line of the song.", 0, 0, 'x', 0, "nothing" };

    // create empty binary search tree
    BSTInit();

    // insert each of 5 Message structures into BST
    BST_link B_ptr = Insert(BTS_node_B);
    BST_link E_ptr = Insert(BTS_node_E);
    BST_link A_ptr = Insert(BTS_node_A);
    BST_link C_ptr = Insert(BTS_node_C);
    BST_link D_ptr = Insert(BTS_node_D);

    // search for BTS_node_D
    Message found_message = Search("Don't need to type");

    // search for non-existant message
    Message no_found_message = Search("Not going to find this");

    // print search results
    printf("Search for 'Don't need to type' found: %s\n", found_message.text);
    printf("Search for 'Not going to find this' found: %s\n", no_found_message.text);

    // count nodes
    int BST_count = count(A_ptr);
    printf("Number of nodes in BST is: %d\n", BST_count);

    // determine tree height
    int BST_height = height(C_ptr);
    printf("Height of the BST is: %d\n", BST_height);

    printf("\n----------- BST with Fortune file starts here ------------\n\n");

    // create new empty binary search tree for Fortune quotes
    BSTInit();

    // for loop to 
    for (i = 0; i < mNumber; i++) {
        GetMessageFromFile(szBuf, iLen, q_start, q_count);  // populate szBuf
        memcpy(BST_node_Q.text, szBuf, strlen(szBuf) + 1);  // populate BST_node_Q.txt with szBuf
        BST_Q_ptr = Insert(BST_node_Q);                     // insert Message into BST
    }

    // print all BST message.text content in sorted (alphabetical) order
    BSTPrint(BST_Q_ptr);

    free(q_start);

    system("pause");
}


