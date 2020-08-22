#include "defines.h"
#include "estado.h"
#include "includes/score_board.h"

/**
@file score_board_main.c
Funções responsáveis pela atualização da score_string board
*/

char *get_score_string(char *fileName);


/**
\brief Função que copia o nome e pontos do 1 classificado para a estutura de dados s. 
A variavel i representa a posição atual na score_string. 
A variável auxiliar v representa a posição atual de cada string que está a ser copiada para a estrutura de dados s.
@param score_string A string que contem o score 
@param s apontador para a estrutura de dados que contem o score
@param i apontador para a posição atual na score_String
*/ 
void obtem_pontos_e_nome_do_1_classificado(char score_string[], SCORE *s, int *i){

	char score_1[24];
	int v = 0;

	for (*i = 2; score_string[*i] != ' '; v++, (*i)++) s->fst_name[v] = score_string[*i]; //sacamos aqui o nome do 1º classificado
	s->fst_name[v] = '\0'; 
	v = 0;
	(*i) += 2; //Aqui passamos p/ o 1º nmr da pontuaçao do 1º classificado

	for (; score_string[*i] != '?'; v++, (*i)++) score_1[v] = score_string[*i]; //sacamos aqui os pontos do 1º classificado
	score_1[v] = '\0';
	s->fst_pontos = atoi(score_1);
	(*i) += 4; //Aqui passamos p/ o 1º char do nome do 2º classificado
}


/**
\brief Função que copia o nome e pontos do 2 classificado para a estutura de dados s. 
A variavel i representa a posição atual na score_string, modificada anteriormente pela função 
ontem_pontos_e_nome_do_1_classificado. 
A variável auxiliar v representa a posição atual de cada string que está a ser copiada para a estrutura de dados s.
@param score_string A string que contem o score 
@param s apontador para a estrutura de dados que contem o score
@param i apontador para a posição atual na score_String
*/
void obtem_pontos_e_nome_do_2_classificado(char score_string[], SCORE *s, int *i){

	char score_2[24];
	int v = 0;

	for (; score_string[*i] != ' '; v++, (*i)++) s->snd_name[v] = score_string[*i]; //sacamos aqui o nome do 2º classificado
	s->snd_name[v] = '\0';
	v = 0;
	(*i) += 2; //Aqui passamos p/ o 1º nmr da pontuaçao do 2º classificado

	for (; score_string[*i] != '?'; v++, (*i)++) score_2[v] = score_string[*i]; //sacamos aqui os pontos do 2º classificado
	score_2[v] = '\0';
	s->snd_pontos = atoi(score_2);
	(*i) += 4; //Aqui passamos p/ o 1º char do nome do 3º classificado
}


/**
\brief Função que copia o nome e pontos do 3 classificado para a estutura de dados s. 
A variavel i representa a posição atual na score_string, modificada anteriormente pela função 
ontem_pontos_e_nome_do_2_classificado. 
A variável auxiliar v representa a posição atual de cada string que está a ser copiada para a estrutura de dados s.
@param score_string A string que contem o score 
@param s apontador para a estrutura de dados que contem o score
@param i apontador para a posição atual na score_String
*/
void obtem_pontos_e_nome_do_3_classificado(char score_string[], SCORE *s, int *i){

	char score_3[24];
	int v = 0;

	for (; score_string[*i] != ' '; v++, (*i)++) s->trd_name[v] = score_string[*i]; //sacamos aqui o nome do 3º classificado
	s->trd_name[v] = '\0';
	v = 0;
	(*i) += 2; //Aqui passamos p/ o 1º nmr da pontuaçao do 3º classificado

	for (; score_string[*i] != '?'; v++, (*i)++) score_3[v] = score_string[*i]; //sacamos aqui os pontos do 3º classificado
	score_3[v] = '\0';
	s->trd_pontos = atoi(score_3);
}


/**
\brief Função que copia os nomes e pontos dos 1, 2 e 3 classificados para a estutura de dados s. 
A variável i é transmitida nas 3 funções de forma a que não se perca informação em 
relação á posição atualizada na score_string.
@param score_string A string que contem o score 
@param s A estrutura de dados que contem o score
@returns A estrutura de dados que contem o score atualizada
*/
SCORE obtem_pontos_e_nome_de_todos_os_classificados(char score_string[], SCORE s){

	int i;

	obtem_pontos_e_nome_do_1_classificado(score_string, &s, &i);
	obtem_pontos_e_nome_do_2_classificado(score_string, &s, &i);
	obtem_pontos_e_nome_do_3_classificado(score_string, &s, &i);

	return s;
}


