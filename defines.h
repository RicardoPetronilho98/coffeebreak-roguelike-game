#ifndef ___DEFINES_H___
#define ___DEFINES_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/**
@file defines.h
Macros úteis para ajudar na escrita das funções e na legibilidade do código
*/

/**
\brief O dano máximo base possivél de ser atingido sem buffs 
*/
#define MAX_DMG								125

/**
\brief A vida máxima base possivél de ser atingida sem buffs
*/
#define MAX_HP								500

/**
\brief Tamanho do tabuleiro
*/
#define TAB_TAM								9

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS						TAB_TAM * TAB_TAM

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS						TAB_TAM * TAB_TAM

/**
\brief Introduz as coordenadas nos respetivos arrays, utilizado na funão PathFinder
*/
#define gerar_coordenadas(i, x_aux, y_aux) 	(*i)++; cx[*i] = *x_aux; cy[*i] = *y_aux;

/**
\brief Dimensão maxima da string que contem o link
*/
#define LINK_BUFFER							100

/**
\brief Tamanho da janela SVG
*/
#define SVG_TAM        						1200

/**
\brief Escala utilizada no programa todo
*/
#define ESCALA								50

/**
\brief Tamanho do menu inicial
*/
#define MENU_TAM 							700

/**
\brief Nome abreviado do jogador Humano Ranged
*/
#define Cavaleiro_humano					"Hmn_C"

/**
\brief Nome abreviado do jogador Humano Ranged
*/
#define Mage_humano							"Hmn_R"

/**
\brief Nome abreviado do jogador Orc Cavaleiro
*/
#define Cavaleiro_orc						"Orc_C"

/**
\brief Nome abreviado do jogador Orc Ranged
*/
#define Mage_Orc							"Orc_R"

/**
\brief Nome da imagem do cavaleiro humano
*/
#define cav_hmn_img							"player_knight.png"

/**
\brief Nome da imagem do mage humano
*/
#define mage_hmn_img						"player_mage.png"

/**
\brief Nome da imagem do cavaleiro orc
*/
#define cav_orc_img				 			"player_deathknight.png"
		
/**
\brief Nome da imagem do mage orc
*/
#define mage_orc_img						"player_ogre_sorc.png"

/**
\brief Caminho para as imagens
*/
#define IMAGE_PATH							"http://http://localhost/~ricardopetronilho/images/"

/**
\brief Caminho para ficheiro link
*/
#define FILE_NAME 							"/link.txt"

/**
\brief Caminho para ficheiro score
*/
#define SCORE_FILE							"/score.txt"

/**
\brief Cria um link associado a um estado do main CGI
*/
#define CRIAR_LINK(link, classe, side, turno, x, y, move, start, inimigo, ab1_act, ab2_act, SUPER_act, ab1_cd, ab2_cd, SUPER_cd, vida, dmg)          	sprintf(link, "http://localhost/cgi-bin/main?%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_", classe, side, turno, x, y, move, start, inimigo, ab1_act, ab2_act, SUPER_act, ab1_cd, ab2_cd, SUPER_cd,vida, dmg)

/**
\brief Cria um link associado a um estado do score_board_main CGI
*/
#define CRIAR_LINK2(link, pontos, a, b, c, submit)								sprintf(link, "http://localhost/cgi-bin/score_board_main?%d_%d_%d_%d_%d_", pontos, a, b, c, submit)							

/**
\brief Macro para começar o html
*/
#define COMECAR_HTML						printf("Content-Type: text/html\n\n")

/**
\brief Macro para abrir um svg
@param tamx O comprimento do svg
@param tamy A altura do svg
*/
#define ABRIR_SVG(tamx, tamy)				printf("<svg width=%d height=%d>\n", tamx, tamy)

/**
\brief Macro para fechar um svg
*/
#define FECHAR_SVG							printf("</svg>\n")

/**
\brief Macro para criar uma imagem
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala da imagem
@param FICHEIRO O caminho para o link do ficheiro
*/
#define IMAGEM(X, Y, ESCALA, FICHEIRO)		printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, IMAGE_PATH FICHEIRO)
/**
\brief Macro para criar um quadrado
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala do quadrado
@param COR A cor de preenchimento do quadrado
*/
#define QUADRADO(X, Y, ESCALA, COR)			printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, COR)
/**
\brief Macro para abrir um link
@param link O caminho para o link
*/
#define ABRIR_LINK(link)					printf("<a xlink:href=%s>\n", link)

/**
\brief Macro para fechar o link
*/
#define FECHAR_LINK							printf("</a>\n")

/**
\brief Macro para escanear a volta comparando com as linhas e colunas   
@param r O raio que se pretende escanear a volta 
@param lk A linha  
@param ck A coluna
*/
#define RADIAL_SCAN(r)						for (int lk = -r; lk <= r; lk++) for (int ck = -r; ck <= r; ck++)

/**
\brief Macro que passa argumentos para array
@param i Para percorrer array 
@param v Para percorrer array auxiliar 
@param args Array com os argumentos 
@param aux Array auxiliar para onde se vai passar 
*/
#define get_aux								for (; args[i] != '_'; i++, v++) aux[v] = args[i]; \
											aux[v] = '\0'; \
											v = 0;

#endif