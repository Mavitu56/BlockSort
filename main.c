#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    int vet_tam[5] = {100, 500, 1000, 10000, 100000};
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