/**
\brief Função que atualiza a estutura de dados do score, modificando a pontuação e nome de 
cada classificado consoante a pontuação do jogador. A função não necessita de "else", ou seja
do caso em que a pontuação do jogador seja menor que a pontuação do 3 classificado da score board, uma
vez que apenas pontuações que alterem a score_board evocam esta CGI.
@param pontos A pontuação do jogador
@param s A estrutura de dados que contem o score
@returns A estrutura de dados que contem o score atualizada
*/
SCORE atualiza_classificados(int pontos, SCORE s){

	if (pontos >= s.fst_pontos){

		s.trd_pontos = s.snd_pontos;
		strcpy(s.trd_name, s.snd_name);
		s.snd_pontos = s.fst_pontos;
		strcpy(s.snd_name, s.fst_name);
		s.fst_pontos = pontos;
		strcpy(s.fst_name, s.j);

	} else if (pontos <= s.fst_pontos && pontos >= s.snd_pontos){

		s.trd_pontos = s.snd_pontos;
		strcpy(s.trd_name, s.snd_name);
		s.snd_pontos = pontos;
		strcpy(s.snd_name, s.j);

	} else if (pontos <= s.snd_pontos && pontos >= s.trd_pontos){

		s.trd_pontos = pontos;
		strcpy(s.trd_name, s.j);
	}

	return s;
}

/**
\brief Função que cria uma string com os nomes e pontos dos 3 classificados atualizados, e 
grava essa string no ficheiro do score. A string é gerada com o formato "C NNN ;PONTOS? ..." 
onde C é o lugar do classificado, NNN é o nome do classificado e PONTOS é a pontuação do classificado. 
Este formato facilita a obtenção de cada nome e pontuação de cada classificado na função 
obtem_pontos_e_nome_de_todos_os_classificados.
@param s A estrutura de dados que contem o score
*/
void criar_novo_ficheiro_de_score(SCORE s){

	char new_score_string[128];

	sprintf(new_score_string, "1 %s ;%d? 2 %s ;%d? 3 %s ;%d?", s.fst_name, s.fst_pontos, s.snd_name, s.snd_pontos, s.trd_name, s.trd_pontos);

	FILE *score_file = fopen(SCORE_FILE, "w");
	fputs(new_score_string, score_file);
	fclose(score_file);

}


/**
\brief Função que atualiza a estrutura de dados através das funções 
obtem_pontos_e_nome_de_todos_os_classificados e atualiza_classificados
de seguida grava a nova string que contem o score no ficheiro do score através da função
criar_novo_ficheiro_de_score.
@param pontos A pontuação do jogador 
@param a A primeira letra do nome do jogador
@param b A segunda letra do nome do jogador
@param c A terceira letra do nome do jogador
@returns A estrutura de dados que contem o score atualizada
*/
SCORE atualiza_estrutura_e_ficheiro_de_score(int pontos, int a, int b, int c){
	
	char *score_string = get_score_string(SCORE_FILE); 
	remove(SCORE_FILE); 

	SCORE s;

	s.j[0] = a; s.j[1] = b; s.j[2] = c; s.j[3] = '\0'; 

	s = obtem_pontos_e_nome_de_todos_os_classificados(score_string, s);

	s = atualiza_classificados(pontos, s);

	criar_novo_ficheiro_de_score(s);

	return s;
}

/**
\brief Função que imprime o botão new_game e cria um link em cima do mesmo de forma a que o utilizador
possa voltar para o menu inicial do jogo.
*/
void imprime_botao_new_game(){

	char link[] = "http://localhost/cgi-bin/main?"; 

	ABRIR_LINK(link);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", ESCALA - 30, 8 * ESCALA, 145, 35, IMAGE_PATH "button_new-game.png");
	FECHAR_LINK;
}

