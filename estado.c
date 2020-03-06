#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"
#include "parser.h"
/**
 * @file
 */

#define MAX_BUFFER		10240

/**
 * @brief verifica se tem inimigo na posição (x,y) e dá 0 caso tenha
 * @param e estado de jogo
 * @param x abcissa a verificar
 * @param y ordenada a verificar
 * @returns retorna 0 caso tenho monstro em (x,y) 1 caso contrário
 */

int temInimigo (ESTADO e, int x,int y){
    
    int i;
    for ( i=0 ; i< e.num_inimigos ;i++)  if (x == e.inimigo[i].x && y == e.inimigo[i].y) return 0;

    for ( i=0 ; i< e.num_inimigos2 ;i++) if (x == e.inimigo2[i].x && y == e.inimigo2[i].y) return 0;
    
    for ( i=0 ; i< e.num_inimigos3;i++)  if (x == e.inimigo3[i].x && y == e.inimigo3[i].y) return 0;

    for ( i=0 ; i< e.num_inimigos4;i++)  if (x == e.inimigo4[i].x && y == e.inimigo4[i].y) return 0;
    
    return 1;
}
/**
 * @brief verifica se a posição é possível
 * @param e estado de jogo
 * @param x abcissa a verificar
 * @param y ordenada a verificar
 * @returns retorna 0 caso haja alguma coisa em (x,y) 1 caso contrário
 */

int pospossivel (ESTADO e, int x, int y){
    int i;
            
    if (x < 0 || y < 0 ||  x >= SIZE || y >= SIZE)return 0;
    if (x == e.especial.bau.x && y == e.especial.bau.y) return 0;
    if (x == e.door.x && y == e.door.y) return 0;
    if (x == e.jog.x && y == e.jog.y) return 0;
    
    for ( i=0 ; i< e.num_inimigos ;i++)  if (x == e.inimigo[i].x && y == e.inimigo[i].y) return 0;
    
    for ( i=0 ; i< e.num_obstaculos; i++)if (x == e.obstaculo[i].x && y == e.obstaculo[i].y) return 0;

    for ( i=0 ; i< e.num_inimigos2 ;i++) if (x == e.inimigo2[i].x && y == e.inimigo2[i].y) return 0;
    
    for ( i=0 ; i< e.num_inimigos3;i++)  if (x == e.inimigo3[i].x && y == e.inimigo3[i].y) return 0;

    for ( i=0 ; i< e.num_inimigos4;i++)  if (x == e.inimigo4[i].x && y == e.inimigo4[i].y) return 0;

    
    return 1;
}
/**
* @brief verifica se a posição é possível mas para os movimentos do jogador
* @param e estado de jogo
* @param x abcisssa a verificar
* @param y ordenada a verificar
* @returns retorna 0 caso haja alguma coisa em (x,y) 1 caso contrário
 */

int pospossivel2 (ESTADO e,int x, int y){
    int i;

    if (x < 0 || y < 0 ||  x >= SIZE || y >= SIZE)return 0;
    
    for ( i=0 ; i< e.num_inimigos ;i++)  if (x == e.inimigo[i].x && y == e.inimigo[i].y) return 0;

    for ( i=0 ; i< e.num_inimigos2 ;i++) if (x == e.inimigo2[i].x && y == e.inimigo2[i].y) return 0;
    
    for ( i=0 ; i< e.num_inimigos3;i++)  if (x == e.inimigo3[i].x && y == e.inimigo3[i].y) return 0;

    for ( i=0 ; i< e.num_inimigos4;i++)  if (x == e.inimigo4[i].x && y == e.inimigo4[i].y) return 0;


    return 1;
}
/**
 * @brief inicializa o estado
 * @param nivel o nivel em que estamos
 * @param vida a vida que temos/começamos
 * @param score score que temos/começamos
 * @param menu indica se estamos no menu ou não
 * @returns estado de jogo
 */

