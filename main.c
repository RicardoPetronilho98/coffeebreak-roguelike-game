#include "defines.h"
#include "estado.h"
#include "includes/path_finder.h" 
#include "includes/menus.h"
#include "includes/imprime_aba_lateral.h"
#include "includes/flood_fill.h"
#include "includes/combat_sys.h"
#include "includes/file_struct_converter.h"
#include "includes/score_board.h"
#include "includes/abilidades.h"

/**
@file main.c
Ficheiro central do jogo.
*/

/**
\brief Função que indica a quantidade de obstaculos e inimigos que são gerados em cada nível,
caso o nível seja mais elevado, é estabelecido uma quantidade máxima de elementos gerados (max), caso
contrário, o mapa não suportava tantos obstaculos e inimigos. O no. de obstaculos por nivel é: nivel * 2,
o no. de inimigos por nivel é: nivel * 3. 
No. max de obtaculos = ((tamanho do mapa)^2 - (no. de posicoes reservadas pela função pathfinder) - (tamanho do mapa)/4)/3
No. max de inimigos = ((tamanho do mapa)^2 - (no. de posicoes reservadas pela função pathfinder) - (tamanho do mapa)/4)/2
@param e ---> estado do jogo
@param v ---> valor que distingue obstaculos (1) de inimigos (0)
@returns num ---> no. de obstaculos ou inimigos por nivel
*/
int inimigos_ou_obstaculos_por_nivel (ESTADO e, int v){

	int max =  (TAB_TAM * TAB_TAM) - e.dim - TAB_TAM / 4; /* este é o máximo possivel de elementos 
	gerados, é guardado espaço para o caminho desde a a coordenada onde o jogador nasce até á saída,
	e também mais algum espaço para que o mapa não fique demasiado cheio, e também para armazenar 
	bonus no mapa quando for caso para isso */ 
	
	int num; /* no. a ser retornado*/
	
	int num_obs = e.NIVEL * 2; /* no. de obstáculos por nivel*/
	int num_ini = e.NIVEL * 3; /* no. de inimigos por nivel*/

	if (num_obs + num_ini > max) { /* defenição de máximos*/
		if (v) num = max / 3; /* max de obstáculos*/
		else num = max / 2; /* max de inimigos*/
	}

	else {
		if (v) num = num_obs; /* no de obstáculos*/
		else num = num_ini; /* no de inimigos*/
	}

	return num; /* valor total de ou obstáculos ou inimigos*/
}

/**
\brief Função que imprime cada casa do tabuleiro com base na posição (x,y).
(0,0) ---> Saida do mapa, fundo de casa par e imagem do portal.
(idx == 0) ou seja posição par ---> fundo par (wasteland 1)
(idx != 0) ou seja posição impar ---> fundo impar (wasteland 2)
@param x ---> coordenada x
@param y ---> coordenada y
*/
void imprime_casa(int x, int y) {
	
	int idx = (x + y) % 2; /* utilizada para distinguir casas pares de impares*/
	
	if (x == 0 && y == 0){ /* impressao da saida*/
		IMAGEM(x, y, ESCALA, "wasteland1.png"); /* fundo*/
		IMAGEM(x, y, ESCALA, "portal_open.png"); /* saída*/
	} 
	
	else if (idx == 0) /* casa par*/
		IMAGEM(x, y, ESCALA, "wasteland1.png"); /* fundo par*/
	
	else /* casa impar*/
		IMAGEM(x, y, ESCALA, "wasteland2.png"); /* fundo impar*/
}

/**
\brief Função que verifica se uma posicao p e igual as coordenadas (x,y).
@param p ---> posicao a testar
@param x ---> coordenada x
@param y ---> coordenada y
@returns 1 se iguais, 0 c.c.
*/
int posicao_igual (POSICAO p, int x, int y) {
	
	return p.x == x && p.y == y; /* retorna 1 sse p.x == x && p.y == y cc 0*/
}

/**
\brief Verifica o array de obstáculos guardado no estado e compara a posição de cada obstáculo com (x,y),
até chegar ao fim do array ou até encontrar um que tenha a mesma (x,y) com posição.
@param e ---> estado e (para verificar as pos dos obstaculos)
@param x ---> coord x a testar
@param y ---> coord y a testar
@returns 1 se encontrar um obstáculo com a posição (x,y), 0 c.c.
*/
int tem_obstaculo(ESTADO e, int x, int y) {
	
	int i;
	
	for (i = 0; i < e.num_obstaculos; i++) /* percorre todos os obstaculos*/
		if (posicao_igual (e.obstaculo[i], x ,y)) /* testa se a pos e igual a do obstaculo e (x,y)*/
			return 1; 
	
	return 0; 	
}