/**
\brief Função que imprime o nome e pontos do 1 classificado no menu da score board.
Para tal é criado a string auxiliar fst de forma a que imprima a classificação com o devido formato.
@param s A estrutura de dados que contem o score
*/
void imprime_primeiro_classificado(SCORE s){

	char fst[128];

	sprintf(fst, "%s_____________________________%d", s.fst_name, s.fst_pontos);

	if (fst[0] != '_') printf("<text x=%d y=%d fill=%s >%s </text>", 2 * ESCALA, ESCALA + 15, "#000000", fst);
	else printf("<text x=%d y=%d fill=%s >AINDA SEM 1 LUGAR!</text>", 2 * ESCALA, ESCALA + 15, "#000000");
}


/**
\brief Função que imprime o nome e pontos do 2 classificado no menu da score board.
Para tal é criado a string auxiliar snd de forma a que imprima a classificação com o devido formato.
@param s A estrutura de dados que contem o score
*/
void imprime_segundo_classificado(SCORE s){

	char snd[128];

	sprintf(snd, "%s_____________________________%d", s.snd_name, s.snd_pontos);

	if (snd[0] != '_') printf("<text x=%d y=%d fill=%s >%s </text>", 2 * ESCALA, 4 * ESCALA - 15, "#000000", snd);
	else printf("<text x=%d y=%d fill=%s >AINDA SEM 2 LUGAR!</text>", 2 * ESCALA, 4 * ESCALA - 15, "#000000");

}


/**
\brief Função que imprime o nome e pontos do 3 classificado no menu da score board.
Para tal é criado a string auxiliar trd de forma a que imprima a classificação com o devido formato.
@param s A estrutura de dados que contem o score
*/
void imprime_terceiro_classificado(SCORE s){

	char trd[128];

	sprintf(trd, "%s_____________________________%d", s.trd_name, s.trd_pontos);

	if (trd[0] != '_') printf("<text x=%d y=%d fill=%s >%s </text>", 2 * ESCALA, 6 * ESCALA + 2, "#000000", trd);
	else printf("<text x=%d y=%d fill=%s >AINDA SEM 3 LUGAR!</text>", 2 * ESCALA, 6 * ESCALA + 2, "#000000");
}


/**
\brief Função que imprime o menu score board. Para tal atualiza primeiro a estrutura de dados do score,
de seguida imprime a imagem 1_2_3.png e imprime os 3 classificados atraves das funções
imprime_primeiro_classificado, imprime_segundo_classificado e imprime_terceiro_classificado. Finalmente
imprime o botao new_game atraves da função imprime_botao_new_game.
@param pontos A pontuação do jogador 
@param a A primeira letra do nome do jogador
@param b A segunda letra do nome do jogador
@param c A terceira letra do nome do jogador
*/
void print_score_board(int pontos, int a, int b, int c){	

	SCORE s = atualiza_estrutura_e_ficheiro_de_score(pontos, a, b, c);

	IMAGEM(0, 0, 400, "1_2_3.png");

	imprime_primeiro_classificado(s);
	imprime_segundo_classificado(s);
	imprime_terceiro_classificado(s);
	imprime_botao_new_game();

}


/**
\brief Função que imprime as imagens das setas superiores utilizadas para mudar o nome do jogador e cria 
um link sobre as mesmas. 
@param pontos A pontuação do jogador 
@param a A primeira letra do nome do jogador
@param b A segunda letra do nome do jogador
@param c A terceira letra do nome do jogador
*/
void criar_link_setas_superiores(int submit, int pontos, int a, int b, int c){

	char link0[LINK_BUFFER];
	char link1[LINK_BUFFER];
	char link2[LINK_BUFFER];

	CRIAR_LINK2(link0, pontos, a + 1, b, c, submit);
	ABRIR_LINK(link0);
	IMAGEM(3, 1, 2*ESCALA, "uparrow.png");
	FECHAR_LINK;

	CRIAR_LINK2(link1, pontos, a, b + 1, c, submit);
	ABRIR_LINK(link1);
	IMAGEM(6, 1, 2*ESCALA, "uparrow.png");
	FECHAR_LINK;

	CRIAR_LINK2(link2, pontos, a , b, c + 1, submit);
	ABRIR_LINK(link2);
	IMAGEM(9, 1, 2*ESCALA, "uparrow.png");
	FECHAR_LINK;
}

