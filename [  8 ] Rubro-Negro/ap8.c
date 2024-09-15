#include <stdio.h>
#include <stdlib.h>

int max (int a, int b) {
    return (a > b) ? a : b; // Retorna o maior valor entre a e b
}

int mudancasCor = 0, rotacoesAVP = 0, rotacoesAVL = 0; // Esse exercício não impediu a utilização de variáveis globais

// ====================================================================================================================
// =============================================== ARVORE AVL =========================================================
typedef struct ArvoreAVl {
    int info; // Informação do nó (Chave)
    int altura; // Altura do nó
    struct ArvoreAVl *esq; // Ponteiro para o filho da esquerda (menor)
    struct ArvoreAVl *dir; // Ponteiro para o filho da direita (maior)
} SAvl; // Estrutura da árvore AVL
typedef SAvl *PAvl; // Ponteiro para a árvore AVL

int alturaAVL (PAvl a) {
    if (a == NULL) return -1; // Árvore vazia tem altura -1
    int esq = ((a->esq != NULL) ? a->esq->altura : -1); // Altura da subárvore da esquerda
    int dir = ((a->dir != NULL) ? a->dir->altura : -1); // Altura da subárvore da direita
    return 1 + max(esq, dir); // Retorna a altura do nó
}

int fatorBalanceamento (PAvl a) {
    if (a != NULL) return alturaAVL(a->esq) - alturaAVL(a->dir); // Retorna o fator de balanceamento
    else return 0; // Se a árvore for vazia, o fator de balanceamento é 0
}

PAvl criaFolhaAVL (int info) {
    PAvl novo = (PAvl) malloc(sizeof(SAvl)); // Aloca memória para o novo nó
    *novo = (SAvl) {info, 0, NULL, NULL}; // Inicializa o novo nó (info, altura, esq, dir)
    return novo; // Retorna o novo nó
}

PAvl rotacaoEsqAVL (PAvl a) {
    PAvl b = a->dir; // b é o filho da direita de a
    a->dir = b->esq; // O filho da direita de a é o filho da esquerda de b
    b->esq = a; // O filho da esquerda de b é a

    a->altura = alturaAVL(a); // Atualiza a altura de a
    b->altura = alturaAVL(b); // Atualiza a altura de b
    return b; // Retorna o novo nó
}

PAvl rotacaoDirAVL (PAvl a) {
    PAvl b = a->esq; // b é o filho da esquerda de a
    a->esq = b->dir; // O filho da esquerda de a é o filho da direita de b
    b->dir = a; // O filho da direita de b é a

    a->altura = alturaAVL(a); // Atualiza a altura de a
    b->altura = alturaAVL(b); // Atualiza a altura de b
    return b; // Retorna o novo nó
}

PAvl balancearNoAVL (PAvl a) {
    int fb = fatorBalanceamento(a); // Calcula o fator de balanceamento
    if (fb >= 2) {
        rotacoesAVL++; // Incrementa a quantidade de rotações
        if (fatorBalanceamento(a->esq) < 0) a->esq = rotacaoEsqAVL(a->esq); // Rotação Dupla (Esquerda-Direita). Se o fator de balanceamento do nó é 2 e o do filho da esquerda é negativo, rotaciona a subárvore da esquerda para a esquerda
        return rotacaoDirAVL(a); // Rotaciona a árvore para a direita
    } else if (fb <= -2) {
        rotacoesAVL++; // Incrementa a quantidade de rotações
        if (fatorBalanceamento(a->dir) > 0) a->dir = rotacaoDirAVL(a->dir); // Rotação Dupla (Direita-Esquerda). Se o fator de balanceamento do nó é -2 e o do filho da direita é positivo, rotaciona a subárvore da direita para a direita
        return rotacaoEsqAVL(a); // Rotaciona a árvore para a esquerda
    }
    return a; // Retorna o nó (já balanceado)
}

