#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_tabuleiro(int cabecalho, const char valores[3][3]);
int encontrar_vencedor(int rodada, const char tabuleiro[3][3]);
int jogada_valida(int i, int j, const char tabuleiro[3][3]);
int pegar_jogada(int *i, int *j);

int main() {
  int jogo = 1;
  int rodada = 1;

  int jogada_invalida = 0;
  int sair = 0;

  int i = 0;
  int j = 0;

  int vencedor = 0;

  char tabuleiro[3][3] = {
    "   ",
    "   ",
    "   "
  };

  while (jogo) {
    print_tabuleiro(1, tabuleiro);

    if (jogada_invalida) {
      printf("> Jogada invalida!\n");
      jogada_invalida = 0;
    }

    int sair = pegar_jogada(&i, &j);
    if (sair) return 0;

    if (!jogada_valida(i, j, tabuleiro)) {
      jogada_invalida = 1;
      continue;
    }

    tabuleiro[i][j] = rodada % 2 ? 'X' : 'O';
    
    vencedor = encontrar_vencedor(rodada, tabuleiro);
    if (vencedor == 1 || vencedor == 2) break;

    rodada++;
  }

  printf("\033[H\033[2J");
  print_tabuleiro(1, tabuleiro);

  printf("==== Fim de jogo! ====\n");
  if (vencedor == 1) {
    printf("> O vencedor foi X");
  }
  if (vencedor == 2) {
    printf("> O vencedor foi O");
  }
  if (vencedor == 0) {
    printf("> Deu velha");
  }

  printf("\n");
}

int jogada_valida(int i, int j, const char tabuleiro[3][3]) {
    if (i < 0 || i > 2 || j < 0 || j > 2) {
      return 0;
    }
    if (tabuleiro[i][j] != ' ') {
      return 0;
    };

    return 1;
}

int encontrar_vencedor(int rodada, const char tabuleiro[3][3]) {
    if (
      (tabuleiro[0][0] == 'X' && tabuleiro[0][1] == 'X' && tabuleiro[0][2] == 'X') ||
      (tabuleiro[1][0] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[1][2] == 'X') ||
      (tabuleiro[2][0] == 'X' && tabuleiro[2][1] == 'X' && tabuleiro[2][2] == 'X') ||
      (tabuleiro[0][0] == 'X' && tabuleiro[1][0] == 'X' && tabuleiro[2][0] == 'X') ||
      (tabuleiro[0][1] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[2][1] == 'X') ||
      (tabuleiro[0][2] == 'X' && tabuleiro[1][2] == 'X' && tabuleiro[2][2] == 'X') ||
      (tabuleiro[0][0] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[2][2] == 'X') ||
      (tabuleiro[0][2] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[2][0] == 'X')
    ) {
      return 1;
    }

    if (
      (tabuleiro[0][0] == 'O' && tabuleiro[0][1] == 'O' && tabuleiro[0][2] == 'O') ||
      (tabuleiro[1][0] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[1][2] == 'O') ||
      (tabuleiro[2][0] == 'O' && tabuleiro[2][1] == 'O' && tabuleiro[2][2] == 'O') ||
      (tabuleiro[0][0] == 'O' && tabuleiro[1][0] == 'O' && tabuleiro[2][0] == 'O') ||
      (tabuleiro[0][1] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[2][1] == 'O') ||
      (tabuleiro[0][2] == 'O' && tabuleiro[1][2] == 'O' && tabuleiro[2][2] == 'O') ||
      (tabuleiro[0][0] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[2][2] == 'O') ||
      (tabuleiro[0][2] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[2][0] == 'O')
    ) {
      return 2;
    }

    if (rodada == 9) return 0;
}

int pegar_jogada(int *i, int *j) {
    char jogada_escolhida[100];
    
    printf("> Escolha uma jogada ('q' para sair): ");
    scanf("%s", jogada_escolhida);

    if (jogada_escolhida[0] == 'q') return 1;
    
    *i = jogada_escolhida[1] - 48 - 1;
    *j = toupper(jogada_escolhida[0]) - 65;
    return 0;
}

void print_tabuleiro(int cabecalho, const char valores[3][3]) {
  printf("\033[H\033[2J");

  if (cabecalho) {
    printf("======== Jogo da Velha ========\n");
  }

  printf("         ");
  printf("╔═══╦═══╦═══╗\n");
  printf("       3 ");
  printf("║ %c ║ %c ║ %c ║\n", valores[2][0], valores[2][1], valores[2][2]);
  printf("         ");
  printf("╠═══╬═══╬═══╣\n");
  printf("       2 ");
  printf("║ %c ║ %c ║ %c ║\n", valores[1][0], valores[1][1], valores[1][2]);
  printf("         ");
  printf("╠═══╬═══╬═══╣\n");
  printf("       1 ");
  printf("║ %c ║ %c ║ %c ║\n", valores[0][0], valores[0][1], valores[0][2]);
  printf("         ");
  printf("╚═══╩═══╩═══╝\n");
  printf("         ");
  printf("  A   B   C  \n");
}
