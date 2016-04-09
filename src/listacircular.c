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
void addBegin(no *lista, int info);
void remove(no *lista, int info);

void appendTest(no *lista);
void addBeginTest(no *lista);
void appendAddBeginTest(no *lista);

int main() {

    no lista;
    create(&lista);

    printf("Itens: ");
//    appendTest(&lista);
//    addBeginTest(&lista);
    appendAddBeginTest(&lista);
    showAll(lista);
}

void create(no *lista) {

    *lista = NULL;
}

void append(no *lista, int info) {

    no p = (no) malloc(sizeof(struct reg));
    p->info = info;

    if (!*lista) {

        *lista = p;
        p->prox = p;
    } else {
        
        no q = *lista;

        if (q->prox != q) {

            while (q->prox != *lista) {

                q = q->prox;
            }
        }

        q->prox = p;
        p->prox = *lista;
    }
}

void showAll(no lista) {

    no p = lista;

    do {

        printf("%d ", p->info);
        p = p->prox;
    } while (p && p != lista);
    printf("\n");
}

void addBegin(no *lista, int info) {

    if (!*lista) {

        append(lista, info);
    } else {

        no p = (no) malloc(sizeof(struct reg));
        p->info = info;

        p->prox = *lista;
        if ((*lista)->prox == *lista) {

            (*lista)->prox = p;
        } else {

            no q = *lista;
            do {
                
                q = q->prox;
            } while (q->prox != *lista);
            q->prox = p;
        }
        *lista = p;
    }
}

void remove(no *lista, int info) {

    if (*lista) {

        if ((*lista)->info == info) {

            if ((*lista)->prox == *lista) {

                free(*lista);
                create(lista);
            } else {

                no p = *lista;
                no q = p;

                do {

                    p = p->prox//at;
                } while (p->prox != *lista);
        } else {

            no p = *lista;
            no q = p;

            do {
                
                if (p->info == info) {

                    q = p->prox;

            } while (p->prox != *lista);
        }
    }
}

void appendTest(no *lista) {

    append(lista, 10);
    append(lista, 11);
    append(lista, 12);
    append(lista, 13);
    append(lista, 14);
}

void addBeginTest(no *lista) {

    addBegin(lista, 9);
    addBegin(lista, 10);
    addBegin(lista, 11);
    addBegin(lista, 12);
    addBegin(lista, 15);
}

void appendAddBeginTest(no *lista) {

    append(lista, 9);
    addBegin(lista, 10);
    append(lista, 11);
}
