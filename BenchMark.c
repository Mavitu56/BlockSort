#include "BenchMark.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int *vet, int tam)
{
	int i, j;
	int comp = 0;
	int temp;
	for (i = 0; i < tam - 1; i++)
	{
		for (j = 0; j < tam - i - 1; j++)
		{
			comp++;
			if (vet[j] > vet[j + 1])
			{
				temp = vet[j];
				vet[j] = vet[j + 1];
				vet[j + 1] = temp;
			}
		}
	}
	return comp;
}

void selectionSort(int *vet, int tam)
{
	// selectionSort
}

void insertionSort(int *vet, int tam)
{
	// insertionSort
}

void quickSort(int *vet, int inicio, int fim)
{
	// quickSort
}

void mergeSort(int *vet, int inicio, int fim)
{
	// mergeSort
}

void blockSort()
{
	// blockSort
}

void merge(int *vet, int inicio, int meio, int fim)
{
	// merge
}

int *geraAleatorios(int tam, int semente)
{
	srand(semente);
	int *vetor = (int *)malloc(tam * sizeof(int));
	for (int i = 0; i < tam; i++)
	{
		vetor[i] = rand() % tam;
	}
	return vetor;
}

int *geraQuaseOrdenados(int tam, int porcentagem)
{
	// abordagem 1
	/*
	int* vetor = (int*)malloc(tam * sizeof(int));
	int num_desordenados = tam * porcentagem / 100;
	int* indices = (int*)malloc(tam * sizeof(int));


	for (int i = 0; i < tam; i++) {
		vetor[i] = i;
		indices[i] = i;
	}

	for (int i = 0; i < num_desordenados; i++) {
		int temp = indices[i];
		int random_index = rand() % tam;
		indices[i] = indices[random_index];
		indices[random_index] = temp;
	}

	for (int i = 0; i < num_desordenados; i++) {
		vetor[indices[i]] = rand() % tam;
	}

	free(indices);
	return vetor;


  */

	// abordagem 2
	int *vetor = (int *)malloc(tam * sizeof(int));

	for (int i = 0; i < tam; i++)
	{

		if (rand() % 100 < porcentagem)
		{

			vetor[i] = rand() % tam;
		}
		else
		{

			vetor[i] = i;
		}
	}

	return vetor;
}

