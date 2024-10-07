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
    struct node *prev;

};

typedef struct node node;

struct linkedList {

    node *head;
    node *tail;
    unsigned int size;

};

typedef struct linkedList linkedList;

linkedList *reset() {
    linkedList *list = (linkedList*)malloc(sizeof(linkedList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void push(linkedList *list, int data) {

    node *head = list->head;
    node *newNode = (node *)malloc(sizeof(node));

    newNode->data.data = data;
    newNode->prev = NULL;

    if (head == NULL) {

        list->head = newNode;
        list->tail = newNode;
        newNode->next = NULL;

    } else {

        head->prev = newNode;
        newNode->next = head;
        list->head = newNode;

    }

    list->size++;
}
void printList(linkedList *list) {
    node *current = list->head;
    printf("\n----- LIST -----\n");
    while (current != NULL) {
        printf(" %d ", current->data.data);
        current = current->next;
    }
}

int empty(linkedList *list) {

    if(list->head == NULL) return 1;

    return 0;
}

int pop(linkedList *list) {

    if(empty(list) == 1) return 0;

    int data;

    node *current = list->head;

    if (list->size == 1) {
        //3. Removes the only node of the list
        list->head = NULL;
        list->tail = NULL;

    }else {
        // Removes the first element
        list->head = current->next;
        list->head->prev = NULL;
    }

    // Save the current data to return
    data = current->data.data;

    //Free the current node to avoid memory leak
    free(current);

    //decrement list size;
    list->size--;

    return data;
}

void clear(linkedList *list) {
    node *current = list->head;

    while(current != NULL) {
        //Free all the elements from the list
        node *elementToDelete = current;
        current = elementToDelete->next;

        free(elementToDelete);
    }

    free(current);

    free(list);
}

int menu() {

    int option = 0;
    do {
        printf("\n -- MENU:\n");
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

    list =  reset();

    if (list == NULL) {
        printf("memory allocation failure");
        exit(-1);
    }

    while(1) {
        int option = menu();
        switch (option) {
            case 1:
                printf("Value to PUSH: ");
                scanf("%d", &data);
                push(list, data);
                break;
            case 2:
                if(empty(list) == 0) {
                    data = pop(list);
                    printf("\nRemoved data: %d\n", data);
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