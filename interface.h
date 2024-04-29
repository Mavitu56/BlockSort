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

typedef struct
{
    long long int trocas;
    long long int comparacoes;
} tReturn;

// Assinatura das funções de ordenação estudadas
tReturn bubbleSort(int *vet, int tam);
tReturn bubbleSortIntelgente(int *vet, int tam);
tReturn SelectionSort(int *vet, int tam);
tReturn InsertionSort(int *vet, int tam);
void MergeSort(int *vet, int inicio, int fim, tReturn *retorno);
void Merge(int *vet, int inicio, int meio, int fim, tReturn *retorno);
int Particiona(int *vet, int inicio, int fim, tReturn *retorno);
void QuickSort(int *vet, int inicio, int fim, tReturn *retorno);

// Assinatura das funções da minheap usadas para fazer o BlockSort
MinHeap *criarMinHeap(int capacidade);
int pai(int i);
void insere(MinHeap *minHeap, int chave, tReturn *retorno);
int extrairMin(MinHeap *minHeap, tReturn *retorno);

// Assinatura das funções do BlockSort
Block *divideEOrdena(int vet[], int n, int tamBloco, tReturn *retorno);
void mergeBlocksRec(Block blocks[], int numBlocos, int n, int vet[], int iAux, MinHeap *minHeap, tReturn *retorno);
void mergeBlocks(Block blocks[], int numBlocos, int n, int vet[], tReturn *retorno);
void BlockSort(int vet[], int n, tReturn *retorno);
void imprimeVetor(int vet[], int n);

// Assinatura das funções do benchmarking
int *geraAleatorios(int tam, int semente);
int *geraQuaseOrdenados(int tam, int porcentagem);
int *geraOrdenados(int tam, int ordem);
void benchmarkSelectionSort(int *vet_tam, int *vet_semente);
void benchmarkInsertionSort(int *vet_tam, int *vet_semente);
void benchmarkQuickSort(int *vet_tam, int *vet_semente);
void benchmarkMergeSort(int *vet_tam, int *vet_semente);
void benchmarkBlockSort(int *vet_tam, int *vet_semente);
void benchmarkBubbleSort(int *vet_tam, int *vet_semente);
void benchmarkBubbleSortInteligente(int *vet_tam, int *vet_semente);

#endif /* SORTING_ALGORITHMS_H */
