#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void imprimirVetor (int *V, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
}

/*
1. Comparar elementos adjacentes de uma lista e permutá–los se eles estiverem fora de ordem;
2. Fazendo isso repetidamente, acabamos “empurrando” (bubbling up) o maior elemento para a última posição da lista;
3. A próxima passagem “empurra” o segundo maior e assim por diante, até n–1 passos, a lista ser ordenada.
*/

void bubbleSort (int *V, int n) {
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (V[j] > V[j + 1]) {
                swap(&V[j], &V[j + 1]);
            }
            imprimirVetor(V, i + 1);
        }
    }
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    2 10 1 4 3 6 7 8 9
    2 1 10 4 3 6 7 8 9
    2 1 4 10 3 6 7 8 9
    2 1 4 3 10 6 7 8 9
    2 1 4 3 6 10 7 8 9
    2 1 4 3 6 7 10 8 9
    2 1 4 3 6 7 8 10 9
    2 1 4 3 6 7 8 9 10
    1 2 4 3 6 7 8 9
    1 2 4 3 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7
    1 2 3 4 6 7
    1 2 3 4 6 7
    1 2 3 4 6 7
    1 2 3 4 6 7
    1 2 3 4 6
    1 2 3 4 6
    1 2 3 4 6
    1 2 3 4 6
    1 2 3 4
    1 2 3 4
    1 2 3 4
    1 2 3
    1 2 3
    1 2
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    4 5 3 2 1
    4 3 5 2 1
    4 3 2 5 1
    4 3 2 1 5
    3 4 2 1
    3 2 4 1
    3 2 1 4
    2 3 1
    2 1 3
    1 2
Saida: 1 2 3 4 5

Entrada: 1 2 3 4 5
Iterações:
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4
    1 2 3 4
    1 2 3 4
    1 2 3
    1 2 3
    1 2
Saida: 1 2 3 4 5
*/
}

void bubbleSortMelhorado (int *V, int n) {
    int troca = 1, i;
    while (troca) {
        troca = 0;
        for (i = 0; i < n - 1; i++) {
            if (V[i] > V[i + 1]) {
                swap(&V[i], &V[i + 1]);
                troca = 1;
            } 
            imprimirVetor(V, n);
        }
        n--;
    }
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    2 10 1 4 3 6 7 8 9
    2 1 10 4 3 6 7 8 9
    2 1 4 10 3 6 7 8 9
    2 1 4 3 10 6 7 8 9
    2 1 4 3 6 10 7 8 9
    2 1 4 3 6 7 10 8 9
    2 1 4 3 6 7 8 10 9
    2 1 4 3 6 7 8 9 10
    1 2 4 3 6 7 8 9
    1 2 4 3 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    4 5 3 2 1
    4 3 5 2 1
    4 3 2 5 1
    4 3 2 1 5
    3 4 2 1
    3 2 4 1
    3 2 1 4
    2 3 1
    2 1 3
    1 2
Saida: 1 2 3 4 5

Entrada: 1 2 3 4 5
Iterações:
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
Saída: 1 2 3 4 5
*/
}

void bubbleSortRecursivo (int *V, int n) {
    if (n < 2) return;
    int troca = 0;
    for (int i = 0; i < n - 1; i++) {
        if (V[i] > V[i + 1]) {
            swap(&V[i], &V[i + 1]);
            troca = 1;
        }
        imprimirVetor(V, n);
    }
    if (troca) bubbleSortRecursivo(V, n - 1);
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    2 10 1 4 3 6 7 8 9
    2 1 10 4 3 6 7 8 9
    2 1 4 10 3 6 7 8 9
    2 1 4 3 10 6 7 8 9
    2 1 4 3 6 10 7 8 9
    2 1 4 3 6 7 10 8 9
    2 1 4 3 6 7 8 10 9
    2 1 4 3 6 7 8 9 10
    1 2 4 3 6 7 8 9
    1 2 4 3 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8 9
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
    1 2 3 4 6 7 8
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    4 5 3 2 1
    4 3 5 2 1
    4 3 2 5 1
    4 3 2 1 5
    3 4 2 1
    3 2 4 1
    3 2 1 4
    2 3 1
    2 1 3
    1 2
Saida: 1 2 3 4 5

Entrada: 1 2 3 4 5
Iterações:
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
    1 2 3 4 5
Saída: 1 2 3 4 5
*/
}

int main () {
    // Teste 1
    int V[] = {10, 2, 1, 4, 3, 6, 7, 8, 9};
    int n = sizeof(V)/sizeof(V[0]);

    printf("Entrada: "), imprimirVetor(V, n);
    bubbleSortRecursivo(V, n);
    printf("Saida: "), imprimirVetor(V, n);
    printf("\n");


    // Teste 2
    int V2[] = {5, 4, 3, 2, 1};
    int n2 = sizeof(V2)/sizeof(V2[0]);

    printf("Entrada: "), imprimirVetor(V2, n2);
    bubbleSortRecursivo(V2, n2);
    printf("Saida: "), imprimirVetor(V2, n2);
    printf("\n");


    // Teste 3
    int V3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(V3)/sizeof(V3[0]);

    printf("Entrada: "), imprimirVetor(V3, n3);
    bubbleSortRecursivo(V3, n3);
    printf("Saida: "), imprimirVetor(V3, n3);
    printf("\n");
}
