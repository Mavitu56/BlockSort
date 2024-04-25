#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

tReturn bubbleSort(int *vet, int tam)
{
	int i, j, aux;
	tReturn retorno;
	retorno.trocas = 0;
	retorno.comparacoes = 0;
	for (i = 0; i < tam; i++)
		for (j = 0; j < tam - 1; j++)
		{
			retorno.comparacoes++;
			if (vet[j] > vet[j + 1])
			{
				aux = vet[j];
				vet[j] = vet[j + 1];
				vet[j + 1] = aux;
				retorno.trocas++;
			}
		}

	return retorno;
}

tReturn bubbleSortIntelgente(int *vet, int tam)
{
	tReturn retorno;
	retorno.trocas = 0;
	retorno.comparacoes = 0;

	int i, j, aux, troca = 0;

	for (i = 0; i < tam - 1; i++)
	{
		troca = 0;
		j = 0;
		while (j < (tam - i - 1))
		{
			retorno.comparacoes++;
			if (vet[j] > vet[j + 1])
			{
				aux = vet[j];
				vet[j] = vet[j + 1];
				vet[j + 1] = aux;
				troca = 1;
				retorno.trocas++;
			}
			j++;
		}

		if (troca == 0)
			break;
	}

    return retorno;
}

tReturn SelectionSort(int vet[], int tam)
{
	tReturn retorno;
	retorno.trocas = 0;
	retorno.comparacoes = 0;

	int marcador = 0;
	int menor;
	int aux;

	while (marcador < tam - 1)
	{
		menor = marcador;
		for (int i = marcador + 1; i < tam; i++)
		{
			retorno.comparacoes++;
			if (vet[i] < vet[menor])
			{
				menor = i;
			}
		}
		retorno.comparacoes++;
		if (menor != marcador)
		{
			aux = vet[marcador];
			vet[marcador] = vet[menor];
			vet[menor] = aux;
			retorno.trocas++;
		}
		marcador++;
	}

	return retorno;
}

tReturn InsertionSort(int vet[], int tam)
{
	tReturn retorno;
	retorno.trocas = 0;
	retorno.comparacoes = 0;

	int marcador;
	int aux;
	int pos;

	for (marcador = 1; marcador < tam; marcador++)
	{
		pos = marcador - 1;
		aux = vet[marcador];
		retorno.comparacoes++;
		while (aux < vet[pos] && pos >= 0)
		{
			vet[pos + 1] = vet[pos];
			pos = pos - 1;
			retorno.trocas++;
			retorno.comparacoes++;
		}
		vet[pos + 1] = aux;
	}

	return retorno;
}

void MergeSort(int *vet, int inicio, int fim, tReturn *retorno)
{
	int meio;
	if (inicio < fim)
	{
		meio = (inicio + fim) / 2;
		MergeSort(vet, inicio, meio, retorno);
		MergeSort(vet, meio + 1, fim, retorno);
		Merge(vet, inicio, meio, fim, retorno);
	}
}

void Merge(int *vet, int inicio, int meio, int fim, tReturn *retorno)
{
	int marcador1 = inicio;
	int marcador2 = meio + 1;
	int i = 0;
	int *vetoraux;

	vetoraux = (int *)malloc(((fim - inicio) + 1) * sizeof(int));
	if (vetoraux == NULL)
	{
		printf("ERRO AO ALOCAR MEMÓRIA\n");
		exit(1);
	}

	while (marcador1 <= meio && marcador2 <= fim)
	{
		retorno->comparacoes++;
		if (vet[marcador1] <= vet[marcador2])
			vetoraux[i++] = vet[marcador1++];
		else
			vetoraux[i++] = vet[marcador2++];
	}
	while (marcador1 <= meio)
		vetoraux[i++] = vet[marcador1++];

	while (marcador2 <= fim)
		vetoraux[i++] = vet[marcador2++];

	for (marcador1 = inicio; marcador1 <= fim; marcador1++)
	{
		vet[marcador1] = vetoraux[marcador1 - inicio];
		retorno->trocas++;
	}

	free(vetoraux);
}

int Particiona(int *vet, int inicio, int fim, tReturn *retorno)
{
	int pivo = vet[inicio];
	int pos = inicio;
	int aux;

	for (int i = inicio + 1; i <= fim; i++)
	{
		retorno->comparacoes++;
		if (vet[i] < pivo)
		{
			pos++;
			if (i != pos)
			{
				aux = vet[i];
				vet[i] = vet[pos];
				vet[pos] = aux;
				retorno->trocas++;
			}
		}
	}

	aux = vet[inicio];
	vet[inicio] = vet[pos];
	vet[pos] = aux;
	retorno->trocas++;

	return pos;
}

