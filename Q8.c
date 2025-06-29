#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// (i) Creation
Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// (ii) Insertion
void insert_node(Node **head, int data, int position) {
    Node *new_node = create_node(data);

    if (*head == NULL) {
        new_node->next = new_node;
        *head = new_node;
        return;
    }
    Node *current = *head;

    if (position == 0) {
        new_node->next = *head;
        while (current->next != *head)
            current = current->next;
        current->next = new_node;
        *head = new_node;
        return;
    }

    for (int i = 0; i < position - 1 && current->next != *head; i++)
        current = current->next;

    new_node->next = current->next;
    current->next = new_node;
}

// (iii) Deletion
void delete_node(Node **head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node *current = *head;

    if (position == 0) {
        if ((*head)->next == *head) {
            free(*head);
            *head = NULL;
            return;
        }
        while (current->next != *head)
            current = current->next;

        Node *temp = *head;
        current->next = (*head)->next;
        *head = (*head)->next;
        free(temp);
        return;
    }
    for (int i = 0; i < position - 1 && current->next != *head; i++)
        current = current->next;

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
}

// (iv) Traversal
void traverse(Node *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node *temp = head;
    printf("Circular Linked List: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    Node *head = NULL;
    insert_node(&head, 10, 0);
    insert_node(&head, 20, 1);
    insert_node(&head, 30, 2);
    insert_node(&head, 5, 0);    
    insert_node(&head, 25, 3);    
    traverse(head);
    delete_node(&head, 0); 
    traverse(head);
    delete_node(&head, 2);   
    traverse(head);
    return 0;
}