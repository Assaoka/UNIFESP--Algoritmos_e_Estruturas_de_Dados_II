#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int n;
    struct No *prox;
} SNo;
typedef SNo *PNo;

void imprimirLista (PNo V[], int n) {
    for (int i = 0; i <= n; i++) {
        printf("%d: ", i);
        for (PNo j = V[i]; j != NULL; j = j->prox) printf(" -> %d", j->n);
        printf("\n");
    }
}

void imprimirVetor (int V[], int n) {
    for (int i = 0; i <= n; i++) printf("%d ", V[i]);
    printf("\n");
}


PNo criaNo (int n, PNo prox) {
    PNo novo = (PNo)malloc(sizeof(SNo));
    *novo = (SNo){n, prox};
    return novo;
}

PNo inserirOrd (PNo ini, int n) {
    if (ini == NULL) return criaNo(n, NULL);
    if (n < ini->n) return criaNo(n, ini);
    else ini->prox = inserirOrd(ini->prox, n);
    return ini;
}

#define BIN 100
void bucketSort (int V[], int n) {
    PNo A[10] = {NULL};
    for (int i = 0; i <= n; i++) A[V[i]/BIN] = inserirOrd(A[V[i]/BIN], V[i]);
    imprimirLista(A, 9);
    for (int i = 0, j = 0; j <= n; i++) {
        for (PNo k = A[i], aux; k != NULL; k = aux, j++) {
            aux = k->prox;
            V[j] = k->n;
            free(k);
        }
    }
    imprimirVetor(V, 9);
}

int main () {
    int A[] = {153, 987, 345, 124, 456, 289, 234, 567, 890, 153};
    bucketSort(A, 9);
/*
0:
1:  -> 124 -> 153 -> 153
2:  -> 234 -> 289
3:  -> 345
4:  -> 456
5:  -> 567
6:
7:
8:  -> 890
9:  -> 987
124 153 153 234 289 345 456 567 890 987
*/

    printf("\n\n");
    int B[] = {780, 170, 390, 260, 720, 940, 210, 120, 230, 680};
    bucketSort(B, 9);

/*
0:
1:  -> 120 -> 170
2:  -> 210 -> 230 -> 260
3:  -> 390
4:
5:
6:  -> 680
7:  -> 720 -> 780
8:
9:  -> 940
120 170 210 230 260 390 680 720 780 940
*/
}