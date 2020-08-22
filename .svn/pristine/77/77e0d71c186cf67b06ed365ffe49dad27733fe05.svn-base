#include "defines.h"


#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Conjunto de typedefs de modo a definir novas estruturas para ser usadas nas funções
*/


/**
\brief Estrutura que armazena a informação relativa ao score
*/
typedef struct score_file {

	/**\brief Nome do jogador */
	char j[4];//nome do jogador

	/**\brief Pontuação do primeiro classificado */
	int fst_pontos;//pontuação de cada classificado
	/**\brief Pontuação do segundo classificado */
	int snd_pontos;
	/**\brief Pontuação do terceiro classificado */
	int trd_pontos;

	/**\brief Nome do primeiro classificado */
	char fst_name[4]; //nome de cada classificado
	/**\brief Nome do segundo classificado */
	char snd_name[4]; 
	/**\brief Nome do terceiro classificado */
	char trd_name[4];

} SCORE;



/**
\brief Estrutura que armazena uma posição
*/
typedef struct posicao { 
	/**\brief Coordenada x */
	char x;
	/**\brief Coordenada y */
	char y;

} POSICAO;

/**
\brief Estrutura que armazena dados relativos aos inimigos
*/
typedef struct inimigo{ //estrutura para inimigos

	/**\brief Vida dos inimigos */
	int hp;
	/**\brief Tipo dos inimigos */
	int type; //indica qual é o inimigo
	/**\brief Dano dos inimigos */
	int dmg;
	/**\brief Condição sobre os inimigos relativo as abilidades do jogador */
	int condition; // 0 -> Não esta sobre o efeito de nenhuma || 1 -> Vamp. Drain || 2 -> Frost Nova
	/**\brief Alcance dos inimigos */
	int raio;
	/**\brief Posição do inimigo */
	POSICAO pos;

} INIMIGO;


/**
\brief Estrutura que armazena dados relativos as abilidades
*/
typedef struct ability{ // estrutura p/ as abilidades (cd == cooldown (comeca a 0))
	/**\brief Flag para ativação das abilidades começa a 0 e passa para 1 quando se seleciona a abilidade */
	int active; // ative começa a 0, passa para 1 quando e selecionado para ativacao
	/**\brief Cooldown das abilidades, tempo de espera */
	int cd; // quando se seleciona o alvo da-se o efeito e cd vai para o nº de turnos precisos descendo 1 por turno

} ABILIDADE;


/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
	 
	/**\brief Pontos do jogador */
	int PONTOS;
	/**\brief Nivel do jogo */
	int NIVEL;
	/**\brief Turno (0 == jogador) (1 == Inimigos) */
	int TURN;
	/**\brief Quantidade de movimentos e ataques que o jogador tem */
	int MOVE;
	/**\brief O nº de inimigos */
	int num_inimigos;
	/**\brief O nº de obstáculos */
	int num_obstaculos;
	/**\brief Indicador de quantas coordenadas são utilizadas para alcançar a saída 
	desde a coordenada onde o jogador nasce */
	int dim;
	/**\brief Classe do Jogador */
	int CLASS;
	/**\brief Fação do Jogador */
	int SIDE;
	/**\brief Indicador se o jogo começou (1) ou não (0) ou está no menu How to play (2). */
	int START;
	/**\brief Dano do jogador */
	int dmg;
	/**\brief Vida do Jogador */
	int VIDA;
	/*\*brief Abilidade 1 */
	ABILIDADE ab1;
	/*\*brief Abilidade 2 */
	ABILIDADE ab2;
	/*\*brief SUPER */
	ABILIDADE SUPER;
	/**\brief A posição do jogador */
	POSICAO jog;
	/**\brief Array com as informações de cada inimigo */
	INIMIGO inimigo[MAX_INIMIGOS];
	/**\brief Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];
	/**\brief Array de coordenadas do caminho guardado em x */
	int cx[40];
	/**\brief Array de coordenadas do caminho guardado em y */
	int cy[40];

} ESTADO;


#endif


