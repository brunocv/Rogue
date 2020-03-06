#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"
#include "parser.h"
/**
 * @file
 */

/**
 * @brief imprime um quadrado numa posição
 * @param px abcissa do quadrado
 * @param py ordenada do quadrado
 * @param tam tamanho de cada quadrado
 */
void print_square (int px,int py, int tam) {
    char *color[]={"#808080","#CCCCCC"};
    int idx = (px+py) % 2;
    printf ("<rect x=%d y=%d width=%d height=%d style=\"fill:%s\"/>",px*tam,py*tam,tam,tam,color[idx]);
}
/**
 * @brief imprime uma imagem numa posição
 * @param px abcissa da imagem
 * @param py ordenada da imagem
 * @param tam tamanho de cada imagem
 * @param *imagem imagem a colocar
 */

void print_image (int px, int py, int tam, char *imagem) {
    printf ("<image x=%d y=%d width=%d height=%d xlink:href=\"%s\"/>\n",px*tam,py*tam,tam,tam,imagem);
}
/**
 * @brief imprime o bau numa posição
 * @param e estado de jogo
 */

void print_bau (ESTADO e){
    if (e.especial.ativaBau==0) print_image (e.especial.bau.x,e.especial.bau.y,50,BAU);
}
/**
 * @brief imprime os links das jogadas possíveis
 * @param e estado de jogo
 * @param difx distancia a percorrer nas abcissas
 * @param dify distancia a percorrer nas ordenadas
 * @param acao para identificar que tipo de movimento foi
 */

void print_move (ESTADO e, int difx, int dify,int acao) {
    if (e.especial.menu) return; 
    int x = e.jog.x + difx;
    int y = e.jog.y + dify;

    if ( pospossivel2 (e,x,y)==0)
        return;

    printf ("<a xlink:href =\"http://127.0.0.1/cgi-bin/rogue?%d,%d,%d\"><rect x=%d y=%d width=50 height=50 style=\"fill-opacity:0\"/></a>\n", acao,e.jog.x,e.jog.y,x*TAM,y*TAM);
}
/**
 * @brief imprime o jogador e chama a print_move para imprimir os links das jogadas
 * @param e estado de jogo
 */

void print_player (ESTADO e) {
    print_image(e.jog.x, e.jog.y, TAM, PLAYER);
    print_move (e,+1,0,0);
    print_move (e,-1,0,1);
    print_move (e,+0,+1,2);
    print_move (e,0,-1,3);
    print_move (e,+1,+1,4);
    print_move (e,-1,-1,5);
    print_move (e,+1,-1,6);
    print_move (e,-1,+1,7);
    if (e.especial.poder2){
        print_move (e,0,-2,16);
        print_move (e,2,0,17);
        print_move (e,0,2,18);
        print_move (e,-2,0,19);
}
}
/**
 * @brief mostra o que o primeiro tipo de monstro ataca
 * @param e estado de jogo
 * @param x posição do monstro nas abcissas
 * @param y posição do monstro nas ordenadas
 */

void ataEspada (ESTADO e,int x,int y) {
        int x1,y1,i;
        for (i=0,x1=x-1,y1=y; i<2; i++,y1++){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);}
        x1=x,y1=y+1; 
        if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);

}
/**
 * @brief mostra o que o segundo tipo de monstro ataca
 * @param e estado de jogo
 * @param x posição do monstro nas abcissas
 * @param y posição do monstro nas ordenadas
 */


void ataLanceiro (ESTADO e,int x,int y){
        int x1,y1,i;
        
        for (i=0,x1=x-1,y1=y-1; i<2; i++,x1--,y1--){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);}
        
        for (i=0,x1=x+1,y1=y+1; i<2; i++,x1++,y1++){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);}
        
        for (i=0,x1=x+1,y1=y-1; i<2; i++,x1++,y1--){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);}

        for (i=0,x1=x-1,y1=y+1; i<2; i++,x1--,y1++){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);}
}
/**
 * @brief mostra o que o terceiro tipo de monstro ataca
 * @param e estado de jogo
 * @param x posição do monstro nas abcissas
 * @param y posição do monstro nas ordenadas
 */

