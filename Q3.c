#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

// Node structure for linked list
typedef struct Node {
    char line[MAX_LINE_LENGTH];
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(const char* line) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        strcpy(newNode->line, line);
        newNode->next = NULL;
    }
    return newNode;
}

// Function to free memory allocated for the linked list
void freeLinkedList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to print the last n lines from the linked list
void printLastLines(Node* head, int n) {
    int count = 0;
    Node* current = head;

    // Count the total number of lines
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Ensure n is not greater than the total number of lines
    if (n > count) {
        n = count;
    }

    // Traverse to the starting point for printing
    current = head;
    int i;
    for (i = 0; i < count - n; i++) {
        current = current->next;
    }

    // Print the last n lines
    for (i = 0; i < n; i++) {
        printf("%s", current->line);
        current = current->next;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please provide a positive integer value for n.\n");
        return 1;
    }

    // Initialize variables
    Node* head = NULL;
    Node* tail = NULL;
    char line[MAX_LINE_LENGTH];

    // Read lines from standard input and create linked list nodes
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        Node* newNode = createNode(line);
        if (newNode == NULL) {
            printf("Memory allocation error.\n");
            freeLinkedList(head);
            return 1;
        }

        // Append new node to the linked list
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Print the last n lines from the linked list
    printf("Last %d lines:\n", n);
    printLastLines(head, n);

    // Free memory allocated for the linked list
    freeLinkedList(head);

    return 0;
}

