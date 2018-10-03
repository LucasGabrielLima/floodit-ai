#include <stdio.h>
#include <stdlib.h>
#include <graphviz/cgraph.h>

typedef struct {
  int nlinhas;
  int ncolunas;
  int ncores;
  int **tabuleiro;
} ttabuleiro;

int main(int argc, char const *argv[]) {
  int i, j, n, m, k;
  ttabuleiro t;

  //le lunhas e colinas
  scanf("%d %d %d\n", &n, &m, &k);

  //aloca tabuleiro
  t.nlinhas = n;
  t.ncolunas = m;
  t.ncores = k;
  t.tabuleiro = (int **) malloc(n * sizeof(int));
  for(int i = 0; i < n; i++) t.tabuleiro[i] = (int *) malloc(m * sizeof(int));

  le tabuleiro
  for(i = 0; i < n; i++){
    for(j = 0; j < m; j++){
      scanf("%d", &t.tabuleiro[i][j]);

      if(t.tabuleiro[i][j] > k){
        printf("Cor %d fora do intervalo [1..%d]\n", t.tabuleiro[i][j], k);
        exit(1);
      }
    }
  }

  tamanho_area(t, 0, 0);
  return 0;
}

int valido(ttabuleiro t, int x, int y){
  return (x >= 0) && (y >= 0) && (x < t.nlinhas) && (y < t.ncolunas);
}

int tamanho_area(ttabuleiro t, int x, int y){
  char **visitados;
  int cor = t.tabuleiro[x][y];

  visitados = (char **) malloc(t.nlinhas * sizeof(char));
  for(int i = 0; i < t.nlinhas; i++) visitados = (char *) malloc(t.ncolunas * sizeof(char));
  // memset(visitados, 0, sizeof(visitados));

  for(int i = 0; i < t.nlinhas;i++)
    for(int j = 0; j < t.ncolunas; j++){


    }
}
