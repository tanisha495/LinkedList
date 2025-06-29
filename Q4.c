#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createList();
struct Node* insertNode(struct Node* head, int value);
struct Node* deleteNode(struct Node* head, int value);
void traverseList(struct Node* head);

int main() {
    //creation
    printf("Creating a linked list...\n");
    struct Node* head = createList();
    
    //traversal
    printf("\nTraversing the initial list:\n");
    traverseList(head);
     
    //insertion
    printf("\nInserting a new node with value 50:\n");
    head = insertNode(head, 50);
    printf("After insertion, the list is:\n");
    traverseList(head);
    
    //deletion
    int valueToDelete = 50;
    printf("\nDeleting node with value %d:\n", valueToDelete);
    head = deleteNode(head, valueToDelete);
    printf("After deletion, new list is:");
    traverseList(head);
    
    // Free the list before exiting
    printf("\nFreeing memory\n");
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
    printf("Program completed successfully.\n");
    
    return 0;
}

// i) CREATION - Creates a new linked list
struct Node* createList() {
    struct Node* head = NULL;
    struct Node* temp = NULL;
    struct Node* newNode = NULL;
    int n, value, i;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Empty list created.\n");
        return NULL;
    }

    // Create the first node
    printf("Enter value for node 1: ");
    scanf("%d", &value);
    
    head = (struct Node*)malloc(sizeof(struct Node));
    if (head == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    head->data = value;
    head->next = NULL;
    temp = head;
    
    // Create remaining nodes
    for (i = 2; i <= n; i++) {
        printf("Node %d: ", i);
        scanf("%d", &value);
        
        newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed!\n");
            // Free previously allocated nodes
            while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp);
            }
            return NULL;
        }
        
        newNode->data = value;
        newNode->next = NULL;
        temp->next = newNode;
        temp = temp->next;
    }
    
    printf("List created\n");
    return head;
}

// ii) INSERTION
struct Node* insertNode(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }
    
    newNode->data = value;
    newNode->next = NULL;
    
    // If list is empty, make the new node as head
    if (head == NULL) {
        printf("Node inserted\n");
        return newNode;
    }
    
    // Traverse to the last node
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Insert at the end
    temp->next = newNode;
    printf("Node inserted\n");
    
    return head;
}

// iii) DELETION
struct Node* deleteNode(struct Node* head, int value) {
    if (head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return NULL;
    }
    
    struct Node *temp = head, *prev = NULL;
    
    // If head node itself holds the value to be deleted
    if (temp != NULL && temp->data == value) {
        head = temp->next;
        printf("Node with value %d deleted.\n", value);
        free(temp);
        return head;
    }
    
    // Search for the value to be deleted
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    
    // If value was not present in the list
    if (temp == NULL) {
        printf("Value %d not found in the list!\n", value);
        return head;
    }
    
    // Unlink the node from the list
    prev->next = temp->next;
    printf("Node with value %d deleted.\n", value);
    free(temp);
    
    return head;
}

// iv) TRAVERSAL
void traverseList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    printf("List elements: ");
    struct Node* temp = head;
    
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}