#ifndef ARVORE_ESTATICA_H
#define ARVORE_ESTATICA_H

#include "direcao.h"

#define MAX 7
#define VAZIA '\0'
#define VAZIO -1
#define INICIO 0

typedef struct {
    char info;
    int esq, dir;
} No;

typedef No Arvore[MAX];

void criar(Arvore arvore);
void mostrar_pre_ordem(Arvore arvore, int i);
void mostrar_pos_ordem(Arvore arvore, int i);
void mostrar_in_ordem(Arvore arvore, int i);
int vazia(Arvore arvore);
void adicionar(Arvore arvore, char info, Direcao direcao);

#endif
