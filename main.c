#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define TAM_BUSCA 4

int valido(ttabuleiro t, int x, int y, int cor, char **visitados){
  return (x >= 0) && (y >= 0) && (x < t.nlinhas) && (y < t.ncolunas) && (!visitados[x][y]) && (t.tabuleiro[x][y] == cor);
}

void zera_visitados(char ***visitados, int nlin, int ncol){
  for(int i = 0; i < nlin;i++)
    for(int j = 0; j < ncol; j++){
      (*visitados)[i][j] = 0;
    }
}

int tamanho_area(ttabuleiro t, int x, int y, char ***visitados){
  int cor = t.tabuleiro[x][y];
  int total = 1;

  //Map de direções
  int index_linha[] = {-1, -1, -1,  0, 0,  1, 1, 1};
  int index_col[]   = {-1,  0,  1, -1, 1, -1, 0, 1};

  (*visitados)[x][y] = 1;

  //Itera em todas as direções
  for(int i = 0; i < 8; i++){
    if(valido(t, x + index_linha[i], y + index_col[i], cor, (*visitados)  )){
      total += (tamanho_area(t, x + index_linha[i], y + index_col[i], visitados));
    }

    //se passou por todas as direções
    if(i == 7){
      return total;

    }
  }

  return 1;
}

void expande_raiz(typeList *fila, typeNode nodo){
  int cor = nodo.t.tabuleiro[0][0];
  int ncores = nodo.t.ncores;

  for(int i = 1; i <= ncores; i++){
    if(i != cor){
      insertList(fila, nodo.t, i, i, 1);
    }

  }
}

void expande_estado(typeList *fila, typeNode nodo, char ***visitados){
  int cor = nodo.t.tabuleiro[0][0];
  int ncores = nodo.t.ncores;

  for(int i = 1; i <= ncores; i++){
    if(i != cor){
                                //Propaga a cor do estado ancestral a este
      insertList(fila, nodo.t, nodo.cor_pai, i, nodo.nivel + 1);
      zera_visitados(visitados, nodo.t.nlinhas, nodo.t.ncolunas);
      fila->first->prev->tam_area = tamanho_area(fila->first->prev->t, 0, 0, visitados);
    }

  }
}

int escolhe_cor(ttabuleiro t){
  typeList fila;
  typeNode *nodo_inicial, *nodo_aux;
  char **visitados;
  int maior_area;

  //Aloca Matriz de células já visitadas
  visitados = (char **) malloc(t.nlinhas * sizeof(char *));
  for(int i = 0; i < t.nlinhas; i++) visitados[i] = (char *) malloc(t.ncolunas * sizeof(char));

  initList(&fila);
  insertList(&fila, t, 0, 0, 0);
  nodo_inicial = removeList(&fila, fila.first);
  //Cria estados iniciais e salva a cor que levou a cada um deles
  expande_raiz(&fila, *nodo_inicial);

  while(fila.first->nivel < TAM_BUSCA){

    nodo_aux = removeList(&fila, fila.first);
    expande_estado(&fila, *nodo_aux, &visitados);

  }

  printList(&fila);
  // initFila(fila)
  // nodo = novoNodo(tabuleiro)
  // insere(File, nodo)
  //
  // while(!filaVazia()){
  //   //tira um cara da fila
  //   //Se cara.nivel < TAM_BUSCA
  //     //ex pan de
  //   //Se cara.nivel = TAM_BUSCA
  //     //Olha o tamanho
  //
  //
  // }
}



int main() {
  int i, j, n, m, k;
  ttabuleiro t;
  char **visitados;

  //le lunhas e colinas
  scanf("%d %d %d\n", &n, &m, &k);

  //aloca tabuleiro
  t.nlinhas = n;
  t.ncolunas = m;
  t.ncores = k;
  t.tabuleiro = (int **) malloc(n * sizeof(int *));
  for(int i = 0; i < n; i++) t.tabuleiro[i] = (int *) malloc(m * sizeof(int));
  //Aloca Matriz de células já visitadas
  visitados = (char **) malloc(n * sizeof(char *));
  for(int i = 0; i < n; i++) visitados[i] = (char *) malloc(m * sizeof(char));

  // le tabuleiro
  for(i = 0; i < n; i++){
    for(j = 0; j < m; j++){
      scanf("%d", &t.tabuleiro[i][j]);
      if(t.tabuleiro[i][j] > k){
        printf("Cor %d fora do intervalo [1..%d]\n", t.tabuleiro[i][j], k);
        exit(1);
      }
    }
  }

  zera_visitados(&visitados, t.nlinhas, t.ncolunas);
  int tam = tamanho_area(t, 0, 0, &visitados);
  printf("%d\n", tam);

  escolhe_cor(t);
  return 0;
}
