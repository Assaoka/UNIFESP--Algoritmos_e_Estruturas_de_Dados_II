#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da lista duplamente encadeada
typedef struct No {
    int info;          // Informação armazenada no nó
    struct No *ant;    // Ponteiro para o nó anterior
    struct No *prox;   // Ponteiro para o próximo nó
} SNo;
typedef SNo *PNo;      // Definição de um tipo de ponteiro para SNo

// Função hash para calcular o índice na tabela
int hash (int chave, int tam) {
    return chave % tam; // Retorna o índice baseado no valor da chave e no tamanho da tabela
}

// Função para buscar um nó com a chave especificada na lista
PNo busca (PNo p, int chave) {
    if (p == NULL || p->info == chave) return p; // Retorna o nó se encontrado ou NULL se não existir
    else return busca(p->prox, chave); // Continua a busca recursivamente no próximo nó
}

// Função para criar um novo nó na lista duplamente encadeada
PNo criaNo (int chave, PNo ant, PNo prox) {
    PNo novo = (PNo)malloc(sizeof(SNo)); // Aloca memória para um novo nó
    *novo = (SNo){chave, ant, prox};     // Inicializa o nó com os valores fornecidos
    return novo;                         // Retorna o ponteiro para o novo nó
}

// Função para inserir um nó na lista
PNo inserir (PNo p, int chave) {
    if (p == NULL) return criaNo(chave, NULL, NULL); // Se a lista estiver vazia (Não teve conflito), cria um novo nó
    else if (p->prox == NULL) p->prox = criaNo(chave, p, NULL); // Insere no final da lista (Teve conflito) 
    else p->prox = inserir(p->prox, chave); // Continua a busca recursiva até encontrar o final da lista
    return p;
}

// Função para remover um nó específico da lista
PNo remover (PNo ini, PNo p) {
    if (p == NULL) { // Se o nó a ser removido não foi encontrado
        printf("Valor nao encontrado\n"); // Imprime mensagem de erro
        return ini; // Retorna o início da lista sem alterações
    }

    if (p->prox != NULL) p->prox->ant = p->ant; // Corrige o ponteiro anterior do próximo nó, se existir
    if (p->ant != NULL) p->ant->prox = p->prox; // Corrige o ponteiro próximo do nó anterior, se existir
    else ini = p->prox; // Se o nó removido era o primeiro, atualiza o início da lista
    free(p); // Libera a memória do nó removido
    return ini; // Retorna o novo início da lista
}

// Função para imprimir os elementos de uma lista encadeada
void imprimir (PNo p) {
    if (p == NULL) return; // Se a lista estiver vazia, retorna sem fazer nada
    else if (p->prox == NULL) printf("%d\n", p->info); // Se for o último elemento, imprime e pula linha
    else printf("%d ", p->info); // Imprime o elemento e continua
    imprimir(p->prox); // Chama recursivamente para o próximo nó
}

// Função para liberar a memória de todos os nós da lista
PNo liberar (PNo p) {
    if (p == NULL) return NULL; // Se a lista estiver vazia, retorna NULL
    liberar(p->prox); // Chama recursivamente para liberar o próximo nó
    free(p); // Libera a memória do nó atual
    return NULL; // Retorna NULL após liberar todos os nós
}

int main () {
    int tam, chave, i; // Declaração de variáveis para o tamanho da tabela, chave e índice
    PNo *tabelaHash = NULL, p; // Declaração de um ponteiro para a tabela hash e um ponteiro auxiliar

    // Linha 1: Leitura do tamanho da tabela hash
    scanf(" %d", &tam);
    tabelaHash = (PNo *)malloc(tam * sizeof(PNo)); // Aloca memória para a tabela hash
    for (i = 0; i < tam; i++) tabelaHash[i] = NULL; // Inicializa todas as listas na tabela como vazias (NULL)

    // Linha 2: Leitura e inserção de chaves na tabela hash
    scanf(" %d", &chave);
    while (chave != -1) { // Continua enquanto a chave não for -1 (indicativo de fim de inserção)
        i = hash(chave, tam); // Calcula o índice da tabela hash para a chave
        tabelaHash[i] = inserir(tabelaHash[i], chave); // Insere a chave na lista correspondente
        scanf(" %d", &chave); // Lê a próxima chave
    }

    // Linha 3: Leitura da chave a ser removida e remoção da tabela hash
    scanf(" %d", &chave);
    i = hash(chave, tam); // Calcula o índice da tabela hash para a chave a ser removida
    p = busca(tabelaHash[i], chave); // Busca o nó com a chave na lista correspondente
    tabelaHash[i] = remover(tabelaHash[i], p); // Remove o nó se encontrado

    // Linha 4: Leitura e impressão da posição indicada na tabela hash
    scanf(" %d", &i);
    printf("[%d] ", i);
    imprimir(tabelaHash[i]); // Imprime a lista correspondente ao índice

    // Liberação da memória de todas as listas na tabela hash
    for (i = 0; i < tam; i++) tabelaHash[i] = liberar(tabelaHash[i]);
    free(tabelaHash); // Libera a memória alocada para a tabela hash
    return 0;
}