#include <stdlib.h>

typedef struct reg *no;
struct reg {
           int info;
           struct reg *prox;
};
//----------------------------------------------------   
// Cria uma lista vazia
//----------------------------------------------------
void cria_lista (no *lista) {
  *lista = NULL;
} 
//----------------------------------------------------
// Inclui um elemento no in?cio da lista
//----------------------------------------------------
void inclui_inicio (no *lista, int info){
  no p = (no) malloc(sizeof(struct reg));
  p->info=info;
  p->prox=*lista;
  *lista=p;
}
//----------------------------------------------------
// Mostra os elementos da lista
//----------------------------------------------------
void mostra_lista (no lista) {
  no p = lista;
  printf ("\nElementos da lista: ");
  while (p) {
    printf ("%d ",p->info);
    p = p->prox;
  }
}
//----------------------------------------------------
// Conta o numero de elementos da lista
//----------------------------------------------------
int conta_nos (no lista){
  no p = lista;
  int cont = 0;
  while (p){
    cont++;
    p = p->prox;
  }
  return cont;
}
//----------------------------------------------------
// Inclui um elemento no final da lista
//----------------------------------------------------
void inclui_final (no *lista, int info){
  no p = (no) malloc(sizeof(struct reg));
  p->info = info;
  p->prox = NULL;
  if (*lista == NULL)
    *lista = p;
  else {
    no q = *lista;
    while (q->prox)
      q = q->prox;
    q->prox = p;
  }
}
//----------------------------------------------------
// Remove elemento do inicio da lista
//----------------------------------------------------
int remove_inicio (no *lista) {
  if (!*lista)
    return 0;
  no p = *lista;
  *lista = p->prox;
  free (p);
  return 1;
}
//----------------------------------------------------
// Remove elemento do final da lista
//----------------------------------------------------
int remove_final (no *lista) {
  // lista vazia
  if (!*lista)
    return 0;
  // lista com apenas um elemento
  if (!(*lista)->prox) {
    free (*lista);
    *lista = NULL;
    return 1;
  }
  // lista com pelo menos dois elementos
  no p = *lista, q;
  while (p->prox) {
    q = p;        
    p = p->prox;
  }  
  free (p);
  q->prox = NULL;
  return 1;
}
//----------------------------------------------------
// Verifica se um determinado elemento pertence a lista
//----------------------------------------------------
int busca_lista (no lista, int info) {
  no p = lista;
  while (p) {  // p != NULL
    if (p->info == info)
      return 1;
    p = p->prox;
  }    
  return 0;
}
//----------------------------------------------------
// Retorna a posicao do elemento na lista (0 se nao estiver)
//----------------------------------------------------
int busca_lista_pos (no lista, int info) {
  no p = lista;
  int cont = 0;
  while (p) {
    cont++;    
    if (p->info == info)
      return cont;
    p = p->prox;
  }    
  return 0;
}
//----------------------------------------------------
// Conta o numero de vezes que um determinado elemento ocorre na lista
//----------------------------------------------------
int conta_valor_lista (no lista, int info) {
  no p = lista;
  int cont = 0;
  while (p) {
    if (p->info == info)
      cont++;
    p = p->prox;
  }    
  return cont;
}
//----------------------------------------------------
// Retorna o conteudo do ultimo elemento da lista
//----------------------------------------------------
int valor_ultimo_lista (no lista, int *info) {
  if (!lista)
    return 0;  
  no p = lista;
  while (p->prox)
    p = p->prox;
  *info = p->info;
  return 1;
}
//----------------------------------------------------
// Programa Principal
//----------------------------------------------------
int main () {
  int info;
  no lista;    
  char resp;
  cria_lista (&lista);
  do {
    printf ("\nDigite um numero inteiro: ");
    scanf ("%d",&info);
    inclui_final (&lista,info);
    mostra_lista (lista);
    printf ("\nQuantidade de elementos na lista: %d",conta_nos(lista));
    printf ("\n\nContinua (S/N)? ");   
    do {
      resp = toupper(getch());
    } while (resp!='N' && resp!='S');
  } while (resp!='N');
  //-------------------------------------------------
  printf ("\n\nRemocao do 1o. elemento da lista realizada!\n");
  remove_inicio (&lista);
  mostra_lista (lista);
  printf ("\nQuantidade de elementos na lista: %d",conta_nos(lista));
  //-------------------------------------------------
  printf ("\n\nRemocao do ultimo elemento da lista realizada!\n");
  remove_final (&lista);
  mostra_lista (lista);
  printf ("\nQuantidade de elementos na lista: %d",conta_nos(lista));
  //-------------------------------------------------
  printf ("\n\nBusca de um elemento na lista");
  printf ("\nDigite um numero inteiro: ");
  scanf ("%d",&info);
  if (busca_lista (lista,info)) 
    printf ("\n--> %d pertence a lista",info);
  else
    printf ("\n--> %d nao pertence a lista",info);
  //-------------------------------------------------
  printf ("\n\nBusca de um elemento na lista");
  printf ("\nDigite um numero inteiro: ");
  scanf ("%d",&info);
  printf ("\n--> Posicao na lista: %d",busca_lista_pos (lista,info));
  //-------------------------------------------------
  printf ("\n\nConta numero de vezes que um elemento aparece na lista");
  printf ("\nDigite um numero inteiro: ");
  scanf ("%d",&info);
  printf ("\n--> O elemento %d aparece %d na lista.",info,conta_valor_lista(lista,info));       
  //-------------------------------------------------
  printf ("\n\nValor do ultimo elemento da lista");
  if (!valor_ultimo_lista (lista,&info)) 
    printf ("\n--> Lista vazia!");
  else
    printf ("\n--> Valor da ultima posicao: %d",info);   
  //-------------------------------------------------
  getch();
}        
