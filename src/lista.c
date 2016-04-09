#include <stdio.h>
#include <stdlib.h>

typedef struct reg *no;

struct reg {

    int info;
    struct reg *prox;
};

void create(no *lista);
int append(no *lista, int info);
no last(no lista);
void showAll(no lista);
void show(no lista, int x);
no findElem(no lista, int index);
int removeElem(no *lista, int index);

int main() {
    
    no lista;
    create(&lista);
    append(&lista, 5);
    append(&lista, 10);
    append(&lista, 15);

    removeElem(&lista, 0);
    showAll(lista);

    printf("\n%d", findElem(lista, 2)->info);
}

no findElem(no lista, int index) {

    if (!lista) {

        return NULL;
    }

    int i;
    for (i = 1; i <= index; i++) {

        lista = lista->prox;
    }
    
    return lista;
}

int removeElem(no *lista, int index) {

    if (!*lista)

        return 1;

    int i;
    no p = *lista;
    no q = p;

    printf("re");
    for (i = 1; i <= index; i++) {

        printf("oi");
        q = p;
        p = p->prox;
    }

    q->prox = NULL;
    free(p);
    printf("%d", p->info);
}

void create(no *lista) {

    *lista = NULL;
}

int append(no *lista, int info) {

    no q = (no) malloc(sizeof(struct reg));
    q->info = info;
    q->prox = NULL;

    if (!*lista) {

        *lista = q;
    } else {

        no p = last(*lista);

        p->prox = q;
    }

    return 1;
}

no last(no lista) {

    if (lista) {

        while (lista->prox != NULL) {

            lista = lista->prox;
        }
    }

    return lista;
}

void showAll(no lista) {

    if (!lista) {

        printf("Lista nao tem elementos");
        return;
    }

    printf("Info: ");
    
    while (lista) {

        if (lista->prox) {

            printf("%d ", lista->info);
        } else {
            
            printf("%d", lista->info);
        }

        lista = lista->prox;
    }
}
