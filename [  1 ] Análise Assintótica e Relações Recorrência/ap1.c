// João Victor Assaoka Ribeiro
// ap01-recursao

#include <stdio.h>
#include <stdlib.h>

int cupons (int n_cupons, int preco_em_cupons) {
    int saldo = n_cupons%preco_em_cupons, comprados = n_cupons/preco_em_cupons;
    if (n_cupons < preco_em_cupons) return 0;
    return comprados + cupons(comprados + saldo, preco_em_cupons);
}

int main () {
    int d, p, v, casos;
    for (scanf(" %d", &casos); casos > 0; casos--) {
        scanf(" %d %d %d", &d, &p, &v);
        printf("%d\n", d/p + cupons(d/p, v)); // Calcula a quantidade comprada com dinheiro (d/p) e soma com a quantidade comprada com cupons
    }
    return 0;
}
