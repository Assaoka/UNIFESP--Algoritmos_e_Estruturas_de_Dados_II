#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void imprimirVetor (int *V, int ini, int fim) {
    for (int i = ini; i <= fim; i++)
        printf("%d ", V[i]);
    printf("\n");
}

int partition (int *V, int ini, int fim) {
    int pivo = ini - 1; // Inicializado como antes do começo do vetor, no fim vai ser a posição do ultimo elemento ordenado corretamente
    for (int i = ini; i <= fim - 1; i++) { // Botei o igual e o -1.
        if (V[i] <= V[fim]) {
            pivo++;
            swap(&V[pivo], &V[i]);
        }
    }
    swap(&V[pivo + 1], &V[fim]);
    return pivo + 1;
}

void quickSort (int *V, int ini, int fim) {
    if (ini >= fim) return;
    int pivo = partition(V, ini, fim);
    quickSort(V, ini, pivo - 1);
    quickSort(V, pivo + 1, fim);
    imprimirVetor(V, ini, fim);
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    1 2
    1 2 3 4
    1 2 3 4 6
    1 2 3 4 6 7
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8 9 10
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    3 4
    2 3 4
    2 3 4 5
    1 2 3 4 5
Saida: 1 2 3 4 5

Entrada: 1 2 3 4 5
Iterações:
    1 2
    1 2 3
    1 2 3 4
    1 2 3 4 5
Saida: 1 2 3 4 5
*/
}

void medianaDe3(int *V, int ini, int fim) {
    int meio = (ini + fim)/2, pivo = fim;
    if (V[ini] > V[meio]) swap(&ini, &meio);
    if (V[meio] > V[fim]) swap(&meio, &fim);
    if (V[ini] > V[meio]) swap(&ini, &meio);
    swap(&V[pivo], &V[meio]);
}

void quickSortMelhorado (int *V, int ini, int fim) {
    if (ini >= fim) return;
    medianaDe3(V, ini, fim);
    int pivo = partition(V, ini, fim);
    quickSort(V, ini, pivo - 1);
    quickSort(V, pivo + 1, fim);
    imprimirVetor(V, ini, fim);
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    1 2
    1 2 3 4
    1 2 3 4 6
    1 2 3 4 6 7
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8 9 10
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    1 2
    4 5
    1 2 3 4 5
Saida: 1 2 3 4 5

Entrada: 1 2 3 4 5
Iterações:
    1 2
    4 5
    1 2 3 4 5
Saida: 1 2 3 4 5
*/
}

int main () {
    // Teste 1
    int V[] = {10, 2, 1, 4, 3, 6, 7, 8, 9};
    int n = sizeof(V)/sizeof(V[0]);

    printf("Entrada: "), imprimirVetor(V, 0, n-1);
    quickSort(V, 0, n-1);
    printf("Saida: "), imprimirVetor(V, 0, n-1);
    printf("\n");


    // Teste 2
    int V2[] = {5, 4, 3, 2, 1};
    int n2 = sizeof(V2)/sizeof(V2[0]);

    printf("Entrada: "), imprimirVetor(V2, 0, n2-1);
    quickSort(V2, 0, n2-1);
    printf("Saida: "), imprimirVetor(V2, 0, n2-1);
    printf("\n");


    // Teste 3
    int V3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(V3)/sizeof(V3[0]);

    printf("Entrada: "), imprimirVetor(V3, 0, n3-1);
    quickSort(V3, 0, n3-1);
    printf("Saida: "), imprimirVetor(V3, 0, n3-1);
    printf("\n");
}