/**
\brief Função que imprime as imagens das setas inferiores utilizadas para mudar o nome do jogador e cria 
um link sobre as mesmas. 
@param pontos A pontuação do jogador 
@param a A primeira letra do nome do jogador
@param b A segunda letra do nome do jogador
@param c A terceira letra do nome do jogador
*/
void criar_link_setas_inferiores(int submit, int pontos, int a, int b, int c){

	char link3[LINK_BUFFER];
	char link4[LINK_BUFFER];
	char link5[LINK_BUFFER];

	CRIAR_LINK2(link3, pontos, a - 1, b, c, submit);
	ABRIR_LINK(link3);
	IMAGEM(3, 4, 2*ESCALA, "downarrow.png");
	FECHAR_LINK;
	
	CRIAR_LINK2(link4, pontos, a, b - 1, c, submit);
	ABRIR_LINK(link4);
	IMAGEM(6, 4, 2*ESCALA, "downarrow.png");
	FECHAR_LINK;

	CRIAR_LINK2(link5, pontos, a, b, c - 1, submit);
	ABRIR_LINK(link5);
	IMAGEM(9, 4, 2*ESCALA, "downarrow.png");
	FECHAR_LINK;
}

/**
\brief Função que imprime a imagem do botão submit e cria um link sobre a mesma para que o menu da 
score board seja atualizado.
@param pontos A pontuação do jogador 
@param a A primeira letra do nome do jogador
@param b A segunda letra do nome do jogador
@param c A terceira letra do nome do jogador
*/
void imprime_botao_submit(int pontos, int a, int b, int c){

	char link6[LINK_BUFFER];

	CRIAR_LINK2(link6, pontos, a, b, c, 1);
	ABRIR_LINK(link6);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 600, 600, 111, 40, IMAGE_PATH "button_submit.png");
	FECHAR_LINK;
}

/**
\brief Função que imrpime as letras do nome do jogador entre as imagens das setas. 
Caso o jogador pretenda utilizar o nome escolhido, carraga no botao submit.
@param pontos A pontuação do jogador 
@param a A primeira letra do nome do jogador
@param b A segunda letra do nome do jogador
@param c A terceira letra do nome do jogador
@param submit O número utlizado para a confirmação do nome do jogador
*/
void ask_for_name(int pontos, int a, int b, int c, int submit){

	if (a < 65) a = 90;
	if (b < 65) b = 90;
	if (c < 65) c = 90;

	if (a > 90) a = 65;
	if (b > 90) b = 65;
	if (c > 90) c = 65;

	printf("<text x=%d y=%d fill=%s >%c </text>", 350, 300, "#000000", a);
	printf("<text x=%d y=%d fill=%s >%c </text>", 650, 300, "#000000", b);
	printf("<text x=%d y=%d fill=%s >%c </text>", 950, 300, "#000000", c);

	criar_link_setas_superiores(submit, pontos, a, b, c);
	criar_link_setas_inferiores(submit, pontos, a, b, c);
	imprime_botao_submit(pontos, a, b, c);

}  


/**
\brief Função que utilizando o link (args) desodifica o mesmo, colocando a informação 
descodificada no (array), desta forma o conjunto de números que o link contem é utilizado nas
restantes funções.
@param args apontador para a string que contem o link da CGI
@param array apontador para o array que contem a informação descodificada do link da CGI
*/
void descodifica_link_2(char *args, int *array){
	
	int i = 0;
	int v = 0;
	char aux[24];

	get_aux; 
	i++;

	array[0] = atoi(aux); //pontos

	get_aux; 
	i++;

	array[1] =  atoi(aux); //a

	get_aux;
	i++;

	array[2] = atoi(aux); //b

	get_aux;
	i++;

	array[3] = atoi(aux); //c

	aux[0] = args[i];
	aux[1] = '\0';
	
	array[4] =  atoi(aux); //submit
}


/**
\brief Função que está constantemente a ser evocada pela CGI que determina a evocação de todas
as restantes funções.
*/
int main(){

	COMECAR_HTML;
	ABRIR_SVG(SVG_TAM, SVG_TAM);

	int array[5];
	descodifica_link_2(getenv("QUERY_STRING"), array);

	int pontos = array[0];
	int a = array[1];
	int b = array[2];
	int c = array[3];
	int submit = array[4];

	if (submit){
		print_score_board(pontos, a, b, c);
		return 0;
	}

	else ask_for_name(pontos, a, b, c, submit);

	FECHAR_SVG;
	return 0;
}