ESTADO inicializar(int nivel,int vida,int score,int menu) {
    int i,x,y,z=0;
    ESTADO e = {0};
    e.especial.menu=menu;
    e.score= score;
    e.vida= vida;
    e.acao=z;
    e.nivel=nivel;
    for (i=0;i<1;){
        x=rand()%TAM;
        y=rand()%TAM;
        if (pospossivel(e,x,y)){
            e.especial.bau.x = x;
            e.especial.bau.y = y;
            i++;
            }
    }

    for (i=0;i<1;){
        x=rand()%TAM;
        y=rand()%TAM;
        if (pospossivel(e,x,y)){
            e.jog.x = x;
            e.jog.y = y;
            i++;
            }
    }

    for (;;){
        x=rand()%TAM;
        y=rand()%TAM;
        if (pospossivel(e,x,y)){
            e.door.x = x;
            e.door.y = y;
            break;
        }
    }
    e.num_inimigos = 0;
    for (i=0; i < NUMINIMIGOS + nivel - 4; ){
        x = rand()%TAM;
        y = rand()%TAM;
        if (pospossivel (e,x,y)){
            e.inimigo[i].x = x;
            e.inimigo[i].y = y;
            e.num_inimigos++;
            i++;
        }
    }
    e.num_inimigos2=0;
    for (i=0; i< 1+(e.nivel/5) ; ){
        x=rand()%TAM;
        y=rand()%TAM;
        if (pospossivel(e,x,y)){
            e.inimigo2[i].x = x;
            e.inimigo2[i].y = y;
            e.num_inimigos2++;
            i++;
            }
    }
    e.num_inimigos3=0;
    for (i=0; i<1+(e.nivel/5) ; ){
        x=rand()%TAM;
        y=rand()%TAM;
        if (pospossivel(e,x,y)){
            e.inimigo3[i].x = x;
            e.inimigo3[i].y = y;
            e.num_inimigos3++;
            i++;
            }
    }
    e.num_inimigos4=0;
    for (i=0; i<1+(e.nivel/5) ; ){
        x=rand()%TAM;
        y=rand()%TAM;
        if (pospossivel(e,x,y)){
            e.inimigo4[i].x = x;
            e.inimigo4[i].y = y;
            e.num_inimigos4++;
            i++;
            }
    }


    e.morto= 0;
    e.num_obstaculos = 0;
    for (i=0; i < NUMOBSTACULOS + 2*nivel - 2;){
        x = rand()%TAM;
        y = rand()%TAM;
        if (pospossivel (e,x,y)){
            e.obstaculo[i].x = x;
            e.obstaculo[i].y = y;
            e.num_obstaculos++;
            i++;
        }
    }
    return e;
}
/**
 * @brief pega no estado e passa para string (deixou se ser usado mas deixa-mos aqui)
 * @param e estado de jogo
 * @returns string com o estado de jogo
 */

char *estado2str(ESTADO e) {
	static char buffer[MAX_BUFFER];
	unsigned char *p = (unsigned char *) &e;
	unsigned int i;

	buffer[0] = 0;

	for(i = 0; i < sizeof(ESTADO); i++)
		sprintf(buffer, "%s%02x", buffer, p[i]);
	
	return buffer;
}
/**
 * @brief pega numa string e converte para estado de jogo (também não está a ser usado)
 * @param *argumentos query string
 * @returns estado de jogo
 */

ESTADO str2estado(char *argumentos) {
	ESTADO e;
	unsigned char *p = (unsigned char *) &e;
	unsigned int i;

	for(i = 0; i < sizeof(ESTADO); i++, argumentos += 2) {
		unsigned int d;
		sscanf(argumentos, "%2x", &d);
		p[i] = (char) d;
	}
	
	return e;
}

