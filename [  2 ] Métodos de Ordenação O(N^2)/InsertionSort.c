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
1. Considere o primeiro elemento do vetor como um subvetor ordenado de um único elemento.
2. Para cada elemento do vetor, a partir do segundo elemento (índice 1), siga os seguintes passos:
  - Compare o "elemento atual" com os elementos do subvetor ordenado (à sua esquerda), movendo para a esquerda.
  - Continue movendo os elementos do subvetor ordenado para a direita enquanto eles forem maiores que o "elemento atual".
  - Insira o "elemento atual" na posição correta dentro do subvetor ordenado.
*/

void insertionSort (int *V, int n) {
    for (int i = 1; i < n; i++) {
        int chave = V[i], j;
        for (j = i - 1; j >= 0 && V[j] > chave; j--) {
            V[j + 1] = V[j];
            imprimirVetor(V, i + 1);
        }
        V[j + 1] = chave; // Suponha o caso da primeira interação. j vai sair como -1, mas você quer a 0. Use o mesmo raciocínio para os próximos (isso justifica o i + 1).
        imprimirVetor(V, i + 1);
    }
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    10 10
    2 10
    2 10 10
    2 2 10
    1 2 10
    1 2 10 10
    1 2 4 10
    1 2 4 10 10
    1 2 4 4 10
    1 2 3 4 10
    1 2 3 4 10 10
    1 2 3 4 6 10
    1 2 3 4 6 10 10
    1 2 3 4 6 7 10
    1 2 3 4 6 7 10 10
    1 2 3 4 6 7 8 10
    1 2 3 4 6 7 8 10 10
    1 2 3 4 6 7 8 9 10
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    5 5
    4 5
    4 5 5
    4 4 5
    3 4 5
    3 4 5 5
    3 4 4 5
    3 3 4 5
    2 3 4 5
    2 3 4 5 5
    2 3 4 4 5
    2 3 3 4 5
    2 2 3 4 5
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

void insertionSortRecursivo (int *V, int ini, int n) {
    if (ini >= n) return;
    int chave = V[ini], j;
    for (j = ini - 1; j >= 0 && V[j] > chave; j--) {
        V[j + 1] = V[j];
        imprimirVetor(V, ini + 1);
    }
    V[j + 1] = chave;
    imprimirVetor(V, ini + 1);
    insertionSortRecursivo(V, ini + 1, n);
/*
Entrada: 10 2 1 4 3 6 7 8 9
Iterações:
    10 10
    2 10
    2 10 10
    2 2 10
    1 2 10
    1 2 10 10
    1 2 4 10
    1 2 4 10 10
    1 2 4 4 10
    1 2 3 4 10
    1 2 3 4 10 10
    1 2 3 4 6 10
    1 2 3 4 6 10 10
    1 2 3 4 6 7 10
    1 2 3 4 6 7 10 10
    1 2 3 4 6 7 8 10
    1 2 3 4 6 7 8 10 10
    1 2 3 4 6 7 8 9 10
Saida: 1 2 3 4 6 7 8 9 10

Entrada: 5 4 3 2 1
Iterações:
    5 5
    4 5
    4 5 5
    4 4 5
    3 4 5
    3 4 5 5
    3 4 4 5
    3 3 4 5
    2 3 4 5
    2 3 4 5 5
    2 3 4 4 5
    2 3 3 4 5
    2 2 3 4 5
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


int main () {
    // Teste 1
    int V[] = {10, 2, 1, 4, 3, 6, 7, 8, 9};
    int n = sizeof(V)/sizeof(V[0]);

    printf("Entrada: "), imprimirVetor(V, n);
    //insertionSort(V, n);
    insertionSortRecursivo(V, 1, n);
    printf("Saida: "), imprimirVetor(V, n);
    printf("\n");


    // Teste 2
    int V2[] = {5, 4, 3, 2, 1};
    int n2 = sizeof(V2)/sizeof(V2[0]);

    printf("Entrada: "), imprimirVetor(V2, n2);
    //insertionSort(V2, n2);
    insertionSortRecursivo(V2, 1, n2);
    printf("Saida: "), imprimirVetor(V2, n2);
    printf("\n");


    // Teste 3
    int V3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(V3)/sizeof(V3[0]);

    printf("Entrada: "), imprimirVetor(V3, n3);
    //insertionSort(V3, n3);
    insertionSortRecursivo(V3, 1, n3);
    printf("Saida: "), imprimirVetor(V3, n3);
    printf("\n");
}
