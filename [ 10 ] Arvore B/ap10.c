#include <stdio.h>
#include <stdlib.h>

typedef struct Pagina {
    int n;
    int *elementos;
    struct Pagina **filhos;
} SArv;
typedef SArv *PArv;

PArv cria(int ordem) {
    PArv arv = (PArv) malloc(sizeof(SArv));
    arv->n = 0;
    arv->elementos = (int *) malloc((2*ordem + 1) * sizeof(int));
    arv->filhos = (PArv *) malloc((2*ordem + 2) * sizeof(PArv));
    for (int i = 0; i <= 2*ordem + 1; i++) {
        arv->filhos[i] = NULL;
    }
    return arv;
}

int inserirNaPagina(PArv a, int chave) {
    int i;
    for (i = a->n - 1; i >= 0 && a->elementos[i] > chave; i--) {
        a->elementos[i + 1] = a->elementos[i];
        a->filhos[i + 2] = a->filhos[i + 1];  // Ajustar os filhos
    }
    a->elementos[i + 1] = chave;
    a->n++;
    return i + 1;
}

int buscaNaPagina (PArv a, int chave) {
    int ini = 0, fim = a->n - 1, meio;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        if (a->elementos[meio] == chave) return meio;
        if (a->elementos[meio] < chave) ini = meio + 1;
        else fim = meio - 1;
    }
    return ini;
}

void dividirPagina(PArv pai, int i) {
    PArv a = pai->filhos[i];
    int ordem = a->n / 2;

    PArv esq = cria(ordem);
    PArv dir = cria(ordem);
    for (int j = 0; j < ordem; j++) {
        esq->elementos[j] = a->elementos[j];
        esq->filhos[j] = a->filhos[j];
        dir->elementos[j] = a->elementos[j + ordem + 1];
        dir->filhos[j] = a->filhos[j + ordem + 1];
    }
    esq->filhos[ordem] = a->filhos[ordem];
    dir->filhos[ordem] = a->filhos[a->n];

    esq->n = ordem;
    dir->n = ordem;

    int j = inserirNaPagina(pai, a->elementos[ordem]);
    pai->filhos[j] = esq;
    pai->filhos[j + 1] = dir;

    free(a->elementos);
    free(a->filhos);
    free(a);
}

PArv inserirNaArv (PArv a, int chave, int ordem) {
    if (a->filhos[0] == NULL) { // é folha
        inserirNaPagina(a, chave);
        return a;
    }

    int i = buscaNaPagina(a, chave);
    inserirNaArv(a->filhos[i], chave, ordem);

    if (a->filhos[i]->n == (2*ordem + 1)) dividirPagina(a, i);
    return a;
}

PArv inserir (PArv a, int chave, int ordem) {
    a = inserirNaArv(a, chave, ordem);
    if (a->n == (2*ordem + 1)) {
        PArv novo = cria(ordem);
        novo->filhos[0] = a;
        dividirPagina(novo, 0);
        return novo;
    }
    return a;
}

PArv buscar (PArv a, int chave) {
    if (a == NULL) return NULL;
    int i = buscaNaPagina(a, chave);
    if (i < a->n && a->elementos[i] == chave) return a;
    return buscar(a->filhos[i], chave);
}

void imprime (PArv a, int nivel) {
    for (int i = 0; i < nivel; i++) printf("  ");
    printf("[");
    
    for (int i = 0; i < a->n; i++) {
        printf("%d ", a->elementos[i]);
    }
    printf("\b]\n");

    for (int i = 0; i <= a->n; i++) {
        if (a->filhos[i] != NULL) imprime(a->filhos[i], nivel + 1);
    }
}

void libera (PArv a) {
    if (a == NULL) return;
    for (int i = 0; i <= a->n; i++) {
        libera(a->filhos[i]);
    }
    free(a->elementos);
    free(a->filhos);
    free(a);
}

int main () {
    int ordem;
    scanf("%d", &ordem);

    PArv arvore = cria(ordem);
    int chave;

    scanf("%d", &chave);
    while (chave >= 0) {
        if (buscar(arvore, chave) == NULL) {
        arvore = inserir(arvore, chave, ordem);
        //imprime(arvore, 0);
        }
        scanf("%d", &chave);
    }

    printf("%d\n", arvore->n);

    scanf("%d", &chave);
    PArv b = buscar(arvore, chave);
    if (b == NULL) printf("Valor nao encontrado\n");
    else{ 
        printf("%d\n", b->n);
        for (int i = 0; i < b->n; i++) {
            printf("%d ", b->elementos[i]);
        }
    }
    printf("\n");

    libera(arvore);
    return 0;
}
