#include "../defines.h"

/**
@file score_board.h
Funções responsáveis para a determinação de permanência no scoreboard consoante os pontos do jogador 
*/


/**
\brief Função que copia caracter a caracter a string (que contem os pontos dos jogadores) que se 
encontra dentro de um ficheiro e retorna um apontador para essa string, excepto quando não existe 
ficheiro, neste caso é retornado "1 ___ ;0? 2 ___ ;0? 3 ___ ;0?"
@param fileName O nome do ficheiro
@returns A string contida no ficheiro ou retorna "1 ___ ;0? 2 ___ ;0? 3 ___ ;0?"
*/
char *get_score_string(char *fileName){
    
    FILE *file = fopen(fileName, "r");
    char *str = malloc(256); 
    size_t n = 0;
    int c;

    if (file == NULL) return "1 ___ ;0? 2 ___ ;0? 3 ___ ;0?";

    while ((c = fgetc(file)) != EOF) str[n++] = (char) c;
   
    str[n] = '\0';        

    return str;
}


/**
\brief Função que utilizando a função get_score_string determina os pontos do terceiro lugar na 
score board, desta forma caso o jogador obteve os mesmos ou mais pontos que o terciro lugar significa 
que o jogador tem direito a ser colocado na socre_board e por isso é retornado 1 (sucesso), caso contrário 
significa que o jogador não tem direito a permancer na score board e por isso é retornado 0 (insucesso)
@param e O estado
@returns 1 - sucesso ou 0 - insucesso
*/
int check_score(ESTADO e){

	char score_3[24];
	char *score = get_score_string(SCORE_FILE); //aqui temos uma string que contem tudo o que esta no ficheiro
	int i = 7; //primeiro ';'
	int v = 0;

	for (; score[i] != ';'; i++); //segundo ';'
	i++;

	for (; score[i] != ';'; i++); //terceiro ';'
	i++;  

	for (; score[i] != '?'; v++, i++) score_3[v] = score[i]; //sacamos aqui os pontos do 3º classificado
	score_3[v] = '\0';
	int trd_place = atoi(score_3);


	if (e.PONTOS >= trd_place && e.PONTOS > 0) return 1; //significa que vai para a kill_screen2()

	else return 0; //significa que vai para o kill_screen()

}