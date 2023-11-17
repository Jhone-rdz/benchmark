#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int linearSearch(int *numbers, int size, int target, double *executionTime) {
    clock_t start = clock();
    for (int i = 0; i < size; i++) {
        if (numbers[i] == target) {
            *executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
            return i;
        }
    }
    *executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
    return -1;
}

int sentinelSearch(int *numbers, int size, int target, double *executionTime) {
    clock_t start = clock();
    numbers[size] = target; 
    int i = 0;
    while (numbers[i] != target) {
        i++;
    }
    numbers[size] = 0; 
    *executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
    return i;
}

int binarySearch(int *numbers, int size, int target, double *executionTime) {
    clock_t start = clock();
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (numbers[mid] == target) {
            *executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
            return mid;
        } else if (numbers[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    *executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
    return -1;
}

    void generateRandomNumbersFile(const char *filename, int numNumbers) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < numNumbers; i++) {
        fprintf(file, "%d ", rand() % 1000 + 1);  
    }

    fclose(file);
}


    void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


    void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


    void bubbleSort(int *arr, int size, double *executionTime) {
    clock_t start = clock();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    *executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}


    void insertionSort(int *arr, int size, double *executionTime) {
    clock_t start = clock();
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    *executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}


    int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

    void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


    void compareAlgorithms(int *arr, int size) {
    double executionTime;

    // Bubble Sort
    int *arrBubble = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arrBubble[i] = arr[i];
    }
    bubbleSort(arrBubble, size, &executionTime);
    printf("Bubble Sort: Tempo de execução: %f segundos\n", executionTime);
    free(arrBubble);

    
    int *arrInsertion = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arrInsertion[i] = arr[i];
    }
    insertionSort(arrInsertion, size, &executionTime);
    printf("Insertion Sort: Tempo de execução: %f segundos\n", executionTime);
    free(arrInsertion);

    
    int *arrQuickIterative = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arrQuickIterative[i] = arr[i];
    }
    clock_t start = clock();
    quickSort(arrQuickIterative, 0, size - 1);
    executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
    printf("Quick Sort Iterativo: Tempo de execução: %f segundos\n", executionTime);
    free(arrQuickIterative);

   
    int *arrQuickRecursive = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arrQuickRecursive[i] = arr[i];
    }
    start = clock();
    quickSort(arrQuickRecursive, 0, size - 1);
    executionTime = ((double) (clock() - start)) / CLOCKS_PER_SEC;
    printf("Quick Sort Recursivo: Tempo de execução: %f segundos\n", executionTime);
    free(arrQuickRecursive);
}


int main() {
    const char *filename = "numbers.txt";
    int numNumbers;
    
    printf("Digite a quantidade de números a serem gerados: ");
    scanf("%d", &numNumbers);
    
    generateRandomNumbersFile(filename, numNumbers);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int *numbers = malloc(numNumbers * sizeof(int));
    for (int i = 0; i < numNumbers; i++) {
        fscanf(file, "%d", &numbers[i]);
    }
    fclose(file);

    int choice;
    do {
        
        printf("\n==== Menu Principal ====\n");
        printf("1. Operações de Busca de Elemento\n");
        printf("2. Operações de Classificação de Elementos\n");
        printf("3. Operações de Comparação entre Algoritmos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
               
                printf("\n==== Menu Busca de Elemento ====\n");
                int target;
                printf("Digite o número a ser procurado: ");
                scanf("%d", &target);

                double linearSearchTime, sentinelSearchTime, binarySearchTime;

                int linearResult = linearSearch(numbers, numNumbers, target, &linearSearchTime);
                printf("Linear Search: Tempo de execução: %f segundos. ", linearSearchTime);
                if (linearResult != -1) {
                    printf("Elemento encontrado na posição %d.\n", linearResult);
                } else {
                    printf("Elemento não encontrado.\n");
                }

                int sentinelResult = sentinelSearch(numbers, numNumbers, target, &sentinelSearchTime);
                printf("Sentinel Search: Tempo de execução: %f segundos. ", sentinelSearchTime);
                if (sentinelResult != -1) {
                    printf("Elemento encontrado na posição %d.\n", sentinelResult);
                } else {
                    printf("Elemento não encontrado.\n");
                }

                int binaryResult = binarySearch(numbers, numNumbers, target, &binarySearchTime);
                printf("Binary Search: Tempo de execução: %f segundos. ", binarySearchTime);
                if (binaryResult != -1) {
                    printf("Elemento encontrado na posição %d.\n", binaryResult);
                } else {
                    printf("Elemento não encontrado.\n");
                }
                break;

            case 2:
                
                printf("\n==== Menu Classificação de Elementos ====\n");
                double bubbleSortTime, insertionSortTime;

                int *arrBubble = malloc(numNumbers * sizeof(int));
                for (int i = 0; i < numNumbers; i++) {
                    arrBubble[i] = numbers[i];
                }
                bubbleSort(arrBubble, numNumbers, &bubbleSortTime);
                printf("Bubble Sort: Tempo de execução: %f segundos\n", bubbleSortTime);
                free(arrBubble);

                int *arrInsertion = malloc(numNumbers * sizeof(int));
                for (int i = 0; i < numNumbers; i++) {
                    arrInsertion[i] = numbers[i];
                }
                insertionSort(arrInsertion, numNumbers, &insertionSortTime);
                printf("Insertion Sort: Tempo de execução: %f segundos\n", insertionSortTime);
                free(arrInsertion);
                break;

            case 3:
                
                printf("\n==== Menu Comparação entre Algoritmos ====\n");
                compareAlgorithms(numbers, numNumbers);
                break;

            case 0:
                
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (choice != 0);

    free(numbers);
    return 0;
}
