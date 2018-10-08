#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int nlinhas;
  int ncolunas;
  int ncores;
  int **tabuleiro;
} ttabuleiro;

typedef struct node{
  ttabuleiro t;
  int nivel;
  int tam_area;
  int cor_pai; //Primeira cor que gerou o caminho para esse nodo a partir do estado inicial
  struct node *prev;
  struct node *next;
} typeNode;

typedef struct list{
  typeNode *first;
  int length;
} typeList;

typedef struct nodeInt{
  int key;
  struct nodeInt *prev;
  struct nodeInt *next;
} typeNodeInt;

typedef struct listInt{
  typeNodeInt *first;
  int length;
} typeListInt;



void initList(typeList *list);
int isEmptyList(typeList *list);
typeNode* removeList(typeList *list, typeNode *i);
void insertList(typeList *list, ttabuleiro t, int cor_pai, int cor, int nivel);
void newNode(typeNode **node, ttabuleiro t);
void printList(typeList *list);
void pinta_mapa(ttabuleiro *m, int cor);
void initListInt(typeListInt *list);
void insertListInt(typeListInt *list, int key);
void printListInt(typeListInt *list);
