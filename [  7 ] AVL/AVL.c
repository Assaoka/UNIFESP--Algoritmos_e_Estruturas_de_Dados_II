#include <stdio.h>
#include <stdlib.h>

typedef struct ArvoreAVl {
    int info; // Informação do nó (Chave)
    int altura; // Altura do nó
    struct ArvoreAVl *esq; // Ponteiro para o filho da esquerda (menor)
    struct ArvoreAVl *dir; // Ponteiro para o filho da direita (maior)
} SAvl; // Estrutura da árvore AVL
typedef SAvl *PAvl; // Ponteiro para a árvore AVL

int max (int a, int b) {
    if (a >= b) return a;
    else return b;
}

int altura (PAvl a) {
    if (a == NULL) return 0;
    int esq = (a->esq == NULL) ? (0) : (a->esq->altura);
    int dir = (a->dir == NULL) ? (0) : (a->dir->altura);
    return max(esq, dir) + 1;
}

int fb (PAvl a) {
    if (a == NULL) return 0;
    else return altura(a->esq) - altura(a->dir);
}

PAvl RR (PAvl a) { // Rotação a direita (subárvore direita é maior -> fb negativo)
    PAvl b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->altura = altura(a);
    b->altura = altura(b);
    return b;
}

PAvl LL (PAvl a) { // Rotação a esquerda (subárvore esquerda é maior -> fb positivo)
    PAvl b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->altura = altura(a);
    b->altura = altura(b);
    return b;
}

PAvl balancear (PAvl a) {
    if (a == NULL) return NULL;
    if (fb(a) == -2) { // Subárvore direita maior
        if (fb(a->dir) == +1) a->dir = LL(a->dir); // Rotação dupla a esquerda (RL)
        return RR(a);
    } else if (fb(a) == +2) { // Subárvore esquerda maior
        if (fb(a->esq) == -1) a->esq = RR(a->esq); // Rotação dupla a direita (LR)
        return LL(a);
    }
}

PAvl criaNo (int n) {
    PAvl novo = (PAvl)malloc(sizeof(SAvl));
    *novo = (SAvl){n, 1, NULL, NULL};
}

PAvl inserir (PAvl a, int n) {
    if (a == NULL) return criaNo(n);
    if (n <= a->info) a->esq = inserir(a->esq, n);
    else a->dir = inserir (a->dir, n);
    a->altura = altura(a);
    return balancear(a);
}

PAvl remover (PAvl a, int n) {
    if (a == NULL) return NULL;
    if (n < a->info) a->esq = remover(a->esq, n);
    else if (n > a->info) a->dir = remover(a->dir, n);
    else {
        if (a->esq == NULL && a->dir == NULL) { // não tem filhos
            free(a);
            return NULL;
        } else if (a->esq == NULL) { // só tem filho a direita
            PAvl aux = a->dir;
            free(a);
            return aux;
        } else if (a->dir == NULL) { // só tem filho a esquerda
            PAvl aux = a->esq;
            free(a);
            return aux;
        } else { // 2 Filhos
            PAvl p;
            if (a->esq->altura >= a->dir->altura) { // Estrategia do Antecessor
                for (p = a->esq; p->dir != NULL;) p = p->dir;
                a->info = p->info;
                a->esq = remover(a->esq, p->info);
            } else {
                for (p = a->dir; p->esq != NULL;) p = p->esq;
                a->info = p->info;
                a->dir = remover(a->dir, p->info);
            }
        }
    }

    a->altura = altura(a);
    return balancear(a);
}

PAvl liberar (PAvl a) {
    if (a == NULL) return NULL; // Se a árvore for vazia, retorna NULL
    a->esq = liberar(a->esq); // Libera a subárvore da esquerda
    a->dir = liberar(a->dir); // Libera a subárvore da direita
    free(a); // Libera o nó
    return NULL; // Retorna NULL
}

void imprimir(PAvl a, int n) {
    for (int i = 0; i > n; i++) printf(" - ");
    printf("%d", a->info);
    imprimir(a->esq, n+1);
    imprimir(a->dir, n+1);
}

int main () {
    PAvl a = NULL;

    int n = 20;
    while (n != 999) {
        scanf("%d", &n);
        a = inserir (a, n);
        imprimir(a, 0);
    }

    n = 20;
    while (n != 999) {
        scanf("%d", &n);
        a = remover(a, n);
        imprimir(a, 0);
    }

    a = liberar(a);
}
