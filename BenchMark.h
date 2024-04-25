#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

typedef struct
{
    int *vet;
    int tam;
    int capacidade;
} MinHeap;

// Estrutura para representar um bloco
typedef struct
{
    int *vet;
    int tamBloco;
    int proxElem;
} Block;


typedef struct Return;
void bubbleSort(int *vet, int tam);
void selectionSort(int *vet, int tam);
void insertionSort(int *vet, int tam);
int particiona(int *vet, int inicio, int fim);
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

MinHeap *criarMinHeap(int capacidade);
int pai(int i);
void insere(MinHeap *minHeap, int chave);
int extrairMin(MinHeap *minHeap);

Block *divideEOrdena(int vet[], int n, int tamBloco);
void mergeBlocksRec(Block blocks[], int numBlocos, int n, int vet[], int iAux, MinHeap *minHeap);
void mergeBlocks(int vet[], Block blocks[], int numBlocos, int n);
void BlockSort(int vet[], int n);
void imprimeVetor(int vet[], int n);

#endif /* SORTING_ALGORITHMS_H */
