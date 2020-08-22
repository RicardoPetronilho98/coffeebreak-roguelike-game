#include "../defines.h"
/**
@file path_finder.h
Funcoes que asseguram que existe sempre um caminho possivel para a saida quando o estado e inicializado,
criando um array de colunas (cx) a reservar e linhas (cy). NOTA: Dada uma direção tem 3 caminhos possiveis:
Na direção, na diagonal para cima ou só para cima.
*/

/**
\brief Função que randomiza a posição a posição a reservar
@param x ---> array de possiveis 'x' a reservar
@param y ---> array de possiveis 'y' a reservar
@param * x_aux ---> guarda o x a reservar
@param * y_aux ---> guarda o y a reservar
*/
void decisao(int x[], int y[], int * x_aux, int * y_aux){

	int i = random() % 3; /* seleciona uma de 3 possiveis posicoes a reservar*/
	
	*x_aux = x[i]; /* guarda o x a ser reservado*/
	*y_aux = y[i]; /* guarda o y a ser reservado*/
}

/**
\brief Função que quando o pathfinder chega á linha da saída é invocada. A próxima coordenada será sempre nesta linha.
@param *i ---> posicao nos array de posicoes a reservar
@param *x_aux ---> pos x a reservar
@param *y_aux ---> pos y a reservar
*/
void gera_coordenada_na_linha_0(int *i, int *x_aux, int *y_aux, int cx[], int cy[]){

	(*x_aux) = cx[*i] - 1; /* prox posicao mais prox da saida (so se altera x_aux pis mantem-se a linha)*/
	gerar_coordenadas(i, x_aux, y_aux); /* guarda as coordenadas em cx e cy*/
}

/**
\brief Função invocada quando o gerador de caminho chega á última coluna. Muda de direção.
@param *i ---> posicao nos arrays de jogadas a reservar
@param *x_aux ---> pos x a reservar
@param *y_aux ---> pos y a reservar
@param cx[] ---> array de x a reservar
@param cy[] ---> array de y a reservar
@param *dir ---> direcao em que o gerador de caminhos esta a seguir
@param xa  ---> novo array de x possiveis a reservar
@param ya  ---> novo array de y possiveis a reservar 
*/
void gera_coordenada_na_ultima_coluna(int *i, int *x_aux, int *y_aux, int cx[], int cy[], char *dir, int xa[], int ya[]){

	*dir = 'E'; /* se chegou aqui e pq a dir era 'D' de direita passa d*/
	xa[0] = TAB_TAM-1; xa[1] = TAB_TAM-2; xa[2] = TAB_TAM-2;/* as 3 possiveis prox coords x*/
	ya[0] = *y_aux-1; ya[1] = *y_aux-1; ya[2] = *y_aux;/* as 3 possiveis prox coords y*/
	decisao(xa, ya, x_aux, y_aux);/* decisao de coords*/
	gerar_coordenadas(i, x_aux, y_aux);/* guarda a decisao em cx e cy*/
}

/**
\brief Função invocada quando o gerador de caminho chega á primeira coluna. Muda de direção.
@param *i ---> posicao nos arrays de jogadas a reservar
@param *x_aux ---> pos x a reservar
@param *y_aux ---> pos y a reservar
@param cx[] ---> array de x a reservar 
@param cy[] ---> array de y a reservar
@param *dir ---> direcao em que o gerador de caminhos esta a seguir
@param xa  ---> novo array de x possiveis a reservar
@param ya  ---> novo array de y possiveis a reservar 
*/
void gera_coordenada_na_primeira_coluna(int *i, int *x_aux, int *y_aux, int cx[], int cy[], char *dir, int xa[], int ya[]){

	*dir = 'D'; /* se chegou aqui em tao a direcao era 'E' portanto muda para 'D'*/
	xa[0] = 0; xa[1] = 1; xa[2] = 1;/* as 3 possiveis coords x*/
	ya[0] = *y_aux-1; ya[1] = *y_aux-1; ya[2] = *y_aux;/* as 3 possiveis coords y*/
	decisao(xa, ya, x_aux, y_aux);/* decisao de coords*/
	gerar_coordenadas(i, x_aux, y_aux);/* guarda a decisao em cx e cy*/
}

