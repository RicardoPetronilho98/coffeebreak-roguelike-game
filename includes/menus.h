#include "../defines.h"

/**
@file menus.h
Funcoes que modificam e imprimem os menus do jogo.
*/

/**
\brief Função que imprime os icones das classes no menu inicial
@param x A coluna do icon
@param y A linha do incon
@param *img A string com o nome da imagem que respresenta o jogador
@param *player A string com o nome da personagem que representa o jogador
*/
void imprime_icon (int x, int y, char *img, char *player){

	x *= 40; //posicionamento da imagem
	y *= 40; 

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n",
	x, y, 80, 80, img); //imprime se o icone da classe
		
	printf("<text x=%d y=%d fill=%s >%s</text>", 
	x + 20, y - 40, "#000000", player); ///imprime o nome do jogador em cima da imagem
}


/**
\brief Função que imprime as imagens de cada persongaem e cria links em cima das memas que irão 
alterar o estado consoante o jogador escolhido.
@param e O estado de jogo 
*/
void decide_classe (ESTADO e){

	int human = 1, orc = 0, melee = 0, ranged = 1; 
	char link0[LINK_BUFFER], link1[LINK_BUFFER], link2[LINK_BUFFER], link3[LINK_BUFFER]; 

	CRIAR_LINK(link0, melee, human, e.TURN, e.jog.x, e.jog.y, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); //cria o link para a classe cavaleiro humano
	CRIAR_LINK(link1, ranged, human, e.TURN, e.jog.x, e.jog.y, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); //cria o link para a classe mago humano
	CRIAR_LINK(link2, melee, orc, e.TURN, e.jog.x, e.jog.y, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); //cria o link para a classe cavaleiro orc
	CRIAR_LINK(link3, ranged, orc, e.TURN, e.jog.x, e.jog.y, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); //cria o link para a classe mago orc

	ABRIR_LINK (link0); 
	imprime_icon (3, 10, IMAGE_PATH cav_hmn_img, Cavaleiro_humano);
	FECHAR_LINK;

	ABRIR_LINK(link1); 
	imprime_icon (6, 10, IMAGE_PATH mage_hmn_img, Mage_humano); 
	FECHAR_LINK; 

	ABRIR_LINK(link2); 
	imprime_icon(9, 10, IMAGE_PATH cav_orc_img, Cavaleiro_orc);
	FECHAR_LINK;

	ABRIR_LINK(link3);
	imprime_icon(12, 10, IMAGE_PATH mage_orc_img, Mage_Orc); 
	FECHAR_LINK; 
}

/**
\brief Função que imprime os botoes para o scoreboard e tutorial.
@param nenhum
*/
void imprime_botoes_menu_incial(){

	char link0[] = "http://localhost/cgi-bin/score_board_main?0_95_95_95_1_"; 

	ABRIR_LINK(link0); 
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 3 * 40, 14 * 40, 145, 35, IMAGE_PATH "score_b_menu_i_button.png");
	FECHAR_LINK;

	char link1[] = "http://localhost/cgi-bin/main?0_0_0_0_0_0_2_0_0_0_0_0_0_0_0_0_"; 

	ABRIR_LINK(link1); 
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 11 * 40, 14 * 40, 145, 35, IMAGE_PATH "how_to_play_button.png");
	FECHAR_LINK; 
}

/**
\brief Funcão que cria e imprime o menu de seleção de personagem.
@param e O estado de jogo 
*/
void menu_facao(ESTADO e){

	remove(FILE_NAME); 

	IMAGEM(0, 0, MENU_TAM, "menu.png"); //imprime a imagem de fundo do menu
	
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 
	175, 60, 320, 132, IMAGE_PATH "logo.png"); //imprime o logotipo

	int c, l; //coordenadas do texto 
	l = MENU_TAM / 3 + 20;
	c = MENU_TAM / 3; 
	printf("<text x=%d y=%d fill=%s >ESCOLHE O TEU LADO!</text>", c, l,"#000000"); //imprime o texto no centro do menu

	imprime_botoes_menu_incial();

	decide_classe(e);
}

