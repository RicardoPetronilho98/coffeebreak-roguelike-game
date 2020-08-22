#include "../defines.h"

/**
@file combat_sys.h
Funções responsáveis pela mecânica de combate por parte dos inimigos e jogador
*/

int tem_jogador(ESTADO e, int x, int y);
int tem_inimigo(ESTADO e, int x, int y);
int vida_por_nivel(ESTADO e);
int dano_por_nivel(ESTADO e);


/**
\brief Função que implementa a mecânica de combate de cada inimigo. Se o jogador se encontrar no raio de 
ataque do inimigo, este causa 100% do seu dano sobre o jogador, excepto quando a abilidade 2 
do Mago Orc está ativada (nesta ocasião apenas é causado 50% do dano do inimigo sobre o jogador).
@param e O estado
@param M O inimigo que vai atacar
@returns O estado
*/
ESTADO M_Attack (ESTADO e, INIMIGO M){

	//ENRAGE DO BOSS
	if (M.type == 2){

		if(M.hp <= (vida_por_nivel(e) / 2)) //caso a vida do BOSS esteja a 25% 
			M.dmg = 2 * dano_por_nivel(e);
	}


	RADIAL_SCAN(M.raio){

		//AB2 DO MAGO ORC
		if (tem_jogador(e, M.pos.x + ck, M.pos.y + lk) && e.CLASS == 1 && e.SIDE == 0 && e.ab2.active == 1){
			e.VIDA -= M.dmg / 2; 
			return e;
		}

		if(tem_jogador(e, M.pos.x + ck, M.pos.y + lk))
			e.VIDA -= M.dmg;
	}
	
	return e;
}

/**
\brief Função auxiliar utilizada pela função J_Attack. Recebendo as coordenadas (x,y) de uma das casas
que o jogador pode atacar, determina se existe algum inimigo nessa coordenada. Caso exista é retornado a posição 
do inmigo no array dos inimigos + 1. Caso contrário é retornado 0. O valor retornado por esta função
é transmitido no link criado para atacar o inimigo em causa.
NOTA: Por questões de eficência não é utilizado números negativos no link. Assim o número mais 
apropriado para se retornar no caso em que não é encontrado nenhum inimigo é o 0, no entanto as 
posições no array dos inimigos começam em 0 logo seria conflituoso retornar este valor quando o inimigo
encontrado tivesse posição 0 no array. 
Desta forma, para contornar este problema, retorna-se a posição do inimigo no array dos inimigos + 1
quando é encontrado o inimigo e 0 caso contrário.       
@param e O estado
@param x Coordenada horizontal da possivel casa que o jogador pode atacar
@param y Coordenada vertical do jogador da possivel casa que o jogador pode atacar
@return A posição do inimigo atacado no array dos inimigos ou é retornado o valor 0
*/
int indica_inimigo_atacado(ESTADO e, int x, int y){ 

	int i;

	for(i = 0; i < e.num_inimigos; i++)
		if (x == e.inimigo[i].pos.x && y == e.inimigo[i].pos.y && e.inimigo[i].hp > 0) 
			return (i + 1);

	return 0; //caso nao tenha encontrado um inimigo
}


/**
\brief Função que implementa a mecânica de combate do jogador. Se um inimigo se encontrar no raio de 
ataque do jogador, este causa dano sobre o inimigo através de um link criado sobre o inimigo. 
Caso o jogador seja o Mago Orc e tenha a abilidade 1 ativada, esta é imediatamente desativada ao 
atacar um inimigo.
@param e O estado
@param ck Coordenada auxiliar usada para se adicionar á coordenada horizontal do jogador
@param lk Coordenada auxiliar usada para se adicionar á coordenada vertical do jogador
*/
void J_Attack (ESTADO e, int ck, int lk){

	int x, y, inimigo;
	char link[LINK_BUFFER];

	x = e.jog.x + ck;
	y = e.jog.y + lk;

	inimigo = indica_inimigo_atacado(e, x, y);
		
	if (inimigo){
		
		e.MOVE--; 
		
		//RESET DA AB 1 DO ORC MAGE
		if (e.CLASS == 1 && e.SIDE == 0 && e.ab1.active == 1) e.ab1.active = 0;
		
		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, inimigo, e.ab1.active, e.ab2.active, e.SUPER.active, e.ab1.cd, e.ab2.cd, e.SUPER.cd, e.VIDA, e.dmg);
		ABRIR_LINK(link);
		IMAGEM(x, y, ESCALA, "transparente.png");
		FECHAR_LINK;
	}
}
