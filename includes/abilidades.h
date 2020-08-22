#include "../defines.h"

/**
@file abilidades.h
Funções responsáveis pela mecânica das abilidades de cada personagem que o jogador pode escolher
*/

/**
\brief Função que indica qual o valor da vida atribuído ao jogador no inicio de cada nivel. Existe um 
valor máximo de vida por nivel possível que é 500
@param e O estado
@returns O valor da vida
*/
int vida_por_nivel (ESTADO e){

	e.VIDA = 100 + (5 * (e.NIVEL - 1));

	if (e.VIDA > MAX_HP) e.VIDA = MAX_HP; // HP CAP

	return e.VIDA;
}


/**
\brief Função que indica qual o valor do dano atribuído ao jogador no inicio de cada nivel. Existe um 
valor máximo de dano por nivel possível que é 125
@param e O estado
@returns O valor do dano
*/
int dano_por_nivel(ESTADO e){

	e.dmg = 25 + (5 * (e.NIVEL - 1));

	if (e.dmg > MAX_DMG) e.dmg = MAX_DMG; // DMG CAP

	return e.dmg;
}


/**
\brief Função que indica qual o valor do dano atribuido ao SUPER do mago humano no inicio de cada nivel. 
Existe um valor máximo de dano do SUPER por nivel possível que é 500
@param e O estado
@returns O valor do dano do SUPER do mago humano
*/
int nuke_por_nivel(ESTADO e){

	int nuke;

	if (e.NIVEL <= 5) nuke = 100;
	else if (e.NIVEL > 5 && e.NIVEL <= 7) nuke = 300;
	else nuke = 500;  

	return nuke;
}


/**
\brief Função que indica o efeito e uso da abilidade 1 do cavaleiro humano. Caso o cooldown (cd) desta
abilidade seja 0 significa que o jogador a pode utilizar desta forma é criado um link em cima da imagem
da abilidade 1. Esta abilidade dá ao cavaleiro humano 25% da sua vida possivel no seu nivel. 
A abilidade tem 3 turnos de cooldown. 
@param e O estado
*/
void ab1_cav_hmno(ESTADO e){

	char link[LINK_BUFFER];

	if (e.ab1.cd == 0){

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, 1, e.ab2.active, e.SUPER.active, 3, e.ab2.cd,  e.SUPER.cd, e.VIDA + vida_por_nivel(e) / 4, e.dmg);
		ABRIR_LINK(link);
		IMAGEM(0, TAB_TAM + 1, ESCALA, "ab1_cav_hmno.png");
		FECHAR_LINK;
	}
}


/**
\brief Função que indica o efeito e uso da abilidade 2 do cavaleiro humano. Caso o cooldown (cd) desta
abilidade seja 0 significa que o jogador a pode utilizar desta forma é criado um link em cima da imagem
da abilidade 2. Esta abilidade aumenta o raio de ataque e movimento do jogador para 2 apenas naquele turno. 
A abilidade tem 2 turnos de cooldown. 
@param e O estado
*/
void ab2_cav_hmno(ESTADO e){

	char link[LINK_BUFFER];

	if (e.ab2.cd == 0){

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, e.ab1.active, 1, e.SUPER.active, e.ab1.cd, 2, e.SUPER.cd, e.VIDA, e.dmg);
		ABRIR_LINK(link);
		IMAGEM(1, TAB_TAM + 1, ESCALA, "ab2_cav_hmno.png");
		FECHAR_LINK;

	}
}


/**
\brief Função que indica o efeito e uso do SUPER do cavaleiro humano. Caso o jogador esteja num 
nivel igual ou superior ao 3 significa que pode utilizar o SUPER desta forma é criado um link em cima 
da imagem do SUPER. Este SUPER dá 200 de vida e triplica o valor do seu dano. 
O SUPER apenas se pode utilizar uma vez por nivel.
@param e O estado
*/
void SUPER_cav_hmno(ESTADO e){

	char link[LINK_BUFFER];

	if (e.SUPER.active){

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, e.ab1.active, e.ab2.active, 0, e.ab1.cd, e.ab2.cd, 5, e.VIDA + 200, e.dmg * 3);
		ABRIR_LINK(link);
		IMAGEM(2, TAB_TAM + 1, ESCALA, "super_cav_hmno.png");
		FECHAR_LINK;
	}
}



/**
\brief Função que indica o efeito e uso da abilidade 1 do mago humano. Caso o cooldown (cd) desta
abilidade seja 0 significa que o jogador a pode utilizar desta forma é criado um link em cima da imagem
da abilidade 1. Esta abilidade congela todos os inimigos num raio de 1 á volta do jogador durante 2 turnos.
A abilidade tem 4 turnos de cooldown. 
@param e O estado
*/
void ab1_mago_hmno(ESTADO e){

	char link[LINK_BUFFER];

	if (e.ab1.cd == 0){
		 
		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, 1, e.ab2.active, e.SUPER.active, 4, e.ab2.cd,  e.SUPER.cd, e.VIDA, e.dmg);
		ABRIR_LINK(link);
		IMAGEM(0, TAB_TAM + 1, ESCALA, "ab1_mago_hmn.png");
		FECHAR_LINK;

	}
}

