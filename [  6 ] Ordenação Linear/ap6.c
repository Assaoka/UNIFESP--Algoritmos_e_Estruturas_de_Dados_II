#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Retorna o índice da letra c no vetor ord
int findIndex (char c, char ord[]) {
    if (c == ' ') return 0; // Espaço é sempre o primeiro
    for (int i = 0; i < 26; i++) // Percorre as letras do alfabeto
        if (c == ord[i]) return i+1;
}

// Ordena as n palavras de acordo com a letra da posição d
void countSort(char **palavras, char ord[], int d, int n) {
    char **aux = (char **)malloc(sizeof(char *) * n); // Array auxiliar para armazenar as palavras ordenadas
    int *count = (int *)calloc(27, sizeof(int)); // Vetor de contagem para cada letra do alfabeto + espaço
 
    for (int i = 0; i < n; i++) // Conta a quantidade de cada letra
        count[findIndex(palavras[i][d], ord)]++; 
 
    // Faz a soma acumulada das quantidades e imprime
    printf("\n%d", count[0]);
    for (int i = 1; i < 27; i++) {
        count[i] += count[i - 1];
        printf(" %d", count[i]);
    }

    // Utiliza o vetor de contagem para ordenar as palavras
    for (int i = n - 1; i >= 0; i--) {
        int j = findIndex(palavras[i][d], ord);
        aux[count[j] - 1] = palavras[i];
        count[j]--;
    }
 
    // Copia os ponteiros de volta para o array original
    for (int i = 0; i < n; i++)
        palavras[i] = aux[i];
 
    // Libera a memória
    free(aux);
    free(count);
}

// Utiliza o CountSort (estável) para ordenar as palavras de acordo com a letra da posição i
void radixSort (char **palavras, char ord[], int n, int m) {
    for (int i = m - 1; i >= 0; i--) 
        countSort(palavras, ord, i, n);
}

// Lê as palavras, converte para minúsculas e completa com espaços
void lerPalavras (char **palavras, int n, int *m) {
    int tam = 0, i, j;
    for (i = 0; i < n; i++) {
        palavras[i] = (char *) malloc (sizeof(char) * 27);
        scanf(" %s", palavras[i]);
        tam = strlen(palavras[i]);
        if (tam > *m) *m = tam;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; palavras[i][j] != '\0'; j++)
            palavras[i][j] = (palavras[i][j] >= 'A' && palavras[i][j] <= 'Z') ? (palavras[i][j] + 32) : (palavras[i][j]);

        printf("%s.\n", palavras[i]);

        for (; j < *m; j++)
            palavras[i][j] = ' ';

        palavras[i][j] = '\0';
    }
}

int main () {
    char **palavras, *ord = (char *) malloc (sizeof(char) * 27);
    int n, m = 0;

    scanf("%d", &n); // Número de palavras
    scanf(" %s", ord); // Ordem que as letras devem ser consideradas

    palavras = (char **) malloc (sizeof(char *) * n);
    lerPalavras(palavras, n, &m);
    printf("%d", m);

    radixSort(palavras, ord, n, m);

    // Liberar memória
    for (int i = 0; i < n; i++) {
        printf("\n%s", palavras[i]);
        free(palavras[i]);
    }


    free(palavras);
    free(ord);

    return 0;
}