PAvl inserirAVL (PAvl a, int info) {
    if (a == NULL) return criaFolhaAVL(info); // Se a árvore for vazia, cria uma folha com a informação
    if (info < a->info) a->esq = inserirAVL(a->esq, info); // Se a informação for menor que a do nó, insere na subárvore da esquerda
    else if (info > a->info) a->dir = inserirAVL(a->dir, info); // Se a informação for maior que a do nó, insere na subárvore da direita

    a->altura = alturaAVL(a); // Atualiza a altura do nó
    return balancearNoAVL(a); // Balanceia a árvore
}

PAvl buscaAVL (PAvl a, int info) {
    if (a == NULL) return NULL; // Se a árvore for vazia, retorna NULL
    if (info < a->info) return buscaAVL(a->esq, info); // Se a informação for menor que a do nó, busca na subárvore da esquerda
    else if (info > a->info) return buscaAVL(a->dir, info); // Se a informação for maior que a do nó, busca na subárvore da direita
    else return a; // Se a informação for igual à do nó, retorna o nó
}

PAvl liberarAVL (PAvl a) {
    if (a == NULL) return NULL; // Se a árvore for vazia, retorna NULL
    a->esq = liberarAVL(a->esq); // Libera a subárvore da esquerda
    a->dir = liberarAVL(a->dir); // Libera a subárvore da direita
    free(a); // Libera o nó
    return NULL; // Retorna NULL
}

// ====================================================================================================================
// =============================================== ARVORE RUBRO-NEGRA =================================================
#define VERMELHO 1
#define PRETO 0
typedef struct ArvoreRubroNegra {
    int info; // Informação do nó (Chave)
    int cor; // Cor do nó
    struct ArvoreRubroNegra *esq; // Ponteiro para o filho da esquerda (menor)
    struct ArvoreRubroNegra *dir; // Ponteiro para o filho da direita (maior)
    struct ArvoreRubroNegra *pai; // Ponteiro para o pai
} SArn; // Estrutura da Árvore Rubro-Negra
typedef SArn *PArn; // Ponteiro para a Árvore Rubro-Negra

PArn criaFolhaRN (int info) {
    PArn novo = (PArn) malloc(sizeof(SArn)); // Aloca memória para o novo nó
    *novo = (SArn) {info, VERMELHO, NULL, NULL, NULL}; // Inicializa o novo nó (info, cor, esq, dir, pai)
    return novo; // Retorna o novo nó
}

int cor (PArn a) {
    if (a == NULL) return PRETO; // Nó nulo é preto
    else return a->cor; // Retorna a cor do nó
}

void imprimir(PArn raiz, int nivel) {
    if (raiz != NULL) {
        for (int i = 0; i < nivel; i++) printf("  ");
        printf("%d (%s)\n", raiz->info, raiz->cor == VERMELHO ? "VERMELHO" : "PRETO");
        imprimir(raiz->esq, nivel + 1);
        imprimir(raiz->dir, nivel + 1);
    }
}

void rotacaoEsqRN(PArn *raiz, PArn x) {
    //printf("Esquerda em %d\n", x->info);
    PArn y = x->dir; // y é o filho da direita de x
    x->dir = y->esq; // O filho da esquerda de y se torna o filho da direita de x
    
    if (y->esq != NULL) y->esq->pai = x; // Se o filho da esquerda de y não for nulo, o pai dele é x
    y->pai = x->pai; // O pai de y é o pai de x

    if (x == *raiz) *raiz = y; // Se x é a raiz, y se torna a nova raiz
    else if (x == x->pai->esq) x->pai->esq = y; // Se x é o filho da esquerda do pai, y se torna o filho da esquerda do pai
    else x->pai->dir = y; // Se x é o filho da direita do pai, y se torna o filho da direita do pai

    y->esq = x; // x se torna o filho da esquerda de y
    x->pai = y; // y se torna o pai de x
}

