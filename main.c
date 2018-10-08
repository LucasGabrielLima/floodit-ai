#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Define altura máxima da árvore de busca. Com nível 3 a melhora é considerável porém o tempo de execução com 100x100 e 10 cores passa de um minuto
#define TAM_BUSCA 2

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

int expande_raiz(typeList *fila, typeNode nodo, char ***visitados){
  int cor = nodo.t.tabuleiro[0][0];
  int ncores = nodo.t.ncores;

  for(int i = 1; i <= ncores; i++){
    if(i != cor){
      insertList(fila, nodo.t, i, i, 1);
      zera_visitados(visitados, nodo.t.nlinhas, nodo.t.ncolunas);
      fila->first->prev->tam_area = tamanho_area(fila->first->prev->t, 0, 0, visitados);
      if(fila->first->prev->tam_area == nodo.t.nlinhas * nodo.t.ncolunas){
        return i;
      }
    }
  }

  return 0;
}

//Retorna 1 se resolveu tabuleiro, 0 caso contrario
int expande_estado(typeList *fila, typeNode nodo, char ***visitados){
  int cor = nodo.t.tabuleiro[0][0];
  int ncores = nodo.t.ncores;

  for(int i = 1; i <= ncores; i++){
    if(i != cor){
                                //Propaga a cor do estado ancestral a este
      insertList(fila, nodo.t, nodo.cor_pai, i, nodo.nivel + 1);
      zera_visitados(visitados, nodo.t.nlinhas, nodo.t.ncolunas);
      fila->first->prev->tam_area = tamanho_area(fila->first->prev->t, 0, 0, visitados);

      if(fila->first->prev->tam_area == nodo.t.nlinhas * nodo.t.ncolunas){
        return 1;
      }
    }

  }

  return 0;
}

int escolhe_cor(ttabuleiro t, char ***visitados){
  typeList fila;
  typeNode *nodo_inicial, *nodo_aux;
  int maior_area = 0, cor = 0;

  initList(&fila);
  insertList(&fila, t, 0, 0, 0);
  nodo_inicial = removeList(&fila, fila.first->next);
  //Cria estados iniciais e salva a cor que levou a cada um deles
  zera_visitados(visitados, t.nlinhas, t.ncolunas);
  if((cor = expande_raiz(&fila, *nodo_inicial, visitados))){
    return cor;
  }

  while(fila.first->next->nivel < TAM_BUSCA){
    nodo_aux = removeList(&fila, fila.first->next);
    zera_visitados(visitados, t.nlinhas, t.ncolunas);
    if(expande_estado(&fila, *nodo_aux, visitados)){
      return nodo_aux->cor_pai;
    };
    free(nodo_aux->t.tabuleiro);
    free(nodo_aux);

  }

  // printList(&fila);

  while(fila.length > 0){
    nodo_aux = removeList(&fila, fila.first->next);
    if(nodo_aux->tam_area > maior_area){
      maior_area = nodo_aux->tam_area;
      cor = nodo_aux->cor_pai;
    }

    free(nodo_aux->t.tabuleiro);
    free(nodo_aux);
  }

  return cor;
}



int main() {
  int i, j, n, m, k, cor_atual;
  ttabuleiro t;
  typeListInt resultados;
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

  initListInt(&resultados);

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
  while(tamanho_area(t, 0, 0, &visitados) < t.nlinhas * t.ncolunas){
    cor_atual = escolhe_cor(t, &visitados);
    pinta_mapa(&t, cor_atual);
    insertListInt(&resultados, cor_atual);
    zera_visitados(&visitados, t.nlinhas, t.ncolunas);
  }

  //Imprime resultados
  printf(" %d\n", resultados.length);
  printListInt(&resultados);



  return 0;
}
