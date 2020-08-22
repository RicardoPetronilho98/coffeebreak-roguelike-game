#include <stdio.h>
#include "../defines.h"
 /** 
@file file_struct_converter.h 
Definição das funções responsáveis por converter estado para ficheiro
e vice versa
 */

/** 
\brief Função utiliza as funções responsáveis pela conversão 
*/
void menu_facao(ESTADO e);
/** 
\brief Função utiliza as funções responsáveis pela conversão 
*/
ESTADO ler_estado(char *args);

/** 
\brief Função que pega no ficheiro de jogo e converte 
no estado de jogo, se o ficheiro existir irá converter
caso contrário o apontador dado para o ficheiro irá ser NULL
sendo que o programa não vai conseguir exectutar com o apontador NULL,  
a conversão é feita com o uso da função fread, para fechar 
o ficheiro apontado pelo fp é preciso utilizar o fclose 
@param  *fp Apontador para FILE, serve para abrir ficheiro e guardar no apontador
@param  e Estado que irá ser retornado
@returns ESTADO é retornado o estado e, o resultado de converter o ficheiro no estado
*/
ESTADO ficheiro2estado(){

	FILE *fp;							//apontador para um ficheiro
	ESTADO e;							//declarei uma variavel do tipo ESTADO
	fp = fopen(FILE_NAME,"r");		//isto abre o ficheiro para ler ("r") e guarda no apontador fp.
										//ATENÇÃO se o ficheiro não existir o fp vai ser igual a NULL
										//e o programa vai crashar ao tentar executar o fread
	if (fp){
		int r;
		r = fread(&e, sizeof(ESTADO), 1, fp);
		fclose(fp); 
		if (r) return e;
	}

	return e;							 
}
/** 
\brief Função que pega no estado de jogo e converte 
num ficheiro, se o ficheiro existir irá escrever os dados do 
estado num ficheiro caso contrário a função cria um vazio sendo que o apontador
aponta para esse novo ficheiro, sendo a escrita feita usando a função fwrite, 
para fechar o ficheiro apontado pelo fp no final utiliza-se o fclose
@param  *fp Apontador para FILE, irá servir para abrir com o intuito de escrever
e guardar nesse apontador 
@param  e Estado que irá ser convertido
@returns void É retornado o ficheiro, sendo portanto void o resultado
*/
void estado2ficheiro(ESTADO e){

	FILE *fp;							//apontador para um ficheiro
	fp=fopen(FILE_NAME,"w");     		//isto abre o ficheiro para escrever ("w") e guarda no apontador fp.
										//ATENÇÃO se o ficheiro não existir o programa cria um vazio e o fp aponta para este novo ficheiro
										//em principio deves de ter de te priocupar com isto mas convem saber
	fwrite(&e, sizeof(ESTADO), 1, fp);	//&e - apontador para a variavel ESTADO de onde a função fwrite vai ler
										//sizeof(ESTADO) - indica a função fwrite o tamanho do tipo de dados que vai escrever
										//1 - indica a função fwrite quantos "estados" vai escrever
										//fp - apontador do ficheiro onde vai escrever
	fclose(fp);							//fecha o ficheiro apontado por fp
}//