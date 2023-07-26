#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

// Node structure for linked list
typedef struct Node {
    char line[MAX_LINE_LENGTH];
    struct Node* next;
} Node;

Node* createNode(const char* line) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        strcpy(newNode->line, line);
        newNode->next = NULL;
    }
    return newNode;
}

void freeLinkedList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void printLastLines(Node* head, int n) {
    int count = 0;
    Node* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    if (n > count) {
        n = count;
    }
    current = head;
    int i;
    for (i = 0; i < count - n; i++) {
        current = current->next;
    }

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

    Node* head = NULL;
    Node* tail = NULL;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        Node* newNode = createNode(line);
        if (newNode == NULL) {
            printf("Memory allocation error.\n");
            freeLinkedList(head);
            return 1;
        }

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printf("Last %d lines:\n", n);
    printLastLines(head, n);

    freeLinkedList(head);

    return 0;
}