/**
\brief Verifica o array de inimigos guardado no estado e compara a posição de cada obstáculo com (x,y),
até chegar ao fim do array ou até encontrar um que tenha a mesma (x,y) com posição.
@param e ---> estado e (para verificar as pos dos inimigos)
@param x ---> coord x a testar
@param y ---> coord y a testar
@returns 1 se encontrar um inimigo com a posição (x,y), 0 c.c.
*/
int tem_inimigo(ESTADO e, int x, int y) {
	
	int i;
	
	for (i = 0; i < e.num_inimigos; i++) /* percorre todos os inimigos*/
		if (posicao_igual (e.inimigo[i].pos, x , y) && e.inimigo[i].hp > 0)  /*f testa se a pos e igual a do inimigo e (x,y)*/
			return 1; /* TRUE*/
	
	return 0; /* FALSE*/		
}

/**
\brief Verifica o estado pela posição do jogador e compara-a com (x,y)
@param e ---> estado e (para verificar as pos do jogador)
@param x ---> coord x a testar
@param y ---> coord y a testar
@returns 1 se o jogador tiver posição (x,y), 0 c.c.
*/
int tem_jogador (ESTADO e, int x, int y) {

	return posicao_igual (e.jog, x, y); /*testa se a pos do jog e igual a (x,y)*/
}


/**
\brief Função que verifica se uma determinada coordenada (x,y) faz parte do caminho gerado pela função pathFinder.
Percorre os arrays cx e cy guardados no estado comparando x com o elemento na posição i de cx, e y com o elemneto
na posição i de cy.
@param e ---> estado para verificar cx e cy
@param x ---> coord x
@param y ---> coord y
@returns 1 se em cx existir x e em cy existir y, 0 c.c.
*/
int e_path (ESTADO e, int x, int y){

	int i;

	for(i = 0; i < e.dim; i++) /* percorre cx e cy*/
		if (e.cx[i] == x && e.cy[i] == y) /*testa se as coords existem em cx e cy*/
			return 1; /* TRUE*/

	return 0; /* FALSE*/

}

/**
\brief Verifica se a posicao (x,y) esta ocupada pelo jogador, um obstaculo ou um inimigo.
@param e ---> estado que contem pos do jog, as pos dos inimigos e dos obstaculos
@param x ---> coord x
@param y ---> coord y
@returns 1 se a posição estiver ocupada pelo jogador, um inimigo ou um obstáculo; 0 c.c.
*/
int posicao_ocupada(ESTADO e, int x, int y) {

	return tem_inimigo(e, x, y) || tem_obstaculo (e, x, y) || tem_jogador (e, x, y); /**\brief 1 se um dos quatro se verificar, 0 cc*/

}

/**
\brief Função que atualiza as caracteristicas de cada inimigo.
@param M ---> apontador para o inimigo a ser atualizado
@param num_inimigos ---> no. do inimigo a ser gerado
@param e ---> O estado de jogo
*/
void determina_inimigo(INIMIGO *M, int num_inimigos, ESTADO e){    

	if ((e.NIVEL % 5) == 0 && num_inimigos == 1){ //inimigo BOSS

		M->hp = vida_por_nivel(e) * 3 + 250;
		M->dmg = dano_por_nivel(e);
		M->type = 2;
		M->raio = 2;
		return;
	}

	else if (e.NIVEL >= 7 && num_inimigos >= 2 && num_inimigos <= 4){ // inimigo guardiao apartir do nivel 7

		M->hp = vida_por_nivel(e) + 100;
		M->dmg = dano_por_nivel(e) / 4;
		M->raio = 1;
		M->type = 3;
		
		if (!posicao_ocupada(e, 1, 1)){ 
			M->pos.x = M->pos.y = 1;
			return;
		}
		
		if (!posicao_ocupada(e, 0, 1)){ 
			M->pos.x = 0; M->pos.y = 1;
			return;
		}
		
		if (!posicao_ocupada(e, 1, 0)){ 
			M->pos.x = 1; M->pos.y = 0;
			return;
		}
	}

	else if ((num_inimigos % 3) == 0){ //inimigo arqueiro

		M->hp = vida_por_nivel(e) / 3 + 20; 
		M->dmg = dano_por_nivel(e) / 2;
		M->type = 1;
		M->raio = 2;
		return;
	}

	else { //inimigo cavaleiro

		M->hp = vida_por_nivel(e) / 2 + 20; 
		M->dmg = dano_por_nivel(e) / 4;
		M->type = 0;
		M->raio = 1;
	}
}


