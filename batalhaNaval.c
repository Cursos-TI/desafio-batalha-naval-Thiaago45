
#include <stdio.h>

#define N 10   // Tamanho do tabuleiro
#define M 5    // Tamanho das matrizes de habilidades

// Constantes para representar os elementos
#define AGUA 0
#define NAVIO 3
#define HABIL 5

// Função para inicializar o tabuleiro
void initTabuleiro(int tab[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tab[i][j] = AGUA;

    // Colocar alguns navios de exemplo
    tab[2][2] = NAVIO;
    tab[2][3] = NAVIO;
    tab[5][7] = NAVIO;
}

// Função para imprimir o tabuleiro
void printTabuleiro(int tab[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", tab[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Construir a máscara em forma de cone (5x5)
void cone(int mask[M][M]) {
    int mid = M/2;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (j >= mid - i && j <= mid + i) mask[i][j] = 1;
            else mask[i][j] = 0;
        }
    }
}

// Construir a máscara em forma de cruz (5x5)
void cruz(int mask[M][M]) {
    int mid = M/2;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == mid || j == mid) mask[i][j] = 1;
            else mask[i][j] = 0;
        }
    }
}

// Construir a máscara em forma de octaedro/losango (5x5)
void octaedro(int mask[M][M]) {
    int mid = M/2;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            int dist = (i > mid ? i - mid : mid - i) + (j > mid ? j - mid : mid - j);
            if (dist <= mid) mask[i][j] = 1;
            else mask[i][j] = 0;
        }
    }
}

// Sobrepor máscara no tabuleiro
void aplicaMascara(int tab[N][N], int mask[M][M], int origemI, int origemJ) {
    int mid = M/2;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (mask[i][j] == 1) {
                int x = origemI + (i - mid);
                int y = origemJ + (j - mid);
                if (x >= 0 && x < N && y >= 0 && y < N) {
                    if (tab[x][y] != NAVIO) // não sobrescreve navio
                        tab[x][y] = HABIL;
                }
            }
        }
    }
}

int main() {
    int tab[N][N];
    initTabuleiro(tab);

    int mask[M][M];

    // Aplicar cone no ponto (2,2)
    cone(mask);
    aplicaMascara(tab, mask, 2, 2);

    // Aplicar cruz no ponto (6,6)
    cruz(mask);
    aplicaMascara(tab, mask, 6, 6);

    // Aplicar octaedro no ponto (4,7)
    octaedro(mask);
    aplicaMascara(tab, mask, 4, 7);

    // Mostrar resultado final
    printTabuleiro(tab);

    return 0;
}