/**
 * @brief move os inimigos
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO moveEnemy (ESTADO e){

    int x=e.jog.x,y=e.jog.y,i,dx=e.door.x,dy=e.door.y;
    
    for (i=0; i<e.num_inimigos; i++){

        if ((X1 >= x+3) && pospossivel (e,X1-1,Y1)) {X1=X1-1; continue;}
        if ((Y1 >= y ||(Y1>y && pospossivel (e,X1-1,X1)==0))  &&pospossivel (e,X1,Y1-1)){Y1=Y1-1; continue;}
        if (X1 < x && pospossivel (e,X1+1,Y1)) {X1=X1+1; continue;}
        if (Y1 <= y+3 && pospossivel (e,X1,Y1+1)) {Y1=Y1+1; continue;}

    }
    for (i=0; i<e.num_inimigos2; i++){

        if (X2>dx && Y2>=dy &&pospossivel (e,X2-1,Y2-1)) {X2=X2-1,Y2=Y2-1; continue;}
        if (X2<=dx && Y2<dy &&pospossivel (e,X2+1,Y2+1)) {X2=X2+1,Y2=Y2+1; continue;}
        if (X2>=dx && Y2<dy &&pospossivel (e,X2-1,Y2+1)) {X2=X2-1,Y2=Y2+1; continue;}
        if (X2<dx && Y2>=dy &&pospossivel (e,X2+1,Y2-1)) {X2=X2+1,Y2=Y2-1; continue;}

    }

    for (i=0; i<e.num_inimigos3; i++){

        if (X3>=dx && Y3>dy &&pospossivel (e,X3-1,Y3-1)) {X3=X3-1,Y3=Y3-1; continue;}
        if (X3<dx && Y3<=dy &&pospossivel (e,X3+1,Y3+1)) {X3=X3+1,Y3=Y3+1; continue;}
        if (X3>dx && Y3<=dy &&pospossivel (e,X3-1,Y3+1)) {X3=X3-1,Y3=Y3+1; continue;}
        if (X3<=dx && Y3>dy &&pospossivel (e,X3+1,Y3-1)) {X3=X3+1,Y3=Y3-1; continue;}

    }
    for (i=0; i<e.num_inimigos4; i++){

        if ((Y4 -2 <= y) && pospossivel (e,X4,Y4+1)) {Y4=Y4+1; continue;}
        if ( (X4<x|| pospossivel (e,X4,Y4-1)==0) &&pospossivel (e,X4+1,Y4)){X4=X4+1; continue;}
        if ((((Y4-y) >4)||pospossivel (e,X4-1,Y4)==0)&&pospossivel (e,X4,Y4-1)){Y4=Y4-1; continue;}
        if ((X4 > x) && pospossivel (e,X4-1,Y4)) {X4=X4-1; continue;}
}
    return e;
}
/**
 * @brief verifica se o jogador está em cima de obstáculos
 * @param e estado de jogo
 * @returns retorna 1 se estiver em cima de obstáculos, 0 caso contrário
 */

