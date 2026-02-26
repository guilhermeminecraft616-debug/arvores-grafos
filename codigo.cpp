#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 10000

// ---------- FUNÇÃO PARA IMPRIMIR ARRAY ----------
void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// ---------- BUBBLE SORT ----------
void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ---------- SELECTION SORT ----------
void selectionSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[min])
                min = j;
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

// ---------- INSERTION SORT ----------
void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ---------- QUICK SORT ----------
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ---------- MERGE SORT ----------
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];
    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ---------- SHELL SORT ----------
void shellSort(int arr[], int n) {
    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// ---------- GERAR ARRAY ALEATÓRIO ----------
void generateRandomArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

// ---------- MAIN ----------
int main() {
    int n, option;
    int original[MAX], arr[MAX];
    clock_t start, end;
    double time_spent;

    srand(time(NULL));

    printf("Digite o tamanho do array: ");
    scanf("%d", &n);

    generateRandomArray(original, n);

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Quick Sort\n");
        printf("5 - Merge Sort\n");
        printf("6 - Shell Sort\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &option);

        memcpy(arr, original, sizeof(int) * n);

        start = clock();

        switch(option) {
            case 1:
                bubbleSort(arr, n);
                break;
            case 2:
                selectionSort(arr, n);
                break;
            case 3:
                insertionSort(arr, n);
                break;
            case 4:
                quickSort(arr, 0, n - 1);
                break;
            case 5:
                mergeSort(arr, 0, n - 1);
                break;
            case 6:
                shellSort(arr, n);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        end = clock();
        time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;

        if(option >= 1 && option <= 6) {
            printf("Tempo de execucao: %f segundos\n", time_spent);
        }

    } while(option != 0);

    return 0;
}
