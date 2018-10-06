#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
  char **visitados;
  int **t; //tabuleiro
  int tam_area;
  struct nodo *pai;
  struct nodo *filhos;
} nodo;

typedef struct{
  nodo *raiz;
  int nnodos;
} grafo;


void novo_nodo(*nodo, ttabuleiro t, int ncores){
  nodo = (nodo *) malloc(sizeof(nodo));
  nodo->filhos = (nodo *) malloc(ncores * sizeof(nodo)); //Uma expansão para cada cor

  nodo->t = (int **) malloc(t.nlinhas * sizeof(int *));
  for(int i = 0; i < n; i++) nodo->t[i] = (int *) malloc(t.ncolunas * sizeof(int));
  nodo->visitados = (char **) malloc(t.nlinhas * sizeof(char *));
  for(int i = 0; i < n; i++) nodo->t[i] = (char *) malloc(t.ncolunas * sizeof(char));

}
