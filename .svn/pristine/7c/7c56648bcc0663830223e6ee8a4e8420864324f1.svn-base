#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "defines.h"
#include "estado.h"
#include "includes/path_finder.h" 
#include "includes/menu_inicial.h"
#include "includes/imprime_aba_lateral.h"
#include "includes/flood_fill.h"

int * converte_mapa (ESTADO e) {

	int m[TAB_TAM][TAB_TAM];
	int i, j;
	for (i = 0; i < TAB_TAM - 1; i++)
		for (j = 0; j < TAB_TAM - 1; j++){

			if (posicao_ocupada(ESTADO e, j, i)) m[i][j] = -1;
			else m[i][j] = 0;

		}
		j = 0;

	return m;
}
