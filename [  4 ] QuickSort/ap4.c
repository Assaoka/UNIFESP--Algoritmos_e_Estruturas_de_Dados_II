#include <stdio.h>
#include <stdlib.h>

// Função trivial de troca
void troca (int *a, int *b) { 
    int aux = *a;
    *a = *b;
    *b = aux;
}

// Função que divide um subvetor em 2 partes, uma com elementos menores que o pivo e outra com elementos maiores
int particiona (int vet[], int ini, int fim) { 
    int pivo = vet[fim]; // Pivo é o último elemento
    int i = ini - 1; // Começa antes do primeiro elemento (representa a posição do último elemento menor que o pivo)

    for (int j = ini; j < fim; j++) { // Percorre o subvetor
        if (vet[j] < pivo) { // Se o elemento é menor que o pivo
            i++; // Incrementa o índice do ultimo elemento menor que o pivo
            troca(&vet[i], &vet[j]); // Troca o novo elemento menor que o pivo com o elemento atual
        }
    }

    troca(&vet[i + 1], &vet[fim]); // Coloca o pivo na posição correta, uma casa depois do último elemento menor que ele
    return i + 1; // Retorna a posição do pivo
}

// Função que coloca a mediana dos 3 elementos em C (que será o ultimo elemento do subvetor, com o objetivo de torna-lo o pivo)
void medianaDeTres(int *A, int *B, int *C) { 
    if (*A == *B) troca(B, C); // Segundo o enunciado, se A == B, troca B com C
    else if (*A > *B) { // A > B
        if (*C > *A) troca(A, C); // C > A > B
        else if (*B > *C) troca(B, C); // A > B > C
    } else { // B > A
        if (*C > *B) troca(B, C); // C > B > A
        else if (*A > *C) troca(A, C); // B > A > C
    }
}

// Função que implementa o algoritmo de ordenação QuickSort modificado para contar a profundidade e permitir utilizar a mediana de 3 para evitar o pior caso)
void QuickSort (int vet[], int ini, int fim, int *maior, int *menor, int mediana) {
    if (ini < fim) { // Se o subvetor tem mais de 1 elemento
        if (mediana == 1) medianaDeTres(&vet[ini], &vet[(ini + fim) / 2], &vet[fim]); // Se a mediana for 1, coloca a mediana dos 3 elementos em C
        int pivo = particiona(vet, ini, fim); // Divide o subvetor e recebe a posição do pivo
        
        int maiorEsq = 0, menorEsq = 0, maiorDir = 0, menorDir = 0; // Variáveis para armazenar a profundidade (miníma e máxima) das subárvores de recursão
        QuickSort(vet, ini, pivo - 1, &maiorEsq, &menorEsq, mediana); // Chama a função recursivamente para a subárvore da esquerda (menores que o pivo)
        QuickSort(vet, pivo + 1, fim, &maiorDir, &menorDir, mediana); // Chama a função recursivamente para a subárvore da direita (maiores que o pivo)
        *maior = (maiorEsq > maiorDir) ? (maiorEsq + 1) : (maiorDir + 1); // Atualiza a profundidade máxima
        *menor = (menorEsq < menorDir) ? (menorEsq + 1) : (menorDir + 1); // Atualiza a profundidade mínima 
    }
}

int main () {
    int tamanho, *vetor1, *vetor2, maior = 0, menor = 0;
    scanf(" %d", &tamanho); // Lê o tamanho do vetor

    // Aloca espaço para os vetores
    vetor1 = (int *) malloc(tamanho * sizeof(int));
    vetor2 = (int *) malloc(tamanho * sizeof(int));

    // Lê os elementos do vetor e copia para o segundo vetor
    for (int i = 0; i < tamanho; i++) {
        scanf(" %d", &vetor1[i]);
        vetor2[i] = vetor1[i];
    }

    // Ordena os vetores e imprime a diferença entre a profundidade máxima e mínima (sem mediana de 3)
    QuickSort(vetor1, 0, tamanho - 1, &maior, &menor, 0);
    printf("%d\n", maior - menor);

    // Ordena os vetores e imprime a diferença entre a profundidade máxima e mínima (com mediana de 3)
    maior = 0, menor = 0;
    QuickSort(vetor2, 0, tamanho - 1, &maior, &menor, 1);
    printf("%d\n", maior - menor);
    
    // Libera o espaço alocado para os vetores e encerra o programa
    free(vetor1);
    free(vetor2);
    return 0;
}