/**
*\brief Função que imprime o ecran de morte quando o jogador não tem pontuação para permanecer no scoreboard.
Imprime a imagem do botão new_game e cria um link sobre a mesma.
*/
void kill_screen() {

	char link[] = "http://localhost/cgi-bin/main?";  //link para o menu inicial (novo jogo)
	
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n",
	0, 0, 575, 350, IMAGE_PATH "killscreen.png"); //imagem de fundo

	ABRIR_LINK(link);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 410, 295, 145, 35, IMAGE_PATH "button_new-game.png"); //botao de novo jogo
	FECHAR_LINK;
	
}

/**
\brief Função que imprime o ecran de morte quando o jogador tem pontuação para chegar ao scoreboard (novo recorde)
Imprime a imagem do botão new_highscoree cria um link sobre a mesma.
*/
void kill_screen2(int pontos) {

	char link[LINK_BUFFER]; //var link que vai ser criado no botao

	sprintf(link, "http://localhost/cgi-bin/score_board_main?%d_65_65_65_0_", pontos); //cria o link para a scoreboard
	
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n",
	0, 0, 575, 350, IMAGE_PATH "killscreen.png"); //imagem de fundo

	ABRIR_LINK(link); 
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 410, 295, 145, 35, IMAGE_PATH "button_score_board.png"); //imprime o botao para a scoreboard
	FECHAR_LINK; 
	
}

/**
\brief Função que imprime o tutorial para o cavaleiro humano.
*/
void how_to_play_cavaleiro_humano(void){

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 50, 50 + 10, 50, 50, IMAGE_PATH cav_hmn_img); //imprime o icon da classe
	
	IMAGEM(4, 0, 35, "ab1_cav_hmno.png"); //icone da abilidade 1
	printf("<text x=%d y=%d fill=%s >FLASH OF LIGHT: CURA O CAVALEIRO POR 1/4 DA SUA VIDA MAXIMA</text>", 6 * 35, 22, "#000000"); //explicacao abilidade 1

	IMAGEM(4, 2, 35, "ab2_cav_hmno.png"); //brief icone da abilidade 2
	printf("<text x=%d y=%d fill=%s >DIVINE CHARGE: DURANTE O TURNO O CAVALEIRO AUMENTA O SEU ALCANCE POR 1</text>", 6 * 35, 22 * 4 + 5, "#000000"); //explicacao abilidade 2
	
	IMAGEM(4, 4, 35, "super_cav_hmno.png"); //brief icone da super abilidade
	printf("<text x=%d y=%d fill=%s >AVENGING WRATH: DURANTE 3 TURNOS TRIPLICA O DANO DO CAVALEIRO E AUMENTA A VIDA POR 200, NO FIM CURA A VIDA MAXIMA</text>", 6 * 35, 22 * 8 - 10, "#000000"); //explicacao SUPER abilidade

}

/**
\brief Função que imprime o tutorial para o mago humano.
*/
void how_to_play_mago_humano(void){

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 50, 50 * 5 + 20, 50, 50, IMAGE_PATH mage_hmn_img);
	
	IMAGEM(4, 6, 35, "ab1_mago_hmn.png"); //icone da abilidade 1
	printf("<text x=%d y=%d fill=%s >FROST NOVA: CONGELA OS INIMIGOS NUM RAIO DE 1 DO MAGO DURANTE 2 TURNOS</text>", 6 * 35, 22 * 11 - 10, "#000000"); //explicacao abilidade 1
	
	IMAGEM(4, 8, 35, "ab2_mago_hmn.png"); //icone da abilidade 2
	printf("<text x=%d y=%d fill=%s >TIMEWARP: RETORNA O NMR DE JOGADAS POSSIVEIS PELO MAGO PARA 2</text>", 6 * 35, 22 * 14 - 6, "#000000"); //explicacao abilidade 2
	
	IMAGEM(4, 10, 35, "super_mago_hmn.png"); //icone da super abilidade
	printf("<text x=%d y=%d fill=%s >PYROBLAST: DURANTE ESTE TURNO OS ATAQUES DO MAGO FICAM SOBRECARREGADOS FAZENDO MAIS DANO</text>", 6 * 35, 22 * 18 - 20, "#000000"); //explicacao super abilidade*/

}

