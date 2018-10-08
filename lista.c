#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


void pinta(ttabuleiro *m, int l, int c, int fundo, int cor) {
  m->tabuleiro[l][c] = cor;
  if(l < m->nlinhas - 1 && m->tabuleiro[l+1][c] == fundo)
    pinta(m, l+1, c, fundo, cor);
  if(l < m->nlinhas - 1 && c < m->ncolunas - 1 && m->tabuleiro[l+1][c+1] == fundo)
    pinta(m, l+1, c+1, fundo, cor);
  if(c < m->ncolunas - 1 && m->tabuleiro[l][c+1] == fundo)
    pinta(m, l, c+1, fundo, cor);
  if(l > 0 && c < m->ncolunas - 1 && m->tabuleiro[l-1][c+1] == fundo)
    pinta(m, l-1, c+1, fundo, cor);
  if(l > 0 && m->tabuleiro[l-1][c] == fundo)
    pinta(m, l-1, c, fundo, cor);
  if(l > 0 && c > 0 && m->tabuleiro[l-1][c-1] == fundo)
    pinta(m, l-1, c-1, fundo, cor);
  if(c > 0 && m->tabuleiro[l][c-1] == fundo)
    pinta(m, l, c-1, fundo, cor);
  if(l < m->nlinhas - 1 && c > 0 && m->tabuleiro[l+1][c-1] == fundo)
    pinta(m, l+1, c-1, fundo, cor);
}

void pinta_mapa(ttabuleiro *m, int cor) {
  if(cor == m->tabuleiro[0][0])
    return;
  pinta(m, 0, 0, m->tabuleiro[0][0], cor);
}

void initList(typeList *list){
  list->first = (typeNode*) malloc(sizeof(typeNode));
  list->first->next = list->first;
  list->first->prev = list->first;

  list->length = 0;
  return;
}


int isEmptyList(typeList *list){
  return (list->length == 0);
}

int isEmptyListInt(typeListInt *list){
  return (list->length == 0);
}

void insertList(typeList *list, ttabuleiro t, int cor_pai, int cor, int nivel){
  typeNode *node; // auxiliary node

  node = (typeNode*) malloc(sizeof(typeNode));
  node->cor_pai = cor_pai;
  node->nivel = nivel;
  node->t.nlinhas = t.nlinhas;
  node->t.ncolunas = t.ncolunas;
  node->t.ncores = t.ncores;
  node->t.tabuleiro = (int **) malloc(t.nlinhas * sizeof(int *));
  for(int i = 0; i < t.nlinhas; i++) node->t.tabuleiro[i] = (int *) malloc(t.ncolunas * sizeof(int));

  //Copia tabuleiro passado
  for(int i = 0; i < t.nlinhas; i++){
    for(int j = 0; j < t.ncolunas; j++){
      node->t.tabuleiro[i][j] = t.tabuleiro[i][j];
    }
  }

  //Pinta com a cor indicada
  if(cor > 0){
    pinta_mapa(&node->t, cor);
  }


  node->next = list->first;
  node->prev = list->first->prev;
  list->first->prev->next = node;

  list->first->prev = node;
  list->length++;
  return;
}


typeNode* removeList(typeList *list, typeNode *i){ //returns 1 on sucessfull removal, returns 0 if target is not found
  // typeNode *i; //iterator pointer
  typeNode *before, *after;

  if(isEmptyList(list))
    return NULL;

  before = i->prev;
  after = i->next;

  before->next = after;
  after->prev = before;
  list->length--;
  return i;
}

void printList(typeList *list){
  typeNode *i; //iterator pointer

  if(isEmptyList(list)){
    printf("\n LISTA VAZIA \n");
    return;
  }

  i = list->first->next;
  printf("\n %d", i->tam_area);

  while(i->next != list->first){
    i = i->next;
    printf(" - %d", i->tam_area);
  }

  return;
}

void initListInt(typeListInt *list){
  list->first = (typeNodeInt*) malloc(sizeof(typeNodeInt));
  list->first->next = list->first;
  list->first->prev = list->first;

  list->length = 0;
  return;
}


void insertListInt(typeListInt *list, int key){
  typeNodeInt *node; // auxiliary node

  node = (typeNodeInt*) malloc(sizeof(typeNodeInt));
  node->key = key;

  node->next = list->first;
  node->prev = list->first->prev;
  list->first->prev->next = node;

  list->first->prev = node;
  list->length++;
  return;
}

void printListInt(typeListInt *list){
  typeNodeInt *i; //iterator pointer

  if(isEmptyListInt(list)){
    return;
  }

  i = list->first->next;
  printf("%d", i->key);

  while(i->next != list->first){
    i = i->next;
    printf(" %d", i->key);
  }

  return;
}
