// João Victor Assaoka Ribeiro
#include <stdlib.h>
#include <stdio.h>

typedef struct No {
	int info; // Informação do Elemento
	struct No *prox; // Ponteiro para o Próximo Elemento
} SNo;
typedef SNo *PNo;

PNo inserirIni (PNo lista, int v) {
	PNo novo = (PNo) malloc(sizeof(SNo)); // Aloca Memória para o Novo Nó
	novo->info = v; // Atribui o Valor ao Novo Nó
	novo->prox = lista; // O Novo Nó Aponta para o Primeiro Elemento da Lista
	lista = novo; // O Primeiro Elemento da Lista Agora é o Novo Nó
	return lista; // Retorna a Lista Atualizada (Novo Nó)
}

void listar (PNo lista) {
	PNo aux; // Ponteiro Auxiliar para Percorrer a Lista
	for (aux = lista; aux != NULL; aux = aux->prox) // Percorre a Lista
		printf("%d ", aux->info); // Imprime a Informação do Elemento
	printf("\n");
}

PNo liberar (PNo lista) {
	PNo aux; // Ponteiro Auxiliar para Percorrer a Lista
	for (aux = lista; aux != NULL; aux = lista) { // Percorre a Lista
		lista = lista->prox; // O Primeiro Elemento da Lista Agora é o Próximo Elemento do Nó Removido
		free(aux); // Libera a Memória Alocada para o Nó Removido
	}
	return NULL; // Retorna NULL (Lista Vazia)
}

PNo merge(PNo esquerda, PNo direita) {
	PNo lista = NULL, ultimo = NULL;

	while ((esquerda != NULL) && (direita != NULL)) {
		if (esquerda->info <= direita->info) {
			if (ultimo == NULL) lista = ultimo = esquerda;
			else {
				ultimo->prox = esquerda;
				ultimo = ultimo->prox;
			}
			esquerda = esquerda->prox;
		} else {
			if (ultimo == NULL) lista = ultimo = direita;
			else {
				ultimo->prox = direita;
				ultimo = ultimo->prox;
			}
			direita = direita->prox;
		}
	}
	
	if (esquerda != NULL) ultimo->prox = esquerda;
	else if (direita != NULL) ultimo->prox = direita;
	return lista;
}

PNo mergeSort(PNo inicio, int tamanho, int *profundidade) {
	if (tamanho == 1) return inicio;
	
	int tamEsquerda = tamanho / 2 + tamanho % 2; // Se for ímpar o valor à esquerda fica maior
	PNo esquerda = inicio, direita, anterior = inicio;
	
	for (int i = 0; i < tamEsquerda - 1; i++, anterior = anterior->prox);
	direita = anterior->prox;
	anterior->prox = NULL;

	int profundidadeEsquerda = 0, profundidadeDireita = 0;
    esquerda = mergeSort(esquerda, tamEsquerda, &profundidadeEsquerda);
    direita = mergeSort(direita, tamanho - tamEsquerda, &profundidadeDireita);
	*profundidade = (profundidadeEsquerda > profundidadeDireita) ? (profundidadeEsquerda + 1) : (profundidadeDireita + 1);

	return merge(esquerda, direita);
}

int main () {
    PNo lista = NULL;
    int numElementos, valor, profundidade;

    scanf(" %d", &numElementos);
    for (int i = 0; i < numElementos; i++) {
        scanf(" %d", &valor);
        lista = inserirIni(lista, valor);
    }

	lista = mergeSort(lista, numElementos, &profundidade);
	
	listar(lista);
	printf("%d", profundidade);

	lista = liberar(lista);
    return 0;
}
