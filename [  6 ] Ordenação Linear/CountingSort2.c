#include <stdio.h>
#include <stdlib.h>

void imprimirVetor (int *V, int k, int n) {
    for (int i = 0; i <= n; i++) {
        if (V[i] > k) printf("_ ");
        else printf("%d ", V[i]);
    }
    printf("\n");
}

void countingSort (int V[], int S[], int n, int k) {
    int C[k + 1];
    for (int i = 0; i <= k; i++) C[i] = 0;
    for (int i = 0; i <= n; i++) C[V[i]] += 1;
    imprimirVetor(C, n + 1, k);
    for (int i = 0; i <= k - 1; i++) C[i + 1] += C[i];
    imprimirVetor(C, n + 1, k);
    for (int i = n; i >= 0; i--) {
        S[C[V[i]] - 1] = V[i];
        C[V[i]] -= 1;
        imprimirVetor(S, k, n);
    }
}

int main () {
    int A[] = {2, 5, 3, 0, 2, 3, 0, 3, 5, 2}, *B = (int *)malloc(9 * sizeof(int)), n = 9;
    imprimirVetor(A, 5, 9);
    imprimirVetor(B, 5, 9);
    countingSort(A, B, n, 5);
    imprimirVetor(A, 5, 9);
    imprimirVetor(B, 5, 9);
/*
Entrada: 2 5 3 0 2 3 0 3 5 2
Transformação:
    2 0 3 3 0 2
    2 2 5 8 8 10
Ordenando:
    _ _ _ _ 2 _ _ _ _ _
    _ _ _ _ 2 _ _ _ _ 5
    _ _ _ _ 2 _ _ 3 _ 5
    _ 0 _ _ 2 _ _ 3 _ 5
    _ 0 _ _ 2 _ 3 3 _ 5
    _ 0 _ 2 2 _ 3 3 _ 5
    0 0 _ 2 2 _ 3 3 _ 5
    0 0 _ 2 2 3 3 3 _ 5
    0 0 _ 2 2 3 3 3 5 5
    0 0 2 2 2 3 3 3 5 5
Saída: 0 0 2 2 2 3 3 3 5 5
*/
}