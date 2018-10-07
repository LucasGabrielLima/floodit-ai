#include <stdio.h>
#include <stdlib.h>


typedef struct node{
  ttabuleiro t;
  int tam_area;
  int cor_pai; //Primeira cor que gerou o caminho para esse nodo a partir do estado inicial
  struct node *prev;
  struct node *next;
} typeNode;

typedef struct list{
  typeNode *first;
  int length;
} typeList;


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

void insertList(typeList *list, ttabuleiro t){
  typeNode *node; // auxiliary node

  node = (typeNode*) malloc(sizeof(typeNode));
  node->t = t;

  node->next = list->first;
  node->prev = list->first->prev;
  list->first->prev->next = node;

  list->first->prev = node;
  list->length++;
  return;
}


int removeList(typeList *list, typeNode *i){ //returns 1 on sucessfull removal, returns 0 if target is not found
  // typeNode *i; //iterator pointer
  typeNode *before, *after;

  if(isEmptyList(list))
    return 0;

  // i = list->first->next;
  //
  // while(i->key != target){ //iterates through list searching for the node with the target
  //   i = i->next;
  //
  //   if(i->next == list->first && i->key != target)
  //     return 0;
  // }

  before = i->prev;
  after = i->next;

  before->next = after;
  after->prev = before;
  free(i);
  list->length--;
  return 1;
}
