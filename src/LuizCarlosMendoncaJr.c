#include <stdio.h>
#include <stdlib.h>

typedef struct reg *no;

struct reg {

    int info;
    struct reg *prox;
};

void create(no *lista);
void append(no *lista, int info);
void showAll(no lista);
void removeAllFirstElement(no *lista, int info);
void removeAll(no *lista, int info);
void removeAllOrdered(no *lista, int info);
void showAllTest(no *lista);
void removeAllTest(no *lista);
void removeAllTest1(no *lista);
void removeAllTest2(no *lista);
void removeAllTest3(no *lista);

void removeAllOrderedTest(no *lista);

void showAllTest(no *lista) {

    append(lista, 10);
    append(lista, 20);
    append(lista, 30);
    append(lista, 20);
    append(lista, 30);
    append(lista, 40);
    no p = *lista;
    showAll(p);
}

void removeAllTest(no *lista) {

    append(lista, 10);
    append(lista, 10);
    append(lista, 20);

    no p = *lista;
    showAll(p);

    removeAll(lista, 10);

    p = *lista;
    showAll(p);
}

// Teste para verificar se na remocao de todos
// os primeiros iguais, neste caso, de todos os
// nos, o programa nao da problema
void removeAllTest1(no *lista) {

    append(lista, 10);
    append(lista, 10);

    no p = *lista;
    showAll(p);

    removeAll(lista, 10);

    p = *lista;
    showAll(p);
}

// Teste para verificar se o programa nao
// continuara a percorrer a lista apos
// remover os primeiros itens corretos
void removeAllTest2(no *lista) {

    append(lista, 10);
    append(lista, 20);

    no p = *lista;
    showAll(p);

    removeAll(lista, 10);

    p = *lista;
    showAll(p);
}

// Ultimo teste, remove todos os elementos
// com info igual ao desejado
void removeAllTest3(no *lista) {

    append(lista, 10);
    append(lista, 10);
    append(lista, 20);
    append(lista, 30);
    append(lista, 10);
    append(lista, 10);

    no p = *lista;
    showAll(p);

    removeAll(lista, 10);

    p = *lista;
    showAll(p);
}

// Teste para verificar se o programa
// para de passar os nos da lista
// quando o info verificado eh maior que
// o do noh.
// Por isso foi adicionado o utlimo 10.
void removeAllOrderedTest(no *lista) {

    append(lista, 10);
    append(lista, 10);
    append(lista, 20);
    append(lista, 10);

    no p = *lista;
    showAll(p);

    removeAllOrdered(lista, 10);

    p = *lista;
    showAll(p);
}

int main() {
    
    no lista;
    create(&lista);
//    removeAllTest(&lista);
//    removeAllTest1(&lista);
//    removeAllTest2(&lista);
//    removeAllTest3(&lista);
    removeAllOrderedTest(&lista);
}

void create(no *lista) {

    lista = NULL;
}

void append(no *lista, int info) {

    no q = (no) malloc(sizeof(struct reg));
    q->info = info;
    q->prox = NULL;

    if (!*lista) {

        *lista = q;
    } else {

        no p = *lista;

        while (p->prox) {

            p = p->prox;
        }
        
        p->prox = q;
    }
}

void showAll(no lista) {

    printf("Lista: ");
    while (lista) {

        printf("%d ", lista->info);
        lista = lista->prox;
    }
    printf("\n");
}

void removeAllFirstElement(no *lista, int info) {

    // Remocao do primeiro elemento, caso seu
    // info seja igual ao desejado
    while (*lista && (*lista)->info == info) {

        no p = *lista;
        *lista = (*lista)->prox;
        free(p);
    }
}

void removeAll(no *lista, int info) {

    removeAllFirstElement(lista, info);

    if (*lista) {

        if ((*lista)->prox) {

            no p = *lista;
            no q = p->prox;

            while (q) {

                if (q->info == info) {

                    p->prox = q->prox;
                    free(q);
                    q = p->prox;
                } else {

                    p = q;
                    q = q->prox;
                }
            }
        }
    }
}

void removeAllOrdered(no *lista, int info) {

    removeAllFirstElement(lista, info);

    if (*lista) {

        if ((*lista)->prox) {

            no p = *lista;
            no q = p->prox;

            while (q && q->info < info) {

                if (q->info == info) {

                    p->prox = q->prox;
                    free(q);
                    q = p->prox;
                } else {

                    p = q;
                    q = q->prox;
                }
            }
        }
    }
}