int obstaculo (ESTADO e){
    int i;

    for (i=0; i<e.num_obstaculos ; i++){
        
        if (e.jog.x == e.obstaculo[i].x && e.jog.y == e.obstaculo[i].y) return 1;
        }
    return 0;
}
/**
 * @brief verifica o que se o primeiro tipo de monstro tem distancia suficiente para nos atacar, também mata o monstro e ao matar dá-nos score
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO atacarEspada (ESTADO e){

    int i , x=e.jog.x , y=e.jog.y;

    for (i=0; i<e.num_inimigos; i++){
        if (e.vida==0) return e;
        if (e.inimigo[i].x== x+1 && e.inimigo[i].y== y+1) {e.inimigo[i].x= 18, e.inimigo[i].y=3, e.morto++,e.score++;}
        if (e.inimigo[i].x== x   && e.inimigo[i].y== y+1) {e.inimigo[i].x= 18, e.inimigo[i].y=3, e.morto++,e.score++;}
        if (e.inimigo[i].x== x-1 && e.inimigo[i].y== y+1) {e.inimigo[i].x= 18, e.inimigo[i].y=3, e.morto++,e.score++;}
        if (e.inimigo[i].x== x-1 && e.inimigo[i].y== y  ) {e.inimigo[i].x= 18, e.inimigo[i].y=3, e.morto++,e.score++;}
        if (e.inimigo[i].x== x-1 && e.inimigo[i].y== y-1) {e.inimigo[i].x= 18, e.inimigo[i].y=3, e.morto++,e.score++;}
        if (e.inimigo[i].x== x+1 && e.inimigo[i].y== y  ) {e.inimigo[i].x= 18, e.inimigo[i].y=3, e.morto++,e.vida--,e.score++;}
        if (e.inimigo[i].x== x+1 && e.inimigo[i].y== y-1) {e.inimigo[i].x= 18, e.inimigo[i].y=3, e.morto++,e.vida--,e.score++;}
        if (e.inimigo[i].x== x   && e.inimigo[i].y== y-1) {e.inimigo[i].x= 18, e.inimigo[i].y=3, e.morto++,e.vida--,e.score++;}
    }

        return e;
    
    }
/**
 * @brief verifica o que se o segundo tipo de monstro tem distancia suficiente para nos atacar, também mata o monstro e ao matar dá-nos score
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO atacarLanceiro (ESTADO e){

    int i , x=e.jog.x , y=e.jog.y;

    for (i=0; i< e.num_inimigos2; i++){
        if (e.vida==0) return e;
        if (e.inimigo2[i].x== x+1 && e.inimigo2[i].y== y+1) {e.inimigo2[i].x= 18, e.inimigo2[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo2[i].x== x   && e.inimigo2[i].y== y+1) {e.inimigo2[i].x= 18, e.inimigo2[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo2[i].x== x-1 && e.inimigo2[i].y== y+1) {e.inimigo2[i].x= 18, e.inimigo2[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo2[i].x== x-1 && e.inimigo2[i].y== y  ) {e.inimigo2[i].x= 18, e.inimigo2[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo2[i].x== x-1 && e.inimigo2[i].y== y-1) {e.inimigo2[i].x= 18, e.inimigo2[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo2[i].x== x+1 && e.inimigo2[i].y== y  ) {e.inimigo2[i].x= 18, e.inimigo2[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo2[i].x== x+1 && e.inimigo2[i].y== y-1) {e.inimigo2[i].x= 18, e.inimigo2[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo2[i].x== x   && e.inimigo2[i].y== y-1) {e.inimigo2[i].x= 18, e.inimigo2[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo2[i].x== x-2 && e.inimigo2[i].y== y-2) e.vida--;
        if (e.inimigo2[i].x== x+2 && e.inimigo2[i].y== y+2) e.vida--;
        if (e.inimigo2[i].x== x-2 && e.inimigo2[i].y== y+2) e.vida--;
        if (e.inimigo2[i].x== x+2 && e.inimigo2[i].y== y-2) e.vida--;

        }

        return e;
    
    }
/**
 * @brief verifica o que se o terceiro tipo de monstro tem distancia suficiente para nos atacar, também mata o monstro e ao matar dá-nos score
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO atacarArqueiro (ESTADO e){

    int i , x=e.jog.x , y=e.jog.y;

    for (i=0; i< e.num_inimigos3; i++){
        if (e.vida==0) return e;
        if (e.inimigo3[i].x== x+1 && e.inimigo3[i].y== y+1) {e.inimigo3[i].x= 18, e.inimigo3[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo3[i].x== x   && e.inimigo3[i].y== y+1) {e.inimigo3[i].x= 18, e.inimigo3[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo3[i].x== x-1 && e.inimigo3[i].y== y+1) {e.inimigo3[i].x= 18, e.inimigo3[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo3[i].x== x-1 && e.inimigo3[i].y== y  ) {e.inimigo3[i].x= 18, e.inimigo3[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo3[i].x== x-1 && e.inimigo3[i].y== y-1) {e.inimigo3[i].x= 18, e.inimigo3[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo3[i].x== x+1 && e.inimigo3[i].y== y  ) {e.inimigo3[i].x= 18, e.inimigo3[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo3[i].x== x+1 && e.inimigo3[i].y== y-1) {e.inimigo3[i].x= 18, e.inimigo3[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo3[i].x== x   && e.inimigo3[i].y== y-1) {e.inimigo3[i].x= 18, e.inimigo3[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo3[i].x== x-2 && e.inimigo3[i].y== y) e.vida--;
        if (e.inimigo3[i].x== x-3 && e.inimigo3[i].y== y) e.vida--;
        if (e.inimigo3[i].x== x+2 && e.inimigo3[i].y== y) e.vida--;
        if (e.inimigo3[i].x== x+3 && e.inimigo3[i].y== y) e.vida--;
        if (e.inimigo3[i].x== x   && e.inimigo3[i].y== y-2) e.vida--;
        if (e.inimigo3[i].x== x   && e.inimigo3[i].y== y-3) e.vida--;
        if (e.inimigo3[i].x== x   && e.inimigo3[i].y== y+2) e.vida--;
        if (e.inimigo3[i].x== x   && e.inimigo3[i].y== y+3) e.vida--;

        }

        return e;
    
    }
/**
 * @brief verifica o que se o quarto tipo de monstro tem distancia suficiente para nos atacar, também mata o monstro e ao matar dá-nos score
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO atacarDragao (ESTADO e){

    int i , x=e.jog.x , y=e.jog.y;

    for (i=0; i< e.num_inimigos4; i++){
        if (e.vida==0) return e;
        if (e.inimigo4[i].x== x+1 && e.inimigo4[i].y== y+1) {e.inimigo4[i].x= 18, e.inimigo4[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo4[i].x== x   && e.inimigo4[i].y== y+1) {e.inimigo4[i].x= 18, e.inimigo4[i].y=3, e.morto++,e.vida--,e.score=e.score+2;}
        if (e.inimigo4[i].x== x-1 && e.inimigo4[i].y== y+1) {e.inimigo4[i].x= 18, e.inimigo4[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo4[i].x== x-1 && e.inimigo4[i].y== y  ) {e.inimigo4[i].x= 18, e.inimigo4[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo4[i].x== x-1 && e.inimigo4[i].y== y-1) {e.inimigo4[i].x= 18, e.inimigo4[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo4[i].x== x+1 && e.inimigo4[i].y== y  ) {e.inimigo4[i].x= 18, e.inimigo4[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo4[i].x== x+1 && e.inimigo4[i].y== y-1) {e.inimigo4[i].x= 18, e.inimigo4[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo4[i].x== x   && e.inimigo4[i].y== y-1) {e.inimigo4[i].x= 18, e.inimigo4[i].y=3, e.morto++,e.score=e.score+2;}
        if (e.inimigo4[i].x== x   && e.inimigo4[i].y== y+2) e.vida--;
        if (e.inimigo4[i].x== x   && e.inimigo4[i].y== y+3) e.vida--;
        if (e.inimigo4[i].x== x   && e.inimigo4[i].y== y+4) e.vida--;
        if (e.inimigo4[i].x== x   && e.inimigo4[i].y== y+5) e.vida--;

        }

        return e;
    
    }
/**
 * @brief ativa/desativa a variavel de controlo e.especial.show, quando carregamos num monstro de primeiro tipo guardamos as coordenadas dele para imprimir o que ele ataca
 * @param e estado de jogo
 * @param x abcissa do monstro
 * @param y ordenada do monstro
 * @returns novo estado de jogo
 */

