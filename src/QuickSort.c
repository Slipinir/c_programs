#include <stdio.h>
#include <conio.h>
//--------------------------------------
void imprimeVetor (int n, int v[]) {
  int i;
  printf ("vetor: ");
  for (i = 0; i < n; i++)
    printf ("%d  ",v[i]);
  printf ("\n\n");
}
//--------------------------------------
int quickSort (int inicio, int fim, int *v) {
  int i, j, pivo, aux;
  i = inicio;
  j = fim;
  pivo = v[(inicio + fim) / 2];
  while (i < j) {
    while (v[i] < pivo)
      i++;
    while (v[j] > pivo)
      j--;
    if (i <= j) {
      aux = v[i];
      v[i] = v[j];
      v[j]= aux;
      i++;
      j--;
    }
  }
  if (j > inicio)
    quickSort (inicio,j,v);
  if (i < fim)
    quickSort (i,fim,v);
}
//--------------------------------------
int main (){
  int vetor[] = {12, 5, 9, 1, 4, 3, 13, 0, 8, 10, 11, 14, 2, 7, 6, 15};
  int n = 16;
  imprimeVetor (n,vetor);
  quickSort (0,n-1,vetor);    
  imprimeVetor (n,vetor);
  getch();    
}    
//--------------------------------------
