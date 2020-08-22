#include "../defines.h"
 /** 
@file imprime_aba_lateral.h  
Definição das funções responsaveis por imprimir lateralmente dados relativos ao jogo 
 */

/** 
\brief Função que pega no estado atual do jogo ou seja, do nivel,  
na coluna e na linha e imprime o nivel atual do jogador com a
largura e altura da letra escolhida no corpo da função
@param  e O estado do jogo, o nivel atual e.NIVEL
@param  c A coluna onde se vai localizar o nível
@param  l A linha onde se vai localizar o nível
@returns void Resultado de imprimir só o nível
*/
void imprime_nivel(ESTADO e) {//imprime o texto referente ao nivels 

	int c = ESCALA * TAB_TAM + ESCALA / 2;
	int l = ESCALA * 5; 
	
	printf("<text x=%d y=%d fill=%s >NIVEL %d</text>", c, l, "#00FF00", e.NIVEL); //cor verde
}
/** 
\brief Função que pega no estado atual do jogo ou seja, dos pontos que são  
acumulado pelo jogador, na coluna e na linha e imprime os pontos do jogador com a
largura e altura da letra escolhida no corpo da função
@param  e O estado do jogo, os pontos e.PONTOS 
@param  c A coluna onde se vai localizar os pontos
@param  l A linha onde se vai localizar os pontos
@returns void Resultado de imprimir só os pontos 
*/
void imprime_pontos(ESTADO e) { 

	int c = ESCALA * TAB_TAM + ESCALA / 2 - 10;
	int l = ESCALA * 2;  

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 
	c + 5, l - 25, 30, 30, IMAGE_PATH "points.png");
	printf("<text x=%d y=%d fill=%s >%d</text>", c + 60, l, "#DC143C", e.PONTOS - 10); //cor red crimson
}

/** 
\brief Função que pega no estado atual do jogo ou seja, do dano capaz de infligir 
acumulado pelo jogador, na coluna e na linha  e imprime o dano do jogador com a
largura e altura da letra escolhida no corpo da função
@param  e O estado do jogo, o dano e.dmg 
@param  c A coluna onde se vai localizar o dano
@param  l A linha onde se vai localizar o dano
@returns void Resultado de imprimir só o dano 
*/
void imprime_dano(ESTADO e) { 


	int c = ESCALA * TAB_TAM + ESCALA / 2 - 10;
	int l = ESCALA * 4; 

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 
	c + 5, l - 25, 30, 30, IMAGE_PATH "damage.png");
	printf("<text x=%d y=%d fill=%s >%d</text>", c + 60, l, "#DC143C", e.dmg); //cor red crimson
}

/** 
\brief Função que imprime o retangulo onde se irão sobrepor todos os outros 
dados ou seja, o dano, a vida, os pontos, o nivel, o nome do jogador e por
fim o botão do turno
@param  l A linha onde se vai localizar o retangulo 
@param  c O comprimento onde se localiza o retangulo
@param  w A largura do retangulo 
@param  h A altura do mesmo
@returns void Resultado de imprimir o retangulo
*/
void imprime_rectangulo_lateral(){ //imprime o rectangulo lateral
	
	int l;
	int c = ESCALA * TAB_TAM; //coluna onde se localiza o rectangulo lateral
	int w = 3 * ESCALA; //width
	int h = ESCALA; //heigth

	for (l = 0; l < ESCALA * (TAB_TAM - 1); l++)
		printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n", c, l, w, h, "#000000"); //cor cinzento
}

/** 
\brief Função que pega no estado atual do jogo ou seja, da vida 
atual do jogador, na coluna e na linha e imprime a vida do jogador com a
largura e altura da letra escolhida no corpo da função
@param  e O estado do jogo, a vida atual do jogador e.VIDA
@param  c A coluna onde se vai localizar a vida
@param  l A linha onde se vai localizar a vida 
@returns void Resultado de imprimir só a vida 
*/
void imprime_vida(ESTADO e){

	int c = ESCALA * TAB_TAM + ESCALA / 2;
	int l = ESCALA * 3;

	if (e.VIDA <= 0) e.VIDA = 0;

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 
	c - 6, l - 20, 25, 25, IMAGE_PATH "heart.png");
	printf("<text x=%d y=%d fill=%s >%d</text>", c + 50, l, "#00FF00", e.VIDA); //cor verde
}

/** 
\brief Função que pega no estado atual do jogo ou seja, da personagem escolhida 
pelo jogador, na coluna e na linha e imprime o nome da personagem do jogador com a
largura e altura da letra escolhida no corpo da função
@param  p O nome do jogador que varia consoante a personagem escolhida
@param  c A coluna onde se vai localizar o nome do jogador
@param  l A linha onde se vai localizar o nome do jogador 
@returns void Resultado de imprimir só o nome do jogado 
*/
void imprime_nome_do_jogador(ESTADO e) {

	char *p;

	if (e.SIDE == 1 && e.CLASS == 0) p = Cavaleiro_humano;
	if (e.SIDE == 1 && e.CLASS == 1) p = Mage_humano;
	if (e.SIDE == 0 && e.CLASS == 0) p = Cavaleiro_orc;
	if (e.SIDE == 0 && e.CLASS == 1) p = Mage_Orc;

	int c = ESCALA * TAB_TAM + ESCALA / 2;
	int l = ESCALA * (TAB_TAM - 1);

	printf("<text x=%d y=%d fill=%s >%s</text>", c, l, "#00FF00", p); //cor verde
}

/** 
\brief Função que pega no estado atual do jogo ou seja no turno do jogador 
e cria um botão, com o auxilio de um link que ao ser carregado irá acabar o turno 
e proceder para o turno dos inimigos variando os cooldowns das abilidades assim 
como o estado do botão, no turno dos inimigos não se pode carregar no botão porque não existe link
@param  link Para possibilitar a interacção, ou não, com o botão
@param  c A coluna onde se vai localizar o botão
@param  l A linha onde se vai localizar o botão 
@returns void Resultado de imprimir a imagem do botão
*/
void imprime_botao_end_turn (ESTADO e){ // alterar valores para expressoes

	if (e.TURN == 0) {

		char link[LINK_BUFFER];
		int c = ESCALA * TAB_TAM + ESCALA / 2;
		int l = ESCALA * (TAB_TAM - 3);  

		e.TURN = 1; 
		e.MOVE = 2;

		// cada vez que o turno acaba os cool downs são decrementados
		if (e.ab1.cd > 0) e.ab1.cd--;
		if (e.ab2.cd > 0) e.ab2.cd--;
		if (e.SUPER.cd > 0) e.SUPER.cd--;

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, e.ab1.active, e.ab2.active, e.SUPER.active, e.ab1.cd, e.ab2.cd, e.SUPER.cd, e.VIDA, e.dmg);
		ABRIR_LINK(link);
		printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", c, l, 80, 80, IMAGE_PATH "button_end-turn.png");
		FECHAR_LINK;
	}

	else printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 420, 250, 80, 80, IMAGE_PATH "button_enemies-turn.png");
}

/** 
\brief Função que pega no estado atual do jogo e imprime 
tudo o que se encontra na aba lateral 
@param  e Estado do jogo 
@returns void Resultado de imprimir tudo referente a aba lateral
*/
void imprime_aba_lateral(ESTADO e){ //imprime tudo o que se econtra na aba

	imprime_rectangulo_lateral();
	imprime_nivel(e);
	imprime_vida(e);
	imprime_pontos(e);
	imprime_nome_do_jogador(e);
	imprime_botao_end_turn(e);
	imprime_dano(e);
}