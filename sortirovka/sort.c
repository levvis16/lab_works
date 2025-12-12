#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int* copyArray(int original[], int n) {
    int* copy = (int*)malloc(n * sizeof(int));
    memcpy(copy, original, n * sizeof(int));
    return copy;
}

int* generateRandomArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

int isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void printResultsTable(double times[][3], int sizes[], int numSizes) {
    printf(" Размер массива   Сортировка пузырьком  Сортировка вставками   Сортировка слиянием  \n");
    
    for (int i = 0; i < numSizes; i++) {
        printf("║ %12d   ║", sizes[i]);
        
        for (int j = 0; j < 3; j++) {
            if (times[i][j] < 0.001 && times[i][j] > 0) {
                printf("     <0.001 ms       ║");
            } else if (times[i][j] >= 1000) {
                printf("     >1.000 s        ║");
            } else {
                printf("    %8.3f ms     ║", times[i][j]);
            }
        }
        printf("\n");
        
    }
}

int main() {
    srand(time(NULL));
    
    int sizes[] = {10, 1000, 10000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    
    double times[numSizes][3];
    
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int* original = generateRandomArray(n);
        
        for (int algo = 0; algo < 3; algo++) {
            int* arr = copyArray(original, n);
            
            clock_t start, end;
            double cpu_time_used;
            
            start = clock();
            
            switch (algo) {
                case 0:
                    bubbleSort(arr, n);
                    break;
                case 1:
                    insertionSort(arr, n);
                    break;
                case 2:
                    mergeSort(arr, 0, n - 1);
                    break;
            }
            
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
            
            if (!isSorted(arr, n)) {
                printf("Ошибка: массив не отсортирован правильно!\n");
            }
            
            times[i][algo] = cpu_time_used;
            
            free(arr);
        }
        
        free(original);
    }
    
    printResultsTable(times, sizes, numSizes);
    
    return 0;
}