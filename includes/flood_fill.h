#include "../defines.h"

/**
@file flood_fill.h
Funções que tratam da decisão de jogada para o inimigo, com base no algoritmo flood fill.
*/

/**\brief Prototipo de função ja documentadas na main. */
int posicao_ocupada(ESTADO e, int x, int y);
/**\brief Prototipo de função ja documentadas na main. */
int posicao_valida(int c, int l);

/**
\brief Função converte o mapa guardado no estado para uma matriz. 0 é a posição do jogador, -1 os obstáculos.
@param m ---> matriz que é alterada para representar o mapa
@param e ---> estado que vai ser convertido em matriz
*/
void converte_mapa_na_matriz (int m[TAB_TAM][TAB_TAM], ESTADO e) {

    int l, c;
    /*ciclos que percorem a matriz */
    for (l = 0; l < TAB_TAM; l++)
        for (c = 0; c < TAB_TAM; c++)
            if (posicao_ocupada(e, c, l)) m[l][c] = -1; /* sinaliza os obstáculos e monstros com inacessiveis*/
}

/**
\brief Função que preenche a matriz com a distancia ao jogador.
@param matrix ---> matriz que representa o mapa
@param l_j ---> linha em que se vai alterar a matriz (inicialmente e a do jogador)
@param c_j ---> coluna em que se vai alterar a matriz (inicialmente e a do jogador)
@param r ---> raio ou distancia ao jogador
*/
void flood_fill(int matrix[TAB_TAM][TAB_TAM], int l_j, int c_j, int r){
    
    int C, L; /* variaveis coluna e linha que vao ser usadas no radial scan para fazer um raio de posicoes*/

    matrix[l_j][c_j] = r; /* alteraçao do valor na matriz para a posiçao a ser testada*/

    RADIAL_SCAN(1){ /* percorre um raio de 1 da posicao a ser testada*/

        C = c_j + ck; /* altera a coluna a ser testada*/
        L = l_j + lk; /* altera a linha a ser testada*/
        
        if (posicao_valida(C, L) && (matrix[L][C] == 0 || matrix[L][C] > r)) /* se a posiçao em que estiver for valida e ainda nao tiver sido mudada ou se existir um caminho melhor*/
            flood_fill(matrix, L, C, r + 1); /* recursivamente aplica esta funcao na posicao que acabou de testar*/
    }
}

/**
\brief Função que decide se a jogada a testar e melhor que a anteriormente calculada.
@param *min ---> valor que verifica que o caminho para o jogador e o menor possivel
@param C ---> coluna da jogada
@param L ---> linha da jogada
@param matrix --->matriz que representa o mapa de jogo
@param *jogada ---> array que guarda a nova posicao do inimigo
*/
void atualiza_jogada(int *min, int C, int L, int matrix[TAB_TAM][TAB_TAM], int *jogada){
    
    if (matrix[L][C] <= *min){ /* condicao que testa se a jogada testada e melhor que a anterior*/
        *min = matrix[L][C]; /* atualiza o valor que representa a melhor jogada*/
        jogada[0] = L; /* atualiza a linha do inimigo*/
        jogada[1] = C; /* atualiza a coluna do inimigo*/
    }
}


/**
\brief Função que verifica se o jogador já está ao alcance do inimigo de tipo 0 (melee), se sim não precisa de se mover só atacar.
@param M ---> inimigo
@param e ---> estado de jogo
@returns 1 se pode atacar, 0 c.c.
*/
int distancia_1_do_jogador(INIMIGO M, ESTADO e){

    if (abs (M.pos.y - e.jog.y) == 1 && abs(M.pos.x - e.jog.x) == 1) return 1; /* verifica as diagonais*/
    if (abs (M.pos.y - e.jog.y) == 1 && abs(M.pos.x - e.jog.x) == 0) return 1; /* verifica as linhas*/
    if (abs (M.pos.y - e.jog.y) == 0 && abs(M.pos.x - e.jog.x) == 1) return 1; /* verifica as colunas*/

    return 0;
}


/**
\brief Função que verifica se o jogador já está ao alcance do inimigo de tipo 1 ou 2 (ranged), se sim não precisa de se mover só atacar.
@param M ---> inimigo
@param e ---> estado de jogo
@returns 1 se pode atacar, 0 c.c.
*/
int distancia_2_do_jogador(INIMIGO M, ESTADO e){

    if (abs (M.pos.y - e.jog.y) == 2 && abs(M.pos.x - e.jog.x) == 2) return 1; /* verifica as diagonais*/
    if (abs (M.pos.y - e.jog.y) == 2 && abs(M.pos.x - e.jog.x) == 0) return 1; /* verifica as linhas*/
    if (abs (M.pos.y - e.jog.y) == 0 && abs(M.pos.x - e.jog.x) == 2) return 1; /* verifica as colunas*/

    return 0;
}

