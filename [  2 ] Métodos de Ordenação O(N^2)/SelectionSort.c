#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void imprimirVetor (int *V, int ini, int n) {
    for (int i = ini; i < n; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
}

/*
1. Começamos varrendo a lista de chaves inteira para encontrar o menor elemento e permutá–lo com o primeiro elemento da lista;
2. Então, varremos a lista, começando pelo segundo elemento, para encontrar o menor dentre os n–1 últimos elementos e permutá–lo com o segundo elemento
3. Repita a operação anterior até que reste apenas um elemento
*/

void selectionSort (int *V, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (V[min] > V[j]) min = j;
            imprimirVetor(V, i, n);
        }
        swap(&V[i], &V[min]);
    }
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    4 10 6 7 8 9
    4 10 6 7 8 9
    4 10 6 7 8 9
    4 10 6 7 8 9
    4 10 6 7 8 9
    10 6 7 8 9
    10 6 7 8 9
    10 6 7 8 9
    10 6 7 8 9
    10 7 8 9
    10 7 8 9
    10 7 8 9
    10 8 9
    10 8 9
    10 9
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    5 4 3 2 1
    5 4 3 2 1
    5 4 3 2 1
    5 4 3 2 1
    4 3 2 5
    4 3 2 5
    4 3 2 5
    3 4 5
    3 4 5
    4 5
Saida: 1 2 3 4 5

Entrada: 1 2 3 4 5
Iterações:
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
    2 3 4 5
    2 3 4 5
    2 3 4 5
    3 4 5
    3 4 5
    4 5
Saida: 1 2 3 4 5
*/
}

void selectionSortRecursivo (int *V, int ini, int n) {
    if (ini >= n - 1) return; // Existe 2 Elementos
    int min = ini;
    for (int i = ini + 1; i < n; i++) {
        if (V[min] > V[i]) min = i;
        imprimirVetor(V, ini, n);
    }
    swap(&V[ini], &V[min]);
    selectionSortRecursivo(V, ini + 1, n);
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    10 2 1 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    2 10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    10 4 3 6 7 8 9
    4 10 6 7 8 9
    4 10 6 7 8 9
    4 10 6 7 8 9
    4 10 6 7 8 9
    4 10 6 7 8 9
    10 6 7 8 9
    10 6 7 8 9
    10 6 7 8 9
    10 6 7 8 9
    10 7 8 9
    10 7 8 9
    10 7 8 9
    10 8 9
    10 8 9
    10 9
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    5 4 3 2 1
    5 4 3 2 1
    5 4 3 2 1
    5 4 3 2 1
    4 3 2 5
    4 3 2 5
    4 3 2 5
    3 4 5
    3 4 5
    4 5
Saida: 1 2 3 4 5

Entrada: 1 2 3 4 5
Iterações:
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
    2 3 4 5
    2 3 4 5
    2 3 4 5
    3 4 5
    3 4 5
    4 5
Saida: 1 2 3 4 5
*/
}

int main () {
    // Teste 1
    int V[] = {10, 2, 1, 4, 3, 6, 7, 8, 9};
    int n = sizeof(V)/sizeof(V[0]);

    printf("Entrada: "), imprimirVetor(V, 0, n);
    //selectionSort(V, n);
    selectionSortRecursivo(V, 0, n);
    printf("Saida: "), imprimirVetor(V, 0, n);
    printf("\n");


    // Teste 2
    int V2[] = {5, 4, 3, 2, 1};
    int n2 = sizeof(V2)/sizeof(V2[0]);

    printf("Entrada: "), imprimirVetor(V2, 0, n2);
    //selectionSort(V2, n2);
    selectionSortRecursivo(V2, 0, n2);
    printf("Saida: "), imprimirVetor(V2, 0, n2);
    printf("\n");


    // Teste 3
    int V3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(V3)/sizeof(V3[0]);

    printf("Entrada: "), imprimirVetor(V3, 0, n3);
    //selectionSort(V3, n3);
    selectionSortRecursivo(V3, 0, n3);
    printf("Saida: "), imprimirVetor(V3, 0, n3);
    printf("\n");
}
