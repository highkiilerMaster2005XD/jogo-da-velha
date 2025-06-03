#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct Jogada {
  int i;
  int j;
} Jogada;

void print_tabuleiro(int cabecalho, const char valores[3][3]);
int encontrar_vencedor(int *vencedor, int rodada, const char tabuleiro[3][3]);
int jogada_valida(int i, int j, const char tabuleiro[3][3]);
Jogada pegar_jogada();

int main() {
  int jogo = 1;
  int rodada = 1;

  int jogada_invalida = 0;
  int sair = 0;

  int vencedor = 0;

  char tabuleiro[3][3] = {
    "   ",
    "   ",
    "   "
  };

  while (jogo) {
    printf("\033[H\033[2J");
    print_tabuleiro(1, tabuleiro);

    if (jogada_invalida) {
      printf("> Jogada invalida!\n");
      jogada_invalida = 0;
    }

    Jogada jogada = pegar_jogada(&sair);
    int i = jogada.i;
    int j = jogada.j;

    if (sair == 1) return 0;

    if (jogada_valida(i, j, tabuleiro) == 0) {
      jogada_invalida = 1;
      continue;
    }

    tabuleiro[i][j] = rodada % 2 ? 'X' : 'O';
    
    encontrar_vencedor(&vencedor, rodada, tabuleiro);

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

int encontrar_vencedor(int *vencedor, int rodada, const char tabuleiro[3][3]) {
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
      *vencedor = 1;
      return 0;
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
      *vencedor = 2;
      return 0;
    }

    if (rodada == 9) return 0;
}

Jogada pegar_jogada(int *sair) {
    Jogada jogada;
    char jogada_escolhida[2];
    
    printf("> Escolha uma jogada ('q' para sair): ");
    scanf("%s", jogada_escolhida);

    if (jogada_escolhida[0] == 'q') *sair = 1;
    
    jogada.i = (int) jogada_escolhida[1] - 48 - 1;
    jogada.j = (int) toupper(jogada_escolhida[0]) - 65;
  
    return jogada;
}

void print_tabuleiro(int cabecalho, const char valores[3][3]) {
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