/**
\brief Função que indica o efeito e uso da abilidade 2 do mago humano. Caso o cooldown (cd) desta
abilidade seja 0 significa que o jogador a pode utilizar desta forma é criado um link em cima da imagem
da abilidade 2. Esta abilidade faz o reset dos movimentos ao jogador (passa a ter 2 moviemntos novamente)
A abilidade tem 5 turnos de cooldown. 
@param e O estado
*/
void ab2_mago_hmno(ESTADO e){

	char link[LINK_BUFFER]; 

	if (e.ab2.cd == 0){

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, 2, e.START, 0, e.ab1.active, e.ab2.active, e.SUPER.active, e.ab1.cd, 5, e.SUPER.cd, e.VIDA, e.dmg);	
		ABRIR_LINK(link);
		IMAGEM(1, TAB_TAM + 1, ESCALA, "ab2_mago_hmn.png");
		FECHAR_LINK;

	}
}


/**
\brief Função que indica o efeito e uso do SUPER do mago humano. Caso o jogador esteja num 
nivel igual ou superior ao 3 significa que pode utilizar o SUPER desta forma é criado um link em cima 
da imagem do SUPER. Este SUPER atumenta o valor do dano do jogador, o valor é dado pela função
nuke_por_nivel. 
O SUPER apenas se pode utilizar uma vez por nivel.
@param e O estado
*/
void SUPER_mago_hmno(ESTADO e){

	char link[LINK_BUFFER]; 

	if (e.SUPER.active){

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, e.ab1.active, e.ab2.active, 0, e.ab1.cd, e.ab2.cd, e.SUPER.cd, e.VIDA, nuke_por_nivel(e));
		ABRIR_LINK(link);
		IMAGEM(2, TAB_TAM + 1, ESCALA, "super_mago_hmn.png");
		FECHAR_LINK;
	}
}


/**
\brief Função que indica o efeito da abilidade 1 do cavaleiro orc. A abilidade não tem cooldown por isso 
significa que o jogador está constantemente a utiliza-la (passiva). 
Esta abilidade causa 25% do dano do jogador sobre os inimigos num raio de 1 á volta do jogador.
@param e O estado
@returns O estado
*/
ESTADO passiva_ab1_cav_orc(ESTADO e){
	
	int i;
	
	RADIAL_SCAN(1){
		
		for (i = 0; i < e.num_inimigos; i++)
			if (e.inimigo[i].pos.x == e.jog.x + ck && e.inimigo[i].pos.y == e.jog.y + lk)
				e.inimigo[i].hp -= e.dmg / 4;
	}

	return e;
}


/**
\brief Função que indica o efeito e uso da abilidade 2 do cavaleiro orc. Caso o cooldown (cd) desta
abilidade seja 0 significa que o jogador a pode utilizar desta forma é criado um link em cima da imagem
da abilidade 2. Esta abilidade causa 25% do dano do jogador sobre os inimigos num raio de 1 á volta do 
jogador e simultanemante dá vida ao jogador com o mesmo valor desse dano causado.
A abilidade tem 3 turnos de cooldown. 
@param e O estado
*/
void ab2_cav_orc(ESTADO e){

	char link[LINK_BUFFER]; 

	if (e.ab2.cd == 0){

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, e.ab1.active, 1, e.SUPER.active, e.ab1.cd, 3, e.SUPER.cd, e.VIDA, e.dmg);
		ABRIR_LINK(link);
		IMAGEM(1, TAB_TAM + 1, ESCALA, "ab2_cav_orc.png");
		FECHAR_LINK;
	}
}


/**
\brief Função que indica o efeito e uso do SUPER do cavaleiro orc. Caso o jogador esteja num 
nivel igual ou superior ao 3 significa que pode utilizar o SUPER desta forma é criado um link em cima 
da imagem do SUPER. Este SUPER duplica valor do dano do jogador e o jogador fica invensivel 
durante 3 turnos.
O SUPER apenas se pode utilizar uma vez por nivel.
@param e O estado
*/
void SUPER_cav_orc(ESTADO e){

	char link[LINK_BUFFER]; 

	if (e.SUPER.active){

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, e.ab1.active, e.ab2.active, 0, e.ab1.cd, e.ab2.cd, 3, e.VIDA, e.dmg * 2);
		ABRIR_LINK(link);
		IMAGEM(2, TAB_TAM + 1, ESCALA, "super_cav_orc.png");
		FECHAR_LINK; 
	}
}

/**
\brief Função que indica o efeito e uso da abilidade 1 do mago orc. Caso o cooldown (cd) desta
abilidade seja 0 significa que o jogador a pode utilizar desta forma é criado um link em cima da imagem
da abilidade 1. Esta abilidade causa o dano do jogador sobre os inimigos num raio de 1 á volta do  
inimigo atacado (assim aplica o dobro do dano do jogador sobre o inimigo incialmente atacado).
A abilidade tem 3 turnos de cooldown. 
@param e O estado
*/
void ab1_mago_orc(ESTADO e){

	char link[LINK_BUFFER]; 

	if (e.ab1.cd == 0){
		
		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, 1, e.ab2.active, e.SUPER.active, 3, e.ab2.cd,  e.SUPER.cd, e.VIDA, e.dmg);
		ABRIR_LINK(link);
		IMAGEM(0, TAB_TAM + 1, ESCALA, "ab1_mago_orc.png");
		FECHAR_LINK;
	}
}