ESTADO show (ESTADO e,int x,int y){
    e.especial.show2=0;
    e.especial.show3=0;
    e.especial.show4=0;
    if (e.especial.poder3) {e.especial.show=0; return e;}
    e.especial.ataque.x=x;
    e.especial.ataque.y=y;
    e.especial.show = !e.especial.show;
    return e;
}

/**
 * @brief ativa/desativa a variavel de controlo e.especial.show, quando carregamos num monstro de segundo tipo guardamos as coordenadas dele para imprimir o que ele ataca
 * @param e estado de jogo
 * @param x abcissa do monstro
 * @param y ordenada do monstro
 * @returns novo estado de jogo
 */

ESTADO show2 (ESTADO e,int x,int y){
    e.especial.show=0;
    e.especial.show3=0;
    e.especial.show4=0;
    if (e.especial.poder3) {e.especial.show2=0; return e;}
    e.especial.ataque.x=x;
    e.especial.ataque.y=y;
    e.especial.show2 = !e.especial.show2;
    return e;
}

/**
 * @brief ativa/desativa a variavel de controlo e.especial.show, quando carregamos num monstro de terceiro tipo guardamos as coordenadas dele para imprimir o que ele ataca
 * @param e estado de jogo
 * @param x abcissa do monstro
 * @param y ordenada do monstro
 * @returns novo estado de jogo
 */

