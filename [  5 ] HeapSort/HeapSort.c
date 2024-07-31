#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void imprimirVetor (int *V, int n) {
    for (int i = 0; i <= n; i++)
        printf("%d ", V[i]);
    printf("\n");
}

void imprimirHeap (int *V, int i, int n) {
    if (i > n) return;
    printf("%d", V[i]);
    if (2*i + 1 <= n) {
        printf("(");
        imprimirHeap(V, 2*i + 1, n); // imprime esquerda
        if (2*i + 2 <= n) {
            printf(", ");
            imprimirHeap(V, 2*i + 2, n); // imprime direita
        }
        printf(")");
    }
    if (i == 0) printf("\n");
}

void maxHeapify (int *V, int i, int n) {
    int l = (2*i + 1), r = (2*i + 2), max;
    if (l <= n && V[l] >= V[i]) max = l; 
    else max = i;
    if (r <= n && V[r] >= V[max]) max = r;

    if (max != i) {
        swap(&V[i], &V[max]);
        maxHeapify(V, max, n);
    }
}

void buildMaxHeap (int *V, int n) {
    for (int i = (n - 1)/2; i >= 0; i--)
        maxHeapify(V, i, n);
}

void heapExtractMax (int *V, int n) {
    if (n < 1) return;
    swap(&V[0], &V[n]);
    maxHeapify(V, 0, n - 1);
}

void heapSort (int *V, int n) {
    buildMaxHeap(V, n);
    imprimirHeap(V, 0, n);
    while (n >= 0) {
        heapExtractMax(V, n);
        n--;
        imprimirHeap(V, 0, n);
    }
}

int main () {
    // Teste 1
    int V[] = {10, 2, 1, 4, 3, 6, 7, 8, 9};
    int n = sizeof(V)/sizeof(V[0]) - 1;

    printf("Entrada: "), imprimirVetor(V, n);
    heapSort(V, n);
    printf("Saida: "), imprimirVetor(V, n);
    printf("\n");


    // Teste 2
    int V2[] = {5, 4, 3, 2, 1};
    int n2 = sizeof(V2)/sizeof(V2[0]) - 1;

    printf("Entrada: "), imprimirVetor(V2, n2);
    heapSort(V2, n2);
    printf("Saida: "), imprimirVetor(V2, n2);
    printf("\n");


    // Teste 3
    int V3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(V3)/sizeof(V3[0]) - 1;

    printf("Entrada: "), imprimirVetor(V3, n3);
    heapSort(V3, n3);
    printf("Saida: "), imprimirVetor(V3, n3);
    printf("\n");
}