void QuickSort(int *vet, int inicio, int fim, tReturn *retorno)
{
	int posPivo;

	if (inicio < fim)
	{
		posPivo = Particiona(vet, inicio, fim, retorno);
		QuickSort(vet, inicio, posPivo - 1, retorno);
		QuickSort(vet, posPivo + 1, fim, retorno);
	}
}

MinHeap *criarMinHeap(int capacidade)
{
	MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
	minHeap->capacidade = capacidade;
	minHeap->tam = 0;
	minHeap->vet = (int *)malloc(capacidade * sizeof(int));
	return minHeap;
}

// Função para conseguir o índice do pai de um nó
int pai(int i)
{
	return (i - 1) / 2;
}

// Função para inserir um elemento na min heap
void insere(MinHeap *minHeap, int chave, tReturn *retorno)
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
		int aux = minHeap->vet[i];
		minHeap->vet[i] = minHeap->vet[pai(i)];
		minHeap->vet[pai(i)] = aux;
		retorno->comparacoes++;
		retorno->trocas++;

		// Continua analisando pelo pai do nó atual
		i = pai(i);
	}
}

int extrairMin(MinHeap *minHeap, tReturn *retorno)
{
	if (minHeap->tam <= 0)
		return -1;

	if (minHeap->tam == 1)
	{
		minHeap->tam--;
		return minHeap->vet[0];
	}

	// Armazena o menor elemento e substitui pelo último elemento
	int r = minHeap->vet[0];
	minHeap->vet[0] = minHeap->vet[minHeap->tam - 1];
	minHeap->tam--;
	retorno->trocas++;

	// Corrige a propriedade da min heap
	int i = 0;
	while (1)
	{
		int esq = 2 * i + 1;
		int dir = 2 * i + 2;
		int menor = i;

		if (esq < minHeap->tam && minHeap->vet[esq] < minHeap->vet[i])
		{
			menor = esq;
			retorno->comparacoes++;
		}

		if (dir < minHeap->tam && minHeap->vet[dir] < minHeap->vet[menor])
		{
			menor = dir;
			retorno->comparacoes++;
		}

		if (menor != i)
		{
			int aux = minHeap->vet[i];
			minHeap->vet[i] = minHeap->vet[menor];
			minHeap->vet[menor] = aux;
			i = menor;
			retorno->trocas++;
		}
		else
		{
			break;
		}
	}

	return r;
}

Block *divideEOrdena(int vet[], int n, int tamBloco, tReturn *retorno)
{

	int numBlocos = (n + tamBloco - 1) / tamBloco;
	Block *blocks = (Block *)malloc(numBlocos * sizeof(Block));

	// Ordena cada bloco separadamente usando o quicksort
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

		blocks[i].vet = (int *)malloc(tamanhoBloco * sizeof(int));

		blocks[i].vet = &vet[inicio];

		// Ordena o bloco atual
		QuickSort(blocks[i].vet, 0, tamanhoBloco - 1, retorno);

		blocks[i].tamBloco = tamanhoBloco;
		blocks[i].proxElem = 0;
	}

	return blocks;
}

// Função para mesclar os blocos em um vetor ordenado usando uma min heap de forma recursiva
void mergeBlocksRec(Block blocks[], int numBlocos, int n, int vet[], int iAux, MinHeap *minHeap, tReturn *retorno)
{
	// Verifica se a min heap não está vazia
	if (minHeap->tam > 0)
	{
		int min = extrairMin(minHeap, retorno);
		vet[iAux++] = min;

		// Encontra o bloco a partir do qual o elemento foi extraído
		for (int i = 0; i < numBlocos; i++)
		{
			if (blocks[i].vet[blocks[i].proxElem] == min)
			{
				blocks[i].proxElem++;

				// Se ainda houver elementos no bloco, insere o próximo elemento na min heap
				if (blocks[i].proxElem < blocks[i].tamBloco)
				{
					insere(minHeap, blocks[i].vet[blocks[i].proxElem], retorno);
				}
				break;
			}
		}
		mergeBlocksRec(blocks, numBlocos, n, vet, iAux, minHeap, retorno);
	}
}