void rotacaoDirRN(PArn *raiz, PArn y) {
    //printf("Direita em %d\n", y->info);
    PArn x = y->esq; // x é o filho da esquerda de y
    y->esq = x->dir; // O filho da direita de x se torna o filho da esquerda de y

    if (x->dir != NULL) x->dir->pai = y; // Se o filho da direita de x não for nulo, o pai dele é y
    x->pai = y->pai; // O pai de x é o pai de y

    if (y == *raiz) *raiz = x; // Se y é a raiz, x se torna a nova raiz
    else if (y == y->pai->esq) y->pai->esq = x; // Se y é o filho da esquerda do pai, x se torna o filho da esquerda do pai
    else y->pai->dir = x; // Se y é o filho da direita do pai, x se torna o filho da direita do pai
    
    x->dir = y; // y se torna o filho da direita de x
    y->pai = x; // x se torna o pai de y
}

// Função para balancear a árvore após a inserção
void balancearRN (PArn *raiz, PArn z) { // z inicialmente é o nó inserido
    while (z != *raiz && z->pai->cor == VERMELHO) { // Se o pai de z é vermelho (temos duas cores vermelhas seguidas)
        if (z->pai == z->pai->pai->esq) { // Se o pai de z é um filho da esquerda
            PArn y = z->pai->pai->dir; // y é o tio de z, que é o filho da direita do avô de z
            if (cor(y) == VERMELHO) { // O pai e o tio são vermelhos
                mudancasCor += 3; // ======================== Mudança de cor ========================
                z->pai->cor = PRETO; // Pinta o pai de preto
                y->cor = PRETO; // Pinta o tio de preto
                z->pai->pai->cor = VERMELHO; // Pinta o avô de vermelho
                z = z->pai->pai; // z se torna o avô
            } else { // O pai é vermelho e o tio é preto
                if (z == z->pai->dir) { // Se z é um filho da direita
                    z = z->pai; // z se torna o pai
                    rotacaoEsqRN(raiz, z); // Rotação à esquerda em z
                    rotacoesAVP++; // Incrementa a quantidade de rotações
                }
                mudancasCor += 2; // ======================== Mudança de cor ========================
                z->pai->cor = PRETO; // Pinta o pai de preto
                z->pai->pai->cor = VERMELHO; // Pinta o avô de vermelho
                rotacaoDirRN(raiz, z->pai->pai); // Rotação à direita no avô
                rotacoesAVP++; // Incrementa a quantidade de rotações (simples ou dupla são consideradas como uma única rotação)
            }
        } else { // Se o pai de z é um filho da direita
            PArn y = z->pai->pai->esq; // y é o tio de z, que é o filho da esquerda do avô de z
            if (cor(y) == VERMELHO) { // O pai e o tio são vermelhos
                mudancasCor += 3; // ======================== Mudança de cor ========================
                z->pai->cor = PRETO; // Pinta o pai de preto
                y->cor = PRETO; // Pinta o tio de preto
                z->pai->pai->cor = VERMELHO; // Pinta o avô de vermelho
                z = z->pai->pai; // z se torna o avô
            } else { // O pai é vermelho e o tio é preto
                if (z == z->pai->esq) { // Se z é um filho da esquerda
                    z = z->pai; // z se torna o pai
                    rotacaoDirRN(raiz, z); // Rotação à direita em z
                    rotacoesAVP++; // Incrementa a quantidade de rotações
                }
                mudancasCor += 2; // ======================== Mudança de cor ========================
                z->pai->cor = PRETO; // Pinta o pai de preto
                z->pai->pai->cor = VERMELHO; // Pinta o avô de vermelho
                rotacaoEsqRN(raiz, z->pai->pai); // Rotação à esquerda no avô
                rotacoesAVP++; // Incrementa a quantidade de rotações
            }
        }
    }
   (*raiz)->cor = PRETO; // Pinta a raiz de preto
}

