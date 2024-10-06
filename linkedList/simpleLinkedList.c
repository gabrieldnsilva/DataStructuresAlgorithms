#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info {
    int data;
};

typedef struct info info;

struct node {
    info data;
    struct node *next;
};

typedef struct node node;

struct linkedList {
    node *head;
};

typedef struct linkedList linkedList;

linkedList *reset() {
    linkedList *list = (linkedList *)malloc(sizeof(linkedList));

    //Starts with NULL -> indicating the list is empty
    list->head = NULL;

    return list;
}

void push(linkedList *list, int data) {

    //  Dinamically allocate space for new node
    node *newNode = (node *)malloc(sizeof(node));

    //  Put data inside new node
    newNode->data.data = data;

    //  Make next of new node as head
    newNode->next = list->head;

    //  Move the head to point to the new node
    list->head = newNode;
}

int empty(linkedList *list) {

    if(list->head == NULL) return 1;

    return 0;
}

int pop(linkedList *list) {

    if(empty(list) == 1) return 0;

    int data;

    node *current = list->head;

    list->head = current->next;

    data = current->data.data;

    free(current);

    return data;
}

void clear(linkedList *list) {
    node *current = list->head;

    while(current->next != NULL) {
        node *elementToDelete = current;
        current = elementToDelete->next;

        free(elementToDelete);
    }

    free(current);

    free(list);
}

void printList(linkedList *list) {
    node *current = list->head;

    printf("\n----\tList----\n");
    while (current != NULL) {

        printf(" %d ", current->data.data);
        current = current->next;
    }
}

int menu() {
    int option = 0;

    do {
        printf("-- MENU:\n");
            printf("\t 1. PUSH\n");
            printf("\t 2. POP\n");
            printf("\t 3. PRINT ELEMENTS\n");
            printf("\t 4. CLEAR LIST\n");
            printf("\t 5. EXIT\n");
            printf("\t -- Select your option: ");
            scanf("%d", &option);
    }while (option < 1 || option > 5);

    getchar();
    return option;
}

int main() {
    linkedList *list;
    int data;

    list = reset();

    if (list == NULL) {
        printf("Memory allocation failure");
        exit(-1);
    }

    while (1) {
        int option = menu();
        switch (option) {
            case 1:
                printf("Value to PUSH: ");
                scanf("%d", &data);
                push(list, data);
                break;
            case 2:
                if (empty(list) == 0) {
                    data = pop(list);
                    printf("\n REMOVED: %d\n", data);
                }else {
                    printf("Empty List");
                }
                break;
            case 3:
                printList(list);
                break;
            case 4:
                clear(list);
                list = reset();
                break;
            case 5:
                clear(list);
                exit(0);
                break;
        }
    }

    return 0;
}