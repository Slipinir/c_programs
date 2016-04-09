#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void pintar(char caracter, int x0, int y0, int x1, int y1) {
	int y;
	for (y = y0; y <= y1; y++) {
		int x;
		for (x = x0; x <= x1; x++) {
			gotoxy(x, y); printf("%c", caracter);
		}
		printf("\n");
	}
}

void pintarQuadrado1(char caracter) {
	pintar(caracter, 2, 2, 7, 11);
	pintar(caracter, 8, 2, 12, 7);
}

void pintarQuadrado2(char caracter) {
	pintar(caracter, 15, 2, 24, 7);
	pintar(caracter, 19, 8, 24, 12);
}

void pintarQuadrado3(char caracter) {
	pintar(caracter, 2, 14, 7, 18);
	pintar(caracter, 2, 19, 11, 24);
}

void pintarQuadrado4(char caracter) {
	pintar(caracter, 19, 14, 24, 18);
	pintar(caracter, 15, 19, 24, 24);
}

void pintarQuadrados(char caracter1, char caracter2, char caracter3, char caracter4) {
	pintarQuadrado1(caracter1);
	pintarQuadrado2(caracter2);
	pintarQuadrado3(caracter3);
	pintarQuadrado4(caracter4);
}

int lengthUnsignedSize(const int array[]) {
  int count = 0;
  while(array[count]) count++;
  return count;
}

int length(int array[]) {
	return sizeof(array) / sizeof(int);
}

int * gerarSequencia(int qtde) {
	srand( (unsigned)time(NULL) );
	int i;
	static int sequencia[10];
	for (i = 1; i <= 10; i++) {
		sequencia[i] = 0;
	}
	for (i = 1; i <= qtde; i++) {
		sequencia[i] = 1 + (rand() % 4);
	}
	return sequencia;
}

void mostrarSequencia(int sequencia[], int tamanho) {
	pintarQuadrados('1', '2', '3', '4');
	sleep(2);
	
	int i;
	for (i = 1; i <= tamanho; i++) {
		if (sequencia[i] == 0) {
			sleep(2);
			break;
		}
		
		int quadrado = sequencia[i];
		switch (quadrado) {
			case 1:
				pintarQuadrado1('*');
				break;
			case 2:
				pintarQuadrado2('*');
				break;
			case 3:
				pintarQuadrado3('*');
				break;
			case 4:
				pintarQuadrado4('*');
				break;
		}
		
		sleep(2);
		
		switch (quadrado) {
			case 1:
				pintarQuadrado1('1');
				break;
			case 2:
				pintarQuadrado2('2');
				break;
			case 3:
				pintarQuadrado3('3');
				break;
			case 4:
				pintarQuadrado4('4');
				break;
		}
	}
}

void pintarQuadro() {
	pintar('#', 1, 1, 80, 1);
	pintar('#', 1, 1, 25, 1);
	//pintar('#', 1, 80, 25, 80);
	//pintar('#', 25, 1, 25, 80);
}

int main() {
	char resp;
	int sequencia[10];
	do {
		pintarQuadro();pintarQuadrado1('1');
		getch();
		memcpy(&sequencia, gerarSequencia(10), sizeof(sequencia));
		mostrarSequencia(sequencia, 10);
		getch();
		
		system("cls");
		pintarQuadro();
		pintarQuadrados('1', '2', '3', '4');
		
		char tecla = getch();
		switch (tecla) {
			case '7':
				pintarQuadrado1('*');
				break;
			case '9':
				pintarQuadrado2('*');
				break;
			case '1':
				pintarQuadrado3('*');
				break;
			case '3':
				pintarQuadrado4('*');
				break;
		}
		sleep(1);
		
		do {
			system("cls");
			printf("Deseja jogar mais uma vez (S/N)? ");
			resp = toupper(getch());
		} while (resp != 'S' && resp != 'N');
	} while(resp != 'N');
	
	getch();
}