/**
\brief Função que inicializa ou um obstaculo ou um inimigo. Randomiza posições no mapa até encontrar uma válida.
Encontrando essa posição, no caso de um obstáculo atualiza a sua posição e incrementa a varável que altera a posição
no array de obstáculos. No caso de um inimigo o mesmo processo se dá, contudo também se atribui um dano e uma vida ao inimigo.
@param e ---> estado que sera alterado
@param v ---> se v == 1 inicializa obstaculos, v == 0 inicializa inimigos
@returns e ---> estado com mais um obstáculo ou inimigo inicializado
*/
ESTADO inic_obs_ou_ini (ESTADO e, int v) { 

	int X; /* coord x onde vai ser colocado o obs ou inimigo*/
	int Y; /* coord y onde vai ser colocado o obs ou inimigo*/

	do {
		X = random() %  TAB_TAM;
		Y = random() %  TAB_TAM;
	} while (posicao_ocupada(e, X, Y) || e_path(e, X, Y) || (X == 0 && Y == 0)); /* enquanto a pos nao for valida (nao estivar ocupada nao for a saida ou parte das coords reservadas) escolhe random coords*/

	if (v) { //1 por isso gera obstaculos
			e.obstaculo[e.num_obstaculos].x = X; /* atualiza coord x do obtaculo*/
			e.obstaculo[e.num_obstaculos].y = Y; /* atualiza coord x do obtaculo*/
			e.num_obstaculos++; /* incrementa-se o que percorre o array*/
		}
	else {//0 por isso gera inimigos
			e.inimigo[e.num_inimigos].pos.x = X; /* atualiza coord x do inimigo */
			e.inimigo[e.num_inimigos].pos.y = Y; /* atualiza coord y do inimigo */
			determina_inimigo(&e.inimigo[e.num_inimigos], e.num_inimigos + 1, e);
			e.num_inimigos++; /* incrementa-se o que percorre o array*/
	}

	return e; /* retorna o estado atualizado*/
}

/**
\brief Função que inicializa todos os obstáculos no nivel, invocando a função inic_obs_ou_ini com v == 1, enquanto
nao se alcançar o máximo de obstáculos nesse nível.
@param e ---> estado a ser alterado
@param num ---> max de obstaculos
@returns e ---> estado com todos os obstáculos inicializados
*/
ESTADO inicializar_obstaculos (ESTADO e, int num) {

	int i;
	
	for (i = 0; i < num; i++) /* ate chegar ao max de obstaculos*/
		e = inic_obs_ou_ini(e, 1); /* funcao que inicializa 1 obstaculo*/
	
	return e; /* retorna o estado alterado*/
}

/**
\brief Função que inicializa todos os inimigos no nivel, invocando a função inic_obs_ou_ini com v == 0, enquanto
nao se alcançar o máximo de inimigos nesse nível.
@param e ---> estado a ser alterado
@param num ---> max de inimigos
@returns e ---> estado com todos os inimigos inicializados
*/
ESTADO inicializar_inimigos (ESTADO e, int num) {

	int i;
	
	for (i = 0; i < num; i++) /* ate chegar ao max de inimigos*/
		e = inic_obs_ou_ini(e, 0); /* funcao que inicializa 1 inimigo*/
	
	return e; /* retorna o estado alterado*/
}

/**
\brief testa se uma posicao pertence aos limites do mapa
@param x ---> coord x
@param y ---> coord y
@returns 1 se a posição estiver dentro dos limites do mapa, 0 c.c.
*/
int posicao_valida(int x, int y) {
	return x >= 0 && y >= 0 && x < TAB_TAM && y < TAB_TAM; /* True (1) se tudo isto se cumprir, false (0) cc*/
}

/**
\brief Função que cria cada link para o movimento do jogador. Neste link, a nova posição do jogador será (e.jog.x + dx, e.jog.y + dy).
O link só é criado se a nova posição for válida e nao estiver ocupada. Reduz-se ainda o no. de jogadas que o jogador terá nesse turno.
@param e ---> estado de jogo
@param dx ---> deslocamento x
@param dy ---> deslocamento y
*/
void imprime_movimento(ESTADO e, int dx, int dy) {
	
	int x = e.jog.x + dx; /* nova coord x*/
	int y = e.jog.y + dy; /* nova coord y*/

	char link[LINK_BUFFER]; /* novo link*/

	if(!posicao_valida(x, y)) /* só pode imprimir dentro dos limites do tabuleiro */
		return;
	if (posicao_ocupada(e, x, y)) 
		return; /* não pode imprimir em casas onde ja tem algo */

	e.MOVE--; /* reduz-se o nmr de jogadas que o jogador tem*/

	CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, x, y, e.MOVE, e.START, 0, e.ab1.active, e.ab2.active, e.SUPER.active, e.ab1.cd, e.ab2.cd, e.SUPER.cd, e.VIDA, e.dmg); /**\brief link para o novo estado*/
	
	ABRIR_LINK(link); /*abre link na casa*/
	imprime_casa(x, y); /* imprime a casa com o link*/
	FECHAR_LINK; /* fecha link*/

} 


