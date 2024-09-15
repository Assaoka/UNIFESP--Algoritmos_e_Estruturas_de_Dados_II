// João Victor Assaoka Ribeiro - 168863
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void swap(char **a, char **b) { // Função trivial para trocar dois elementos
    char *aux = *a;
    *a = *b;
    *b = aux;
}
 
void maxHeapify(char *v[], int tam, int i) {
    int esq = 2 * i + 1; // índice do filho da esquerda
    int dir = 2 * i + 2; // índice do filho da direita
    int max = i; // índice do maior elemento
 
    if (esq < tam && strcmp(v[max], v[esq]) < 0) max = esq; // se o filho da esquerda for maior que o pai
    if (dir < tam && strcmp(v[max], v[dir]) < 0) max = dir; // se o filho da direita for maior que o pai
     
    if (max != i) { // se o maior elemento não for o pai
        swap(&v[i], &v[max]); // troca o pai com o maior filho
        maxHeapify(v, tam, max); // chama recursivamente para o filho que foi trocado
    }
}
 
void buildMaxHeap(char *v[], int tam) {
    for (int i = tam / 2 - 1; i >= 0; i--) // começa do último nó não folha até a raiz
        maxHeapify(v, tam, i); // chama a função para cada nó
}
 
void heapSort(char *v[], int tam) {
    buildMaxHeap(v, tam); // cria o heap máximo
 
    printf("build_heap:"); // Imprime a mensagem
    for (int i = 0; i < tam; i++) printf(" %s", v[i]); // Imprime o heap
    printf("\n");

    for (; tam > 1; tam--) { // Enquanto houver elementos
        maxHeapify(v, tam, 0); // reorganiza o heap a partir do primeiro elemento
        swap(&v[0], &v[tam - 1]); // troca o primeiro (maior elemento) com o último
    }
}
 
int palavraValida(char palavra[]) { // Função que verifica se a palavra é válida
    for (int i = 0; palavra[i] != '\0'; i++) { // Percorre a palavra
        if (palavra[i] < 'a' || palavra[i] > 'z') { // Se não for uma letra minúscula
            printf("a palavra %s eh invalida\n", palavra); // Imprime a mensagem de erro
            return 0; // Se não for uma letra minúscula
        }
    }
    return 1; // Se for uma palavra válida
}
 
int lerVetor(char *V[], int N) {
    for (int i = 0; i < N; i++) { // Lê N palavras
        V[i] = (char *) malloc(21 * sizeof(char)); // Aloca espaço para a i-ésima palavra
        scanf("%s", V[i]); // Lê a i-ésima palavra
        if (palavraValida(V[i]) == 0) return 0; // Encerra o programa se a palavra for inválida
    }
    return 1; // Prossegue se todas as palavras forem válidas
}
 
void liberarVetor(char *V[], int N) {
    for (int i = 0; i < N; i++) free(V[i]); // Libera cada palavra
    free(V); // Libera o vetor de palavras
}
 
int main() {
    int N, M; // Quantidade de palavras do conjunto inicial e do conjunto de palavras selecionadas
    char **V; // Vetor de Palavras
 
    // A primeira linha contem a quantidade N do total de palavras do conjunto inicial
    scanf("%d", &N);
 
    // A segunda linha contem as N palavras separadas por um espaço, representando o conjunto inicial de palavras.
    V = (char **) malloc(N * sizeof(char *));
    if (lerVetor(V, N) == 0) { // Palavra inválida (Já imprime a mensagem)
        liberarVetor(V, N); // Libera o vetor
        return 0; // Encerra o programa
    }
 
 
    // A terceira linha refere-se a quantidade (M) de palavras do conjunto de palavras selecionadas.
    scanf("%d", &M);
 
    // A quarta linha contem M inteiros que representam as posições separados por espaço, que representam as palavras a serem ordenadas.
    char **V2 = (char **) malloc(M * sizeof(char *));
    for (int i = 0; i < M; i++) {
        int pos;
        scanf("%d", &pos);
        V2[i] = strdup(V[pos]); // Copia a palavra do vetor original para o vetor de palavras selecionadas
    }
 
    // A primeira linha da saída representa o conjunto heap de tamanho M.
    heapSort(V2, M);
    
    // A segunda linha da saída e composta pela string 'palavras:' e o novo conjunto ordenado das M palavras.
    printf("palavras:");
    for (int i = 0; i < M; i++) printf(" %s", V2[i]);
    printf("\n");
    
    // Libera os vetores
    liberarVetor(V, N), liberarVetor(V2, M); 
    return 0;
}