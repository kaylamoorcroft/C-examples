/* 
 * File:	program.c 
 * Author:	Kayla Moorcroft 
 * Date:	2024/03/26 - 2024/03/28
 * Version:	1.0 
 * Purpose:	Doubly-linked list with number as identifier of node
 *          This program supports the following functions:
 *          - addNode(value): adds the node to the end of the list with the particular value
 *          - addNodePosition(value, position) - adds the node with value at position in the linked list.
 *          - deleteNode(value) - deletes the first node in the list with this value
 *          - deleteNodePosition(position) - deletes the node at position in the list.
 *          - printList(list) - will print the list starting at the head of the list
 *          - printListReverse(list) - will print the list from the tail instead of the head.
 * Notes:	The functions are implemented as part of a menu for the user to choose what operations to do with the list
 *          Can pass testing.txt as input instead of typing in manually to see how program works
 */
#include <stdio.h>
#include <stdlib.h>
// type definition for node - has pointer to next/previous 
typedef struct node {
    int data;
    struct node *next;
    struct node *previous;
} NodeT, *NodeTP;
// type definition for list - has head/tail node pointers
typedef struct {
    NodeTP first; // head of list
    NodeTP last; // tail
} ListT, *ListTP;
// list constructor - returns list pointer and sets head/tail pointers to NULL
ListTP constructList(void) {
    ListTP p;
    if ((p = malloc(sizeof(ListT))) == NULL) {
        return NULL;
    }
    p->first = NULL;
    p->last = p->first;
    return p;
}
// printing all the elements in the list
void printList(ListTP this) {
    NodeTP current = malloc(sizeof(NodeT));
    if (this->first == NULL) {
        printf("The list is empty.\n");
    }
    else {
        printf("The list:\n");
        for (current = this->first; current != NULL; current = current->next) {
            printf("%d\n", current->data);
        }
    }
} // printing the elements in the list in reverse order
void printListReverse(ListTP this) {
    NodeTP current = malloc(sizeof(NodeT));
    if (this->first == NULL) {
        printf("The list is empty.\n");
    }
    else {
        printf("The list in reverse:\n");
        for (current = this->last; current != NULL; current = current->previous) {
            printf("%d\n", current->data);
        }
    }
}
// allocate memory for a node and handle error if no memory available
NodeTP createNode(void) {
    NodeTP node;
    if ((node = malloc(sizeof(NodeT))) == NULL) {
        fprintf(stderr, "Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return node;
}
// add node to end of list, returns 1 if successful
int addNode(ListTP this, int data) {
    NodeTP node = createNode(); // allocate memory for node
    if (this->first == NULL) { // treat first node differently
        this->first = node;
    }
    else {
        this->last->next = node; // adding node to end of list
        node->previous = this->last;
    }
    node->data = data;
    this->last = node; // move reference for tail of list 
    return 1;
}
// add node at specific position, returns 1 if successful
// returns -1 if position index out of bounds and prints error
int addNodePosition(ListTP this, int data, int position) {
    if (position < 0) { // input validation
        fprintf(stderr, "Cannot add node. Specified index is negative\n");
        return -1;
    }
    int i = 0; // keeping track of current position
    NodeTP aux, node;
    aux = createNode(); // allocate memory for nodes
    node = createNode();
    if (this->first == NULL) { // treat empty list differently
        this->first = node;
    }
    else if (position == 0) { // adding node at start is different
        node->next = this->first;
        this->first->previous = node;
        this->first = node;
    }
    else { // traverse to node before specified position
        for (aux->next = this->first; (i < position) && (aux->next != NULL); aux = aux->next, i++)
            ;
        if (i != position) { // next node was NULL before reached position - out of bounds
            fprintf(stderr, "Cannot add node. Specified index out of bounds of list\n");
            return -1;
        }
        node->next = aux->next; // connecting rest of list to node
        aux->next = node; // adding node to list
        node->previous = aux;
        if (node->next == NULL) {
            this->last = node; // if at end of list, move reference for tail of list
        } else { // if not at end of list add backwards link to next element
            node->next->previous = node; 
        }
    }
    node->data = data;
    return 1;
}
// delete first node in list with specific value, returns 1 if successful
// returns 0 if nothing deleted (either empty list or value not found)
int deleteNode(ListTP this, int value) {
    NodeTP current;
    if (this->first == NULL) { // empty list
        return 0;
    }
    if (this->first->next == NULL) { // only 1 element
        free(this->first);
        this->first = NULL;
        return 1;
    }
    if (this->first->data == value) { // removing node from start is different
        current = this->first;
        this->first = current->next; // skip first element
        this->first->previous = NULL;
        free(current);
        return 1;
    }
    // traverse to node before node with specified value
    for (current = this->first; (current->next->data != value) && (current->next->next != NULL); current = current->next)
        ;
    if (current->next->data != value) { // couldn't find node with value
        fprintf(stderr, "Node not removed. Value not found in list\n");
        return 0; 
    }
    NodeTP next = current->next->next; // NULL if at end of list
    free(current->next);
    current->next = next; // link to rest of list
    if (next == NULL) {
        this->last = current; // if at end of list, move reference for tail of list
    } else { // if not at end of list link backwards as well
        next->previous = current; 
    }
    return 1;  
}
// delete node at specified, returns 1 if successful
// returns 0 if nothing deleted (empty list)
// returns -1 if position index out of bounds
int deleteNodePosition(ListTP this, int position) {
    if (position < 0) { // input validation
        fprintf(stderr, "Cannot remove node. Specified index is negative\n");
        return -1;
    }
    NodeTP current;
    int i = 0;
    if (this->first == NULL) { // empty list
        return 0;
    }
    if (this->first->next == NULL) { // only 1 element
        free(this->first);
        this->first = NULL;
        return 1;
    }
    if (position == 0) { // removing node from start is different
        current = this->first; 
        this->first = current->next; // skip first element
        this->first->previous = NULL;
        free(current);
        return 1;
    } 
    for (current = this->first; (i < position - 1) && (current->next->next != NULL); current = current->next, i++)
        ; // traverse to element before specified position
    if (i != position - 1) { // next node was NULL before reached position - out of bounds
        fprintf(stderr, "Cannot remove node. Specified index out of bounds of list\n");
        return -1;
    }
    NodeTP next = current->next->next; // NULL if at end of list
    free(current->next);
    current->next = next; // link to rest of list
    if (next == NULL) {
        this->last = current; // if at end of list, move reference for tail of list
    }
    else { // if not at end of list link backwards as well
        next->previous = current; 
    }
    return 1;  
}
// deallocate memory for list and nodes in list
int deleteList(ListTP this) {
    printf("Deleting whole list...\n");
    while(deleteNodePosition(this, 0))
        ;
    this->first = NULL;
    this->last = NULL;
    free(this);
    this = NULL;
    return 1;
}
// clear input till end of line - for readability in code 
void clearLine(void) {
	while(getchar() != '\n') 
			;
}
int main(void) {
    ListTP list;
    int option, value, position; // to use for user input
    if ((list = constructList()) == NULL) { // creating list
        fprintf(stderr, "Cannot allocate memory\n");
        return EXIT_FAILURE;
    }
    while(1) { // infinite loop and only breaking out of it when user types 'q'
		printf("--- Choose an option for the linked list ---\n"
		"1. Add node at end of list \n2. Add node at specific position \n"
		"3. Delete the first node found in list with a specific value \n"
        "4. Delete node at specific position \n"
        "5. Print list normally \n6. Print list in reverse \n"
		"Enter 1/2/3/4/5/6 or enter 'q'uit to stop the program \n > ");
    	option = getchar(); // getting user input for menu option
		clearLine();
		putchar('\n'); 
        switch(option) { // different operation based on option
            // adding node to end of list
			case '1':	printf("Enter a number to add to the end of the list > ");
						scanf("%d", &value);
                        clearLine();
						addNode(list, value);
						break;
            // adding node at specific position
			case '2':	printf("Enter a number to add to the list > ");
						scanf("%d", &value);
                        clearLine();
                        printf("Enter position to add number > ");
						scanf("%d", &position);
                        clearLine();
						addNodePosition(list, value, position);
						break;
            // deleting node from list based on value
			case '3':	printf("Enter a number to delete from the list > ");
						scanf("%d", &value);
                        clearLine();
						if (deleteNode(list, value) == 0) {
                            fprintf(stderr, "Node not removed - list is empty.\n");
                        }
						break;
            // deleting node from list based on position
            case '4':	printf("Enter position of node to delete > ");
						scanf("%d", &position);
                        clearLine();
						if (deleteNodePosition(list, position) == 0) {
                            fprintf(stderr, "Node not removed - list is empty.\n");
                        }
						break;
            // printing list normally
            case '5':   printList(list);
						break;
            // printing list in reverse
            case '6':   printListReverse(list);
						break;
            // quit program 
            case 'Q':
            case 'q':   deleteList(list); // deallocate memory
                        printf("Goodbye.\n");
                        return EXIT_SUCCESS;
            default:    printf("Invalid input... try again\n");
        }
        printf("-----\n\n");
    }
}