/**
\brief Função que imprime os links de ataque e movimento dos cavaleiros.
@param e ---> apontador para o estado de jogo.
@param r O raio de movimento e ataque do caveleiro 
*/
void imprime_movimentos_e_ataques_dos_cavaleiros(ESTADO *e, int r){

	RADIAL_SCAN(r){

		if (r == 2) e->ab2.active = 0; // FAZ RESET DA AB_2 DO CAVALEIRO HUMANO
			
		if (ck != 0 || lk != 0){
			imprime_movimento(*e, ck,  lk);
			J_Attack(*e, ck, lk);
		}
	}
}


/**
\brief Função que imprime os links de ataque e movimentos dos magos.
@param e ---> estado de jogo.
*/
void imprime_movimentos_e_ataques_dos_magos(ESTADO e){

	RADIAL_SCAN(1){

		if (ck != 0 || lk != 0) 
			imprime_movimento(e, ck,  lk);
	}

	RADIAL_SCAN(2){ //podem atacar a 2 casas de distancia

		if (ck != 0 || lk != 0)
			J_Attack(e, ck, lk);
	}
}


/**
\brief Função que imprime os links de ataque e movimento do jogador. Para os movimentos invoca-se a função imprime_movimento
com raio 1, excepto no caso do cavaleiro humano com a segunda abilidade ativa em que o raio é de 2. Para ataques depende-se da classe.
Os magos têm um raio de ataque de 2 unidades e o cavaleiro humano com a segunda abilidade ativa também. Os cavaleiros têm raio de ataque 1.
@param e ---> estado de jogo.
*/
void imprime_movimentos_e_ataques(ESTADO e) {
	
	int r = 1;

	if (e.CLASS == 1 && e.SIDE == 0 && e.SUPER.cd == 1) e.SUPER.cd = 0; //reset do SUPER do mago orc

	if (e.SIDE == 1 && e.CLASS == 0 && e.ab2.active == 1) r = 2;  //efeito da AB 2 do cavaleiro humano

	if (e.CLASS == 0) imprime_movimentos_e_ataques_dos_cavaleiros(&e, r);

	else imprime_movimentos_e_ataques_dos_magos(e);

}


/**
\brief Função invocada no início de cada nível para inicializar os obstáculos e inimigos de acordo com o nível.
Incrementa a pontuação do jogador, restora a vida do jogador e incrementa-a, incrementa o dano do jogador. Faz reset
ás abilidades e se o nivel for > 3, concede a super abilidade ao jogador.
@param nivel ---> nivel anterior do jogador
@param pontos ---> pontos acumulados do jogador
@param CLASS ---> classe do jogador
@param SIDE ---> fação do jogador
@returns e ---> estado atualizado para o nivel correspondente
*/
ESTADO inicializar_nivel(int nivel, int pontos, int CLASS, int SIDE) {

	int num;
	
	ESTADO e = {0}; /* tudo na struct é inicializado a 0
	
	NOTA: como a estrutura de dados faz o "reset", as informações que precisam de 
	ser transmitidas de, nivel a nivel, sao dadas como argumentos */

	e.PONTOS = pontos + 10; 
	e.NIVEL = nivel + 1; //MUDAR DEPOIS!!!!!!!!!!!!!!!!!!!!!!!!!

	e.ab1.active = e.ab2.active = 0;
	if (e.NIVEL >= 3) e.SUPER.active = 1; // so tem o super depois do 3º Nivel

	e.CLASS = CLASS;
	e.SIDE = SIDE;

	if (e.CLASS == 0 && e.SIDE == 0) e.ab1.active = 1; //passiva o cavaleiro orc (constantemente ativada)
	e.MOVE = 2; //o nº de jogadas do jogador começa
	e.jog.x = e.jog.y = TAB_TAM - 1; //coordenadas iniciais do jogador
	
	e.dim = pathFinder(e.cx, e.cy); /* quantidade de coordenadas utilizadas para criar o 
	caminho livre de obstaculos e inimigos desde a coordenada onde o jogador nasce até á saída */
	
	e.VIDA = vida_por_nivel(e); //a vida é regenerada no inicio de cada nivel 
	e.dmg = dano_por_nivel(e);
	num = inimigos_ou_obstaculos_por_nivel(e, 0); //0 por isso determina quantos inimigos sao gerados

	e = inicializar_inimigos(e, num); 
	
	num = inimigos_ou_obstaculos_por_nivel(e, 1); //1 por isso determina quantos obstaculos sao gerados
	e = inicializar_obstaculos(e, num); 
	
	return e;
}

