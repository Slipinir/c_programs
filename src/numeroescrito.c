#include <stdio.h>
#include <string.h>
#include <math.h>

static int const MAX = 10;

typedef char *(*pertence) (char *, int);

char *pertence10 (char *numero, int posicaoComeco) {
	switch (numero[posicaoComeco + 1]) {
		case '1': return "onze";
		case '2': return "doze";
		case '3': return "treze";
		case '4': return "catorze";
		case '5': return "quinze";
		case '6': return "dezesseis";
		case '7': return "dezesete";
		case '8': return "dezoito";
		case '9': return "dezenove";
		default: return "dez";
	}
}

char *pertence100 (char *numero, int posicaoComeco) {
	if ((numero[posicaoComeco + 1] != '0') || (numero[posicaoComeco + 2] != '0')) {
		return "cento";
	} else {
		return "cem";
	}
}

typedef struct {
	char *escrito[9];
	char *ordem;
	char *sufixo;
	//função que retorna o tipo correto se o parâmetro passado for igual a exceção
	int temExecessao;
	int indiceExcessao;
	pertence excessao;
} numerosEscritos;

const numerosEscritos numeros[3] = {
	{{"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove"}, "unidade", "", 0, -1, NULL},
	{{"dez", "vinte", "trinta", "quarenta", "cinquenta", "secenta", "setenta", "oitenta", "noventa"}, "dezena", " e ", 1, 0, &pertence10},
	{{"cem", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seiscentos", "setecentos", "oitocentos", "novecentos"}, "centena", " e ", 1, 0, &pertence100}
};

typedef struct {
	char *nomeSingular;
	char *nomePlural;
	char *sufixo;
} casasGrandes;

// Pode adicionar quantas casas forem necessárias e/ ou possiveis
const casasGrandes casas[5] = {
	{"", "", ""},
	{" mil", " mil", ", "},
	{" milhao", " milhoes", ", "},
	{" bilhao", " bilhoes", ", "}
};

int quantidadeCasasPor3(char *numero) {
	int casas = strlen(numero) / 3;
	int casasRestantes = strlen(numero) % 3;
	if (casasRestantes) {
		casas += (3 - casasRestantes);
	}
	
	return casas;
}

void numeroCom0AEsquerdaPor3(char numero[MAX]) {
	while (strlen(numero) % 3) {
      int i;
		for (i = strlen(numero) + 1; i >= 0; i--) {
         numero[i] = numero[i - 1];
		}
		numero[0] = '0';
	}
}

void primeiraLetraMaiuscula(char *numero) {
	numero[0] = numero[0] - 32;
}

void ftoa(float n, char res[MAX]) {
	sprintf (res, "%.2f", n);  
	printf("%.2f = %s", n, res);
	int i;
	for (i = 0; i <= strlen(res); i++) {
		if (res[i] == '.') {
			res[i] = '0';
      }
   }
   printf("%.2f ftoa %s", n, res);
}

void preencherCheque() {
	printf("\nDigite o valor do cheque: R$ ");
	float numero;
	scanf("%f", &numero);
	
	char numeroEscrito[256];
	strcpy(numeroEscrito, "");
	char numeroTexto[MAX];
	strcpy(numeroTexto, "");
	int numeroInt = (int)(numero + 0.5);
	snprintf(numeroTexto, MAX, "%d", numeroInt);
	numeroCom0AEsquerdaPor3(numeroTexto);
	int i;
	int casa = strlen(numeroTexto);
	int casaGrande = quantidadeCasasPor3(numeroTexto);
	for (i = 0; i <= strlen(numeroTexto) - 1; i++) {
		int j;
		for (j = 0; j <= 8; j++) {
			if (numeroTexto[i] == (char) (j + 1) + '0') {
				int casaIndice = (casa - 1) % 3;
				if ((numeros[casaIndice].temExecessao) && ((numeros[casaIndice].indiceExcessao) == j)) {
					strcat(numeroEscrito, numeros[casaIndice].excessao(numeroTexto, i));
					if ((casaIndice % 3) == 1) {
						i++;
						casa--;
						break;
					}
				} else {
					strcat(numeroEscrito, numeros[casaIndice].escrito[j]);
				}
				strcat(numeroEscrito, numeros[casaIndice].sufixo);
			}
		}
		if ((casa % 3) == 1) {
			if (numeroTexto[strlen(numeroTexto) - casa] == '1') {
				strcat(numeroEscrito, casas[casaGrande - 1].nomeSingular);
			} else {
				strcat(numeroEscrito, casas[casaGrande - 1].nomePlural);
			}
			strcat(numeroEscrito, casas[casaGrande - 1].sufixo);
			casaGrande--;
		}
		casa--;
	}
	primeiraLetraMaiuscula(numeroEscrito);
	if ((int)numero > 1) {
		strcat(numeroEscrito, " Bits");
	} else {
		strcat(numeroEscrito, " Bit");
	}
	int parteDecimal = (long)(((numero - (int) numero) * 100) + 0.5);
	if (parteDecimal > 0) {
		strcat(numeroEscrito, " e ");
		snprintf(numeroTexto, sizeof(parteDecimal), "%d", parteDecimal);
		numeroCom0AEsquerdaPor3(numeroTexto);
		casa = strlen(numeroTexto);
		for (i = 0; i <= strlen(numeroTexto) - 1; i++) {
			int j;
			for (j = 0; j <= 8; j++) {
				if (numeroTexto[i] == (char) (j + 1) + '0') {
					int casaIndice = (casa - 1) % 3;
					if ((numeros[casaIndice].temExecessao) && ((numeros[casaIndice].indiceExcessao) == j)) {
						strcat(numeroEscrito, numeros[casaIndice].excessao(numeroTexto, i));
						if ((casaIndice % 3) == 1) {
							i++;
							casa--;
							break;
						}
					} else {
						strcat(numeroEscrito, numeros[casaIndice].escrito[j]);
					}
					strcat(numeroEscrito, numeros[casaIndice].sufixo);
				}
			}
		casa--;
		}
		if (parteDecimal > 1)
			strcat(numeroEscrito, " CentBits");
		else strcat(numeroEscrito, " CentBit");
	}
	printf("\n%.2f = %s\n", numero, numeroEscrito);
	char c;
	scanf("%c", &c);
}

typedef struct {
	int quantidade;
	float valor;
	char *nome;
	char *tipo;
} bitsStruct;

void saque() {
	bitsStruct tiposBits[11] =
		{
			{0, 100, "cem Bits", "nota"}, {0, 50, "cinquenta Bits", "nota"}, {0, 20, "vinte Bits", "nota"}, {0, 10, "dez Bits", "nota"}, {0, 5, "cinco Bits", "nota"}, {0, 2, "dois Bits", "nota"}, 
			{0, 1, "um Bit", "moeda"}, {0, 0.5, "cinquenta CentBits", "moeda"}, {0, 0.25, "vinte e cinco CentBits", "moeda"}, {0, 0.1, "dez CentBits", "moeda"}, {0, 0.01, "um CentBit", "moeda"}
		};
	float bits;
	do {
		printf("\nDigite o valor a ser sacado B$ ");
		scanf("%f", &bits);
		if (bits < 0.01) {
			printf("\nDigite um valor maior que B$ 0,01");
			getchar();
			getchar();
			
			#ifdef linux
				system("clear");
			#endif
			#ifdef _WIN32
				system("cls");
			#endif
		}
	} while (bits <= 0);
	
	char valorSaque[100];
	int i;
	int primeiroIndice = 0, ultimoIndice = 0;
	float bitsRestantes = bits;
	for (i = 0; i <= 10; i++) {
		while ((bitsRestantes - tiposBits[i].valor) >= 0) {
			if ((primeiroIndice == 0) && (ultimoIndice == 0)) {
				primeiroIndice = i;
				ultimoIndice = i;
			} else {
				if (i != ultimoIndice) {
					ultimoIndice = i;
				}
			}
			bitsRestantes -= tiposBits[i].valor;
			tiposBits[i].quantidade++;
		}
	}
	
	printf("\nValores entregues:");
	for (i = primeiroIndice; i <= ultimoIndice; i++) {
		if (tiposBits[i].quantidade > 0) {
			if (tiposBits[i].quantidade > 1) {
				printf("\n%d %ss de %s", tiposBits[i].quantidade, tiposBits[i].tipo, tiposBits[i].nome);
			} else {
				printf("\n%d %s de %s", tiposBits[i].quantidade, tiposBits[i].tipo, tiposBits[i].nome);
			}
		}
	}
	getchar();
	getchar();
}

int main() {
	int opcao;
	do {
		printf("\nBem vindo ao sistema bancario das ilhas Weblands");
		printf("\nQual operação deseja realizar?");
		printf("\n(1) Saque;");
		printf("\n(2) Preenchimento de cheque;");
		printf("\n(3) Sair");
		
		printf("\nOperacao: ");
		scanf("%d", &opcao);
		if ((opcao != 3) && (opcao != 2) && (opcao != 1)) {
			printf("\nOpcao invalida!");
			getchar();
			getchar();
		}
		
		#ifdef linux
			system("clear");
		#endif
		#ifdef _WIN32
			system("cls");
		#endif
		
		switch (opcao) {
			case 1:
				saque();
				break;
			case 2:
				preencherCheque();
				break;
		}
		#ifdef linux
			system("clear");
		#endif
		#ifdef _WIN32
			system("cls");
		#endif
	} while (opcao != 3);
	printf("\nObrigado por utilizar o sistema bancário da Weblands\n");
	getchar();
	getchar();
}
