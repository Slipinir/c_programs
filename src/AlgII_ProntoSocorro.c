#include <stdio.h>
#include <stdlib.h>

#define NOME 100

typedef enum {peRegular, peRuim, pePessimo} pacienteEstado;

typedef enum {moSair, moRecepcionista, moMedico} modoOperacao;

typedef struct {

    int codigo;
    char nome[NOME];
    int idade;
    pacienteEstado estado;
} Paciente;

typedef struct reg *no;

struct reg {

    Paciente paciente;
    struct reg *prox;
};

void recepcionista(no *pacientes, int *ultimoCodigo);
void medico(no *pacientes);
void mostrarPaciente(Paciente paciente);

void create(no *lista);
void append(no *lista, Paciente paciente);
void showAll(no lista);
void removePaciente(no *lista, int codigo);

int main() {

    int pacienteCodigo = 1;
    no pacientes;
    create(&pacientes);

    modoOperacao opcao = moRecepcionista;
    while (opcao != moSair) {

        system("clear");
        printf("Sistema do pronto-socorro \"Deus nos Ajude\"\n");
        printf("Modos de operação:\n");
        printf("1 - Recepcionista;\n");
        printf("2 - Medico;\n");
        printf("0 - Sair\n");

        printf("Modo desejado (0-2): ");
        int modo;
        scanf("%d", &modo);

        opcao = (modoOperacao) modo;

        switch (opcao) {

            case moRecepcionista:
                recepcionista(&pacientes, &pacienteCodigo);
                break;
            case moMedico:
                medico(&pacientes);
                break;
        }
    }
}

void recepcionista(no *pacientes, int *ultimoCodigo) {

    Paciente paciente;

    char repetir = 'S';
    while (repetir == 'S') {

        system("clear");
        printf("Modo recepcionista:\n\n");
        printf("Ficha do paciente:\n");
        printf("Nome: ");
        scanf("%s", &(paciente.nome));
        printf("Idade: ");
        scanf("%d", &(paciente.idade));
        printf("Estados:\n");
        printf("0 - Regular;\n");
        printf("1 - Ruim;\n");
        printf("2 - Pessimo;\n");
        printf("Estado (0-2): ");
        int estado;
        scanf("%d", &estado);
        paciente.estado = (pacienteEstado) estado;

        printf("Confirma Ficha? (S/N) ");
        char confirma;
        scanf(" %c", &confirma);

        if (confirma == 'S') {

            paciente.codigo = *ultimoCodigo;
            *ultimoCodigo = *ultimoCodigo + 1;
            append(pacientes, paciente);
        }

        printf("Cadastrar outro? (S/N) ");
        scanf(" %c", &repetir);
    }
}

void medico(no *pacientes) {

    if (*pacientes) {

        no p;
        create(&p);

        no q = *pacientes;
        while (q) {

            if (q->paciente.estado == pePessimo) {
                
                append(&p, q->paciente);
            }

            q = q->prox;
        }

        q = *pacientes;
        while (q) {

            if (q->paciente.estado == peRuim) {
                
                append(&p, q->paciente);
            }

            q = q->prox;
        }

        q = *pacientes;
        while (q) {

            if (q->paciente.estado == peRegular) {
                
                append(&p, q->paciente);
            }

            q = q->prox;
        }

        char repetir = 'S';
        while (repetir == 'S' && p) {

            system("clear");
            printf("Ficha do paciente:\n");
            mostrarPaciente(p->paciente);
            printf("Paciente atendido? (S/N) ");
            char atendido;
            scanf(" %c", &atendido);

            if (atendido == 'S') {

                removePaciente(pacientes, p->paciente.codigo);
            }

            q = p->prox;
            free(p);
            p = q;

            printf("Atender outro paciente? (S/N) ");
            scanf(" %c", &repetir);
        }

        while (p) {

            q = p->prox;
            free(p);
            p = q;
        }
    }
}

void mostrarPaciente(Paciente paciente) {

    printf("Nome: %s\n", paciente.nome);
    printf("Idade: %d\n", paciente.idade);
    printf("Estado: ");
    switch (paciente.estado) {

        case peRegular:
            printf("0 - Regular");
            break;
        case peRuim:
            printf("1 - Ruim");
            break;
        case pePessimo:
            printf("2 - Pessimo");
            break;
    }
    printf("\n");
}

void create(no *lista) {

    *lista = NULL;
}

void append(no *lista, Paciente paciente) {

    no q = (no) malloc(sizeof(struct reg));
    q->paciente = paciente;
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

    printf("Pacientes: \n");
    while (lista) {

        mostrarPaciente(lista->paciente);
        if (lista->prox) {

            printf("\n");
        }
        lista = lista->prox;
    }
    printf("\n");
}

void removePaciente(no *lista, int codigo) {

    if (*lista && (*lista)->paciente.codigo == codigo) {

        no p = (*lista)->prox;
        free(*lista);
        *lista = p;
    }

    if (*lista) {

        no p = *lista;
        no q = p->prox;

        while (q && codigo <= q->paciente.codigo) {

            if (q->paciente.codigo == codigo) {

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