/**
\brief Função que imprime o jogador com base na classe e fação escolhida. Também trata da impressão de
ataques e movimentos pela invocação da função imprime_movimentos_e_ataques.
@param e ---> estado de jogo
*/
void imprime_jogador(ESTADO e) {

	if (e.SIDE == 1 && e.CLASS == 0){
		IMAGEM(e.jog.x, e.jog.y, ESCALA, cav_hmn_img); 
		imprime_abilidades_cav_hum(e);
	}

	if (e.SIDE == 1 && e.CLASS == 1){
		IMAGEM(e.jog.x, e.jog.y, ESCALA, mage_hmn_img);
		imprime_abilidades_mage_hum(e);
	}

	if (e.SIDE == 0 && e.CLASS == 0){
		IMAGEM(e.jog.x, e.jog.y, ESCALA, cav_orc_img);
		imprime_abilidades_cav_orc(e);
	}  
	
	if (e.SIDE == 0 && e.CLASS == 1){
		IMAGEM(e.jog.x, e.jog.y, ESCALA, mage_orc_img);
		imprime_abilidades_mage_orc(e);
	}

	if (e.TURN == 0 && e.MOVE > 0) imprime_movimentos_e_ataques(e);
}

/**
\brief Função que imprime os inimigos que jogam contra os humanos consoante o tipo de inimigo.
@param M ---> inimigo a ser impresso.
*/
void imprime_inimigo_para_humanos(INIMIGO M){

	if (M.type == 0) IMAGEM(M.pos.x, M.pos.y, ESCALA, "npc_orc_grunt.png");
	else if (M.type == 1) IMAGEM(M.pos.x, M.pos.y, ESCALA, "npc_troll_ranged.png");
	else if (M.type == 2) IMAGEM(M.pos.x, M.pos.y, ESCALA, "npc_dragon.png");
	else IMAGEM(M.pos.x, M.pos.y, ESCALA, "orc_guardian.png");

}

/**
\brief Função que imprime os inimigos que jogam contra os orcs consoante o tipo de inimigo.
@param M ---> inimigo a ser impresso.
*/
void imprime_inimigo_para_orcs(INIMIGO M){

	if (M.type == 0) IMAGEM(M.pos.x, M.pos.y, ESCALA, "npc_warrior.png");
	else if (M.type == 1) IMAGEM(M.pos.x, M.pos.y, ESCALA, "npc_archer.png");
	else if (M.type == 2) IMAGEM(M.pos.x, M.pos.y, ESCALA, "npc_gryphon_rider.png");
	else IMAGEM(M.pos.x, M.pos.y, ESCALA, "humano_guardian.png");
}


/**
\brief Função que imprime os inimigos vivos no mapa.
@param e ---> estado de jogo.
*/
void imprime_inimigos(ESTADO e) {
	
	int i;
	
	for(i = 0; i < e.num_inimigos; i++)
		if (e.inimigo[i].hp > 0){
			if (e.SIDE == 1) imprime_inimigo_para_humanos(e.inimigo[i]);
			else imprime_inimigo_para_orcs(e.inimigo[i]);
		}
}



/**
\brief Função que imprime os obstáculos no mapa.
@param e ---> estado de jogo
*/
void imprime_obstaculos(ESTADO e) {
	
	int i;
	
	for(i = 0; i < e.num_obstaculos; i++)
		IMAGEM(e.obstaculo[i].x, e.obstaculo[i].y, ESCALA, "lava_pool1.png");
}

/**
\brief Função que imprime o tabuleiro de jogo invocando para cada posição (x,y) a função imprime casa.
@param dim ---> dimensão do tabuleiro de jogo
*/
void imprime_tabueleiro(int dim) {
	
	int x, y;
	
	for(y = 0; y < dim; y++)
		for(x = 0; x < dim; x++)
			imprime_casa(x, y);
	IMAGEM(0, 0, ESCALA, "portal_closed.png"); //quando o jogador esta longe do portal imprime o portal fechado
}


/**
\brief Função que verifica se a abilidade 1 do mago orc esta ativada, caso afirmativo, 
o efeito da abilidade é executada.
@param *e ---> apontador para os estado de jogo ser alterado
*/
void efeito_da_AB1_mago_orc(ESTADO *e, char aux[]){

	int i;

	if (e->CLASS == 1 && e->SIDE == 0 && e->ab1.active == 1){

		RADIAL_SCAN(1){
			
			for (i = 0; i < e->num_inimigos; i++) //faz tambem o dorbro do dano ao proprio inimigo
				if (e->inimigo[i].pos.x == e->inimigo[atoi(aux) - 1].pos.x + ck && e->inimigo[i].pos.y == e->inimigo[atoi(aux) -1].pos.y + lk)
					e->inimigo[i].hp -= e->dmg;
		}
	} 
}