/**
\brief Função que imprime o tutorial para o cavaleiro orc.
*/
void how_to_play_cavaleiro_orc(void){

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 50, 50 * 9 + 33, 50, 50, IMAGE_PATH cav_orc_img);

	IMAGEM(4, 12, 35, "ab1_cav_orc.png"); //icone da abilidade 1
	printf("<text x=%d y=%d fill=%s >DEATH & DECAY: (PASSIVA) O CAVALEIRO ORC FAZ 1/4 DO SEU DANO NUM RAIO DE 1</text>", 6 * 35, 22 * 21 - 20, "#000000"); //explicacao abilidade 1
	
	IMAGEM(4, 14, 35, "ab2_cav_orc.png"); //icone da abilidade 2
	printf("<text x=%d y=%d fill=%s >SYPHON HEALTH: O CAVALEIRO ORC FAZ 1/4 DO SEU DANO NUM RAIO DE 1, O DANO FEITO CURA O CAVALEIRO ORC</text>", 6 * 35, 22 * 24 - 15, "#000000"); //explicacao abilidade 2
	
	IMAGEM(4, 16, 35, "super_cav_orc.png"); //icone da super abilidade
	printf("<text x=%d y=%d fill=%s >THE DEAD CANNOT DIE: O DANO DO CAVALEIRO ORC E DUPLICADO E ESTE FICA IMUNE A TODO O DANO DURANTE 3 TURNOS</text>", 6 * 35, 22 * 27 - 10, "#000000"); //explicacao super abilidade

}

/**
\brief Função que imprime o tutorial para o mago orc.
*/
void how_to_play_mago_orc(void){

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 50, 50 * 13 + 43, 50, 50, IMAGE_PATH mage_orc_img);

	IMAGEM(4, 18, 35, "ab1_mago_orc.png"); //icone da abilidade 1
	printf("<text x=%d y=%d fill=%s >CHAINED LIGHTNING: O PROXIMO ATAQUE DO MAGO ORC AFETA TODOS OS INIMIGOS A VOLTA DO INIMIGO ATACADO, O ATACADO RECEBE O DOBRO DO DANO</text>", 6 * 35, 22 * 30 - 10, "#000000"); //explicacao abilidade 1
	
	IMAGEM(4, 20, 35, "ab2_mago_orc.png"); //icone da abilidade 2
	printf("<text x=%d y=%d fill=%s >LIGHTNING SHIELD: DURANTE 3 TURNOS O MAGO ORC RECEBE 1/2 DO DANO INFLIGIDO REFLETINDO A OUTRA 1/2</text>", 6 * 35, 22 * 34 - 25, "#000000"); //explicacao abilidade 2
	
	IMAGEM(4, 22, 35, "super_mago_orc.png"); //icone da super abilidade
	printf("<text x=%d y=%d fill=%s >LIGHTNING STORM: O MAGO ORC INFLIGE O SEU DANO A TODOS OS INIMIGOS DO MAPA</text>", 6 * 35, 22 * 36, "#000000"); //explicacao super abilidade

}

/**
\brief Função que imprime o tutorial.
*/
void how_to_play(void){

	char link[] = "http://localhost/cgi-bin/main?";  //link para o menu inicial
	how_to_play_cavaleiro_humano(); //imprime o tutorial para o cavaleiro humano
	how_to_play_mago_humano(); //imprime o tutorial para o mago humano
	how_to_play_cavaleiro_orc();//imprime o tutorial para o cavaleiro orc
	how_to_play_mago_orc(); //imprime o tutorial para o mago orc

	printf("<text x=%d y=%d fill=%s >ATENCAO: apenas SCORE > 0 tem direito a permancer no Score Board! O SUPER apenas pode ser ativado a partir do nivel 3!</text>", 225, 875, "#000000"); //brief dicas adicionais
	ABRIR_LINK(link); //brief abrir link para o menu inicial 
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", 50, 850, 145, 35, IMAGE_PATH "main_menu_button.png"); //brief imprime botao para o menu inicial
	FECHAR_LINK; //brief fecha o link 

}