void ataArqueiro (ESTADO e,int x,int y){
        
        int i, x1,y1;

        for (i=0,x1=x,y1=y-1; i<3; i++,y1--){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);}
        for (i=0,x1=x,y1=y+1; i<3; i++, y1++){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);} 
        for (i=0,x1=x-1,y1=y; i<3; i++,x1--){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);} 
        for (i=0,x1=x+1,y1=y; i<3;i++,x1++){
            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);} 
}
/**
 * @brief mostra o que o quarto tipo de monstro ataca
 * @param e estado de jogo
 * @param x posição do monstro nas abcissas
 * @param y posição do monstro nas ordenadas
 */

void ataDragao (ESTADO e,int x,int y){
        
        int i, x1,y1;

        for (i=0,x1=x,y1=y-1; i<5; i++,y1--){

            if ((x1 >= 0 && y1 >= 0 && x1 < SIZE && y1 < SIZE) && temInimigo (e,x1 ,y1)) A(x1,y1);}
         }
/**
 * @brief imprime os inimigos assim como o link para cada um para mostrar o que ataca (ou se o poder 3 tiver ativado para matar o monstro)
 * @param e estado de jogo
 */

void print_enemies (ESTADO e) {
    int i;
    for(i = 0; i < e.num_inimigos; i++){  
        
        print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, ENEMY);
        printf ("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?9,%d,%d\"><rect x=%d y=%d width=50 height=50 style=\"fill-opacity:0\"/></A>",e.inimigo[i].x,e.inimigo[i].y,e.inimigo[i].x * TAM, e.inimigo[i].y * TAM);
        
        if (e.especial.show ) ataEspada (e,e.especial.ataque.x,e.especial.ataque.y);
        if (e.especial.cheat) ataEspada (e,e.inimigo[i].x,e.inimigo[i].y);}

    for(i = 0; i < e.num_inimigos2; i++){
        print_image (e.inimigo2[i].x,e.inimigo2[i].y,TAM,ENEMY2);
        printf ("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?10,%d,%d\"><rect x=%d y=%d width=50 height=50 style=\"fill-opacity:0\"/></A>",e.inimigo2[i].x,e.inimigo2[i].y,e.inimigo2[i].x * TAM, e.inimigo2[i].y * TAM);
        
        if (e.especial.show2) ataLanceiro (e,e.especial.ataque.x,e.especial.ataque.y);
        if (e.especial.cheat) ataLanceiro (e,e.inimigo2[i].x,e.inimigo2[i].y);}


    for(i = 0; i < e.num_inimigos3; i++){
        print_image (e.inimigo3[i].x,e.inimigo3[i].y,TAM,ENEMY3);
        printf ("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?11,%d,%d\"><rect x=%d y=%d width=50 height=50 style=\"fill-opacity:0\"/></A>",e.inimigo3[i].x,e.inimigo3[i].y,e.inimigo3[i].x * TAM, e.inimigo3[i].y * TAM);
        
        if (e.especial.show3) ataArqueiro (e,e.especial.ataque.x,e.especial.ataque.y);
        if (e.especial.cheat) ataArqueiro (e,e.inimigo3[i].x,e.inimigo3[i].y);}


    for(i = 0; i < e.num_inimigos4; i++){ 
        print_image (e.inimigo4[i].x,e.inimigo4[i].y,TAM,ENEMY4);
        printf ("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?12,%d,%d\"><rect x=%d y=%d width=50 height=50 style=\"fill-opacity:0\"/></A>",e.inimigo4[i].x,e.inimigo4[i].y,e.inimigo4[i].x * TAM, e.inimigo4[i].y * TAM);
        
        if (e.especial.show4) ataDragao (e,e.especial.ataque.x,e.especial.ataque.y);
        if (e.especial.cheat) ataDragao (e,e.inimigo4[i].x,e.inimigo4[i].y);}



}
/**
 * @brief imprime os obstaculos
 * @param e estado de jogo
 */

void print_walls (ESTADO e) {
    int i;
    for(i = 0; i < e.num_obstaculos; i++)
        print_image(e.obstaculo[i].x, e.obstaculo[i].y, TAM, WALL);

}
/**
 * @brief imprime a porta
 * @param e estado de jogo
 */

void print_door (ESTADO e) {
    print_image(e.door.x, e.door.y, TAM, DOOR);

}
/**
 * @brief imprime o mapa de jogo
 */