ESTADO show3 (ESTADO e,int x,int y){
    e.especial.show=0;
    e.especial.show2=0;
    e.especial.show4=0;
    if (e.especial.poder3) {e.especial.show3=0; return e;}
    e.especial.ataque.x=x;
    e.especial.ataque.y=y;
    e.especial.show3 = !e.especial.show3;
    return e;
}

/**
 * @brief ativa/desativa a variavel de controlo e.especial.show, quando carregamos num monstro de quarto tipo guardamos as coordenadas dele para imprimir o que ele ataca
 * @param e estado de jogo
 * @param x abcissa do monstro
 * @param y ordenada do monstro
 * @returns novo estado de jogo
 */

ESTADO show4 (ESTADO e,int x,int y){
    e.especial.show=0;
    e.especial.show2=0;
    e.especial.show3=0;
    e.especial.ataque.x=x;
    e.especial.ataque.y=y;
    if (e.especial.poder3) {e.especial.show4=0; return e;}
    e.especial.show4 = !e.especial.show4;
    return e;
}
/**
 * @brief ativa/desativa a variavel de controlo e.especial.cheat que serve para depois imprimir os ataques de todos os monstros
 * @param e estado de jogo
 * @returns novo estado de jogo
 */


ESTADO cheater (ESTADO e){
    e.especial.cheat = !e.especial.cheat;
   
    return e;
}

/**
 * @brief move o jogador, vê se estamos em cima de obstáculo, se apanhamos o baú e move os monstros
 * @param e estado de jogo
 * @param difx distancia a mover
 * @param dify distancia a mover
 * @returns novo estado de jogo
 */

ESTADO move_player(ESTADO e, int difx, int dify){
   
    if (e.especial.menu) return e;
    
    int x = e.jog.x + difx;
    int y = e.jog.y + dify;

    e.jog.x = x;
    e.jog.y = y;

    if (obstaculo (e)) e.vida--;
    if (e.jog.x==e.especial.bau.x &&e.jog.y==e.especial.bau.y) e.especial.ativaBau=1,e.especial.bau.x=18,e.especial.bau.y=3;
    
    e=atacarDragao(atacarArqueiro(atacarLanceiro(atacarEspada(e))));

    e = moveEnemy (e);
    e.especial.show=0;
    e.especial.show2=0;
    e.especial.show3=0;
    e.especial.show4=0;
    e.especial.cheat=0;
     
    return e;
}
/**
 * @brief desativa a váriavel e.especial.menu para começar o jogo
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO play(ESTADO e){
    e.especial.menu = 0;
    return e;
}
/**
 * @brief ativa o poder 1 e mete a variável e.especial.nope a 1 para evitar que o jogador volte atrás e possa estar sempre a escolher novos poderes
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO poder1(ESTADO e){
    if (e.especial.nope) return e;
    e.especial.nope=1;
    if (e.vida <5) e.vida++;
    
    e.especial.ativaBau=2;
    
    return e;
}
/**
 * @brief ativa o poder 2 e mete a variável e.especial.nope a 1 para evitar que o jogador volte atrás e possa estar sempre a escolher novos poderes
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO poder2(ESTADO e){
    if (e.especial.nope) return e;
    e.especial.nope=1;

    e.especial.poder2=1;
    
    e.especial.ativaBau=2;
    
    return e;
}
/**
 * @brief ativa o poder 3 e mete a variável e.especial.nope a 1 para evitar que o jogador volte atrás e possa estar sempre a escolher novos poderes
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO poder3(ESTADO e){
    if (e.especial.nope) return e;
    e.especial.nope=1;

    e.especial.poder3=1;
    
    e.especial.ativaBau=2;
    
    return e;
}
/**
 * @brief pega no estado e nas coordenadas e mata o monstro que estiver nessas coordenadas (poder 3)
 * @param e estado de jogo
 * @param x abcissa do monstro
 * @param y ordenada do monstro
 * @returns estado de jogo
 */