void mergeBlocks(Block blocks[], int numBlocos, int n, int vet[], tReturn *retorno)
{
	MinHeap *minHeap = criarMinHeap(numBlocos);

	int *vetorAuxiliar = (int *)malloc(n * sizeof(int));

	// Insere o primeiro elemento de cada bloco na min heap
	for (int i = 0; i < numBlocos; i++)
	{
		if (blocks[i].tamBloco > 0)
		{
			insere(minHeap, blocks[i].vet[0], retorno);
		}
	}

	mergeBlocksRec(blocks, numBlocos, n, vetorAuxiliar, 0, minHeap, retorno);

	for (int i = 0; i < n; i++)
	{
		vet[i] = vetorAuxiliar[i];
	}

	free(vetorAuxiliar);
	free(minHeap->vet);
	free(minHeap);
}

void BlockSort(int vet[], int n,tReturn *retorno)
{
	int tamBloco = floor(sqrt(n));
	Block *blocks = divideEOrdena(vet, n, tamBloco, retorno);
	mergeBlocks(blocks, (n + tamBloco - 1) / tamBloco, n, vet, retorno);
	printf("Comparações: %lld\n", retorno->comparacoes);
	printf("Trocas: %lld\n", retorno->trocas);

	free(blocks);
}

void imprimeVetor(int vet[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", vet[i]);
	printf("\n");
}

int *geraAleatorios(int tam, int semente)
{
	// utiliza a semente para gerar números aleatórios
	srand(semente);
	int *vetor = (int *)malloc(tam * sizeof(int));
	for (int i = 0; i < tam; i++)
	{
		vetor[i] = rand() % tam; // gera números aleatórios entre 0 e tam-1
	}
	return vetor;
}

int *geraQuaseOrdenados(int tam, int porcentagem)
{
	// abordagem 1
	int *vetor = (int *)malloc(tam * sizeof(int));
	int num_desordenados = tam * porcentagem / 100;	 // calcula a quantidade de elementos que serão desordenados
	int *indices = (int *)malloc(tam * sizeof(int)); // aloca um vetor de indices para embaralhar os elementos

	for (int i = 0; i < tam; i++)
	{
		// preenche o vetor com valores ordenados
		vetor[i] = i;
		indices[i] = i; 
	}

	for (int i = 0; i < num_desordenados; i++)
	{
		// define os indices aleatoriamente em que ficarão os elementos desordenados
		int temp = indices[i];
		int random_index = rand() % tam;
		indices[i] = indices[random_index];
		indices[random_index] = temp;
	}

	for (int i = 0; i < num_desordenados; i++)
	{
		vetor[indices[i]] = rand() % tam; // preenche os elementos desordenados com valores aleatórios
	}

	// dessa forma, o vetor está quase ordenado

	free(indices);
	return vetor;
}

int *geraOrdenados(int tam, int ordem)
{
	// gerar vetor ordenado crescente
	int *vetor = (int *)malloc(tam * sizeof(int));
	if (ordem == 0)
	{
		for (int i = 0; i < tam; i++)
		{
			vetor[i] = i;
		}
	}
	else
	{
		// gerar vetor ordenado decrescente
		for (int i = 0; i < tam; i++)
		{
			vetor[i] = tam - i - 1;
		}
	}
	return vetor;
}

void benchmarkBubbleSort(int *vet_tam, int *vet_semente)
{
	// Construção do cabeçalho da tabela
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq, "\n\n\n--------------------------------------------------------------------------------Tabela 1: Bubble Sort---------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		long long int *vet_trocas = (long long int *)malloc(4 * sizeof(long long int)); // alocação do vetor para armazenar as trocas em cada execução
		long long int *vet_comp = (long long int *)malloc(4 * sizeof(long long int));	// alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double));						// alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;
		int comp_total = 0, trocas_total = 0;
		tReturn retorno;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			retorno = bubbleSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno.comparacoes;
			trocas_total += retorno.trocas;
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado
		vet_comp[0] = comp_total / 5;
		vet_trocas[0] = trocas_total / 5;

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		retorno = bubbleSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		vet_comp[1] = retorno.comparacoes;
		vet_trocas[1] = retorno.trocas;
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		retorno = bubbleSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		vet_comp[2] = retorno.comparacoes;
		vet_trocas[2] = retorno.trocas;
		free(vet);
		tempo_total = 0.0;
		comp_total = 0;
		trocas_total = 0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			retorno = bubbleSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno.comparacoes;
			trocas_total += retorno.trocas;
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado
		vet_comp[3] = comp_total / 5;
		vet_trocas[3] = trocas_total / 5;

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo os tempos
		fprintf(arq, "   %lld %lld %lld %lld\n", vet_comp[0], vet_comp[1], vet_comp[2], vet_comp[3]);					// escreve no arquivo as comparações
		fprintf(arq, "   %lld %lld %lld %lld\n\n\n", vet_trocas[0], vet_trocas[1], vet_trocas[2], vet_trocas[3]);		// escreve no arquivo as trocas
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkBubbleSortInteligente(int *vet_tam, int *vet_semente)
{
	// Construção do cabeçalho da tabela
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq, "\n\n\n-------------------------------------------------------------------------------Tabela 2: Bubble Sort Inteligente------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		long long int *vet_trocas = (long long int *)malloc(4 * sizeof(long long int)); // alocação do vetor para armazenar as trocas em cada execução
		long long int *vet_comp = (long long int *)malloc(4 * sizeof(long long int));	// alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double));						// alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;
		int comp_total = 0, trocas_total = 0;
		tReturn retorno;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			retorno = bubbleSortIntelgente(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno.comparacoes;
			trocas_total += retorno.trocas;
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado
		vet_comp[0] = comp_total / 5;
		vet_trocas[0] = trocas_total / 5;

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		retorno = bubbleSortIntelgente(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		vet_comp[1] = retorno.comparacoes;
		vet_trocas[1] = retorno.trocas;
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		retorno = bubbleSortIntelgente(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		vet_comp[2] = retorno.comparacoes;
		vet_trocas[2] = retorno.trocas;
		free(vet);
		tempo_total = 0.0;
		comp_total = 0;
		trocas_total = 0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			retorno = bubbleSortIntelgente(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno.comparacoes;
			trocas_total += retorno.trocas;
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado
		vet_comp[3] = comp_total / 5;
		vet_trocas[3] = trocas_total / 5;

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo os tempos
		fprintf(arq, "   %lld %lld %lld %lld\n", vet_comp[0], vet_comp[1], vet_comp[2], vet_comp[3]);					// escreve no arquivo as comparações
		fprintf(arq, "   %lld %lld %lld %lld\n\n\n", vet_trocas[0], vet_trocas[1], vet_trocas[2], vet_trocas[3]);		// escreve no arquivo as trocas
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkSelectionSort(int *vet_tam, int *vet_semente)
{
	// Construção do cabeçalho da tabela
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq, "\n\n\n------------------------------------------------------------------------------------Tabela 3: Selection Sort------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		long long int *vet_trocas = (long long int *)malloc(4 * sizeof(long long int)); // alocação do vetor para armazenar as trocas em cada execução
		long long int *vet_comp = (long long int *)malloc(4 * sizeof(long long int));	// alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double));						// alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;
		tReturn retorno;
		int comp_total = 0, trocas_total = 0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			retorno = SelectionSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno.comparacoes;
			trocas_total += retorno.trocas;
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado
		vet_comp[0] = comp_total / 5;
		vet_trocas[0] = trocas_total / 5;

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		retorno = SelectionSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		vet_comp[1] = retorno.comparacoes;
		vet_trocas[1] = retorno.trocas;
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		retorno = SelectionSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		vet_comp[2] = retorno.comparacoes;								// armazena na terceira posição do vetor o terceiro resultado
		vet_trocas[2] = retorno.trocas;									// armazena na terceira posição do vetor o terceiro resultado
		free(vet);
		tempo_total = 0.0;
		comp_total = 0;
		trocas_total = 0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			retorno = SelectionSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno.comparacoes;
			trocas_total += retorno.trocas;
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado
		vet_comp[3] = comp_total / 5;
		vet_trocas[3] = trocas_total / 5;

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		fprintf(arq, "   %lld %lld %lld %lld\n", vet_comp[0], vet_comp[1], vet_comp[2], vet_comp[3]);					// escreve no arquivo as comparações
		fprintf(arq, "   %lld %lld %lld %lld\n\n\n", vet_trocas[0], vet_trocas[1], vet_trocas[2], vet_trocas[3]);		// escreve no arquivo as trocas
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkInsertionSort(int *vet_tam, int *vet_semente)
{
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq, "\n\n\n---------------------------------------------------------------------------------Tabela 4: Insertion Sort--------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		long long int *vet_trocas = (long long int *)malloc(4 * sizeof(long long int)); // alocação do vetor para armazenar as trocas em cada execução
		long long int *vet_comp = (long long int *)malloc(4 * sizeof(long long int));	// alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double));						// alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;
		tReturn retorno;
		int comp_total = 0, trocas_total = 0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			retorno = InsertionSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno.comparacoes;
			trocas_total += retorno.trocas;
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5;	  // armazena na primeira posição do vetor o primeiro resultado
		vet_comp[0] = comp_total / 5;	  // armazena na primeira posição do vetor o primeiro resultado
		vet_trocas[0] = trocas_total / 5; // armazena na primeira posição do vetor o primeiro resultado

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		retorno = InsertionSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		vet_comp[1] = retorno.comparacoes;								// armazena na segunda posição do vetor o segundo resultado
		vet_trocas[1] = retorno.trocas;									// armazena na segunda posição do vetor o segundo resultado
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		retorno = InsertionSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		vet_comp[2] = retorno.comparacoes;								// armazena na terceira posição do vetor o terceiro resultado
		vet_trocas[2] = retorno.trocas;									// armazena na terceira posição do vetor o terceiro resultado
		free(vet);
		tempo_total = 0.0;
		comp_total = 0;
		trocas_total = 0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			retorno = InsertionSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno.comparacoes;
			trocas_total += retorno.trocas;
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5;	  // armazena na quarta posição do vetor o quarto resultado
		vet_comp[3] = comp_total / 5;	  // armazena na quarta posição do vetor o quarto resultado
		vet_trocas[3] = trocas_total / 5; // armazena na quarta posição do vetor o quarto resultado

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		fprintf(arq, "   %lld %lld %lld %lld\n", vet_comp[0], vet_comp[1], vet_comp[2], vet_comp[3]);					// escreve no arquivo as comparações
		fprintf(arq, "   %lld %lld %lld %lld\n\n\n", vet_trocas[0], vet_trocas[1], vet_trocas[2], vet_trocas[3]);		// escreve no arquivo as trocas

		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkQuickSort(int *vet_tam, int *vet_semente)
{
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq, "\n\n\n------------------------------------------------------------------------------------------Tabela 5: Quick Sort------------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		long long int *vet_trocas = (long long int *)malloc(4 * sizeof(long long int)); // alocação do vetor para armazenar as trocas em cada execução
		long long int *vet_comp = (long long int *)malloc(4 * sizeof(long long int));	// alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double));						// alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;
		tReturn *retorno = (tReturn *)malloc(sizeof(tReturn));
		retorno->comparacoes = 0;
		retorno->trocas = 0;
		int comp_total = 0, trocas_total = 0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			QuickSort(vet, 0, vet_tam[i] - 1, retorno);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno->comparacoes;
			trocas_total += retorno->trocas;
			retorno->comparacoes = 0;
			retorno->trocas = 0;
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado
		vet_comp[0] = comp_total / 5;
		vet_trocas[0] = trocas_total / 5;

		retorno->comparacoes = 0;
		retorno->trocas = 0;

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		QuickSort(vet, 0, vet_tam[i] - 1, retorno);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		vet_comp[1] = retorno->comparacoes;
		vet_trocas[1] = retorno->trocas;
		retorno->comparacoes = 0;
		retorno->trocas = 0;
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		QuickSort(vet, 0, vet_tam[i] - 1, retorno);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		vet_comp[2] = retorno->comparacoes;
		vet_trocas[2] = retorno->trocas;
		retorno->comparacoes = 0;
		retorno->trocas = 0;
		free(vet);
		tempo_total = 0.0;
		comp_total = 0;
		trocas_total = 0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			QuickSort(vet, 0, vet_tam[i] - 1, retorno);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno->comparacoes;
			trocas_total += retorno->trocas;
			retorno->comparacoes = 0;
			retorno->trocas = 0;
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado
		vet_comp[3] = comp_total / 5;
		vet_trocas[3] = trocas_total / 5;
		retorno->comparacoes = 0;
		retorno->trocas = 0;

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		fprintf(arq, "   %lld %lld %lld %lld\n", vet_comp[0], vet_comp[1], vet_comp[2], vet_comp[3]);					// escreve no arquivo as comparações
		fprintf(arq, "   %lld %lld %lld %lld\n\n\n", vet_trocas[0], vet_trocas[1], vet_trocas[2], vet_trocas[3]);		// escreve no arquivo as trocas

		free(retorno);
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkMergeSort(int *vet_tam, int *vet_semente)
{
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq, "\n\n\n------------------------------------------------------------------------------------Tabela 6: Merge Sort------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		long long int *vet_trocas = (long long int *)malloc(4 * sizeof(long long int)); // alocação do vetor para armazenar as trocas em cada execução
		long long int *vet_comp = (long long int *)malloc(4 * sizeof(long long int));	// alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double));						// alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;
		tReturn *retorno = (tReturn *)malloc(sizeof(tReturn));
		retorno->comparacoes = 0;
		retorno->trocas = 0;
		int comp_total = 0, trocas_total = 0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			MergeSort(vet, 0, vet_tam[i] - 1, retorno);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno->comparacoes;
			trocas_total += retorno->trocas;
			retorno->comparacoes = 0;
			retorno->trocas = 0;
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado
		vet_comp[0] = comp_total / 5;
		vet_trocas[0] = trocas_total / 5;
		retorno->comparacoes = 0;
		retorno->trocas = 0;

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		MergeSort(vet, 0, vet_tam[i] - 1, retorno);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		vet_comp[1] = retorno->comparacoes;
		vet_trocas[1] = retorno->trocas;
		free(vet);
		retorno->comparacoes = 0;
		retorno->trocas = 0;

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		MergeSort(vet, 0, vet_tam[i] - 1, retorno);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		vet_comp[2] = retorno->comparacoes;
		vet_trocas[2] = retorno->trocas;
		retorno->comparacoes = 0;
		retorno->trocas = 0;
		free(vet);
		tempo_total = 0.0;
		comp_total = 0;
		trocas_total = 0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			MergeSort(vet, 0, vet_tam[i] - 1, retorno);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno->comparacoes;
			trocas_total += retorno->trocas;
			retorno->comparacoes = 0;
			retorno->trocas = 0;
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado
		vet_comp[3] = comp_total / 5;
		vet_trocas[3] = trocas_total / 5;
		retorno->comparacoes = 0;
		retorno->trocas = 0;

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		fprintf(arq, "   %lld %lld %lld %lld\n", vet_comp[0], vet_comp[1], vet_comp[2], vet_comp[3]);					// escreve no arquivo as comparações
		fprintf(arq, "   %lld %lld %lld %lld\n\n\n", vet_trocas[0], vet_trocas[1], vet_trocas[2], vet_trocas[3]);		// escreve no arquivo as trocas

		free(retorno);
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkBlockSort(int *vet_tam, int *vet_semente)
{
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq, "\n\n\n------------------------------------------------------------------------------------------Tabela 7: Block Sort------------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		long long int *vet_trocas = (long long int *)malloc(4 * sizeof(long long int)); // alocação do vetor para armazenar as trocas em cada execução
		long long int *vet_comp = (long long int *)malloc(4 * sizeof(long long int));	// alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double));						// alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;
		tReturn *retorno = (tReturn *)malloc(sizeof(tReturn));
		retorno->comparacoes = 0;
		retorno->trocas = 0;
		int comp_total = 0, trocas_total = 0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			BlockSort(vet, vet_tam[i],retorno);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno->comparacoes;
			trocas_total += retorno->trocas;
			retorno->comparacoes = 0;
			retorno->trocas = 0;
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado
		vet_comp[0] = comp_total / 5;
		vet_trocas[0] = trocas_total / 5;
		retorno->comparacoes = 0;
		retorno->trocas = 0;

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		BlockSort(vet, vet_tam[i], retorno);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		vet_comp[1] = retorno->comparacoes;
		vet_trocas[1] = retorno->trocas;
		retorno->comparacoes = 0;
		retorno->trocas = 0;
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		BlockSort(vet, vet_tam[i],retorno);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		vet_comp[2] = retorno->comparacoes;
		vet_trocas[2] = retorno->trocas;
		retorno->comparacoes = 0;
		retorno->trocas = 0;
		free(vet);
		tempo_total = 0.0;
		comp_total = 0;
		trocas_total = 0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			BlockSort(vet, vet_tam[i],retorno);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			comp_total += retorno->comparacoes;
			trocas_total += retorno->trocas;
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado
		vet_comp[3] = comp_total / 5;
		vet_trocas[3] = trocas_total / 5;

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		fprintf(arq, "   %lld %lld %lld %lld\n", vet_comp[0], vet_comp[1], vet_comp[2], vet_comp[3]);					// escreve no arquivo as comparações
		fprintf(arq, "   %lld %lld %lld %lld\n\n\n", vet_trocas[0], vet_trocas[1], vet_trocas[2], vet_trocas[3]);		// escreve no arquivo as trocas

		free(retorno);
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}