#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    int vet[] = {5, 8, 3, 9, 4, 2, 6, 1, 7, 10, 14, 18, 20, 3, 4, 19, 115, 600, 230, 4, 1300, 10000, 7, 29, 612, 515, 447, 47, 400, 4000, 1000, 12, 29, 115, 167, 312};
    int n = sizeof(vet) / sizeof(vet[0]);

    imprimeVetor(vet, n);
    BlockSort(vet, n);
    imprimeVetor(vet, n);

    /*
    int vet_tam[5] = {100, 500, 1000, 5000, 10000};
	int vet_semente[5] = {1, 2, 3, 4, 5};
	benchmarkBlockSort(vet_tam, vet_semente);
	benchmarkMergeSort(vet_tam, vet_semente);
	benchmarkQuickSort(vet_tam, vet_semente);
	benchmarkInsertionSort(vet_tam, vet_semente);
	benchmarkSelectionSort(vet_tam, vet_semente);
	benchmarkBubbleSortInteligente(vet_tam, vet_semente);
	benchmarkBubbleSort(vet_tam, vet_semente);
    
    return 0;
}
