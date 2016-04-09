#include <stdio.h>

int ehNumeroPrimo(int numero) {
	int eh_primo = 1;
	
	int i;
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
	
	return eh_primo;
}

void primosSoma(int n, int *nprimo1, int *nprimo2) {
	int i, j;
	
	for (i = 2; i <= n; i++) {
		if (ehNumeroPrimo(i)) {
			*nprimo1 = i;
			
			for (j = 2; j <= n; j++) {
				if (ehNumeroPrimo(j)) {
					*nprimo2 = j;
					
					if (*nprimo1 + *nprimo2 == n) {
						return;
					}
				}
			}
		}
	}
	
	return;
}

int main() {
	int n;
	for (n = 502; n <= 1300; n+=2) {
		int nprimo1 = 0, nprimo2 = 0;
		primosSoma(n, &nprimo1, &nprimo2);
		printf("%d = %d + %d\n", n, nprimo1, nprimo2);
		getch();
	}
	
	getch();
}
