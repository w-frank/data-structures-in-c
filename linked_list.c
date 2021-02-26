/**
 * @file linked_list.c
 * @author Will Frank
 * @date 26 Feb 2021
 * @brief File containing linked list implementation in C. 
 *
 * Linked list data structure:
 *
 *  Head node                     Tail node
 * |data|next| -> |data|next| -> |data|next| -> NULL
 *
 * Operations:
 * - Insert node at nth position in list
 * - Delete node at nth position in list
 * - TODO: Delete nodes in list with a particular value
 * - Print all nodes in list
 * - Print all nodes in list in reverse (recursion)
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/** 
 * @struct node structure
 * @brief A single node in the linked list.
 */
typedef struct node {
    int data;               /**< Integer value stored in node.*/
    struct node* next_node; /**< Pointer to next node in linked list.*/
}node_t;

void insert_node(node_t** head_node_ptr, int data, int position);
void delete_node(node_t** head_node_ptr, int position);
void reverse_list(node_t** head_node_ptr);
void print_nodes(node_t* head_node);
void print_nodes_recursive(node_t* node_ptr, bool reverse);
void reverse_list_recursive(node_t* current_node, node_t* prev_node, node_t** head_node_ptr);

int main(void) {

    int node_position;

    node_t* head_node = NULL; // create empty list

    // Build linked list
    insert_node(&head_node, 2, 1);
    print_nodes(head_node);
    insert_node(&head_node, 3, 2);
    print_nodes(head_node);
    insert_node(&head_node, 4, 1);
    print_nodes(head_node);
    insert_node(&head_node, 5, 2);
    print_nodes(head_node);

    // User input to delete nodes
    printf("Enter a node position to delete:\n");
    scanf("%d", &node_position);
    delete_node(&head_node, node_position);
    print_nodes(head_node);

    // Reverse linked list
    printf("Reversing linked list...\n");
    reverse_list_recursive(head_node, NULL, &head_node);
    print_nodes(head_node);

}

/**
 * @brief Insert a new node holding @p data at @p position in a linked list.
 *
 * @param head_node_ptr Pointer to a pointer to the head of the linked list.
 * @param data Integer value to be stored in the new node.
 * @param position Position in the list to insert the new node.
 */
void insert_node(node_t** head_node_ptr, int data, int position) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t)); // allocate memory for new node
    // Initialise new node (no link yet)
    new_node->data = data;
    new_node->next_node = NULL;

    // If inserting new node into head then create link and update head pointer
    if (position == 1) {
        new_node->next_node = *head_node_ptr;
        *head_node_ptr = new_node;
        return;
    }
    // Else find node at position-1 and update links to include new node
    node_t* prev_node = *head_node_ptr;
    for(int i = 0; i < position-2; i++) {
        prev_node = prev_node->next_node;
    }
    new_node->next_node = prev_node->next_node;
    prev_node->next_node = new_node;

}

/**
 * @brief Delete an existing node from @p position in a linked list.
 *
 * @param head_node_ptr A pointer to a pointer to the head of the linked list.
 * @param position The position in the list of the node to be deleted.
 */
void delete_node(node_t** head_node_ptr, int position) {

    node_t* node_ptr_1 = *head_node_ptr; // start by pointing to the head node

    // If deleting existing head node
    if (position == 1) {
        *head_node_ptr = node_ptr_1->next_node; // update head pointer to second node
        free(node_ptr_1);                     // free memory of existing head node
        return;
    }
    // Else start by finding node at position-1
    for(int i = 0; i < position-2; i++) {
        node_ptr_1 = node_ptr_1->next_node;
    }
    node_t* node_ptr_2 = node_ptr_1->next_node;    // point to node at position
    node_ptr_1->next_node = node_ptr_2->next_node; // bypass node at position with next node links
    free(node_ptr_2);                              // free memory of node at position

}

/**
 * @brief Reverse the nodes in a linked list.
 *
 * @param head_node_ptr A pointer to a pointer to the head of the linked list.
 * @param position The position in the list of the node to be deleted.
 */
void reverse_list(node_t** head_node_ptr) {
    node_t* current_node = *head_node_ptr;
    node_t* prev_node = NULL;
    node_t* next_node;

    // Traverse linked list until the end
    while(current_node != NULL) {
        next_node = current_node->next_node; // store existing next node link
        current_node->next_node = prev_node; // reverse next node link
        prev_node = current_node;            // current node becomes previous
        current_node = next_node;            // next node becomes current
    }
    *head_node_ptr = prev_node;              // update head to the last node in list
}

/**
 * @brief Reverse the nodes in a linked list (recursive).
 *
 * @param current_node  A pointer to the current node (initially the head)
 * @param prev_node     A pointer to the previous node (initially NULL)
 * @param head_node_ptr A pointer to a pointer to the head of the linked list.
 */
void reverse_list_recursive(node_t* current_node, node_t* prev_node, node_t** head_node_ptr) {

    // Check for empty list
    if(head_node_ptr == NULL)
        return;

    // If last node in the list
    if(current_node->next_node == NULL) {
        *head_node_ptr = current_node;       // update head pointer to tail node
        current_node->next_node = prev_node; // reverse next node link
        return;
    }

    node_t* next_node = current_node->next_node; // store existing next node link
    current_node->next_node = prev_node;         // next node becomes previous

    // Repeat recursively, traversing list (next node becomes current node and current node becomes previous node)
    reverse_list_recursive(next_node, current_node, head_node_ptr);

}

/**
 * @brief Print the data values of all nodes in a linked list.
 *
 * @param head_node A pointer to the head node of the list to be printed.
 */
void print_nodes(node_t* head_node) {
    node_t* current_node = head_node; // start at the head node
    printf("Linked list: ");
    // Traverse the linked list, printing all data values until the end
    while(current_node != NULL) {
        if(current_node->next_node == NULL) {
            printf("%d", current_node->data); // if tail node omit trailing comma
        }
        else {
            printf("%d, ", current_node->data); // else include trailing comma
        }

        current_node = current_node->next_node;
    }
    printf("\n");
}

/**
 * @brief Print the data values of all nodes in a linked list (recursive).
 *
 * @param current_node A pointer to the current node to be printed (initially the head node).
 * @param reverse      Option to print linked list nodes in reverse (true=reversed, false=forward)
 */
void print_nodes_recursive(node_t* current_node, bool reverse) {
    // If list is empty or ar the end of the list
    if (current_node == NULL) {
        printf("\n");
        return;
    }
    // Else check if printing in reverse or not
    if(reverse) {
        // Traverse linked list, before returning to each node and printing
        print_nodes_recursive(current_node->next_node, true);
        printf("%d, ", current_node->data);

    }else {
        // Print current node and move on to the next
        printf("%d, ", current_node->data);
        print_nodes_recursive(current_node->next_node, false);
    }

}
