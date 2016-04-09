#include <stdio.h>

char *numero_primo(int numero) {
	int i;
	int eh_primo = 1;
	if (numero == 1) {
		eh_primo = 0;
	} else {	
		for (i = 2; i < numero; i++) {
			if (!(numero % i)) {
				eh_primo = 0;
				break;
			}
		}
	}
	
	if (eh_primo) {
		return "eh";
	} else {
		return "nao eh";
	}
}

int main() {
	int numero;
	
	scanf("%d", &numero);
	printf("O numero %d %s primo", numero, numero_primo(numero));
}