void print_board(){
    int x,y;
    for (y=0; y<SIZE; y++)
        for (x=0;x<SIZE;x++)
            print_square (x,y,TAM);
}
/**
 * @brief imprime a imagem de fundo
 */

void print_background(){
    
    printf ("<image x=-700 y=-700 width=2000 height=1500 xlink:href=\"%s\"/>\n",BACKGROUND);
}
/**
 * @brief imprime informações como nível,score e vida
 * @param e estado de jogo
 */

void print_info (ESTADO e){
    
    char *color[]={"#CCCCCC"};
    int x= 800,y=50,z=e.vida,i=0;
    
    printf ("<rect x=770 y=30 width=310 height=460 RY=15 style=\"fill:%s\"/>",color[0]);
   
    while (i<5) {
        printf ("<image x=%d y=%d width=50 height=50 xlink:href=\"%s\"/>\n",x,y,HEALTH2);
        x+=50;
        i++;
    }
    x=800;
    while (z >0){
        printf ("<image x=%d y=%d width=50 height=50 xlink:href=\"%s\"/>\n",x,y,HEALTH);
        x+=50;
        z--;
    }
    printf ("<image x=825 y=100 width=200 height=50 xlink:href=\"%s\"/>\n",NIVEL);
    printf("<TEXT X=920 Y=165> %d </TEXT>\n",e.nivel);
    printf ("<image x=825 y=170 width=200 height=50 xlink:href=\"%s\"/>\n",SCORE);
    printf("<TEXT X=920 Y=235> %d </TEXT>\n",e.score);

}
/**
 * @brief imprime o game over e também botões para reniciar o jogo ou ir para o menu
 * @param e estado de jogo
 */

void print_end(ESTADO e){
    
    printf ("<image x=0 y=0 width=700 height=700 xlink:href=\"%s\"/>\n",END);
    printf ("<image x=120 y=25 width=350 height=250 xlink:href=\"%s\"/>\n",ESPADA);
    printf ("<image x=240 y=25 width=350 height=250 xlink:href=\"%s\"/>\n",ESPADA2);
    printf ("<image x=0 y=400 width=300 height=200 xlink:href=\"%s\"/>\n",FOGO);
    printf ("<image x=400 y=400 width=300 height=200 xlink:href=\"%s\"/>\n",FOGO);

    printf ("<image x=250 y=400 width=200 height=105 xlink:href=\"%s\"/>\n",MENU);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue\"><RECT X=270 Y=430 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>");
    
    printf ("<image x=250 y=480 width=200 height=105 xlink:href=\"%s\"/>\n",RESTART);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?22,%d,%d\"><RECT X=270 Y=510 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);


}
/**
 * @brief imprime o botão HELP que mostra o que cada monstro ataca
 * @param e estado de jogo
 */

void print_bcheat(ESTADO e){
    printf ("<image x=825 y=240 width=200 height=105 xlink:href=\"%s\"/>\n",HELP);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?8,%d,%d\"><RECT X=845 Y=270 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);

}
/**
 * @brief imprime um botão para dar restart
 */

void print_brestart(){
    printf ("<image x=825 y=320 width=200 height=105 xlink:href=\"%s\"/>\n",MENU);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue\"><RECT X=845 Y=350 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>");
}
/**
 * @brief imprime um botão que faz com que fiquemos parados uma jogada
 * @param e estado de jogo
 */

void print_bnext(ESTADO e){
    printf ("<image x=825 y=400 width=200 height=105 xlink:href=\"%s\"/>\n",NEXT);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?23,%d,%d\"><RECT X=845 Y=430 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
}
/**
 * @brief imprime um botão para guardar o jogo
 * @param e estado de jogo
 */

void print_bguardar (ESTADO e){

    printf ("<image x=250 y=700 width=200 height=105 xlink:href=\"%s\"/>\n",B2);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?27,%d,%d\"><RECT X=270 Y=730 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
 
}
/**
 * @brief imprime o menu e seus botões
 * @param e estado de jogo
 */

