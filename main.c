#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
	int vet_tam[5] = {1000, 8000, 20000, 75000, 150000};
	int vet_semente[5] = {16, 12, 35, 46, 52};
	benchmarkBubbleSortInteligente(vet_tam, vet_semente);
	return 0;
}
