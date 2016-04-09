#include <stdlib.h>

typedef struct reg *no;
struct reg {
           int info;
           struct reg *prox;
};
//----------------------------------------------------   
// Cria uma lista vazia
//----------------------------------------------------
void cria_LCSE (no *lista) {
  *lista = NULL;
} 
//----------------------------------------------------
// Mostra os elementos da lista circular
//----------------------------------------------------
void mostra_LCSE (no lista) {
  if (lista == NULL) {
    printf ("\nLista vazia");
    return;
  }
  no p = lista;
  printf ("\nElementos da lista: ");
  do {
    printf ("%d ",p->info);
    p = p->prox;
  } while (p != lista);
}
//----------------------------------------------------
// Inclui um elemento no inicio da lista circular
//----------------------------------------------------
void inclui_inicio_LCSE (no *lista, int info) {
  no p = (no) malloc(sizeof(struct reg));
  p->info = info;
  if (!*lista) {
    p->prox = p;
    *lista = p;
  }
  else {
    no q = *lista;
    while (q->prox != *lista)
      q = q->prox;
    q->prox = p;
    p->prox = *lista;
    *lista = p;
  }
}
//----------------------------------------------------
// Inclui um elemento no final da lista circular
//----------------------------------------------------
void inclui_final_LCSE (no *lista, int info) {
  no p = (no) malloc(sizeof(struct reg));
  p->info = info;
  if (!*lista) {
    p->prox = p;
    *lista = p;
  }
  else {
    no q = *lista;
    while (q->prox != *lista)
      q = q->prox;
    q->prox = p;
    p->prox = *lista;
  }
}
//------------------------------------------------------
// Inclui um elemento numa lista ordenada
//------------------------------------------------------
void inclui_ordenada_LCSE (no *lista, int info){
  // criacao do no
  no p = (no) malloc(sizeof(struct reg));
  p->info = info;
  // se lista for vazia
  if (*lista == NULL) { 
    p->prox = p;
    *lista = p;
  }     
  else 
    // se o elemento menor que o primeiro elemento da lista
    if (info <= (*lista)->info){
      // posiciona q no final da lista       
      no q = *lista;
      while (q->prox != *lista)
        q = q->prox;
      // ligacoes necessarias para a inclusao  
      q->prox = p;
      p->prox = *lista;
      *lista = p;
    }
    // elemento sera incluido no meio ou final da lista
    else {
      no q = *lista, r;
      do {
        r = q;
        q = q->prox;
      } while (q != *lista && q->info < info); 
      p->prox = q; 
      r->prox = p;                
    } 
}
//------------------------------------------------------
// Remove todas ocorrências de um determinado elemento de uma lista circular
//------------------------------------------------------
int remove_todos_LCSE (no *lista, int elem) {
  int flag = 0;
  // se lista vazia  
  if (!*lista)
    return flag;
  // se o elemento a ser removido eh o primeiro da lista  
  while (*lista && elem == (*lista)->info) {
    no p = *lista;
    if (*lista == (*lista)->prox){
      *lista = NULL;
      free(p);
      return 1;
    }  
    else {
      no q = *lista;
      while (q->prox != *lista)
        q = q->prox;
      q->prox = (*lista)->prox;    
      *lista = (*lista)->prox;
    }  
    free (p);
    flag = 1;
  }
  // elemento a ser removido esta no meio/final da lista circular
  no q = (*lista)->prox, r = *lista;
  do {
    if (q->info == elem) {
      r->prox = q->prox;
      free (q);
      q = r->prox;
      flag = 1;
    }  
    else {
      r = q;
      q = q->prox;
    }         
  } while (q != *lista);
  return flag;
}
//------------------------------------------------------
// Remove todas ocorrencias de um determinado elemento de uma lista circular ordenada
//------------------------------------------------------
int remove_todos_LCSE_ord (no *lista, int elem) {
  int flag = 0;
  // se lista vazia  
  if (!*lista)
    return flag;
  // se o elemento a ser removido eh o primeiro da lista  
  while (*lista && elem == (*lista)->info) {
    no p = *lista;
    if (*lista == (*lista)->prox) {
      *lista = NULL;
      free(p);
      return 1;
    }  
    else {
      no q = *lista;
      while (q->prox != *lista)
        q = q->prox;
      q->prox = (*lista)->prox;    
      *lista = (*lista)->prox;
    }  
    free (p);
    flag = 1;
  }
  // elemento a ser removido esta no meio/final da lista circular
  no q = (*lista)->prox, r = *lista;
  do {
    if (q->info == elem) {
      r->prox = q->prox;
      free (q);
      q = r->prox;
      flag = 1;
    }  
    else {
      r = q;
      q = q->prox;
    }         
  } while (q != *lista && q->info <= elem );
  return flag;   
}
//----------------------------------------------------
// Programa Principal
//----------------------------------------------------
int main () {
  int info;
  no lista;    
  char resp;
  cria_LCSE (&lista);
  // Insere elementos na lista
  printf ("I N S E R C A O\n");
  do {
    printf ("\nDigite um numero inteiro: ");
    scanf ("%d",&info);
    inclui_ordenada_LCSE (&lista,info);
    mostra_LCSE (lista);
    printf ("\n\nContinua (S/N)? ");   
    do {
      resp = toupper(getch());
    } while (resp!='N' && resp!='S');
  } while (resp!='N');
  // Remove elementos na lista
  printf ("\n\nR E M O C A O\n");
  do {
    printf ("\nDigite um numero inteiro: ");
    scanf ("%d",&info);
    if (remove_todos_LCSE (&lista,info))
      printf ("-> %d removido.",info);
    else  
      printf ("-> elemento %d nao pertence a lista.",info);
    mostra_LCSE (lista);
    printf ("\n\nContinua (S/N)? ");   
    do {
      resp = toupper(getch());
    } while (resp!='N' && resp!='S');
  } while (resp!='N');
  getch();
}        
