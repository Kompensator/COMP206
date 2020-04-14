/** poly.c: linked list struc and fuctions for polyapp
Author: Ding Yi Zhang
Faculty: Science
To compile:
Changelog:
- April 8 16h10: initializing poly.c
- April 9 18h00: added struct PolyTerm
- April 12 12h30: addPolyTerm() and displayPolynomial() are both working!!
- April 12 12h45: evalutePolynomial() is also working! header file is sketch
- April 12 1h30: header file is working properly
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"


// struct for polynomial term object, aka linked list
struct PolyTerm {
    int coeff;
    int expo;
    struct PolyTerm *next;
};

// function declarations
int addPolyTerm(int coeff, int expo);
void displayPolynomial();
int evaluatePolynomial(int x);
void appendNode(struct PolyTerm *node);

// head tracks the first item in the list
struct PolyTerm *head = NULL;

int addPolyTerm(int coeff, int expo) {
    // creates the new node and and put data in it
    struct PolyTerm *nextNode = (struct PolyTerm *)malloc(sizeof(struct PolyTerm));
    if (nextNode == NULL) return(-1);
    nextNode->coeff = coeff;
    nextNode->expo = expo;
    nextNode->next = NULL;
    if (head == NULL) {
        head = nextNode;
    }
    else {
        appendNode(nextNode);
    }
    return(0);
}

void appendNode(struct PolyTerm *node) {
    struct PolyTerm *ptr1, *temp;
    ptr1 = head;
    // search for where to add the new node
    while(ptr1 != NULL) {
        if (node->expo < head->expo) {
            // case where the new node becomes the head
            temp = head;
            head = node;
            node->next = temp;
            break;
        }
        else if (ptr1->expo == node->expo) {
            // case where they have same exponent
            ptr1->coeff += node->coeff;
            break;
        }
        else if (ptr1->next == NULL) {
            // case where new node is appended at the back
            ptr1->next = node;
            break;
        }
        else if (ptr1->expo < node->expo && ptr1->next->expo > node->expo) {
            // case where the node has to inserted between 2 nodes
            temp = ptr1->next;
            ptr1->next = node;
            node->next = temp;
            break;
        }
        ptr1 = ptr1->next;
    }
}

void displayPolynomial() {
    // displays the polynomial to stdout according to the format
    struct PolyTerm *current;
    current = head;
    while(current != NULL) {
        printf("%dx%d", current->coeff, current->expo);
        if (current->next != NULL) {
            if (current->next->coeff >= 0) printf("+");
        }
        current = current->next;
    }
    printf("\n");
}

int evaluatePolynomial(int x) {
    /** calls utils.c/powi to compute the polynomial
     */
    struct PolyTerm *current;
    current = head;
    int sum = 0;
    while(current != NULL) {
        sum += current->coeff * powi(x, current->expo);
        current = current->next;
    }
    return sum;
}