void print_menu (ESTADO e) {
    print_background();
    
    printf ("<image x=350 y=50 width=600 height=400 xlink:href=\"%s\"/>\n",LOGO);

    
    printf ("<image x=550 y=350 width=200 height=105 xlink:href=\"%s\"/>\n",NEWGAME);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?13,%d,%d\"><RECT X=570 Y=380 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
    
    printf ("<image x=550 y=450 width=200 height=105 xlink:href=\"%s\"/>\n",BEST);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?24,%d,%d\"><RECT X=570 Y=480 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
    
    printf ("<image x=550 y=550 width=200 height=105 xlink:href=\"%s\"/>\n",INST);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?25,%d,%d\"><RECT X=570 Y=580 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
    
    printf ("<image x=550 y=650 width=200 height=105 xlink:href=\"%s\"/>\n",CONTINUE);
    printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?26,%d,%d\"><RECT X=570 Y=680 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
    }

/**
 * @brief imprime o menu de poderes quando se apanha o baú
 * @param e estado de jogo
 */

void print_poderes(ESTADO e){
        if (e.especial.ativaBau==1){
        printf ("<image x=830 y=475 width=180 height=105 xlink:href=\"%s\"/>\n",PODER1);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?14,%d,%d\"> <RECT X=830 Y=505 WIDTH=183 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
        
        printf ("<image x=830 y=555 width=180 height=105 xlink:href=\"%s\"/>\n",PODER2);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?15,%d,%d\"> <RECT X=830 Y=585 WIDTH=183 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
 
        printf ("<image x=830 y=635 width=180 height=105 xlink:href=\"%s\"/>\n",PODER3);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?20,0,0\"> <RECT X=830 Y=665 WIDTH=183 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>");
 
        printf ("<image x=830 y=715 width=180 height=105 xlink:href=\"%s\"/>\n",PODER4);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?21,%d,%d\"> <RECT X=830 Y=745 WIDTH=183 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
        }
        else return;
        
    }
/**
 * @brief imprime a página Highscore e os 3 melhores scores
 * @param top struct com os 3 melhores scores
 */

void print_topscore (SCORES top){
        print_background();
        printf ("<image x=550 y=0 width=250 height=250 xlink:href=\"%s\"/>\n",TOPSCORE1);
        printf ("<image x=350 y=150 width=150 height=150 xlink:href=\"%s\"/>\n",TOPSCORE2);
        printf ("<image x=350 y=300 width=150 height=150 xlink:href=\"%s\"/>\n",TOPSCORE3);
        printf ("<image x=350 y=450 width=150 height=150 xlink:href=\"%s\"/>\n",TOPSCORE4);
        printf ("<rect x=600 y=160 width=150 height=100 RY=15 style=\"fill:#ffff00\"/>");
        printf ("<rect x=600 y=320 width=150 height=100 RY=15 style=\"fill:#b3b3b3\"/>");
        printf ("<rect x=600 y=470 width=150 height=100 RY=15 style=\"fill:#bf8040\"/>");
        
        printf ("<image x=550 y=650 width=200 height=105 xlink:href=\"%s\"/>\n",MENU);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue\"><RECT X=570 Y=680 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>");
        printf("<TEXT X=670 Y=210> %d </TEXT>\n",top.score[0]);
        printf("<TEXT X=670 Y=370> %d </TEXT>\n",top.score[1]);
        printf("<TEXT X=670 Y=520> %d </TEXT>\n",top.score[2]);
}
/**
 * @brief imprime a primeira página de instruções
 * @param e estado de jogo 
 */

void print_instructions (ESTADO e){
        print_background();

        printf ("<image x=100 y=0 width=400 height=205 xlink:href=\"%s\"/>\n",PIC1);
        printf ("<image x=100 y=100 width=400 height=205 xlink:href=\"%s\"/>\n",PIC2);
        printf ("<image x=100 y=200 width=400 height=205 xlink:href=\"%s\"/>\n",PIC3);
        printf ("<image x=150 y=350 width=300 height=105 xlink:href=\"%s\"/>\n",PIC4);
        printf ("<image x=100 y=400 width=400 height=205 xlink:href=\"%s\"/>\n",PIC5);
        printf ("<image x=100 y=550 width=400 height=150 xlink:href=\"%s\"/>\n",HEALTH);
        printf ("<image x=750 y=0 width=400 height=205 xlink:href=\"%s\"/>\n",PIC6);
        printf ("<image x=1120 y=70 width=100 height=50 xlink:href=\"%s\"/>\n",HEALTH);
        printf ("<image x=800 y=150 width=300 height=105 xlink:href=\"%s\"/>\n",PIC7);
        printf ("<image x=750 y=300 width=400 height=200 xlink:href=\"%s\"/>\n",PIC8);
        printf ("<image x=750 y=520 width=200 height=100 xlink:href=\"%s\"/>\n",PIC9);
        printf ("<image x=950 y=520 width=200 height=200 xlink:href=\"%s\"/>\n",PIC10);

        printf ("<image x=450 y=650 width=200 height=105 xlink:href=\"%s\"/>\n",MENU);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue\"><RECT X=470 Y=680 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>");
   
        printf ("<image x=700 y=650 width=200 height=105 xlink:href=\"%s\"/>\n",NEXT);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?28,%d,%d\"><RECT X=720 Y=680 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);


}
/**
 * @brief imprime a segunda página de instruções
 * @param e estado de jogo
 */

