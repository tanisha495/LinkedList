#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function declarations
struct Node* createList();
struct Node* insertAtEnd(struct Node* head, int value);
struct Node* deleteNode(struct Node* head, int value);
void traverseList(struct Node* head);

int main() {
    struct Node* head = NULL;

    printf("Creating doubly linked list:\n");
    head = createList();

    printf("\nList after creation:\n");
    traverseList(head);

    printf("\nInserting value 50 at the end:\n");
    head = insertAtEnd(head, 50);
    traverseList(head);

    int valueToDelete;
    printf("\nEnter a value to delete: ");
    scanf("%d", &valueToDelete);
    head = deleteNode(head, valueToDelete);
    printf("List after deletion:\n");
    traverseList(head);

    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

// i) CREATION
struct Node* createList() {
    struct Node* head = NULL;
    int n, i, value;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("No nodes to create.\n");
        return NULL;
    }
    for (i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);
        head = insertAtEnd(head, value);
    }
    return head;
}

// ii) INSERTION 
struct Node* insertAtEnd(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }
    newNode->data = value;
    newNode->next = NULL;
    if (head == NULL) {
        newNode->prev = NULL;
        return newNode;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;

    return head;
}

// iii) DELETION
struct Node* deleteNode(struct Node* head, int value) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    struct Node* temp = head;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Value %d not found in the list.\n", value);
        return head;
    }
    if (temp == head) {
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }
    printf("Node with value %d deleted successfully.\n", value);
    free(temp);
    return head;
}

// iv) TRAVERSAL
void traverseList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Forward traversal: ");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        if (temp->next == NULL) break;
        temp = temp->next;
    }
    printf("\n");
    printf("Backward traversal: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}