ESTADO efeitoPoder3 (ESTADO e,int x,int y){
    int i;
    for (i=0; i<e.num_inimigos; i++){
            if (e.especial.poder3 && e.inimigo[i].x==x && e.inimigo[i].y==y){ 
                e.inimigo[i].x=18,e.inimigo[i].y=3,e.morto++,e.score++,e.especial.poder3=0;
            } 
        }
    for (i=0; i<e.num_inimigos2; i++){
            if (e.especial.poder3 && e.inimigo2[i].x==x && e.inimigo2[i].y==y){ 
                e.inimigo2[i].x=18,e.inimigo2[i].y=3,e.morto++,e.score=e.score+2,e.especial.poder3=0;
            }
    }
    for (i=0; i<e.num_inimigos3; i++){
            if (e.especial.poder3 && e.inimigo3[i].x==x && e.inimigo3[i].y==y){ 
                e.inimigo3[i].x=18,e.inimigo3[i].y=3,e.morto++,e.score=e.score+2,e.especial.poder3=0;
            }
    }
    for (i=0; i<e.num_inimigos4; i++){
            if (e.especial.poder3 && e.inimigo4[i].x==x && e.inimigo4[i].y==y){ 
                e.inimigo4[i].x=18,e.inimigo4[i].y=3,e.morto++,e.score=e.score+2,e.especial.poder3=0;
            }
    }

    return e;
}
/**
 * @brief ativa o poder 4 e mete a variável e.especial.nope a 1 para evitar que o jogador volte atrás e possa estar sempre a escolher novos poderes
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO poder4(ESTADO e){
    int i;
    if (e.especial.nope) return e;
    e.especial.nope=1;

    i=rand()%3;
    if (i==1 && e.vida >=3) e.vida =5;
    if (i==1 && e.vida <3) {e.vida=e.vida+3;}
    e.especial.ativaBau=2;
    
    return e;
}
/**
 * @brief ativa a variável e.epecial.topscore que é para no menu ir para a página dos scores quando carrego no botão "Highscore"
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO topScore (ESTADO e){
    e.especial.topscore=1;
    e.especial.menu=2;
    return e;
}
/**
 * @brief ativa a variável e.epecial.instruction que é para no menu ir para a página das instruções quando carrego no botão "Instructions"
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO instruction (ESTADO e){
    e.especial.instruction=1;
    e.especial.instruction2=0;
    e.especial.menu=2;
    e.extra.enemy1=0;
    e.extra.enemy2=0;
    e.extra.enemy3=0;
    e.extra.enemy4=0;
    return e;
}
/**
 * @brief ativa a variável e.ficheiro.ler que é para quando carregar em "Continue" saber que tenho de ir ao ficheiro à parte ler o estado que tinha guardado quando mandei guardar e começar o jogo com este estado
 * @param e estado de jogo
 * @returns novo estado de jogo
 */


ESTADO ler (ESTADO e){
    e.ficheiro.ler=1;
    return e;
}
/**
 * @brief ativa a variável e.ficheiro.guardar que é para guardar o estado num ficheiro para ser possível continuar mais tarde e também ativa a e.ficheiro.guardou para evitar que volte atrás para tentar jogar outra vez
 * @param e estado de jogo
 * @returns novo estado de jogo
 */
