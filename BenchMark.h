#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

typedef struct Return;
void bubbleSort(int *vet, int tam);
void selectionSort(int *vet, int tam);
void insertionSort(int *vet, int tam);
void quickSort(int *vet, int inicio, int fim);
void mergeSort(int *vet, int inicio, int fim) ;
void merge(int *vet, int inicio, int meio, int fim);
int* geraAleatorios(int tam, int semente);
int* geraQuaseOrdenados(int tam, int porcentagem);
int* geraOrdenados(int tam, int ordem);
void benchmarkBubbleSort(int *vet_tam, int *vet_semente);
void benchmarkSelectionSort(int *vet_tam, int *vet_semente);
void benchmarkInsertionSort(int *vet_tam, int *vet_semente);
void benchmarkQuickSort(int *vet_tam, int *vet_semente);
void benchmarkMergeSort(int *vet_tam, int *vet_semente);

#endif /* SORTING_ALGORITHMS_H */
