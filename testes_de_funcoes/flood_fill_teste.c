#include <stdio.h>
#include <stdlib.h>
#define TAB_TAM     10


void print_matrix(int matrix[][10]){
    
    int c, l;
    for (l = 0; l < 10; l++){
        for(c = 0; c < 10; c++)
            printf("%d   ", matrix[l][c]);
        printf("\n");
    }
}

int posicao_valida (int l, int c){
    return c >= 0 && c < 10 && l >= 0 && l < 10;
}


void mete_a_zeros(int l_j, int c_j, int matrix[][TAB_TAM]){ //todos os quadrados a volta do jogador ficam a 0

    int ck, lk;

    for (lk = -1; lk <= 1; lk++)
        for (ck = -1; ck <= 1; ck++)
             if (posicao_valida(l_j+lk, c_j+ck)) 
                matrix[l_j+lk][c_j+ck] = 0;
}

void flood_fill(int matrix[][10], int l, int c, int r){
    
    int ck, lk;

    matrix[l][c] = r;

    for (lk = -1; lk <= 1; lk++)
        for (ck = -1; ck <= 1; ck++)
            if (posicao_valida(l + lk, c + ck) && (matrix[l + lk][c + ck] == 0 || matrix[l + lk][c + ck] > r))
                flood_fill(matrix, l +lk, c + ck, r + 1);
}


int main(void){
    
    
    //NOTA:     ------> flood fill começa no jogador <------

    puts("\n-1 -> OBSTACULO");
    puts("-2 -> JOGADOR");
    puts("-3 -> MONSTRO\n");

    
    int matrix[10][10] = {{0}};
    matrix[2][4] = -1;
    matrix[3][4] = -1;
    matrix[4][4] = -1;
    matrix[5][4] = -1;

    matrix[5][5] = -1;
    matrix[5][6] = -1;

    matrix[4][6] = -1;
    matrix[3][6] = -1;
    matrix[2][6] = -1;

    matrix[1][1] = -1;
    matrix[2][1] = -1;
    matrix[3][1] = -1;
    matrix[4][1] = -1;
    matrix[5][1] = -1;
    matrix[6][1] = -1;
    matrix[7][1] = -1;
    matrix[8][1] = -1;
    matrix[9][1] = -1;

    matrix[9][5] = 0; //jogador

    matrix[9][4] = -1;
    matrix[9][6] = -1;
    matrix[8][5] = -1;
    matrix[8][4] = -1;
    matrix[8][6] = -1;

    mete_a_zeros(9, 5, matrix);


    //flood_fill(matrix, 9, 5, 0);

    //matrix[4][5] = -2; //monstro

    //obstaculos a -1
    //print_matrix(matrix);

    //flood_fill(matrix, 9, 5, 1);

    print_matrix(matrix);

    return 0;  
}