/**
\brief Função que descodifica o link em que o jogador carrega. Primeiro carrega os estado guardado no ficheiro e guarda-o em e.
Segundo guarda-se a classe do jogador, a sua fação e se o turno é do jogador ou do inimigo. De seguida, através do define get_aux
guarda-se a posição do jogador icrementando a variável i que percorre o array *args. (Esta começa a 6 pois as 7 primeiras posições são sempre
classe, fação e turno). Guarda-se o no. de jogadas que o jogador ainda tem e o valor start que controla se o jogo já comecou ou nao.
Verific-se se o jogador atacou e se sim reduz a vida do inimigo atacado pelo dano do jogador. Finalmente, guardam-se os estados de cada abilidade,
os respetivos cooldowns, o dano e a vida do jogador.
NOTA: Quando o orc mago ativa a sua primeira abilidade, o inimigo alvo recebe o dobro do dano e todos os inimigos num raio de um
do alvo recebem o dano do orc mago.
@param *args ---> string que representa os argumentos do link
@returns e ---> novo estado com as alterações feitas
*/
ESTADO descodifica_link(char *args){

	ESTADO e = ficheiro2estado();
	int i = 6;
	int v = 0;

	//get_aux é utilizada para descodificar argumentos de forma genérica

	char aux[TAB_TAM];
	aux[1] = '\0'; 
	
	aux[0] = args[0]; //independentemente do tamanho do mapa fica sempre na mesma posição do array
	e.CLASS = atoi(aux);

	aux[0] = args[2]; //independentemente do tamanho do mapa fica sempre na mesma posição do array
	e.SIDE = atoi(aux);

	aux[0] = args[4]; //independentemente do tamanho do mapa fica sempre na mesma posição do array
	e.TURN = atoi(aux);

	get_aux; //começa sempre na i = 6
	i++;

	e.jog.x = atoi(aux);

	get_aux;
	i++;

	e.jog.y = atoi(aux);

	aux[1] = '\0';

	aux[0] = args[i]; 
	e.MOVE = atoi(aux);
	i += 2;

	aux[0] = args[i];
	e.START = atoi(aux);
	i += 2;

	get_aux;

	if (atoi(aux)) e.inimigo[atoi(aux) - 1].hp -= e.dmg;
	i++;

	efeito_da_AB1_mago_orc(&e, aux);

	aux[1] = '\0';

	aux[0] = args[i];
	e.ab1.active = atoi(aux);
	i += 2;

	aux[0] = args[i];
	e.ab2.active = atoi(aux);
	i += 2;

	aux[0] = args[i];
	e.SUPER.active = atoi(aux);
	i += 2;

	aux[0] = args[i];
	e.ab1.cd = atoi(aux);
	i += 2;

	aux[0] = args[i];
	e.ab2.cd = atoi(aux);
	i+= 2;

	aux[0] = args[i];
	e.SUPER.cd = atoi(aux);
	i+= 2;

	get_aux;
	i++;

	e.VIDA = atoi(aux);

	get_aux;

	e.dmg = atoi(aux);

	return e;
}

/**
\brief Função que lê o link. Se este ainda não tiver argumentos imprime o menu inicial. C.C. descodifica *args.
@param *args ---> argumentos do link
@returns inicial ---> Se o não tiver argumentos ou seja novo jogo. descodifica_link(args) ---> se o jogo ja começou.
*/
ESTADO ler_estado(char *args) {  

	if(strlen(args) == 0){ /*o link é apenas "http://localhost/cgi-bin/main?" */
		
		ESTADO inicial = {0};
		menu_facao(inicial); //incializa o menu inicial
		return inicial;
	} 

	return descodifica_link(args); //str2estado(args);
}

/**
\brief imprime o fundo do tabuleiro (a preto)
*/
void imprime_fundo(){
	
	printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n",
	0, 0, TAB_TAM * ESCALA, TAB_TAM * ESCALA, "#000000");
}


/**
\brief Função que verifica se a abilidade 2 do mago orc esta ativada, caso afirmativo, 
o efeito da abilidade é executada.
@param *e ---> apontador para os estado de jogo ser alterado
*/
void efeito_da_AB2_do_mago_orc(ESTADO *e, int *i){

	if (e->CLASS == 1 && e->SIDE == 0 && e->ab2.active == 1){ //AB2 MAGO ORC
					
		*e = M_Attack (*e, e->inimigo[*i]);
					
		if (monstro_pode_atacar_jogador (e->inimigo[*i], *e)) 
			e->inimigo[*i].hp -= e->inimigo[*i].dmg / 2 + 1;
	}
}


