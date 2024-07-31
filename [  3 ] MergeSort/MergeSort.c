#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void imprimirVetor (int *V, int ini, int fim) {
    for (int i = ini; i <= fim; i++)
        printf("%d ", V[i]);
    printf("\n");
}

void merge (int *V, int ini, int meio, int fim) {
    int n1 = meio - ini + 1, n2 = fim - meio;
    int V1[n1 + 1], V2[n2 + 1];
    for (int i = 0; i < n1; i++)
        V1[i] = V[ini + i];
    V1[n1] = INT_MAX; // Sentinela
    for (int i = 0; i < n2; i++)
        V2[i] = V[meio + i + 1];
    V2[n2] = INT_MAX; // Sentinela

    for (int i = ini, j = 0, k = 0; i <= fim; i++) {
        if (V1[j] <= V2[k]) {
            V[i] = V1[j];
            j++;
        } else {
            V[i] = V2[k];
            k++;
        }
    }
}

void mergeSort (int *V, int ini, int fim) {
    if (ini >= fim) return;
    int meio = (ini + fim)/2;
    mergeSort(V, ini, meio);
    mergeSort(V, meio + 1, fim);
    merge(V, ini, meio, fim);
    imprimirVetor(V, ini, fim);
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    2 10
    1 2 10
    3 4
    1 2 3 4 10
    6 7
    8 9
    6 7 8 9
    1 2 3 4 6 7 8 9 10
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    4 5
    3 4 5
    1 2
    1 2 3 4 5
Saida: 1 2 3 4 5

Entrada: 1 2 3 4 5
Iterações:
    1 2
    1 2 3
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
    mergeSort(V, 0, n-1);
    printf("Saida: "), imprimirVetor(V, 0, n-1);
    printf("\n");


    // Teste 2
    int V2[] = {5, 4, 3, 2, 1};
    int n2 = sizeof(V2)/sizeof(V2[0]);

    printf("Entrada: "), imprimirVetor(V2, 0, n2-1);
    mergeSort(V2, 0, n2-1);
    printf("Saida: "), imprimirVetor(V2, 0, n2-1);
    printf("\n");


    // Teste 3
    int V3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(V3)/sizeof(V3[0]);

    printf("Entrada: "), imprimirVetor(V3, 0, n3-1);
    mergeSort(V3, 0, n3-1);
    printf("Saida: "), imprimirVetor(V3, 0, n3-1);
    printf("\n");
}