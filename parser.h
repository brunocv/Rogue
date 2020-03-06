#ifndef ___PARSER_H___
#define ___PARSER_H___
/**
 * @brief tamanho do mapa
 */
#define SIZE 14
/**
 * @brief tamanho de cada célula
 */
#define TAM 50
#define PLAYER "http://127.0.0.1/player.gif"
#define ENEMY "http://127.0.0.1/monstro.png"
#define ENEMY2 "http://127.0.0.1/monstro2.png"
#define ENEMY3 "http://127.0.0.1/monstro3.gif"
#define ENEMY4 "http://127.0.0.1/monstro4.gif"
#define WALL "http://127.0.0.1/parede.png"
#define DOOR "http://127.0.0.1/porta.png"
#define BACKGROUND "http://127.0.0.1/background.jpg"
#define HEALTH "http://127.0.0.1/vida.png"
#define HEALTH2 "http://127.0.0.1/vida2.png"
#define END "http://127.0.0.1/end1.gif"
#define BAU "http://127.0.0.1/bau.png"
#define HELP "http://127.0.0.1/help.png"
#define RESTART "http://127.0.0.1/restart.png"
#define ESPADA "http://127.0.0.1/espada1.png"
#define ESPADA2 "http://127.0.0.1/espada2.png"
#define FOGO "http://127.0.0.1/fogo.gif"
#define NEWGAME "http://127.0.0.1/newgame.png"
#define LOGO "http://127.0.0.1/logo.png"
#define INST "http://127.0.0.1/inst.png"
#define BEST "http://127.0.0.1/best.png"
#define MENU "http://127.0.0.1/menu.png"
#define NEXT "http://127.0.0.1/next.png"
#define NIVEL "http://127.0.0.1/level.png"
#define SCORE "http://127.0.0.1/score2.png"
#define BACK "http://127.0.0.1/back.png"
#define CONTINUE "http://127.0.0.1/continue.png"
#define PODER1 "http://127.0.0.1/poder1.png"
#define PODER2 "http://127.0.0.1/poder2.png"
#define PODER3 "http://127.0.0.1/poder3.png"
#define PODER4 "http://127.0.0.1/poder4.png"
#define PIC1 "http://127.0.0.1/1.png"
#define PIC2 "http://127.0.0.1/2.png"
#define PIC3 "http://127.0.0.1/3.png"
#define PIC4 "http://127.0.0.1/3.5.png"
#define PIC5 "http://127.0.0.1/4.png"
#define PIC6 "http://127.0.0.1/5.png"
#define PIC7 "http://127.0.0.1/5.5.png"
#define PIC8 "http://127.0.0.1/6.png"
#define PIC9 "http://127.0.0.1/7.png"
#define PIC10 "http://127.0.0.1/8.png"
#define DETAIL1 "http://127.0.0.1/enemy1.png"
#define DETAIL2 "http://127.0.0.1/enemy2.png"
#define DETAIL3 "http://127.0.0.1/enemy3.png"
#define DETAIL4 "http://127.0.0.1/enemy4.png"
#define DETAIL5 "http://127.0.0.1/enemy5.png"
#define SCORE1 "http://127.0.0.1/score1.png"
#define SCORE2 "http://127.0.0.1/score3.png"
#define TYPE1 "http://127.0.0.1/type1.png"
#define TYPE2 "http://127.0.0.1/type2.png"
#define TYPE3 "http://127.0.0.1/type3.png"
#define TYPE4 "http://127.0.0.1/type4.png"
#define DETAILP1 "http://127.0.0.1/detailp1.png"
#define DETAILP2 "http://127.0.0.1/detailp2.png"
#define DETAILP3 "http://127.0.0.1/detailp3.png"
#define DETAILP4 "http://127.0.0.1/detailp4.png"
#define B1 "http://127.0.0.1/b1.png"
#define B2 "http://127.0.0.1/b2.png"
#define DETAILPALL "http://127.0.0.1/detailpall.png"
#define TOPSCORE1 "http://127.0.0.1/topscore1.png"
#define TOPSCORE2 "http://127.0.0.1/topscore2.png"
#define TOPSCORE3 "http://127.0.0.1/topscore3.png"
#define TOPSCORE4 "http://127.0.0.1/topscore4.png"






/**
 * @brief pintar de amarelo em força de quadrado a posição (x,y)
 */
#define A(X,Y) printf ("<rect x=%d y=%d width=50 height=50 style=\"fill:%s\"/>",X*50, Y *50,"#ffff66");



/**
 * @brief função que comanda o jogo todo, lê Query String, manda alterar o estado, manda guardar/ler ficheiros, passa de nível, e imprime o jogo
 */

void parser ();





#endif