/**
\brief Função que verifica se a abilidade 2 do cavaleiro orc esta ativada, caso afirmativo, 
o efeito da abilidade é executada.
@param *e ---> apontador para os estado de jogo ser alterado
*/
void efeito_da_AB2_do_cavaleiro_orc(ESTADO *e){

	int i;

	if (e->CLASS == 0 && e->SIDE == 0 && e->ab2.active == 1){  
		
		RADIAL_SCAN(1){ /*rouba vida num raio de 1 do cavaleiro orc*/
			for (i = 0; i < e->num_inimigos; i++)
				if (e->inimigo[i].pos.x == e->jog.x + ck && e->inimigo[i].pos.y == e->jog.y + lk){
					e->inimigo[i].hp -= e->dmg / 4; //condition 1 -> LIFE_STEAL
					e->VIDA += e->dmg / 4;
				}
		}

		if (e->ab2.cd == 2) e->ab2.active = 0; //dura 1 turno (DETERMINA-SE ATRAVES DOS Cool Downs)
	}
}

/**
\brief Função que verifica se a abilidade 1 do mago humano esta ativada, caso afirmativo, 
o efeito da abilidade é executada, caso negativo é restirado o efeito da abilidade sobre 
os inimigos.
@param *e ---> apontador para os estado de jogo ser alterado
*/
void efeito_ou_reset_da_AB1_do_mago_humano(ESTADO *e){

	int i;

	if (e->CLASS == 1 && e->SIDE == 1 && e->ab1.active == 0) //reset/ retira efeito da abilidade
		for (i = 0; i < e->num_inimigos; i++)
			e->inimigo[i].condition = 0;

	if (e->CLASS == 1 && e->SIDE == 1 && e->ab1.active == 1){ //faz o efeito da abilidade
		
		RADIAL_SCAN(1){
			for (i = 0; i < e->num_inimigos; i++)
				if (e->inimigo[i].pos.x == e->jog.x + ck && e->inimigo[i].pos.y == e->jog.y + lk)
					e->inimigo[i].condition = 2; //condition 2 -> FROST NOVA
		}

		if (e->ab1.cd == 1) e->ab1.active = 0; //dura 2 turnos (DETERMINA-SE ATRAVES DOS Cool Downs)
	}
}


/**
\brief Função que retira o efeito do SUPER do cavaleiro orc
@param *e ---> apontador para os estado de jogo ser alterado
*/
void reset_do_SUPER_cavaleiro_orc(ESTADO *e){

	if (e->CLASS == 0 && e->SIDE == 0 && e->SUPER.cd == 0) e->dmg = dano_por_nivel(*e);
}


/**
\brief Função que retira o efeito da abilidade 2 do cavaleiro orc
@param *e ---> apontador para os estado de jogo ser alterado
*/
void reset_da_AB2_do_cavaleiro_orc(ESTADO *e){

	if (e->CLASS == 0 && e->SIDE == 0 && e->ab2.cd == 2) e->ab2.active = 0;	
}


/**
\brief Função que retira o efeito do SUPER do mago humano
@param *e ---> apontador para os estado de jogo ser alterado
*/
void reset_do_SUPER_mago_humano(ESTADO *e){

	if (e->CLASS == 1 && e->SIDE == 1 && e->SUPER.active == 0) e->dmg = dano_por_nivel(*e); 
}


/**
\brief Função que retira o efeito do SUPER do mago orc
@param *e ---> apontador para os estado de jogo ser alterado
*/
void reset_da_AB2_do_mago_orc(ESTADO *e){

	if (e->CLASS == 1 && e->SIDE == 0 && e->ab2.cd == 2) e->ab2.active = 0;
}


/**
\brief Função que trata de todos os eventos que decorrem durante a ronda dos inimigos. Estes são:
1. Movimentação dos inimigos;
2. Ataques dos inimigos ao jogar (sendo que o inimigo pode mover e atacar no mesmo turno);
3. Volta a ronda do jogador.\n\n 
Aplica, se estiverem ativadas, as seguintes abilidades: 
\n AB2 ---> mago orc
\n AB1 ---> mago humano
\n AB2 ---> cavaleiro orc
\n\n Reinicia /Reset das seguintes abilidades:
\n AB1 ---> mago humano
\n AB2 ---> cavaleiro orc
\n AB2 ---> mago orc
\n SUPER ---> cavaleiro orc
\n\n e ainda remove o efeito do super do mago humano.
@param *e ---> apontador para os estado de jogo a ser alterado
*/
void ronda_inimigos(ESTADO *e){

	int jogada[2]; //array que vai conter as novas coordenadas de cada inimigo (movimento dos inimigos)
	int i = 0;

	efeito_ou_reset_da_AB1_do_mago_humano(e);	
	efeito_da_AB2_do_cavaleiro_orc(e);

	if (e->TURN == 1){
		
		for(i = 0; i < e->num_inimigos; i++)
			if (e->inimigo[i].hp > 0 && e->inimigo[i].condition != 2){

				//interessa inicializar as coordenadas com estes valores qd o jogador esta a beira do inimigo
				jogada[0] = e->inimigo[i].pos.y;
				jogada[1] = e->inimigo[i].pos.x;

				indica_jogada_M(jogada, e->inimigo[i], *e); //determinação das proximas coordenadas de cada inimigo

				//novas coordenadas de cada inimigo
				e->inimigo[i].pos.y = jogada[0];
				e->inimigo[i].pos.x = jogada[1];

				//caso o SUPER do cavaleiro orc NÃO esteja ativado E caso a AB2 do mago orc NÃO esteja ativada entao os montros atacam
				if (!((e->CLASS == 0 && e->SIDE == 0 && e->SUPER.cd > 0) || (e->CLASS == 1 && e->SIDE == 0 && e->ab2.active == 1))) 
					*e = M_Attack (*e, e->inimigo[i]);
				
				efeito_da_AB2_do_mago_orc(e, &i);
			}

		reset_do_SUPER_cavaleiro_orc(e);
		reset_da_AB2_do_cavaleiro_orc(e);
		reset_do_SUPER_mago_humano(e);
		reset_da_AB2_do_mago_orc(e);

		e->TURN = 0; //para passar o turno ao jogador
	}
}

