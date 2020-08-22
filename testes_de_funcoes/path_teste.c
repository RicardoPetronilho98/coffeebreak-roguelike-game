#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB_TAM 	10
#define gerar_coordenadas(i, x_aux, y_aux) 		i++; cx[i] = x_aux; cy[i] = y_aux;

void decisao(int x[], int y[], int * x_aux, int * y_aux){

	int i = random() % 3;
	*x_aux = x[i];
	*y_aux = y[i];
}

int pathFinder (int cx[], int cy[]){
    int x_aux, y_aux; 
	x_aux = y_aux = cx[0] = cy[0] = TAB_TAM - 1; /* coordenadas iniciais do jogador */
	int i = 0;
	char dir; /* direção do jogador */ 
	int xa[3], ya[3];

	while (x_aux >= 0 && y_aux >= 0){ 
		
		if (y_aux == 0){
			x_aux = cx[i] - 1;
			gerar_coordenadas(i, x_aux, y_aux);
		}

		else if (x_aux == TAB_TAM - 1 && y_aux != 0){ 
			dir = 'E'; 
			xa[0] = TAB_TAM-1; xa[1] = TAB_TAM-2; xa[2] = TAB_TAM-2;
			ya[0] = y_aux-1; ya[1] = y_aux-1; ya[2] = y_aux;
			decisao(xa, ya, &x_aux, &y_aux);
			gerar_coordenadas(i, x_aux, y_aux);
		}

		else if (x_aux == 0){
			dir = 'D'; 
			xa[0] = 0; xa[1] = 1; xa[2] = 1;
			ya[0] = y_aux-1; ya[1] = y_aux-1; ya[2] = y_aux;
			decisao(xa, ya, &x_aux, &y_aux);
			gerar_coordenadas(i, x_aux, y_aux);
		}
	
		else if (dir == 'D'){ 
			xa[0] = x_aux; xa[1] = x_aux+1; xa[2] = x_aux+1;
			ya[0] = y_aux-1; ya[1] = y_aux-1; ya[2] = y_aux;
			decisao (xa, ya, &x_aux, &y_aux);
			gerar_coordenadas(i, x_aux, y_aux);
		}
		
		else if (dir == 'E' && x_aux != 0){ 
			xa[0] = x_aux; xa[1] = x_aux-1; xa[2] = x_aux-1;
			ya[0] = y_aux-1; ya[1] = y_aux-1; ya[2] = y_aux;
			decisao (xa, ya, &x_aux, &y_aux);
			gerar_coordenadas(i, x_aux, y_aux);
		}
	}

	return i;
}

int e_path (int x, int y){

	int cx[40] = {0};
	int cy[40] = {0};
	int dim = pathFinder(cx, cy);
	int i;
	
	for(i = 0; i < dim; i++) 
		if (cx[i] == x && cy[i] == y) 
			return 1;

	return 0;

}

int main() {

	int x, y;

	scanf("%d %d", &x, &y);

	printf("%d\n", e_path(x, y));

	return 0;

}
