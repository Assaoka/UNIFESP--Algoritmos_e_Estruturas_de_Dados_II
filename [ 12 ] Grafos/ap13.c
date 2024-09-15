#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// #####################################################
// Estrutura do Grafo
typedef struct No {
    int chave, peso; // Chave do Vertice e Peso da Aresta
    struct No *prox; // Ponteiro para o proximo vertice
} SNo;
typedef SNo *PNo;

typedef struct Grafo {
    int pred, dist;
    PNo adj; // Lista de Adjacencia (Nós que o vertice se conecta)
} SGrafo;
typedef SGrafo *PGrafo;

// #####################################################
// Criando o Grafo
PNo criarNo (int chave, int peso, PNo prox) {
    PNo novo = (PNo) malloc(sizeof(SNo));
    *novo = (SNo) {chave, peso, prox};
    return novo;}

PNo criarAresta (PNo p, int chave, int peso) {
    if (p == NULL) return criarNo(chave, peso, NULL);
    else if (chave < p->chave) return criarNo(chave, peso, p);
    else p->prox = criarAresta(p->prox, chave, peso);
    return p;}

PGrafo criarGrafo (int n) {
    PGrafo grafo = (PGrafo) malloc(n * sizeof(SGrafo));
    for (int i = 0; i < n; i++) 
        grafo[i].adj = NULL;
    return grafo;}

// #####################################################
// Caminho Minimo (Bellman-Ford)

void relax (PGrafo g, int u, int v, int w) {
    if (g[u].dist != INT_MAX && g[v].dist > g[u].dist + w) { // Se u for int_max, somar com w vai dar overflow.
        g[v].dist = g[u].dist + w;
        g[v].pred = u;}}

int bellmanFord (PGrafo g, int n, int s) {
    for (int i = 0; i < n; i++) {
        g[i].dist = INT_MAX;
        g[i].pred = -1;}
    g[s].dist = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (PNo p = g[u].adj; p != NULL; p = p->prox) {
                int v = p->chave;
                int w = p->peso;
                relax(g, u, v, w);}}}
}

// #####################################################
void imprimirGrafo (PGrafo grafo, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d(%d): ", i, grafo[i].dist);
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
    int v, r, n, m; // Vertice Inicial, Restrição, Numero de Vertices, Numero de Arestas
    int a, b, w; // Vertices que se conectam e Peso da Aresta

    // Criando o Grafo
    scanf("%d %d %d %d", &v, &r, &n, &m);
    grafo = criarGrafo(n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &w);
        if (w <= r) grafo[a].adj = criarAresta(grafo[a].adj, b, w);
    }

    // Caminho Minimo
    bellmanFord(grafo, n, v);
    
    // Imprime as distancias
    printf("%d", grafo[0].dist);
    for (int i = 1; i < n; i++) {
        printf(" %d", grafo[i].dist);}

    // Imprimindo o Grafo
    imprimirGrafo(grafo, n);
    liberarGrafo(grafo, n);
    return 0;}