/**
\brief Função que retira o efeito do SUPER do cavaleiro humano
@param *e ---> apontador para os estado de jogo ser alterado
*/
void reset_do_SUPER_cavaleiro_humano(ESTADO *e){

	if (e->SIDE == 1 && e->CLASS == 0 && e->SUPER.cd == 1 && e->SUPER.active == 0){ //Human_Cav -> quando o cd == 0 perde o SUPER (atenção: atua no inicio e no fim)
		e->VIDA = vida_por_nivel(*e);
		e->dmg = dano_por_nivel(*e);
	}
}


/**
\brief Função que verifica se a abilidade 1 do cavaleiro orc esta ativada, caso afirmativo, 
o efeito da abilidade é executada.
@param *e ---> apontador para os estado de jogo ser alterado
*/
void efeito_da_AB1_cavaleiro_orc(ESTADO *e){

	if (e->SIDE == 0 && e->CLASS == 0 && e->ab1.active == 1) //--> CAV ORC AB_1 PASSIVA
		*e = passiva_ab1_cav_orc(*e);
}

/**
\brief Função que verifica se o SUPER do mago orc esta ativado, caso afirmativo, 
o efeito do SUPER é executado.
@param *e ---> apontador para os estado de jogo ser alterado
*/
void efeito_do_SUPER_do_mago_orc(ESTADO *e){

	int i;

	if (e->SIDE == 0 && e->CLASS == 1 && e->SUPER.cd == 1 && e->SUPER.active == 0){ //--> MAGO ORC SUPER 

		for(i = 0; i < e->num_inimigos; i++)
			e->inimigo[i].hp -= e->dmg;
		e->SUPER.cd = 0;
	}
}


/**
\brief Função Central. Imprime todos os elementos necessários ao jogo, invoca a ronda_inimigos na ronda dos inimigos.
Invoca as funções de movimento e ataque do jogador.
Converte cada iteração do estado para o ficheiro. Faz o reset do SUPER do cavaleiro humano e do mago orc.
Executa a passiva do cavaleiro orc.
@returns 0 para sair da função.
*/
int main(){

	srandom(time(NULL)); /* o srandom muda a seed dos outros random no inicio da execução do programa */ 

	COMECAR_HTML;
	ABRIR_SVG(2000, SVG_TAM);

	ESTADO e = ler_estado(getenv("QUERY_STRING"));

	if (e.START == 0){ //significa que o jogo ainda nao começou (permance na mesma pagina)
		FECHAR_SVG; 
		return 0;
	}

	if (e.START == 2){ //significa que foi carregado no link para abrir o menu How to play
		how_to_play();
		return 0;
	}

	if (e.jog.x == 0 && e.jog.y == 0) //o jogador chegou á saída
		e = inicializar_nivel(e.NIVEL, e.PONTOS, e.CLASS, e.SIDE);

	if (e.VIDA <= 0) {
		e.PONTOS -= 10;
		int cs = check_score(e);
		if (cs == 0) kill_screen();
		else kill_screen2(e.PONTOS);
		return 0;
	}

	reset_do_SUPER_cavaleiro_humano(&e);
	efeito_da_AB1_cavaleiro_orc(&e);
	efeito_do_SUPER_do_mago_orc(&e);

	e.START = 1; //significa que o jogo já começou
	imprime_fundo(); 
	imprime_tabueleiro(TAB_TAM);
	ronda_inimigos(&e); //modifica o estado (se necessário -> se for os turnos dos inimigos)
	imprime_inimigos(e);
	imprime_obstaculos(e);
	imprime_aba_lateral(e);
	imprime_jogador(e);
	
	estado2ficheiro(e);

	FECHAR_SVG;
	return 0;
}