/**
\brief Função que verifica se o jogador já está ao alcance do inimigo (se sim não precisa de se mover só atacar).
@param M ---> inimigo
@param e ---> estado de jogo
@returns 1 se pode atacar, 0 c.c.
*/
int monstro_pode_atacar_jogador(INIMIGO M, ESTADO e){

    if (M.raio == 1) return distancia_1_do_jogador(M, e);

    else return distancia_2_do_jogador(M, e);
}



/**
\brief Função que afasta os inimigos de tipo 1 do jogador a uma distância de 2.
@param M ---> apontador para o inimigo
@param matrix ---> matriz que contem o resultado do flood fill
@param jogada ---> a proxima jogada do inimigo
@param e ---> O estado de jogo
*/
void foge_do_jogador(INIMIGO *M, int matrix[TAB_TAM][TAB_TAM], int *jogada, ESTADO e){

    int C, L;

    RADIAL_SCAN(1){ /* testa um raio de 1 a volta do inimigo*/

        C = M->pos.x + ck;/* altera a coluna*/
        L = M->pos.y + lk;/* altera a linha*/

        if (posicao_valida (C, L) && !posicao_ocupada(e, C, L) && C != 0 && L != 0 && matrix[L][C] == 2){
            jogada[0] = L;
            jogada[1] = C;
            M->pos.y = L;
            M->pos.x = C;
            return;
        }
    }
}



/**
\brief Função que indica a melhor jogada possível para o inimigo.
1º Calcula a matriz mapa com as células representando a distância ao jogador.
2º Verifica se pode atacar o jogador se sim, ataca, se nao prox. passo.
3º Percorre o raio de movimento do inimigo e verifica qual casa tem a menor distância ao jogador.
4º Atualiza a jogada do inimigo.
@param *jogada ---> array que guarda a melhor jogada para o inimigo (que antes tem de ser calculada)
@param M ---> inimigo ao qual esta funcao vai ser aplicada (ou seja para o qual se vai decidir o prox. move)
@param e ---> estado de jogo
*/
void indica_jogada_M(int *jogada, INIMIGO M, ESTADO e){

    int r;
    int min = TAB_TAM * TAB_TAM; /* o valor de minimo incializado com o valor max possivel para depois ser alterado*/
    int l_j = e.jog.y, c_j = e.jog.x;/* posicao do jogador*/
    int l_M = M.pos.y, c_M = M.pos.x;/* posicao do monstro*/
    int C, L;/* nova posicao*/
    int matrix[TAB_TAM][TAB_TAM] = {{0}};/* matriz que ira representar o mapa de jogo*/
    
    if (M.type == 3) return; //faz com que os GUARDIOES da saida nao se movam

    converte_mapa_na_matriz(matrix, e); /* modifica a matriz consoante o mapa atual*/

    if (posicao_valida(c_j, l_j - 1)) matrix[l_j - 1][c_j] = 0; /* se o jogador estiver rodeado a prox posicao desejavel sera uma acima dele (se esta existir)*/
    else matrix[l_j + 1][c_j] = 0; /* se o jogador estiver rodeado a prox posicao desejavel sera uma abaixo dele (se estaa de cima nao existir)*/

    flood_fill(matrix, l_j, c_j, 0); /* preenche a matriz com a distancia ponto desejavel (normalmente sendo o jogador se este nao estiver cercado, c.c. ver acima)*/

    if (M.type == 1 && distancia_1_do_jogador(M, e)){ /* Os arqueiros tentam-se manter a 2 casas de distancia do jogador.*/
        foge_do_jogador(&M, matrix, jogada, e);
        return;
    }

    if (M.type == 2) r = 2; //AB2 do BOSS
    else r = 1; 

    if (monstro_pode_atacar_jogador(M, e)) return; /* se o inimigo puder atacar o jogador entao nao se mexe*/

    RADIAL_SCAN(r){/* testa um raio de 1 a volta do inimigo*/

        C = c_M + ck;/* altera a coluna*/
        L = l_M + lk;/* altera a linha*/

        if (posicao_valida (C, L) && !posicao_ocupada(e, C, L) && C != 0 && L != 0) /* condicoes em que uma jogada e decidida: se for valida, nao for ocupada e se nao for (0,0) (representa a saida)*/
            atualiza_jogada(&min, C, L, matrix, jogada); /* atualizacao de jogada do inimigo*/
    }
}