#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


MinHeap *criarMinHeap(int capacidade)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->capacidade = capacidade;
    minHeap->tam = 0;
    minHeap->vet = (int *)malloc(capacidade * sizeof(int));
    return minHeap;
}

// Função para obter o índice do pai de um nó
int pai(int i)
{
    return (i - 1) / 2;
}

// Função para adicionar um elemento à min heap
void insere(MinHeap *minHeap, int chave)
{
    if (minHeap->tam == minHeap->capacidade)
    {
        return;
    }

    minHeap->tam++;
    int i = minHeap->tam - 1;
    minHeap->vet[i] = chave;

    // Corrige a propriedade da min heap
    while (i != 0 && minHeap->vet[pai(i)] > minHeap->vet[i])
    {
        // Troca o nó atual com o seu pai
        int aux = minHeap->vet[i];
        minHeap->vet[i] = minHeap->vet[pai(i)];
        minHeap->vet[pai(i)] = aux;

        // Move para o pai
        i = pai(i);
    }
}

int extrairMin(MinHeap *minHeap)
{
    if (minHeap->tam <= 0)
        return -1;

    if (minHeap->tam == 1)
    {
        minHeap->tam--;
        return minHeap->vet[0];
    }

    // Armazena o elemento mínimo e substitui-o pelo último elemento
    int r = minHeap->vet[0];
    minHeap->vet[0] = minHeap->vet[minHeap->tam - 1];
    minHeap->tam--;

    // Corrige a propriedade da min heap
    int i = 0;
    while (1)
    {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int menor = i;

        if (esq < minHeap->tam && minHeap->vet[esq] < minHeap->vet[i])
            menor = esq;

        if (dir < minHeap->tam && minHeap->vet[dir] < minHeap->vet[menor])
            menor = dir;

        if (menor != i)
        {
            int aux = minHeap->vet[i];
            minHeap->vet[i] = minHeap->vet[menor];
            minHeap->vet[menor] = aux;
            i = menor;
        }
        else
        {
            break;
        }
    }

    return r;
}

int Particiona(int *vet, int inicio, int fim)
{
    int pivo = vet[inicio];
    int pos = inicio;
    int aux;

    for (int i = inicio + 1; i <= fim; i++)
    {
        if (vet[i] < pivo)
        {
            pos++;
            if (i != pos)
            {
                aux = vet[i];
                vet[i] = vet[pos];
                vet[pos] = aux;
            }
        }
    }

    aux = vet[inicio];
    vet[inicio] = vet[pos];
    vet[pos] = aux;

    return pos;
}

void QuickSort(int *vet, int inicio, int fim)
{
    int posPivo;

    if (inicio < fim)
    {
        posPivo = Particiona(vet, inicio, fim);
        QuickSort(vet, inicio, posPivo - 1);
        QuickSort(vet, posPivo + 1, fim);
    }
}

// Função para dividir o vetor em blocos e ordená-los usando quicksort
Block *divideEOrdena(int vet[], int n, int tamBloco)
{
    
    int numBlocos = (n + tamBloco - 1) / tamBloco;

    
    Block *blocks = (Block *)malloc(numBlocos * sizeof(Block));

    // Ordena cada bloco separadamente
    for (int i = 0; i < numBlocos; i++)
    {
        int inicio = i * tamBloco;
        int tamanhoBloco;
        if (i == numBlocos - 1)
        {
            tamanhoBloco = n - i * tamBloco;
        }
        else
        {
            tamanhoBloco = tamBloco;
        }

        QuickSort(vet, inicio, inicio + tamanhoBloco - 1);

        blocks[i].vet = &vet[inicio];
        blocks[i].tamBloco = tamanhoBloco;
        blocks[i].proxElem = 0;
    }

    return blocks;
}

// Função para mesclar os blocos em um vetor ordenado usando uma min heap de forma recursiva
void mergeBlocksRec(Block blocks[], int numBlocos, int n, int vet[], int iAux, MinHeap *minHeap)
{
    // Verifica se a min heap não está vazia
    if (minHeap->tam > 0)
    {
        int min = extrairMin(minHeap);
        vet[iAux++] = min;

        // Encontra o bloco a partir do qual o elemento foi extraído
        for (int i = 0; i < numBlocos; i++)
        {
            if (blocks[i].vet[blocks[i].proxElem] == min)
            {
                // Avança para o próximo elemento no bloco
                blocks[i].proxElem++;

                // Se ainda houver elementos no bloco, insere o próximo elemento na min heap
                if (blocks[i].proxElem < blocks[i].tamBloco)
                {
                    insere(minHeap, blocks[i].vet[blocks[i].proxElem]);
                }
                break;
            }
        }
      
        mergeBlocksRec(blocks, numBlocos, n, vet, iAux, minHeap);
    }
}

void mergeBlocks(int vet[], Block blocks[], int numBlocos, int n)
{

    MinHeap *minHeap = criarMinHeap(numBlocos);

    // Insere o primeiro elemento de cada bloco na min heap
    for (int i = 0; i < numBlocos; i++)
    {
        if (blocks[i].tamBloco > 0)
        {
            insere(minHeap, blocks[i].vet[0]);
        }
    }

    mergeBlocksRec(blocks, numBlocos, n, vet, 0, minHeap);
    free(minHeap->vet);
    free(minHeap);
}

void *BlockSort(int vet[], int n)
{
    int tamBloco = floor(sqrt(n));
    Block *blocks = divideEOrdena(vet, n, tamBloco);
    mergeBlocks(vet, blocks, (n + tamBloco - 1) / tamBloco, n);

    free(blocks);
}

void imprimeVetor(int vet[], int n){
     for (int i = 0; i < n; i++)
        printf("%d ", vet[i]);
        printf("\n");
}

int main()
{
    int vet[] = {5, 8, 3, 9, 4, 2, 6, 1, 7, 10, 14, 18, 20, 3, 4, 19, 115, 600, 230, 4, 1300, 10000, 7, 29, 612, 515, 447, 47, 400, 4000, 1000, 12, 29, 115, 167, 312};
    int n = sizeof(vet) / sizeof(vet[0]);

    imprimeVetor(vet, n);
    BlockSort(vet, n);
    imprimeVetor(vet, n);

    return 0;
}
