#include <stdio.h>

void insertionSort(int data[], int length) {
    if (length <= 0) {
        printf("Array is empty. Cannot sort. \n");
        return;
    }

    int currentElement, index, j;
    for(j = 1; j < length; j++) {
        index = j - 1;
        currentElement = data[j];
        while ((index >= 0) && (currentElement < data[index])) {
            data[index+1] = data[index];
            index--;
        }
        data[index + 1] = currentElement;
    }
}

void printAll(int data[], int length) {
    int index;
    for (index = 0; index < length; index++) {
        printf("Data [%d] = %d \n", index + 1, data[index]);
    }
}

int main() {
    int data[] = {5, 2, 4, 6, 1, 6};
    int length = sizeof(data) / sizeof(data[0]);

    printf("Before sorting: \n");
    printAll(data, length);

    insertionSort(data, length);

    printf("\nAfter sorting:\n");
    printAll(data, length);

    return 0;
}