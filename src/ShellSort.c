#include <stdio.h>
#include <conio.h>
#define max 50
//--------------------------------------
void imprimeVetor (int n, int v[]) {
  int i;
  printf ("vetor: ");
  for (i = 0; i < n; i++)
    printf ("%d  ",v[i]);
  printf ("\n\n");
}
//--------------------------------------
void shellSort (int n, int v[]) {
  int i , j , valor;
  int gap = 1;
  while(gap < n) 
    gap = 3*gap+1;
  while ( gap > 1) {
    gap /= 3;
    for(i = gap; i < n; i++) {
      valor = v[i];
      j = i - gap;
      while (j >= 0 && valor < v[j]) {
        v[j+gap] = v[j];
        j -= gap;
      }
      v[j+gap] = valor;
    }
  }
}
//--------------------------------------
int main (){
  int vetor[] = {12, 5, 9, 1, 4, 3, 13, 0, 8, 10, 11, 14, 2, 7, 6, 15};
  int n = 16;
  imprimeVetor (n,vetor);
  shellSort (n,vetor);    
  imprimeVetor (n,vetor);
  getch();    
}    
//--------------------------------------