/**
\brief Função que gera as coordenadas quando a direção é esquerda ('E')
@param *i ---> posicao nos arrays de jogadas a reservar
@param *x_aux ---> pos x a reservar
@param *y_aux ---> pos y a reservar
@param cx[] ---> array de x a reservar 
@param cy[] ---> array de y a reservar
@param xa  ---> novo array de x possiveis a reservar
@param ya  ---> novo array de y possiveis a reservar 
*/
void gera_coordenada_na_direcao_esquerda(int *i, int *x_aux, int *y_aux, int cx[], int cy[], int xa[], int ya[]){

	xa[0] = *x_aux; xa[1] = *x_aux-1; xa[2] = *x_aux-1;/* as 3 possiveis coords x*/
	ya[0] = *y_aux-1; ya[1] = *y_aux-1; ya[2] = *y_aux;/* as 3 possiveis coords y*/
	decisao (xa, ya, x_aux, y_aux);/* decisao de coords*/
	gerar_coordenadas(i, x_aux, y_aux);/* guarda a decisao em cx e cy*/

}

/**
\brief Função que gera as coordenadas quando a direção é direita ('D')
@param *i ---> posicao nos arrays de jogadas a reservar
@param *x_aux ---> pos x a reservar
@param *y_aux ---> pos y a reservar
@param cx[] ---> array de x a reservar 
@param cy[] ---> array de y a reservar
@param xa  ---> novo array de x possiveis a reservar
@param ya  ---> novo array de y possiveis a reservar 
*/
void gera_coordenada_na_direcao_direita(int *i, int *x_aux, int *y_aux, int cx[], int cy[], int xa[], int ya[]){

	xa[0] = *x_aux; xa[1] = *x_aux+1; xa[2] = *x_aux+1;/* as 3 possiveis coords x*/
	ya[0] = *y_aux-1; ya[1] = *y_aux-1; ya[2] = *y_aux;/* as 3 possiveis coords y*/
	decisao (xa, ya, x_aux, y_aux);/* decisao de coords*/
	gerar_coordenadas(i, x_aux, y_aux);/* guarda a decisao em cx e cy*/
}

/**
\brief funcao que reserva um caminho possivel do spawn do jogador ate a saida no inicio de cada nivel
@param cx ---> array de coords x a reservar
@param cy ---> array de coord y a reservar
@returns dimensão dos arrays cx e cy
*/
int pathFinder (int cx[], int cy[]){
    
    int x_aux, y_aux; /* auxiliares a ser usados na gera_coord...*/
	x_aux = y_aux = cx[0] = cy[0] = TAB_TAM - 1; /* coordenadas iniciais do jogador */
	int i = 0;
	char dir; /* direção do jogador gera_coordenada_na_ultima_coluna, gera_coordenada_na_primeira_coluna, gera_coordenada_na_primeira_coluna e gera_coordenada_na_direcao_esquerda*/ 
	int xa[3], ya[3];/* arrays auxiliares as funcoes:*/

	while (x_aux >= 0 && y_aux >= 0){ /* enquanto nao chegou a saida*/
		
		if (y_aux == 0) gera_coordenada_na_linha_0(&i, &x_aux, &y_aux, cx, cy);/* linha 0*/

		else if (x_aux == TAB_TAM - 1 && y_aux != 0)
			gera_coordenada_na_ultima_coluna(&i, &x_aux, &y_aux, cx, cy, &dir, xa, ya);/* coluna 0*/

		else if (x_aux == 0) 
			gera_coordenada_na_primeira_coluna(&i, &x_aux, &y_aux, cx, cy, &dir, xa, ya);/* coluna maxima*/

		else if (dir == 'D')
			gera_coordenada_na_direcao_direita(&i, &x_aux, &y_aux, cx, cy, xa, ya);/* direita sem estar num extemo*/
		
		else if (dir == 'E' && x_aux != 0)
			gera_coordenada_na_direcao_esquerda(&i, &x_aux, &y_aux, cx, cy, xa, ya);/* esquerda sem estar num extemo*/
	}

	return i; /* diemsao do caminho */
}