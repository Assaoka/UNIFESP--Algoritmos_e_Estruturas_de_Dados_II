#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// #####################################################
// Estrutura do Grafo
typedef struct No {
    int chave; // Chave do Vertice
    struct No *prox; // Ponteiro para o proximo vertice
} SNo;
typedef SNo *PNo;

#define BRANCO 0
#define CINZA 1
#define PRETO 2
typedef struct Grafo {
    int cor, pred; // Presente em ambos (Cor e Predecessor)
    int dist; // Busca em Largura (Distancia)
    int desc, fim; // Busca em Profundidade (Tempo de Descoberta e Finalizacao)
    PNo adj; // Lista de Adjacencia (Nós que o vertice se conecta)
} SGrafo;
typedef SGrafo *PGrafo;

// Estrutura da Fila Auxiliar (Busca em Largura)
typedef struct Fila {
    PNo inicio, fim;
} SFila;
typedef SFila *PFila;


// #####################################################
// Criando o Grafo
PNo criarNo (int chave, PNo prox) {
    PNo novo = (PNo) malloc(sizeof(SNo));
    *novo = (SNo) {chave, prox};
    return novo;}

PNo criarAresta (PNo p, int chave) {
    if (p == NULL) return criarNo(chave, NULL);
    else if (chave < p->chave) return criarNo(chave, p);
    else p->prox = criarAresta(p->prox, chave);
    return p;}

PGrafo criarGrafo (int n) {
    PGrafo grafo = (PGrafo) malloc(n * sizeof(SGrafo));
    for (int i = 0; i < n; i++) 
        grafo[i].adj = NULL;
    return grafo;}

        
// #####################################################
// Busca em Largura
PFila criarFila (int chave) {
    PFila fila = (PFila) malloc(sizeof(SFila));
    fila->inicio = fila->fim = criarNo(chave, NULL);
    return fila;}

void enfileirar (PFila fila, int chave) {
    PNo novo = criarNo(chave, NULL);
    if (fila->fim != NULL) fila->fim->prox = novo;
    else fila->inicio = novo;
    fila->fim = novo;}

int desenfileirar (PFila fila) {
    PNo aux = fila->inicio;
    int chave = aux->chave;
    fila->inicio = aux->prox;
    if (fila->inicio == NULL) fila->fim = NULL;
    free(aux);
    return chave;}

void buscaEmLargura (PGrafo g, int n, int s) { // Grafo, Numero de Vertices, Vertice Inicial
    for (int i = 0; i < n; i++) {
        g[i].cor = BRANCO;
        g[i].dist = INT_MAX;
        g[i].pred = -1;}

    g[s].cor = CINZA;
    g[s].dist = 0;
    PFila fila = criarFila(s);
    printf("%d", s);

    while (fila->inicio != NULL) {
        int u = desenfileirar(fila);
        for (PNo p = g[u].adj; p != NULL; p = p->prox) {
            int v = p->chave;
            if (g[v].cor == BRANCO) {
                printf(" %d", v);
                g[v].cor = CINZA;
                g[v].dist = g[u].dist + 1;
                g[v].pred = u;
                enfileirar(fila, v);}}
        g[u].cor = PRETO;}
    printf("\n");
    free(fila);}


// #####################################################
// Busca em Profundidade
void visitaBP (PGrafo g, int u, int *tempo) {
    *tempo = *tempo + 1;
    g[u].desc = *tempo;
    g[u].cor = CINZA;

    for (PNo p = g[u].adj; p != NULL; p = p->prox) {
        int v = p->chave;
        if (g[v].cor == BRANCO) {
            g[v].pred = u;
            printf(" %d", v);
            visitaBP(g, v, tempo);}}

    *tempo = *tempo + 1;
    g[u].fim = *tempo;
    g[u].cor = PRETO;}

void buscaEmProfundidade (PGrafo g, int n, int s) {
    for (int i = 0; i < n; i++) {
        g[i].cor = BRANCO;
        g[i].pred = -1;}
    int tempo = 0;

    printf("%d", s);
    visitaBP(g, s, &tempo);
    for (int i = 0; i < n; i++) {
        if (g[i].cor == BRANCO) {
            printf(" %d", i);
            visitaBP(g, i, &tempo);}}

    printf("\n");}
        

// #####################################################
// Imprimindo e Liberando o Grafo
void imprimirGrafo (PGrafo grafo, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d: ", i);
        for (PNo p = grafo[i].adj; p != NULL; p = p->prox)
            printf("%d ", p->chave);
        printf("\n");}}

void liberarGrafo (PGrafo grafo, int n) {
    for (int i = 0; i < n; i++) {
        PNo p = grafo[i].adj;
        while (p != NULL) {
            PNo aux = p;
            p = p->prox;
            free(aux);}
        grafo[i].adj = NULL;}
    free(grafo);}

int main () {
    PGrafo grafo;
    int v, n, m; // Vertice Inicial, Numero de Vertices, Numero de Arestas
    int a, b; // Vertices que se conectam

    // Criando o Grafo
    scanf("%d %d %d", &v, &n, &m);
    grafo = criarGrafo(n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        grafo[a].adj = criarAresta(grafo[a].adj, b);
    }

    // Busca em Largura
    buscaEmLargura(grafo, n, v);

    // Busca em Profundidade
    buscaEmProfundidade(grafo, n, v);

    // Imprimindo o Grafo
    //imprimirGrafo(grafo, n);
    liberarGrafo(grafo, n);
    return 0;}