void print_instructions2 (ESTADO e){
        print_background();
        if (e.extra.enemy1 || e.extra.enemy2 || e.extra.enemy3 || e.extra.enemy4) printf ("<rect x=150 y=220 width=400 height=400 RY=15 style=\"fill:#c2c2a3\"/>");
        if (e.extra.enemy1==0&&e.extra.enemy2==0&&e.extra.enemy3==0&&e.extra.enemy4==0) {
            printf ("<image x=120 y=150 width=400 height=400 xlink:href=\"%s\"/>\n",DETAIL5);
            printf ("<image x=120 y=250 width=400 height=400 xlink:href=\"%s\"/>\n",DETAILPALL);
        }
        if (e.extra.enemy1) {
            printf ("<rect x=30 y=30 width=150 height=150 RY=15 style=\"fill:#c2c2a3\"/>");
            printf ("<image x=250 y=240 width=200 height=200 xlink:href=\"%s\"/>\n",DETAIL1);
            printf ("<image x=250 y=400 width=200 height=200 xlink:href=\"%s\"/>\n",TYPE1);
            printf ("<image x=250 y=440 width=200 height=200 xlink:href=\"%s\"/>\n",SCORE1);
        }
        if (e.extra.enemy2) {
            printf ("<rect x=180 y=30 width=150 height=150 RY=15 style=\"fill:#c2c2a3\"/>");
            printf ("<image x=250 y=240 width=200 height=200 xlink:href=\"%s\"/>\n",DETAIL2);
            printf ("<image x=250 y=400 width=200 height=200 xlink:href=\"%s\"/>\n",TYPE2);
            printf ("<image x=250 y=440 width=200 height=200 xlink:href=\"%s\"/>\n",SCORE2);
        }
        if (e.extra.enemy3) {
            printf ("<rect x=330 y=30 width=150 height=150 RY=15 style=\"fill:#c2c2a3\"/>");
            printf ("<image x=250 y=240 width=200 height=200 xlink:href=\"%s\"/>\n",DETAIL3);
            printf ("<image x=250 y=400 width=200 height=200 xlink:href=\"%s\"/>\n",TYPE3);
            printf ("<image x=250 y=440 width=200 height=200 xlink:href=\"%s\"/>\n",SCORE2);
        }
        if (e.extra.enemy4) {
            printf ("<rect x=470 y=30 width=150 height=150 RY=15 style=\"fill:#c2c2a3\"/>");
            printf ("<image x=250 y=240 width=200 height=200 xlink:href=\"%s\"/>\n",DETAIL4);
            printf ("<image x=250 y=400 width=200 height=200 xlink:href=\"%s\"/>\n",TYPE4);
            printf ("<image x=250 y=440 width=200 height=200 xlink:href=\"%s\"/>\n",SCORE2);
        }
        printf ("<image x=0 y=50 width=200 height=105 xlink:href=\"%s\"/>\n",ENEMY);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?31,%d,%d\"><RECT X=50 Y=70 WIDTH=160 HEIGHT=80 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);
  
        printf ("<image x=150 y=50 width=200 height=105 xlink:href=\"%s\"/>\n",ENEMY2);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?32,%d,%d\"><RECT X=200 Y=50 WIDTH=160 HEIGHT=90 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);

        printf ("<image x=300 y=50 width=200 height=105 xlink:href=\"%s\"/>\n",ENEMY3);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?33,%d,%d\"><RECT X=350 Y=50 WIDTH=150 HEIGHT=90 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);

        printf ("<image x=450 y=50 width=200 height=105 xlink:href=\"%s\"/>\n",ENEMY4);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?34,%d,%d\"><RECT X=480 Y=50 WIDTH=140 HEIGHT=100 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);

        printf ("<image x=450 y=650 width=200 height=105 xlink:href=\"%s\"/>\n",MENU);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue\"><RECT X=470 Y=680 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>");
   
        printf ("<image x=700 y=650 width=200 height=105 xlink:href=\"%s\"/>\n",BACK);
        printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/rogue?25,%d,%d\"><RECT X=720 Y=680 WIDTH=160 HEIGHT=50 RY=10 STYLE=\"fill-opacity:0\"/></A>",e.jog.x,e.jog.y);

        printf ("<image x=900 y=0 width=170 height=170 xlink:href=\"%s\"/>\n",PODER1);
        printf ("<image x=800 y=40 width=170 height=200 xlink:href=\"%s\"/>\n",DETAILP1);
        printf ("<image x=940 y=110 width=100 height=50 xlink:href=\"%s\"/>\n",HEALTH);
        printf ("<image x=900 y=120 width=170 height=170 xlink:href=\"%s\"/>\n",PODER2);
        printf ("<image x=800 y=170 width=380 height=200 xlink:href=\"%s\"/>\n",DETAILP2);
        printf ("<image x=900 y=270 width=170 height=170 xlink:href=\"%s\"/>\n",PODER3);
        printf ("<image x=800 y=320 width=380 height=200 xlink:href=\"%s\"/>\n",DETAILP3);
        printf ("<image x=900 y=420 width=170 height=170 xlink:href=\"%s\"/>\n",PODER4);
        printf ("<image x=800 y=470 width=380 height=200 xlink:href=\"%s\"/>\n",DETAILP4);
        printf ("<image x=850 y=560 width=100 height=50 xlink:href=\"%s\"/>\n",HEALTH);


}


