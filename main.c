#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
  int i, j, n, m, k;
  int **tabuleiro;

  //le lunhas e colinas
  scanf("%d %d %d\n", &n, &m, &k);

  //aloca tabuleiro
  tabuleiro = (int **) malloc(n * sizeof(int));
  for(int i = 0; i < n; i++) tabuleiro[i] = (int *) malloc(m * sizeof(int));

  //le tabuleiro
  for(i = 0; i < n; i++){
    for(j = 0; j < m; j++){
      scanf("%d", &tabuleiro[i][j]);

      if(tabuleiro[i][j] > k){
        printf("Cor %d fora do intervalo [1..%d]\n", tabuleiro[i][j], k);
        exit(1);
      }
    }
  }
  
  return 0;
}
