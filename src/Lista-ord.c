#include <stdlib.h>

typedef struct reg *no;
struct reg {
           int info;
           struct reg *prox;
};

//------------------------------------------------------   
// Cria uma lista vazia
//------------------------------------------------------
void cria_lista (no *lista) {
  *lista = NULL;
} 
//------------------------------------------------------
// Mostra os elementos da lista
//------------------------------------------------------
void mostra_lista (no lista) {
  no p = lista;
  printf ("\n\nElementos da lista: ");
  while (p) {  // while (p != NULL)
    printf ("%d ",p->info);
    p = p->prox;
  }
}
//------------------------------------------------------
// Inclui um elemento numa lista ordenada
//------------------------------------------------------
void inclui_ordenada (no *lista, int info){
  // criacao do no
  no p = (no) malloc(sizeof(struct reg));
  p->info = info;
  // se lista for vazia ou elemento menor que o primeiro elemento da lista
  if (*lista == NULL || info <= (*lista)->info){
    p->prox = *lista;
    *lista = p;
  }     
  else {
    no q = *lista, r;
    while (q != NULL && q->info < info){
      r = q;
      q = q->prox;
    }      
    p->prox = q; 
    r->prox = p;
  } 
}
//------------------------------------------------------
// Remove um elemento de uma lista 
//------------------------------------------------------
int remove_elem (no *lista, int elem) {
  if (!*lista)
    return 0;
  // elem eh o primeiro elemento da lista
  if (elem == (*lista)->info) {
    no q = *lista;
    *lista = (*lista)->prox;
    free (q);
    return 1;
  }
  no q = *lista, r;
  while (q != NULL && q->info != elem) {
    r = q;        
    q = q->prox;
  }  
  if (!q)
    return 0;
  r->prox = q->prox;
  free (q);
  return 1;
}
//------------------------------------------------------
// Remove um elemento de uma lista ordenada
//------------------------------------------------------
int remove_elem_ord (no *lista, int elem) {
  if (!*lista)
    return 0;
  if (elem == (*lista)->info) {
    no q = *lista;
    *lista = (*lista)->prox;
    free (q);
    return 1;
  }
  no q = *lista, r;
  while (q != NULL && q->info < elem) {
    r = q;        
    q = q->prox;
  }  
  if (!q || q->info != elem)
    return 0;
  r->prox = q->prox;
  free (q);
  return 1;
}
//------------------------------------------------------
// Programa Principal
//------------------------------------------------------
int main () {
  int info;
  char resp;
  no lista;
  cria_lista (&lista);
  do {
    printf ("\n\nDigite um numero inteiro: ");
    scanf ("%d",&info);
    inclui_ordenada (&lista,info);
    mostra_lista (lista);
    printf ("\n\n\nContinua (S/N)? ");   
    do {
      resp = toupper(getch());
    } while (resp!='N' && resp!='S');
  } while (resp!='N');
  mostra_lista (lista);
  getch();
}      
