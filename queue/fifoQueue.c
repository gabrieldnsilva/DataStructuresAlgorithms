#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info {
    int data;
};

typedef  struct info info;

struct node {
    info data;
    struct node *next;
};

typedef  struct node node;

struct heap {
    node *first;
    node *last;
};

typedef struct heap heap;

heap *reset() {
    heap *list  = (heap *)malloc(sizeof(heap));

    list->first = NULL;
    list->last = NULL;

    return list;
}

void append(heap *list, int data) {
    node *new;

    new = (node *)malloc(sizeof(node));
    new->data.data = NULL;

    if(list->last != NULL) {
        list->last->next = new;
    } else {
        list->first = new;
    }

    // Set new node as last element
    list->last = new;
}

int empty(heap *list) {
    if (list->first == NULL) {
        printf("Empty heap\n");

        return 1;
    } else {
        return 0;
    }
}

int pop(heap *list) {
    node *top;
    int data;

    // If the list is not empty
    if(list->first != NULL) {
        top = list->first;

        // Make the first now point to first->next
        list->first = list->first->next;

        // If it was the only element, change the last to NULL as well
        if(list->first == NULL) {
            list->last = NULL;
        }

        data = top->data.data;

        // Free the ex-head
        free(top);

        // Return the value that was removed
        return data;
    }

    // If empty return 0;
    return 0;
}

void print (heap *list) {
    if(empty(list) == 0) {
        node *currentNode = list->first;

        while(currentNode != NULL) {
            printf("\n Data: %d ", currentNode->data.data);
            currentNode = currentNode->next;
        }
    }
}


void clear(heap *list) {
    if(empty(list) == 0) {
        node *currentNode = list->first;
        node *toFree;

        while(currentNode != NULL) {
            toFree = currentNode;
            currentNode = currentNode->next;
            free(toFree);
        }
        free(list);
    }
}

int menu() {
    int option = 0;

    do {
        printf("\n==============================");
        printf("\n          MAIN MENU           ");
        printf("\n==============================");
        printf("\n 1. APPEND                   ");
        printf("\n 2. POP                      ");
        printf("\n 3. PRINT ELEMENTS           ");
        printf("\n 4. CLEAR LIST               ");
        printf("\n 5. EXIT                     ");
        printf("\n==============================");
        printf("\nChoose an option: ");
        scanf("%d", &option);
    } while(option < 1 || option > 5);
    getchar();

    return option;
}

int main(){
    heap *list;
    int data;

    list = reset();

    if (list == NULL) {
        printf("\nFailed in memory allocation");
        exit(-1);
    }

    while(1) {
        int option = menu();
        switch (option) {
            case 1:
                printf("Value to APPEND: ");
                scanf("%d", &data);
                append(list, data);
                break;
            case 2:
                if(empty(list) == 0) {
                    data = pop(list);
                    printf("\nRemoved: %d", data);
                }
                break;
            case 3:
                print(list);
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