int *geraOrdenados(int tam, int ordem)
{

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
	fprintf(arq,"\n\n\n------------------------------------------------------------------------------------------Tabela 1: Bubble Sort------------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		int *vet_trocas = (int *)malloc(4 * sizeof(int));		  // alocação do vetor para armazenar as trocas em cada execução
		int *vet_comp = (int *)malloc(4 * sizeof(int));			  // alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double)); // alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			bubbleSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		bubbleSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		bubbleSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		free(vet);
		tempo_total = 0.0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			bubbleSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado

		
		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkSelectionSort(int *vet_tam, int *vet_semente)
{	
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq,"\n\n\n------------------------------------------------------------------------------------------Tabela 2: Selection Sort------------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		int *vet_trocas = (int *)malloc(4 * sizeof(int));		  // alocação do vetor para armazenar as trocas em cada execução
		int *vet_comp = (int *)malloc(4 * sizeof(int));			  // alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double)); // alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			SelectionSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		SelectionSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		SelectionSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		free(vet);
		tempo_total = 0.0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			SelectionSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado
		
		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkInsertionSort(int *vet_tam, int *vet_semente)
{
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq,"\n\n\n------------------------------------------------------------------------------------------Tabela 3: Insertion Sort------------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		int *vet_trocas = (int *)malloc(4 * sizeof(int));		  // alocação do vetor para armazenar as trocas em cada execução
		int *vet_comp = (int *)malloc(4 * sizeof(int));			  // alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double)); // alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			InsertionSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		InsertionSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		InsertionSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		free(vet);
		tempo_total = 0.0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			InsertionSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkQuickSort(int *vet_tam, int *vet_semente)
{
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq,"\n\n\n------------------------------------------------------------------------------------------Tabela 4: Quick Sort------------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		int *vet_trocas = (int *)malloc(4 * sizeof(int));		  // alocação do vetor para armazenar as trocas em cada execução
		int *vet_comp = (int *)malloc(4 * sizeof(int));			  // alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double)); // alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			QuickSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		QuickSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		QuickSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		free(vet);
		tempo_total = 0.0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			QuickSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkMergeSort(int *vet_tam, int *vet_semente)
{
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq,"\n\n\n------------------------------------------------------------------------------------------Tabela 5: Merge Sort------------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		int *vet_trocas = (int *)malloc(4 * sizeof(int));		  // alocação do vetor para armazenar as trocas em cada execução
		int *vet_comp = (int *)malloc(4 * sizeof(int));			  // alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double)); // alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			MergeSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		MergeSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		MergeSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		free(vet);
		tempo_total = 0.0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			MergeSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

void benchmarkBlockSort(int *vet_tam, int *vet_semente)
{
	FILE *arq;
	arq = fopen("resultados.txt", "a");
	fprintf(arq,"\n\n\n------------------------------------------------------------------------------------------Tabela 6: Block Sort------------------------------------------------------------------------------------------\n\n");

	// Ciclo de repetição de testes
	for (int i = 0; i < 5; i++)
	{
		int *vet_trocas = (int *)malloc(4 * sizeof(int));		  // alocação do vetor para armazenar as trocas em cada execução
		int *vet_comp = (int *)malloc(4 * sizeof(int));			  // alocação do vetor para armazenar as comparações em cada execução
		double *vet_tempo = (double *)malloc(4 * sizeof(double)); // alocação do vetor para armazenar o tempo de cada execução
		double tempo_total = 0.0;

		// Processamento com vetor aleatório
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraAleatorios(vet_tam[i], vet_semente[i]); // chama a função de gerarAleatorios
			clock_t start = clock();							   // inicia a contagem de tempo
			BlockSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza a contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}
		vet_tempo[0] = tempo_total / 5; // armazena na primeira posição do vetor o primeiro resultado

		// Processamento com vetor ordenado crescente
		int *vet = geraOrdenados(vet_tam[i], 0); // chama a função de geraOrdenados
		clock_t start = clock();				 // inicia a contagem de tempo
		BlockSort(vet, vet_tam[i]);
		clock_t end = clock();											// finaliza a contagem de tempo
		vet_tempo[1] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na segunda posição do vetor o segundo resultado
		free(vet);

		// Processamento com vetor ordenado decrescente
		vet = geraOrdenados(vet_tam[i], 1); // chama a função de geraOrdenados
		start = clock();					// inicia a contagem de tempo
		BlockSort(vet, vet_tam[i]);
		end = clock();													// finaliza a contagem de tempo
		vet_tempo[2] = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // armazena na terceira posição do vetor o terceiro resultado
		free(vet);
		tempo_total = 0.0;

		// Processamento com vetor Quase Ordenado
		for (int j = 0; j < 5; j++)
		{
			int *vet = geraQuaseOrdenados(vet_tam[i], 10); // chama a função geraQuaseOrdenado
			clock_t start = clock();					   // inicia a contagem de tempo
			BlockSort(vet, vet_tam[i]);
			clock_t end = clock();											// finaliza contagem de tempo
			double tempo = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // transforma o tempo em milissegundos
			tempo_total += tempo;											// soma no total
			free(vet);
		}

		vet_tempo[3] = tempo_total / 5; // armazena na quarta posição do vetor o quarto resultado

		fprintf(arq, "%d %d %f %f %f %f\n", i + 1, vet_tam[i], vet_tempo[0], vet_tempo[1], vet_tempo[2], vet_tempo[3]); // escreve no arquivo
		free(vet_tempo);
		free(vet_trocas);
		free(vet_comp);
	}
}

int main()
{
	
	int vet_tam[5] = {100, 500, 1000, 5000, 10000};
	int vet_semente[5] = {1, 2, 3, 4, 5};
	benchmarkBubbleSort(vet_tam, vet_semente);
}