/**
 * @brief imprime todo o jogo chamando outras funções
 * @param e estado de jogo
 * @param top struct com os 3 melhores scores
 */

void jogo (ESTADO e,SCORES top){
    if (e.especial.menu) {
        print_menu(e);
    }
    if (e.especial.topscore &&e.especial.menu==2){
        print_topscore(top); 
    }
    if (e.especial.instruction &&e.especial.menu==2){
        print_instructions(e);
    }
    if (e.especial.instruction2) {
        print_instructions2(e);
    }
    if (e.vida<=0) { 
        print_background();
        print_end(e);
        print_info(e);
    }

    if (e.vida >0 && e.especial.menu==0) {
         
        print_background ();
        print_board();
        print_enemies(e);
        print_door (e);
        print_walls(e);
        print_bau(e);
        print_player(e);
        print_info (e);
        print_brestart();
        print_bcheat(e);
        print_bnext(e);
        print_poderes(e);
        print_bguardar(e);

    }
}
/**
 * @brief guarda o estado de jogo num ficheiro para ser continuado
 * @param e estado de jogo
 */

void guardar_estado (ESTADO e){
    size_t nmember=0;

    FILE *f;

    f = fopen ("/var/www/html/continua.txt","wb");
    if (f ==NULL || (nmember = fwrite (&e,sizeof (ESTADO) , 1, f)) != 1)
        perror ("nope2"),exit (1);

    fclose(f);
}
/**
 * @brief lê o estado de jogo que está guardado e importa para o jogo
 * @returns novo estado de jogo
 */

ESTADO ler_estado_guardado (){
    size_t nmember=0;
    ESTADO e={0};

    FILE *f;
    f = fopen ("/var/www/html/continua.txt","rb");
    if (f ==NULL) 
        perror ("nope"), exit (1);
    nmember = fread (&e,sizeof (ESTADO) , 1, f);
    
    if (nmember != 1) return e;

    fclose(f);

    return e;
}
/**
 * @brief lê o estado do ficheiro de jogo (cada jogada lê)
 * @param *args parâmetros da Query String
 * @returns estado de jogo
 */

