#include <stdio.h>
#include <stdlib.h>
#include <graphviz/cgraph.h>

typedef struct {
  int nlinhas;
  int ncolunas;
  int ncores;
  int **tabuleiro;
} ttabuleiro;

int valido(ttabuleiro t, int x, int y, char **visitados){
  return (x >= 0) && (y >= 0) && (x < t.nlinhas) && (y < t.ncolunas) && !visitados[x][y];
}

void zera_visitados(char ***visitados, int nlin, int ncol){
  for(int i = 0; i < nlin;i++)
    for(int j = 0; j < ncol; j++){
      printf("%d\n", j);
      *visitados[i][j] = 0;
    }
}

int tamanho_area(ttabuleiro t, int x, int y, char **visitados){
  int cor = t.tabuleiro[x][y];

  //Map de direções
  int index_linha[] = {-1, -1, -1,  0, 0,  1, 1, 1};
  int index_col[]   = {-1,  0,  1, -1, 1, -1, 0, 1};

  visitados[x][y] = 1;

  //Itera em todas as direções
  for(int i = 0; i < 8; i++){
    if(valido(t, x + index_linha[i], y + index_col[i], visitados)){
      return (tamanho_area(t, x + index_linha[i], y + index_col[i], visitados) + 1);
    }

  }

  return 1;
}

int main(int argc, char const *argv[]) {
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

  puts("a");
  zera_visitados(&visitados, t.nlinhas, t.ncolunas);
  int tam = tamanho_area(t, 0, 0, visitados);
  printf("%d\n", tam);
  return 0;
}