ESTADO guardar (ESTADO e){
    e.ficheiro.guardou=1;
    e.ficheiro.guardar=1;
    return e;
}
/**
 * @brief ativa a variável e.especial.instruction2 que vai para a segunda página de instruções
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO instruction2 (ESTADO e){
    e.especial.instruction=0;
    e.especial.instruction2=1;
    e.especial.menu=2;
    return e;
}
/**
 * @brief ativa a variável e.extra.enemy1 que é para na segunda página de instruções mostrar informação sobre o tipo 1 de monstro
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO enemy1 (ESTADO e){
    e.extra.enemy1= !e.extra.enemy1;
    e.extra.enemy2=0;
    e.extra.enemy3=0;
    e.extra.enemy4=0;
    return e;
}
/**
 * @brief ativa a variável e.extra.enemy2 que é para na segunda página de instruções mostrar informação sobre o tipo 2 de monstro
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO enemy2 (ESTADO e){
    e.extra.enemy2= !e.extra.enemy2;
    e.extra.enemy1=0;
    e.extra.enemy3=0;
    e.extra.enemy4=0;
    return e;
}
/**
 * @brief ativa a variável e.extra.enemy3 que é para na segunda página de instruções mostrar informação sobre o tipo 3 de monstro
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO enemy3 (ESTADO e){
    e.extra.enemy3= !e.extra.enemy3;
    e.extra.enemy1=0;
    e.extra.enemy2=0;
    e.extra.enemy4=0;
    return e;
}
/**
 * @brief ativa a variável e.extra.enemy4 que é para na segunda página de instruções mostrar informação sobre o tipo 4 de monstro
 * @param e estado de jogo
 * @returns novo estado de jogo
 */

ESTADO enemy4 (ESTADO e){
    e.extra.enemy4= !e.extra.enemy4;
    e.extra.enemy1=0;
    e.extra.enemy2=0;
    e.extra.enemy3=0;
    return e;
}
/**
 * @brief altera o estado conforme a ação do link
 * @param e estado de jogo
 * @param acao acao a executar
 * @param x segundo parametro da query que pode representar a abcissa de monstro ou jogador
 * @param y terceiro parametro da query que pode representar a ordenada de monstro ou jogador
 * @returns novo estado de jogo
 */


ESTADO alteraAcao (ESTADO e, int acao, int x,int y){
    
    switch (acao){
        case 0:
            return move_player (e,1,0); 
        case 1:
            return move_player (e,-1,0);
        case 2:
            return move_player (e,0,1);
        case 3:
            return move_player (e,0,-1);
        case 4:
            return move_player (e,1,1);
        case 5:
            return move_player (e,-1,-1);
        case 6:
            return move_player (e,1,-1);
        case 7:
            return move_player (e,-1,1);
        case 8:
            return cheater (e);
        case 9:
            return efeitoPoder3 ((show (e,x,y)),x,y);
        case 10:
            return efeitoPoder3 ((show2 (e,x,y)),x,y);
        case 11:
            return efeitoPoder3 ((show3 (e,x,y)),x,y);
        case 12:
            return efeitoPoder3 ((show4 (e,x,y)),x,y);
        case 13:
            return play (e);
        case 14: 
            return poder1(e);
        case 15:
            return poder2(e);
        case 16:
            return move_player (e,0,-2);
        case 17:
            return move_player (e,2,0);
        case 18:
            return move_player (e,0,2);
        case 19:
            return move_player (e,-2,0);
        case 20: 
            return poder3 (e);
        case 21:
            return poder4 (e);
        case 22:
            return (inicializar (1,3,0,0));
        case 23:
            return move_player(e,0,0);
        case 24:
            return topScore(e);
        case 25:
            return instruction(e);
        case 26:
            return ler(e);
        case 27:
            return guardar (e);
        case 28: 
            return instruction2(e);
        default: return e;
    }
}

/**
 * @brief altera o estado conforme a ação do link
 * @param e estado de jogo
 * @param acao acao a executar
 * @returns novo estado de jogo
 */

ESTADO alteraAcao_menu (ESTADO e, int acao){
    

    switch (acao){
        case 31:
            return enemy1(e);
        case 32:
            return enemy2(e);
        case 33:
            return enemy3(e);
        case 34:
            return enemy4(e);
        default:
            return e;
    }
}
















