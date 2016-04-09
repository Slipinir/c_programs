#include <stdio.h>
#include <stdlib.h>
#include "arvore_estatica.h"

void criar(Arvore arvore) {
    int i;
    for (i = 0; i < MAX; i++) {
        arvore[i].info = VAZIA;
        arvore[i].esq = arvore[i].dir = VAZIO;
    }
}

void mostrar_pre_ordem(Arvore arvore, int i) {
    if (arvore[i].info != VAZIA) {
        printf("%c", arvore[i].info);
        mostrar(arvore, arvore[i].esq);
        mostrar(arvore, arvore[i].dir);
    }
}

int vazia(Arvore arvore) {
    return arvore[0].info != VAZIA;
}

void adicionar(Arvore arvore, char info) {
    
}
