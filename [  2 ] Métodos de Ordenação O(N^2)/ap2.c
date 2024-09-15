// João Victor Assaoka Ribeiro - 168863
#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

void insertionSort(int vetor[], int n) { // Ordenação por Inserção - O(n^2)
	int chave, i, j;
	for (i = 1; i < n; i++) { // Percorre o vetor a partir do segundo elemento (dado que um vetor de um elemento já está ordenado)
		chave = vetor[i]; // Armazena o valor do i-ésimo elemento
		for (j = i - 1; j >= 0 && vetor[j] > chave; j--) // Percorre da posição anterior à i até a primeira posição, enquanto o elemento for maior que a chave
			vetor[j + 1] = vetor[j]; // Enquanto a chave for menor que o elemento, o elemento é deslocado uma posição para a direita (para a posição i)
		vetor[j + 1] = chave; // A chave é inserida na posição correta
	} // O vetor está ordenado
}

int podeCurar(int infect[], int cura[], int n) {
	insertionSort(infect, n); // Ordena o vetor infect
	insertionSort(cura, n); // Ordena o vetor cura
	
	for (int i = 0; i < n; i++) // Percorre os vetores ordenados
		if (infect[i] >= cura[i]) return False; // Se o i-ésimo mais infectado não puder ser curado com a i-ésima maior cura, não é possível curar todos.
	return True; // Caso contrário, é possível curar todos.
}

int main () {
	int n, *infect, *cura;
	scanf("%d", &n);

	// Alocação dinâmica de memória
	infect = (int *) malloc(n * sizeof(int));
	cura = (int *) malloc(n * sizeof(int));

	// Leitura dos vetores
	for (int i = 0; i < n; i++)
		scanf("%d", &infect[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &cura[i]);

	// Comparação dos vetores
	if (podeCurar(infect, cura, n)) printf("sim\n"); // Se retornar True, é possível curar todos
	else printf("nao\n"); // Caso contrário, não é possível curar todos

	// Liberação da memória alocada
	free(infect);
	free(cura);
	return 0;
}