void inserirRN(PArn *raiz, int info) {
    PArn z = criaFolhaRN(info); // Cria o novo nó z
    PArn y = NULL; // Nó auxiliar y (no futuro, será o pai de z)
    PArn x = *raiz; // Nó auxiliar x (percorre a árvore, começando pela raiz)
    
    while (x != NULL) { // Busca o local correto para inserir o novo nó
        y = x;
        if (z->info < x->info) x = x->esq;
        else x = x->dir;
    }

    z->pai = y; // O pai do novo nó é y
    if (y == NULL) *raiz = z; // Se a árvore for vazia, z se torna a raiz
    else if (z->info < y->info) y->esq = z; // Se z é menor que y, z se torna o filho da esquerda de y
    else y->dir = z; // Se z é maior que y, z se torna o filho da direita de y
    balancearRN(raiz, z); // Balanceia a árvore após a inserção
}

PArn buscaRN (PArn raiz, int info) {
    if (raiz == NULL || raiz->info == info) return raiz; // Se a raiz for nula ou a informação for igual à da raiz, retorna a raiz
    if (info < raiz->info) return buscaRN(raiz->esq, info); // Se a informação for menor que a da raiz, busca na subárvore da esquerda
    return buscaRN(raiz->dir, info); // Se a informação for maior que a da raiz, busca na subárvore da direita
}

int alturaNegra (PArn raiz) {
    int altura = 0; // Inicializa a altura negra como 0
    for (PArn p = raiz; p != NULL;) {
        if (cor(p) == PRETO) altura++; // Se o nó for preto, incrementa a altura negra
        p = p->esq; // Percorre a árvore pela esquerda (não importa o caminho, pois a altura negra é a mesma)
    }
    return altura; // Retorna a altura negra (não contamos o nó nulo, segundo o enunciado)
}

int alturaRN(PArn raiz) {
    if (raiz == NULL) return -1; // Se a árvore for nula, a altura é 0
    int altEsq = alturaRN(raiz->esq); // Altura da subárvore da esquerda
    int altDir = alturaRN(raiz->dir); // Altura da subárvore da direita
    return 1 + max(altEsq, altDir); // Retorna a altura da árvore
}

void liberarRN(PArn raiz) {
    if (raiz != NULL) {
        liberarRN(raiz->esq); // Libera a subárvore da esquerda
        liberarRN(raiz->dir); // Libera a subárvore da direita
        free(raiz); // Libera a raiz
    }
}

// ====================================================================================================================
// ====================================================================================================================
int main() {
    PArn RaizRN = NULL;
    PAvl RaizAVL = NULL;
    int chave;

    scanf("%d", &chave);
    while (chave != -1) {
        inserirRN(&RaizRN, chave);
        RaizAVL = inserirAVL(RaizAVL, chave);
        scanf("%d", &chave);
    }

    // A primeira linha da saída contem a altura máxima da árvore AVL a partir do seu nó raiz seguida da altura da sub-árvore da esquerda e da direita do nó raiz. 
    printf("%d, %d, %d\n", RaizAVL->altura, alturaAVL(RaizAVL->esq) + 1, alturaAVL(RaizAVL->dir) + 1);

    // A segunda linha deve conter a altura máxima da árvore vermelha e preta a partir do seu no raiz, seguida da altura da sub-árvore da esquerda e da direita do nó raiz. 
    printf("%d, %d, %d\n", alturaRN(RaizRN), alturaRN(RaizRN->esq) + 1, alturaRN(RaizRN->dir) + 1);

    // A terceira linha devera conter um único número inteiro: a altura negra da árvore AVP, contada a partir da raiz.
    printf("%d\n", alturaNegra(RaizRN));

    // A ultima linha deverá conter trés números inteiros: a quantidade total de mudanças de cor de nos da AVP, a quantidade total de rotações executadas na AVP e, por fim, a quantidade total de rotações executadas na AVL.
    printf("%d, %d, %d\n", mudancasCor, rotacoesAVP, rotacoesAVL);
    
    liberarAVL(RaizAVL);
    liberarRN(RaizRN);
    return 0;
}

