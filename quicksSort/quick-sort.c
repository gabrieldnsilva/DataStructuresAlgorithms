#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to avoid worst case when define pivot
int medianOfThree(int data[], int left, int right) {
    int mid = (left + right) / 2;

    // Colocar os três valores (data[left], data[mid], data[right]) em ordem
    if (data[left] > data[mid]) {
        swap(&data[left], &data[mid]);
    }
    if (data[left] > data[right]) {
        swap(&data[left], &data[right]);
    }
    if (data[mid] > data[right]) {
        swap(&data[mid], &data[right]);
    }

    return data[mid];
}

void quickSort(int data[], int left, int right) {
    if (left >= right) return;  // Base case

    int i = left;
    int j = right;

    int pivot = medianOfThree(data, left, right);

    do {
        while (data[i] < pivot) i++;
        while (data[j] > pivot) j--;
        if (i <= j) {
            swap(&data[i], &data[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) quickSort(data, left, j);
    if (i < right) quickSort(data, i, right);
}

void printAll(int data[], int length) {
    for (int i = 0; i < length; i++) {
        printf("Data[%d] = %d \n", i + 1, data[i]);
    }
}

int main() {
    int data[] = {5, 7, 500, 250, 375, 222, 10, 23, 19, 1050};
    int length = sizeof(data) / sizeof(data[0]);

    quickSort(data, 0, length - 1);
    printAll(data, length);

    return 0;
}
