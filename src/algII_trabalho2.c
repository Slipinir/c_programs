/*
    Feito no linux, distribuição Arch Linux, com o compilador gcc 5.2.0.
    Utiliza algumas funcoes do OS Linux/ GNU (ou somente Linux).

    Não utiliza as setas e não captura o botão F1 porque para captura-lo é
    necessário utilizar bibliotecas especifícas do Sistema e do terminal.

    Feito por Luiz Carlos Mendonça Jr. RA 151025282.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>

#define NOME_SIZE  100
#define PASTA_SIZE 100

#define OPCAO_CADASTRO_PESSOA     1
#define OPCAO_MANIPULACAO_ARQUIVO 2

#define ALTERAR_PASTA           1
#define MOSTRAR_ARQUIVOS_PASTA  2
#define RENOMEAR_ARQUIVO        3
#define REMOVER_ARQUIVO         4
#define CRIAR_PASTA             5
#define RENOMEAR_PASTA          6
#define MOVER_ARQUIVO           7

#define OPCAO_CADASTRAR 1
#define OPCAO_ALTERAR   2
#define OPCAO_EXCLUIR   3
#define OPCAO_CONSULTAR 4

#define CONSULTAR_TODOS 1
#define CONSULTAR_NOME  2
#define CONSULTAR_IDADE 3
    
#define EXCLUIR_LOGICA  1
#define EXCLUIR_FISICA  2

#define OPCAO_CANCELAR  0

typedef struct {
	
	char nome[NOME_SIZE];
	int idade;
	float altura;
	float peso;
	char genero;
    int excluida;
} Pessoa;

void gotoxy(int x, int y);
char getch();
void menu();
void mostrarPessoa(Pessoa pessoa);
void limparPessoa(Pessoa * pessoa);
char receberResposta(char * pergunta);
void receberPessoa(Pessoa * pessoa);
void apresentarEscolhas();
void apresentarCadastroPessoasEscolhas();
void cadastroPessoas();
int receberOpcao(int intervaloMinimo, int intervaloMaximo);
int criarPessoaCodigo();
void cadastrarPessoa();
void apresentarConsultarPessoasOpcoes();
void consultarPessoaTodos();
void consultarPessoaPorNome();
void consultarPessoaPorIdade();
void consultarPessoa();
void alterarPessoa();
void excluirPessoa();
void apresentarExcluirPessoasOpcoes();
void apresentarManipulacaoArquivosEscolhas();
void manipulacaoArquivos();
int pastaExiste(char * pasta); 
void alterarPasta();
void mostrarArquivos();
void diretorioAtual(char * diretorio);
void renomearArquivo();
int arquivoExiste(char * arquivo);
void removerArquivo();
void criarPasta();
void renomearPasta();
void moverArquivo();

// Fazer parte das setas por último!
// Não considera pessoas com mesmo nome ou idade

int main() {

    int tecla;
    do {

        fflush(stdin);
        tecla = getch();
        printf("Tecla pressionada: %d", tecla);
    } while (1);
    menu();
}

void menu() {

    int opcao;
    do {

        system("clear");
        apresentarEscolhas();
        opcao = receberOpcao(OPCAO_CANCELAR, OPCAO_MANIPULACAO_ARQUIVO);

        switch (opcao) {

            case OPCAO_CADASTRO_PESSOA: cadastroPessoas(); break;
            case OPCAO_MANIPULACAO_ARQUIVO: manipulacaoArquivos(); break;
        }
    } while (opcao != OPCAO_CANCELAR);
}

void mostrarArquivos() {

    char diretorio[PASTA_SIZE];
    diretorioAtual(diretorio);
        
    printf("Arquivos na pasta atual %s:\n", diretorio);

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (diretorio)) != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            // Não quero arquivos temporários
            if (ent->d_name[0] != '.') {

                printf("%s\n", ent->d_name);
            }
        }

        closedir (dir);
    } else {

        printf("\nProblema com o diretorio\n");
    }
}

void renomearArquivo() {

    char resposta = '\0';
    do {

        printf("\n");
        printf("Renomear Arquivo:\n");
        printf("Arquivo a ser renomeado: ");
        char arquivo[PASTA_SIZE];
        fflush(stdin);
        scanf("%s", arquivo);

        if (arquivoExiste(arquivo)) {

            printf("Novo nome do arquivo: ");
            char novoNomeArquivo[PASTA_SIZE];
            fflush(stdin);
            scanf("%s", novoNomeArquivo);

            if (!arquivoExiste(novoNomeArquivo)) {
            
                rename(arquivo, novoNomeArquivo);
            } else {

                printf("Arquivo %s ja existe\n", novoNomeArquivo);
            }
        } else {

            printf("Arquivo nao Existe\n");
        }

        resposta = receberResposta("Deseja renomear outro arquivo (S/s/N/n)? ");
    } while (toupper(resposta) != 'N');
}

void criarPasta() {

    char resposta = '\0';
    do {

        printf("\n");
        printf("Criar Pasta:\n");
        printf("Nome da pasta a ser criada: ");
        char pasta[PASTA_SIZE];
        fflush(stdin);
        scanf("%s", pasta);

        if (!pastaExiste(pasta)) {

            if (!mkdir(pasta, S_IRWXU)) {

                printf("Pasta criada com sucesso!\n");
            } else {
                
                printf("Falha na criacao da pasta %s\n", pasta);
            }
        } else {

            printf("Pasta ja existe\n");
        }

        resposta = receberResposta("Deseja criar outra pasta (S/s/N/n)? ");
    } while (toupper(resposta) != 'N');
}

void renomearPasta() {

    char resposta = '\0';
    do {

        printf("\n");
        printf("Renomear Pasta:\n");
        printf("Pasta a ser renomeada: ");
        char pasta[PASTA_SIZE];
        fflush(stdin);
        scanf("%s", pasta);

        if (pastaExiste(pasta)) {

            printf("Novo nome da pasta %s: ", pasta);
            char novoNomePasta[PASTA_SIZE];
            fflush(stdin);
            scanf("%s", novoNomePasta);

            if (!arquivoExiste(novoNomePasta)) {
            
                if (!rename(pasta, novoNomePasta)) {

                    printf("Renomeacao da pasta realizado com sucesso!\n");
                } else {

                    printf("Falha na renomeacao da pasta %s para %s!\n", pasta, novoNomePasta);
                }
            } else {

                printf("Pasta %s ja existe\n", novoNomePasta);
            }
        } else {

            printf("Pasta nao Existe\n");
        }

        resposta = receberResposta("Deseja renomear outra pasta (S/s/N/n)? ");
    } while (toupper(resposta) != 'N');
}

void removerArquivo() {

    char resposta = '\0';
    do {

        printf("\n");
        printf("Remover Arquivo:\n");
        printf("Arquivo a ser removido: ");
        char arquivo[PASTA_SIZE];
        fflush(stdin);
        scanf("%s", arquivo);

        if (arquivoExiste(arquivo)) {

            if (!remove(arquivo)) {

                printf("Arquivo removido com sucesso!\n");
            } else {

                printf("Falha na remocao do arquivo %s", arquivo);
            }
        } else {

            printf("Arquivo nao Existe\n");
        }

        resposta = receberResposta("Deseja remover outro arquivo (S/s/N/n)? ");
    } while (toupper(resposta) != 'N');
}

void apresentarEscolhas() {

    printf("Trabalho de Algoritmo 2\n");
    printf("( ) Cadastro de Pessoas\n");
    printf("( ) Manipulacao de Arquivos\n");
    printf("( ) Fechar programa\n");
}

void apresentarManipulacaoArquivosEscolhas() {

    printf("Manipulacao de Arquivos\n");
    printf("( ) Alterar pasta\n");
    printf("( ) Mostrar arquivos no diretorio\n");
    printf("( ) Renomear arquivo\n");
    printf("( ) Remover arquivo\n");
    printf("( ) Criar pasta\n");
    printf("( ) Renomear pasta\n");
    printf("( ) Mover arquivo\n");
    printf("( ) Fechar manipulacao de arquivo\n");
}

void manipulacaoArquivos() {

    int opcao;
    do {

        system("clear");
        apresentarManipulacaoArquivosEscolhas();
        opcao = receberOpcao(OPCAO_CANCELAR, MOVER_ARQUIVO);

        switch (opcao) {
            
            case ALTERAR_PASTA: alterarPasta(); break; 
            case MOSTRAR_ARQUIVOS_PASTA: mostrarArquivos(); break;
            case RENOMEAR_ARQUIVO: renomearArquivo(); break;
            case REMOVER_ARQUIVO: removerArquivo(); break;
            case CRIAR_PASTA: criarPasta(); break;
            case RENOMEAR_PASTA: renomearPasta(); break;
            case MOVER_ARQUIVO: moverArquivo(); break;
        }
    } while (opcao != OPCAO_CANCELAR);

}

void moverArquivo() {

   printf("\n");
   printf("Mover Arquivo:\n");
   
   char resposta = '\0';
   do {

        printf("Arquivo a ser movido: ");
        char arquivo[PASTA_SIZE];
        fflush(stdin);
        scanf("%s", arquivo);

        if (arquivoExiste(arquivo)) {

            printf("Nome da pasta destino: ");
            char pastaDestino[PASTA_SIZE];
            fflush(stdin);
            scanf("%s", pastaDestino);

            if (pastaExiste(pastaDestino)) {
                
                strcat(pastaDestino, "/");
                strcat(pastaDestino, arquivo);
                
                if (!rename(arquivo, pastaDestino)) {

                    printf("Arquivo movido com sucesso!\n");
                } else {

                    printf("Falha na movimentacao!\n");
                }
            } else {

                printf("Pasta destino nao existe!\n");
            }
        } else {
        
            printf("Arquivo nao existe!\n");
        }

    resposta = receberResposta("Deseja mover outro arquivo (S/s/N/n)? ");
    } while (toupper(resposta) != 'N');
}

void alterarPasta() {

    char resposta = '\0';
    do {
        printf("\n");
        printf("Digite a pasta de destino (../ = anterior a atual): ");
        char pasta[PASTA_SIZE];
        fflush(stdin);
        scanf("%s", pasta);

        if (pastaExiste(pasta)) {
    
            chdir(pasta);
            printf("Pasta alterada com sucesso!\n");

            char diretorio[PASTA_SIZE];
            diretorioAtual(diretorio);
            printf("Voce esta agora em: %s\n", diretorio);
        } else {

            char pastaNaoExiste[PASTA_SIZE];
            diretorioAtual(pastaNaoExiste);
            strcat(pastaNaoExiste, "/");
            strcat(pastaNaoExiste, pasta);
            printf("Pasta %s nao existe\n", pastaNaoExiste);
        }
        
        resposta = receberResposta("Deseja alterar outra pasta (S/s/N/n)? ");
    } while (toupper(resposta) != 'N');
}

void cadastroPessoas() {

	int opcao;
	do {

        system("clear");
		apresentarCadastroPessoasEscolhas();
		opcao = receberOpcao(OPCAO_CANCELAR, OPCAO_CONSULTAR);
		switch (opcao) {
			case OPCAO_CADASTRAR:
                cadastrarPessoa();
				break;
			case OPCAO_ALTERAR:
				alterarPessoa();
				break;
			case OPCAO_EXCLUIR:
                excluirPessoa();
				break;
			case OPCAO_CONSULTAR:
				consultarPessoa();
                break;
		}
	} while(opcao != OPCAO_CANCELAR);
}

void alterarPessoa() {

    FILE * file;
    file = fopen("pessoas.dat", "rb");

    if (file != NULL) {

        fclose(file);
        file = fopen("pessoas.dat", "r+b");

        printf("\nNome: ");
        char nome[NOME_SIZE];
        fflush(stdin);
        scanf("%s", nome);

        int encontrouPessoa = 0;
        Pessoa pessoa;
        fread(&pessoa, sizeof(Pessoa), 1, file);
        do {

            encontrouPessoa = strcmp(pessoa.nome, nome) == 0 && !pessoa.excluida;
            if (encontrouPessoa) {
            
                mostrarPessoa(pessoa);
                receberPessoa(&pessoa);
                rewind(file);
                fwrite(&pessoa, sizeof(Pessoa), 1, file);
            }

            fread(&pessoa, sizeof(Pessoa), 1, file);
        } while (!feof(file) && !encontrouPessoa);

        if (!encontrouPessoa) {

            printf("\nPessoa de nome \"%s\" nao encontrada\n", nome);
        }

        fclose(file);
    } else {

        printf("\nNao ha pessoas cadastradas!\n");
    }
}

void mostrarPessoa(Pessoa pessoa) {
	
	printf("Pessoa cadastrada:\n");
	printf("Nome: %s\n", pessoa.nome);
	printf("Idade: %d\n", pessoa.idade);	
	printf("Altura (m): %.2f\n", pessoa.altura);	
	printf("Peso (kg): %.2f\n", pessoa.peso);
	printf("Genero: %c\n", pessoa.genero);
}

// Para limpar sujeiras
void limparPessoa(Pessoa * pessoa) {
	
    strcpy(pessoa->nome, "");
	pessoa->idade = 0;
	pessoa->altura = 0;
	pessoa->peso = 0;
	pessoa->genero = '\0';
    pessoa->excluida = 0;
}

char receberResposta(char * pergunta) {

    char resposta = '\0';
    do {

        printf(pergunta);
        scanf(" %c", &resposta);
        resposta = toupper(resposta);

        if (resposta != 'N' && resposta != 'n' && resposta != 'S' && resposta != 's') {
        
            printf("Resposta invalida. Tem de ser 'N', 'n', 'S', ou 's'.\n");
        }
    } while (resposta != 'N' && resposta != 'n' && resposta != 'S' && resposta != 's');

    return resposta;
}

void receberPessoa(Pessoa * pessoa) {
	
    char resposta;
    do {

	    // Para limpar sujeiras
    	limparPessoa(pessoa);

    	printf("\n");
        printf("Cadastro de Pessoa:\n");

	    printf("Nome: ");
        fflush(stdin);
        scanf("%s", (pessoa->nome));
	    
	    printf("Idade: ");
	    scanf("%d", &(pessoa->idade));
	    
	    printf("Altura (m): ");
	    scanf("%f", &(pessoa->altura));
	    
	    printf("Peso (kg): ");
	    scanf("%f", &(pessoa->peso));
	    
	    do {
	        
            printf("Genero (M/F/m/f): ");
	    	scanf(" %c", &(pessoa->genero));
	    	pessoa->genero = toupper(pessoa->genero);
	    	
	    	if (toupper(pessoa->genero) != 'M' && toupper(pessoa->genero) != 'F') {
	    		printf("Genero invalido. Tem de ser 'M', 'F', 'm', ou 'f'.\n");
	    	}
	    } while (toupper(pessoa->genero) != 'M' && toupper(pessoa->genero) != 'F');

        pessoa->excluida = 0;

        resposta = receberResposta("Os dados estao corretos (S/s/N/n)? ");
    } while (resposta != 'S');
        
    printf("\n");

    mostrarPessoa(*pessoa);
}

void apresentarCadastroPessoasEscolhas() {

	printf("Sistema de CP (Controle de Pessoas):\n");
	printf("%d) Cadastrar\n", OPCAO_CADASTRAR);
	printf("%d) Alterar\n", OPCAO_ALTERAR);
	printf("%d) Excluir\n", OPCAO_EXCLUIR);
	printf("%d) Consultar\n", OPCAO_CONSULTAR);
	printf("%d) Fechar CP\n", OPCAO_CANCELAR);
}

int receberOpcao(int intervaloMinimo, int intervaloMaximo) {

    int opcao = intervaloMinimo + 1;
    char teclaPressionada = '\0';
    do {

        do {

        } while (teclaPressionada != 1);
        gotoxy(2,1 + opcao);
    } while (opcao < intervaloMinimo || opcao > intervaloMaximo);
}

int receberOpcaoDigitada(int intervaloMinimo, int intervaloMaximo) {

	int opcao;
	do {

		printf("Opcao desejada: ");
		scanf("%d", &opcao);
		
		if (opcao < intervaloMinimo || opcao > intervaloMaximo) {

			printf("Opcao invalida. Por favor, escolha uma valida.\n");
		}
	} while(opcao < intervaloMinimo || opcao > intervaloMaximo);
	
	return opcao;
}

void cadastrarPessoa() {

    FILE * file;
    file = fopen("pessoas.dat", "a+b");
	Pessoa pessoa;
    char resposta = '\0';
    do {

	    receberPessoa(&pessoa);
        fwrite(&pessoa, sizeof(Pessoa), 1, file);

        resposta = receberResposta("Deseja cadastrar mais uma pessoa(S/s/N/n)? ");
    } while (toupper(resposta) != 'N');
    
    fclose(file);
}

void apresentarConsultarPessoasOpcoes() {

    printf("\n");
    printf("Opcoes:\n");
    printf("%d) Todos\n", CONSULTAR_TODOS);
    printf("%d) Por nome\n", CONSULTAR_NOME);
    printf("%d) Por idade\n", CONSULTAR_IDADE);
    printf("%d) Cancelar\n", OPCAO_CANCELAR);
    printf("\n");
}

void consultarPessoaTodos() {

    FILE * file;
    file = fopen("pessoas.dat", "rb");

    if (file != NULL) {

        char resposta = '\0';
        Pessoa pessoa;
        fread(&pessoa, sizeof(Pessoa), 1, file);
        int pessoaExcluida = 0;
        do {

            pessoaExcluida = pessoa.excluida;
            if (!pessoaExcluida) {

                mostrarPessoa(pessoa);
            }
            fread(&pessoa, sizeof(Pessoa), 1, file);

            if (!feof(file) && !pessoaExcluida) {

                resposta = receberResposta("Continuar (S/s/N/n)? ");
                printf("\n");
            }
        } while (!feof(file) && resposta != 'N');

        fclose(file);
    } else {

        printf("\nNao ha pessoas cadastradas!\n");
    }
}

void consultarPessoaPorNome() {

    printf("\n");
    printf("Consulta por nome:\n");

    FILE * file;
    file = fopen("pessoas.dat", "rb");

    if (file != NULL) {

        char resposta;
        Pessoa pessoa;
        do {

            fseek(file, sizeof(Pessoa), SEEK_SET);
            rewind(file);

            printf("Nome: ");
            char nome[NOME_SIZE];
            fflush(stdin);
            scanf("%s", nome);
            printf("\n");

            int pessoaEncontrada = 0;
            do {
                
                fread(&pessoa, sizeof(Pessoa), 1, file);
                pessoaEncontrada = strcmp(pessoa.nome, nome) == 0 && !pessoa.excluida;
            } while (!feof(file) && !pessoaEncontrada);

            if (pessoaEncontrada) {

                mostrarPessoa(pessoa);
            } else {
    
                printf("Pessoa de nome \"%s\" nao encontrada\n", nome);
            }

            resposta = receberResposta("Deseja realizar outra consulta por nome (S/s/N/n)? ");
            getchar();
        } while (toupper(resposta) != 'N');
        
        fclose(file);
    } else {

        printf("\nNao ha pessoas cadastradas!\n");
    }
}

void consultarPessoaPorIdade() {

    printf("\n");
    printf("Consultar por idade: \n");

    FILE * file;
    file = fopen("pessoas.dat", "rb");

    if (file !=  NULL) {

        Pessoa pessoa;
        char resposta = '\0';
        do {

            fseek(file, sizeof(Pessoa), SEEK_SET);

            printf("Idade: ");
            int idade;
            scanf("%d", &idade);
            printf("\n");

            int pessoaEncontrada = 0;
            do {

                fread(&pessoa, sizeof(Pessoa), 1, file);
                pessoaEncontrada = pessoa.idade == idade && !pessoa.excluida;
            } while (!feof(file) && !pessoaEncontrada);

            if (pessoaEncontrada) {
            
                mostrarPessoa(pessoa);
            } else {
            
                printf("Pessoa com idade \"%d\" nao encontrada\n\n", idade);
            }

            resposta = receberResposta("Deseja realizar outra consulta por idade (S/s/N/n)? ");
        } while (toupper(resposta) != 'N');

        fclose(file);
    } else {

        printf("\nNao ha pessoas cadastradas!\n");
    }
}

void consultarPessoa() {

    FILE * file;
    file = fopen("pessoas.dat", "rb");

    if (file != NULL) {

        char resposta;
        int opcao;

        do {

            apresentarConsultarPessoasOpcoes();
            opcao = receberOpcao(OPCAO_CANCELAR, CONSULTAR_IDADE);
            getchar();

            if (opcao == OPCAO_CANCELAR) {

                break;
            }

            switch (opcao) {

                case CONSULTAR_TODOS: consultarPessoaTodos(); break;
                case CONSULTAR_NOME:  consultarPessoaPorNome(); break;
                case CONSULTAR_IDADE: consultarPessoaPorIdade(); break;
            }

           resposta = receberResposta("Deseja realizar uma nova consulta (S/s/N/n)? ");
       } while (resposta != 'N');
    } else {

        printf("\nNao ha pessoas cadastradas!\n");
    }
}

void apresentarExcluirPessoasOpcoes() {

    printf("\n");
    printf("Opcoes:\n");
    printf("%d) Exclusao logica\n", EXCLUIR_LOGICA);
    printf("%d) Exclusao fisica\n", EXCLUIR_FISICA);
    printf("%d) Cancelar\n", OPCAO_CANCELAR);
    printf("\n");
}

void excluirPessoaLogicamente() {

    FILE * file;
    file = fopen("pessoas.dat", "r+b");
    if (file != NULL) {

        printf("\nNome: ");
        char nome[NOME_SIZE];
        fflush(stdin);
        scanf("%s", nome);

        int encontrouPessoa = 0;
        Pessoa pessoa;
        fread(&pessoa, sizeof(Pessoa), 1, file);
        do {

            encontrouPessoa = strcmp(pessoa.nome, nome) == 0 && !pessoa.excluida;
            if (encontrouPessoa) {
            
                mostrarPessoa(pessoa);

                char querExcluir = '\0';
                querExcluir = receberResposta("Deseja excluir esta pessoa (S/s/N/n)? ");

                if (toupper(querExcluir) == 'S') {

                    pessoa.excluida = 1;
                    rewind(file);
                    fwrite(&pessoa, sizeof(Pessoa), 1, file);
                }
            }

            fread(&pessoa, sizeof(Pessoa), 1, file);
        } while (!feof(file) && !encontrouPessoa);

        if (!encontrouPessoa) {

            printf("\nPessoa de nome \"%s\" nao encontrada\n\n", nome);
        }

        fclose(file);
    } else {

        printf("\nNao ha pessoas cadastradas!\n");
    }
}

void excluirPessoa() {

    FILE * file;
    file = fopen("pessoas.dat", "rb");

    if (file != NULL) {

        fclose(file);

        char resposta;
        int opcao;
        do {

            printf("\n");
            printf("Excluir pessoa:\n");
            apresentarExcluirPessoasOpcoes();
            opcao = receberOpcao(OPCAO_CANCELAR, EXCLUIR_FISICA);
            getchar();

            if (opcao == OPCAO_CANCELAR) {
            
                break;
            }

            switch (opcao) {
            
                case EXCLUIR_LOGICA: excluirPessoaLogicamente(); break;
                case EXCLUIR_FISICA: printf("Excluir Fisica"); break;
            }

            resposta = receberResposta("Deseja excluir outra pessoa (S/s/N/n)? ");
        } while (toupper(resposta) != 'N');
    } else {

        printf("\nNao ha pessoas cadastradas!\n");
    }
}

int pastaExiste(char * pasta) {

    struct stat info;
    char caminho[PASTA_SIZE];
    diretorioAtual(caminho);
    strcat(caminho, pasta);
    return stat(pasta, &info) == 0 && info.st_mode & S_IFDIR;
}

int arquivoExiste(char * arquivo) {

    struct stat info;
    return (stat(arquivo, &info) == 0);
}

void diretorioAtual(char * diretorio) {

    char dir[PASTA_SIZE];

    getcwd(dir, sizeof(dir));
    strcpy(diretorio, dir);
}

void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1B,y,x);
}

char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
}