/**
\brief Função que indica o efeito e uso da abilidade 2 do mago orc. Caso o cooldown (cd) desta
abilidade seja 0 significa que o jogador a pode utilizar desta forma é criado um link em cima da imagem
da abilidade 2. Esta abilidade reflete 50% do dano causado pelos inimigos sobre jogador e simultaneamente 
causa o valor do dano refeltido sobre os prórpios inimigos, atua durante 3 turnos.
A abilidade tem 5 turnos de cooldown. 
@param e O estado
*/
void ab2_mago_orc(ESTADO e){

	char link[LINK_BUFFER]; 

	if (e.ab2.cd == 0){

		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, e.ab1.active, 1, e.SUPER.active, e.ab1.cd, 5, e.SUPER.cd, e.VIDA, e.dmg);
		ABRIR_LINK(link);
		IMAGEM(1, TAB_TAM + 1, ESCALA, "ab2_mago_orc.png");
		FECHAR_LINK;
	}
}

/**
\brief Função que indica o efeito e uso do SUPER do mago orc. Caso o jogador esteja num 
nivel igual ou superior ao 3 significa que pode utilizar o SUPER desta forma é criado um link em cima 
da imagem do SUPER. Este SUPER causa o dano do jogador sobre todos os inimigos.
O SUPER apenas se pode utilizar uma vez por nivel.
@param e O estado
*/
void SUPER_mago_orc(ESTADO e){

	char link[LINK_BUFFER];

	if(e.SUPER.active){
 
		CRIAR_LINK(link, e.CLASS, e.SIDE, e.TURN, e.jog.x, e.jog.y, e.MOVE, e.START, 0, e.ab1.active, e.ab2.active, 0, e.ab1.cd, e.ab2.cd, 1, e.VIDA, e.dmg);
		ABRIR_LINK(link);
		IMAGEM(2, TAB_TAM + 1, ESCALA, "super_mago_orc.png");
		FECHAR_LINK; 
	}
}


/**
\brief Função que junta as 2 funções de abilidades e a do SUPER referentes ao cavaleiro humano
@param e O estado
*/
void imprime_abilidades_cav_hum(ESTADO e){

	IMAGEM(0, TAB_TAM + 1, ESCALA, "ab1_cav_hmno.png"); //ab1
	IMAGEM(1, TAB_TAM + 1, ESCALA, "ab2_cav_hmno.png"); //ab2
	IMAGEM(2, TAB_TAM + 1, ESCALA, "super_cav_hmno.png"); //SUPER
	
	ab1_cav_hmno(e);
	ab2_cav_hmno(e);
	SUPER_cav_hmno(e);
}


/**
\brief Função que junta as 2 funções de abilidades e a do SUPER referentes ao mago humano
@param e O estado
*/
void imprime_abilidades_mage_hum(ESTADO e){

	IMAGEM(0, TAB_TAM + 1, ESCALA, "ab1_mago_hmn.png"); //ab1
	IMAGEM(1, TAB_TAM + 1, ESCALA, "ab2_mago_hmn.png"); //ab2
	IMAGEM(2, TAB_TAM + 1, ESCALA, "super_mago_hmn.png"); //SUPER

	ab1_mago_hmno(e);
	ab2_mago_hmno(e);
	SUPER_mago_hmno(e);
}


/**
\brief Função que junta as 2 funções de abilidades e a do SUPER referentes ao cavaleiro orc
@param e O estado
*/
void imprime_abilidades_cav_orc(ESTADO e){

	IMAGEM(0, TAB_TAM + 1, ESCALA, "ab1_cav_orc.png"); //ab1
	IMAGEM(1, TAB_TAM + 1, ESCALA, "ab2_cav_orc.png"); //ab2
	IMAGEM(2, TAB_TAM + 1, ESCALA, "super_cav_orc.png"); //SUPER

	//AB_1 passiva -> tira 1/4 dano num raio de 1 do jogador
	ab2_cav_orc(e);
	SUPER_cav_orc(e);
}


/**
\brief Função que junta as 2 funções de abilidades e a do SUPER referentes ao mago orc
@param e O estado
*/
void imprime_abilidades_mage_orc(ESTADO e){

	IMAGEM(0, TAB_TAM + 1, ESCALA, "ab1_mago_orc.png"); //ab1
	IMAGEM(1, TAB_TAM + 1, ESCALA, "ab2_mago_orc.png"); //ab2
	IMAGEM(2, TAB_TAM + 1, ESCALA, "super_mago_orc.png"); //SUPER

	ab1_mago_orc(e);
	ab2_mago_orc(e);
	SUPER_mago_orc(e);
}