ESTADO ler_estado (char *args){
    size_t nmember=0;
    ESTADO e={0};

    FILE *fp;
    fp = fopen ("/var/www/html/estadojogo.txt","rb");
    if (fp ==NULL) 
        perror ("nope"), exit (1);
    nmember = fread (&e,sizeof (ESTADO) , 1, fp);

    if(args != NULL && *args == '\0' && fp != NULL && (nmember =fread (&e,sizeof (ESTADO) , 1, fp))!=1)
        e= inicializar(1,3,0,1);
    fclose(fp);

    return e;
}
/**
 * @brief escreve o estado de jogo no ficheiro (cada jogada)
 * @param e estado de jogo
 */

void escreve_estado (ESTADO e){
    size_t nmember=0;

    FILE *fp;

    fp = fopen ("/var/www/html/estadojogo.txt","wb");
    if (fp ==NULL || (nmember = fwrite (&e,sizeof (ESTADO) , 1, fp)) != 1)
        perror ("nope2"),exit (1);

    fclose(fp);
}
/**
 * @brief guarda os melhores scores num ficheiro
 * @param top struct com os melhores scores
 */

void guardar_highscore (SCORES top){

    FILE *f;

    f = fopen ("/var/www/html/highscore6.txt","wb");
    if (f ==NULL)
        perror ("nope2"),exit (1);
    
    for (int i=0; i<3;i++){
        fprintf(f,"%d\n",top.score[i]);
    }
    fclose(f);
}
/**
 * @brief lê os melhores scores do ficheiro
 * @returns struct com melhores scores
 */

SCORES ler_highscore (){
    SCORES top={0};
    char line[1024];

    FILE *f;
    f = fopen ("/var/www/html/highscore6.txt","rb");
    if (f ==NULL) 
        perror ("nope"), exit (1);
    
    for (int i=0; i<3; i++){
        if (fgets(line,sizeof (line), f)==NULL){
            perror("no more scores");break;}
        sscanf(line,"%d",&top.score[i]);
    }

    fclose(f);

    return top;
}
/**
 * @brief modifica a struct de melhores scores conforme o score obtido no jogo anterior
 * @param top struct com os melhores scores
 * @param x score a colocar
 * @returns struct atualizada dos melhores scores
 */

SCORES modifica (SCORES top, int x){
    if (x>= top.score[0]) {top.score[2]=top.score[1],top.score[1]=top.score[0],top.score[0]=x;return top;}
    if (x>= top.score[1]) {top.score[2]=top.score[1],top.score[1]=x;return top;}
    if (x>= top.score[2]) {top.score[2]=x;return top;}
    return top;
}
/**
 * @brief função que comanda o jogo todo, lê Query String, manda alterar o estado, manda guardar/ler ficheiros, passa de nível, e imprime o jogo
 */

void parser() {
    ESTADO e;
    int y;
    int acao,x1,y1;
    SCORES top;
    char *args = getenv ("QUERY_STRING");
    if (args != NULL)
        sscanf (args,"%d,%d,%d",&acao,&x1,&y1);

    e =ler_estado (args);
    top=ler_highscore();
    
    if (args !=NULL && ((e.jog.x==x1 && e.jog.y==y1)||(x1==0 &&y1==0)|| (acao==9)||(acao==10)||(acao==11)||(acao==12))) e= alteraAcao (e,acao,x1,y1),e=alteraAcao_menu (e,acao);

    if (e.ficheiro.ler==1) e=ler_estado_guardado(), e.ficheiro.ler=0;
    
    y=e.num_inimigos + e.num_inimigos2+ e.num_inimigos3+e.num_inimigos4;

    if ((e.jog.x == e.door.x && e.jog.y == e.door.y) && e.vida==5 && y ==e.morto) {e = inicializar (e.nivel+1, e.vida,e.score,0);}
    else {
        if ((e.jog.x == e.door.x && e.jog.y == e.door.y)  && y==e.morto){ e = inicializar(e.nivel+1, e.vida+1,e.score,0);}
    }
    if (e.ficheiro.guardou==1&& e.vida<=0) guardar_estado(inicializar(1,3,0,1));
    if (e.ficheiro.guardar==1) guardar_estado (e),e.ficheiro.guardar=0;

    escreve_estado (e);
    if (e.vida<=0){
        top = modifica (top,e.score);
        guardar_highscore(top);
    }

    jogo (e,top);
}


