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
void mergeSort(int inicio, int fim, int v[]) {
  int i, j, k, meio, vetaux[max];
  
  if (inicio == fim) 
    return;

  // ordenacao recursiva das duas metades
  meio = (inicio+fim) / 2;
  mergeSort (inicio,meio,v);
  mergeSort (meio+1,fim,v);
  
  // intercalacao no vetor temporario t
  i = inicio;
  j = meio + 1;
  k = 0;
  
  while (i<meio+1 || j<fim+1) {
    if (i == meio + 1 ) { // i passou do final da primeira metade, pegar v[j]
      vetaux[k] = v[j];
      j++;
      k++;
    } 
    else {
      if (j == fim+1) { // j passou do final da segunda metade, pegar v[i]
        vetaux[k] = v[i];
        i++;
        k++;
      } 
      else {
        if (v[i] < v[j]) { 
          vetaux[k] = v[i];
          i++;
          k++;
        } 
        else { 
          vetaux[k] = v[j];
          j++;
          k++;
        }
      }
    }
  }
  // copia vetor intercalado para o vetor original
  for (i = inicio; i <= fim; i++) 
    v[i] = vetaux[i-inicio];
}
//--------------------------------------
int main (){
  int vetor[] = {12, 5, 9, 1, 4, 3, 13, 0, 8, 10, 11, 14, 2, 7, 6, 15};
  int n = 16;
  imprimeVetor (n,vetor);
  mergeSort (0,n-1,vetor);    
  imprimeVetor (n,vetor);
  getch();    
}    
//--------------------------------------
