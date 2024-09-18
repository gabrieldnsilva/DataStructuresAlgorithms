#include <stdio.h>
#include <stdlib.h>

struct Data {
    int data;
};

typedef struct Data Data;

struct stack {
    Data *dataList;
    Data *top;
    Data *bottom;
    int limit;
};

typedef struct stack stack;

void reset(stack *stack) {
    stack->bottom = NULL;
    stack->top = NULL;
    stack->dataList = NULL;
    stack->limit = 0;
}

void clear(stack *stack) {
    free(stack->dataList);
    reset(stack);
}

int empty(stack *stack) {
    if (stack->top == NULL) {
        return 1;
    }
    return 0;
}

int full(stack * stack) {
    Data *data;
    stack->limit++;
    if((stack->dataList = realloc(stack->dataList, sizeof(Data) * stack->limit)) == NULL){
    printf("Unable to allocate memory");
    stack->limit--;
    return 1;
}
    return 0;
}
void push(stack *stack, Data *includeData) {
    if(full(stack) == 0) {
        stack->dataList[stack->limit -1] = *includeData;
        stack->top = &stack->dataList[stack->limit -1];
        stack->bottom = stack->dataList;

        return;
    }
    return;
}

void list(stack *stack) {
    int cont = 0;
    for(; cont < stack->limit; cont++) {
        printf("\n Data[%d] = %d", cont + 1, stack->dataList[cont].data);

    }
}

void pop(stack *stack, Data *popData) {
    if (empty(stack)) {
        popData->data = -1;
        return;
    }

    popData = stack->top;
    stack->limit--;

    if(stack->limit <= 0){
        free(stack->dataList);
        reset(stack);
        return;
    }

    stack->top = &stack->dataList[stack->limit - 1];
    stack->bottom = stack->dataList;
    Data *temp = realloc(stack->dataList, sizeof(Data) * stack->limit);
    if (temp != NULL) {
        stack->dataList = temp;
    }else {

    }

    return;
}

stack *initialize() {
    stack *stack = malloc(sizeof(struct stack));
    reset(stack);
    stack->dataList = malloc(sizeof(Data) * stack->limit);
    return stack;
}

int menu() {

    int option = 0;
    do {
        printf("=====================================\n");
        printf("|              STACK MENU           |\n");
        printf("=====================================\n");
        printf("| 1 - Insert element into stack     |\n");
        printf("| 2 - Remove element from stack     |\n");
        printf("| 3 - List elements in stack        |\n");
        printf("| 4 - Clear stack                   |\n");
        printf("| 5 - Exit                          |\n");
        printf("=====================================\n");
        printf("Enter your option: ");
        scanf("%d", &option);
    }while(option < 1 || option > 5);
    getchar();
    return option;
}

int main() {
    stack *stack = initialize();
    int option = 0;
    Data *dataToManipulate = malloc(sizeof(Data));

    while(1) {
        option = menu();
        switch (option) {
            case 1:
                printf("What value to add? ");
                scanf("%d", &dataToManipulate->data);
                push(stack, dataToManipulate);
                break;
            case 2:
                pop(stack, dataToManipulate);
                if(dataToManipulate->data != -1) {
                    printf("Value removed: %d \n", dataToManipulate->data);

                }else {
                    printf("WARN: Empty list");
                }
                break;
            case 3:
                list(stack);
                break;
            case 4:
                clear(stack);
                break;
            case 5:
                clear(stack);
                exit(0);
                break;
        }
    }

    return 0;
}