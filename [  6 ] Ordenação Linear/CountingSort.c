#include <stdio.h>
#include <stdlib.h>

void imprimirVetor (int *V, int k, int n) {
    for (int i = 0; i <= n; i++) {
        if (V[i] > k) printf("_ ");
        else printf("%d ", V[i]);
    }
    printf("\n");
}

int * countingSort (int *V, int n, int k) {
    int *A = (int *)malloc(sizeof(int) * (n + 1)), C[k + 1];
    for (int i = 0; i <= k; i++) C[i] = 0;
    for (int i = 0; i <= n; i++) C[V[i]] += 1;
    imprimirVetor(C, n + 1, k);
    for (int i = 0; i <= k - 1; i++) C[i + 1] += C[i];
    imprimirVetor(C, n + 1, k);
    for (int i = n; i >= 0; i--) {
        A[C[V[i]] - 1] = V[i];
        C[V[i]] -= 1;
        imprimirVetor(A, k, n);
    }
    free(V);
    return A;
}

int main () {
    int *V = (int *)malloc(sizeof(int)*10), n = 9;
    int A[] = {2, 5, 3, 0, 2, 3, 0, 3, 5, 2};
    for (int i = 0; i <= n; i++) V[i] = A[i];
    imprimirVetor(V, 5, n);
    V = countingSort(V, n, 5);
    imprimirVetor(V, 5, n);

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
