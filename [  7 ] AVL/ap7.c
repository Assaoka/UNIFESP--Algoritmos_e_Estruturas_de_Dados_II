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
    return (a > b) ? a : b; // Retorna o maior valor entre a e b
}

int altura (PAvl a) {
    if (a == NULL) return -1; // Árvore vazia tem altura -1
    int esq = ((a->esq != NULL) ? a->esq->altura : -1); // Altura da subárvore da esquerda
    int dir = ((a->dir != NULL) ? a->dir->altura : -1); // Altura da subárvore da direita
    return 1 + max(esq, dir); // Retorna a altura do nó
}

int fatorBalanceamento (PAvl a) {
    if (a != NULL) return altura(a->esq) - altura(a->dir); // Retorna o fator de balanceamento
    else return 0; // Se a árvore for vazia, o fator de balanceamento é 0
}

PAvl criaFolha (int info) {
    PAvl novo = (PAvl) malloc(sizeof(SAvl)); // Aloca memória para o novo nó
    *novo = (SAvl) {info, 0, NULL, NULL}; // Inicializa o novo nó (info, altura, esq, dir)
    return novo; // Retorna o novo nó
}

PAvl rotacaoEsq (PAvl a) {
    PAvl b = a->dir; // b é o filho da direita de a
    a->dir = b->esq; // O filho da direita de a é o filho da esquerda de b
    b->esq = a; // O filho da esquerda de b é a

    a->altura = altura(a); // Atualiza a altura de a
    b->altura = altura(b); // Atualiza a altura de b
    return b; // Retorna o novo nó
}

PAvl rotacaoDir (PAvl a) {
    PAvl b = a->esq; // b é o filho da esquerda de a
    a->esq = b->dir; // O filho da esquerda de a é o filho da direita de b
    b->dir = a; // O filho da direita de b é a

    a->altura = altura(a); // Atualiza a altura de a
    b->altura = altura(b); // Atualiza a altura de b
    return b; // Retorna o novo nó
}

PAvl balancearNo (PAvl a) {
    int fb = fatorBalanceamento(a); // Calcula o fator de balanceamento
    if (fb >= 2) {
        if (fatorBalanceamento(a->esq) < 0) a->esq = rotacaoEsq(a->esq); // Rotação Dupla (Esquerda-Direita). Se o fator de balanceamento do nó é 2 e o do filho da esquerda é negativo, rotaciona a subárvore da esquerda para a esquerda
        return rotacaoDir(a); // Rotaciona a árvore para a direita
    } else if (fb <= -2) {
        if (fatorBalanceamento(a->dir) > 0) a->dir = rotacaoDir(a->dir); // Rotação Dupla (Direita-Esquerda). Se o fator de balanceamento do nó é -2 e o do filho da direita é positivo, rotaciona a subárvore da direita para a direita
        return rotacaoEsq(a); // Rotaciona a árvore para a esquerda
    }
    return a; // Retorna o nó (já balanceado)
}

PAvl inserir (PAvl a, int info) {
    if (a == NULL) return criaFolha(info); // Se a árvore for vazia, cria uma folha com a informação
    if (info < a->info) a->esq = inserir(a->esq, info); // Se a informação for menor que a do nó, insere na subárvore da esquerda
    else if (info > a->info) a->dir = inserir(a->dir, info); // Se a informação for maior que a do nó, insere na subárvore da direita

    a->altura = altura(a); // Atualiza a altura do nó
    return balancearNo(a); // Balanceia a árvore
}

PAvl remover (PAvl a, int info) {
    if (a == NULL) return NULL; // Não encontrou a informação
    if (info < a->info) a->esq = remover(a->esq, info); // Se a informação for menor que a do nó, remove da subárvore da esquerda
    else if (info > a->info) a->dir = remover(a->dir, info); // Se a informação for maior que a do nó, remove da subárvore da direita
    else { // Encontrou a informação
        PAvl p; // Ponteiro auxiliar
        if (a->esq == NULL && a->dir == NULL) { // Se o nó for folha
            free(a); // Libera o nó
            return NULL; // Retorna NULL
        } else if (a->esq == NULL) { // Se o nó tiver apenas um filho à direita
            p = a->dir; // p é o filho da direita
            free(a); // Libera o nó
            return p; // Retorna o filho da direita
        } else if (a->dir == NULL) { // Se o nó tiver apenas um filho à esquerda
            p = a->esq; // p é o filho da esquerda
            free(a); // Libera o nó
            return p; // Retorna o filho da esquerda
        } else { // Se o nó tiver dois filhos (usando a estratégia de substituição por sucessor)
            for (p = a->dir; p->esq != NULL; p = p->esq); // Encontra o nó sucessor
            a->info = p->info; // Substitui a informação do nó pelo sucessor
            p = remover(a->dir, p->info); // Remove o sucessor (que foi duplicado na posição atual)
            a->dir = p; // O filho da direita do nó é o sucessor
        }
    }
    
    a->altura = altura(a); // Atualiza a altura do nó
    return balancearNo(a); // Balanceia a árvore
}

PAvl busca (PAvl a, int info) {
    if (a == NULL) return NULL; // Se a árvore for vazia, retorna NULL
    if (info < a->info) return busca(a->esq, info); // Se a informação for menor que a do nó, busca na subárvore da esquerda
    else if (info > a->info) return busca(a->dir, info); // Se a informação for maior que a do nó, busca na subárvore da direita
    else return a; // Se a informação for igual à do nó, retorna o nó
}

PAvl liberar (PAvl a) {
    if (a == NULL) return NULL; // Se a árvore for vazia, retorna NULL
    a->esq = liberar(a->esq); // Libera a subárvore da esquerda
    a->dir = liberar(a->dir); // Libera a subárvore da direita
    free(a); // Libera o nó
    return NULL; // Retorna NULL
}

int main () {
    int chave = 1; // Chave a ser inserida
    PAvl arv = NULL, p; // Cria uma árvore AVL vazia

    while (chave > -1) {
        scanf("%d", &chave); // Lê a chave
        if (chave > -1) arv = inserir(arv, chave); // Insere a chave na árvore
    }

    // A primeira linha da saída contem a altura máxima da ABB a partir do seu nó raiz seguida da altura da sub-arvore da esquerda e da direita.
    printf("%d, %d, %d\n", arv->altura, altura(arv->esq) + 1, altura(arv->dir) + 1); // Imprime a altura da árvore
    
    chave = 1; // Chave a ser removida
    while (chave > -1) {
        scanf("%d", &chave); // Lê a chave
        if (chave > -1) {
            p = busca(arv, chave); // Busca a chave na árvore
            if (p != NULL) arv = remover(arv, chave); // Se a chave foi encontrada, remove da árvore
            else inserir(arv, chave); // Se a chave não foi encontrada, insere na árvore
        }
    }

    // Na segunda linha, deve ser impresso o valor da altura do no pesquisado (linha 03 dos dados de entrada), seguido pela altura da sub-arvore da esquerda e direita. Caso esse valor pesquisado nao seja encontrado, deve ser exibido ”Valor nao encontrado”.
    scanf("%d", &chave); // Lê a chave
    p = busca(arv, chave); // Busca a chave na árvore
    if (p != NULL) printf("%d, %d, %d\n", p->altura, altura(p->esq) + 1, altura(p->dir) + 1); // Se a chave foi encontrada, imprime a altura do nó
    else printf("Valor nao encontrado\n"); // Se a chave não foi encontrada, imprime "Valor nao encontrado" 

    arv = liberar(arv); // Libera a árvore
    return 0; // Retorna 0
}
