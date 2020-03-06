#ifndef ___ESTADO_H___
#define ___ESTADO_H___
/**
 * @brief máximo de inimigos
 */
#define MAX_INIMIGOS 100
/**
 * @brief máximo de obstáculos
 */
#define MAX_OBSTACULOS 100
/**
 * @brief número de inimigos
 */
#define NUMINIMIGOS 10
/**
 * @brief número de obstáculos
 */
#define NUMOBSTACULOS 20
/**
 * @brief abcissa de um monstro do tipo 1
 */
#define X1 e.inimigo[i].x
/**
 * @brief ordenada de um monstro do tipo 1
 */
#define Y1 e.inimigo[i].y
/**
 * @brief abcissa de um monstro do tipo 2
 */
#define X2 e.inimigo2[i].x
/**
 * @brief ordenada de um monstro do tipo 2
 */
#define Y2 e.inimigo2[i].y
/**
 * @brief abcissa de um monstro do tipo 3
 */
#define X3 e.inimigo3[i].x
/**
 * @brief ordenada de um monstro do tipo 3
 */
#define Y3 e.inimigo3[i].y
/**
 * @brief abcissa de um monstro do tipo 4
 */
#define X4 e.inimigo4[i].x
/**
 * @brief ordenada de um monstro do tipo 4
 */
#define Y4 e.inimigo4[i].y
/**
 * @brief melhores scores
 */

typedef struct score{
	/** 3 melhores scores*/
	int score[3];
} SCORES;

/**
 * @brief posição
 */
typedef struct posicao {
	/** abcissa da posição*/
	char x;
	/** ordenada da posição*/
	char y;
} POSICAO;

/**
 * @brief struct com as variáveis de controlo para informações sobre monstros
 */
typedef struct extra {
	/** variável de controlo para ver as informações do primeiro tipo de monstro*/
	char enemy1;
	/** variável de controlo para ver as informações do segundo tipo de monstro*/
	char enemy2;
	/** variável de controlo para ver as informações do terceiro tipo de monstro*/
	char enemy3;
	/** variável de controlo para ver as informações do quarto tipo de monstro*/
	char enemy4;
	
} EXTRA;

/**
 * @brief struct com as variáveis de controlo para ficheiros
 */
typedef struct ficheiro {
	/** variável de controlo para dizer que é para guardar o estado de jogo*/
	char guardar;
	/** variável de controlo para dizer que é para ler do ficheiro o estado de jogo */
	char ler;
	/** variável de controlo para saber se o presente jogo foi guardado antes*/
	char guardou;
} FICHEIRO;

/**
 * @brief bónus do jogo
 */
typedef struct especial {
	/** variável de controlo para dizer que é para mostrar o que o monstro de primeiro tipo ataca*/
	char show;
	/** variável de controlo para dizer que é para mostrar o que o monstro de segundo tipo ataca*/
	char show2;
	/** variável de controlo para dizer que é para mostrar o que o monstro de terceiro tipo ataca*/
	char show3;
	/** variável de controlo para dizer que é para mostrar o que o monstro de quarto tipo ataca*/
	char show4;
	/** posição do monstro que vou mostrar o que ataca*/
	POSICAO ataque;	
	/** variável de controlo para mostrar os ataques de todos os monstros*/
	char cheat;
	/** variável de controlo para saber se estou no menu ou não*/
	char menu;
	/** posição do baú*/
	POSICAO bau;
	/** variável de controlo para mostrar o menu de poderes*/
	char ativaBau;
	/** variável de controlo para executar o poder 2*/
	char poder2;
	/** variável de controlo para executar o poder 3*/
	char poder3;
	/** variável de controlo para evitar voltar atrás no jogo*/
	char nope;
	/** variável de controlo para mostrar a página de Highscores*/
	char topscore;
	/** variável de controlo para mostrar a primeira página de instruções*/
	char instruction;
	/** variável de controlo para mostrar a segunda página de instruções*/
	char instruction2;
	
} ESPECIAL;

/**
 * @brief estado de jogo
 */
typedef struct estado {
	/** score**/
	unsigned char score;
	/** vida do jogador**/	
	unsigned char vida;
	/**ações de botões **/
	unsigned char acao;
	/** ver numero de mortos**/
	unsigned char morto;
	/** Nível do jogo**/
	unsigned char nivel;
	/** A posição do jogador */
	POSICAO jog;
	/** posição da porta*/
	POSICAO door;
	/** O nº de inimigos tipo 1 */
	char num_inimigos;	
	/** O nº de inimigos tipo 2 */
	char num_inimigos2;
	/** O nº de inimigos tipo 3 */
	char num_inimigos3;
	/** O nº de inimigos tipo 4 */
	char num_inimigos4;
	/** O nº de obstáculos */
	char num_obstaculos;
	/** Array com a posição dos inimigos */
	POSICAO inimigo[MAX_INIMIGOS];
	/** Array com a posição dos inimigos */
	POSICAO inimigo2[MAX_INIMIGOS];
	/** Array com a posição dos inimigos */
	POSICAO inimigo3[MAX_INIMIGOS];
	/** Array com a posição dos inimigos */
	POSICAO inimigo4[MAX_INIMIGOS];
	/** Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];
	/** Struct com extras para o jogo*/	
	ESPECIAL especial;
	/** Struct com informações sobre ficheiros*/
	FICHEIRO ficheiro;
	/** Struct com extras para o jogo*/
	EXTRA extra;
	
} ESTADO;

/**
 * @brief Função que converte um estado numa string
 * @param e O estado
 * @returns A string correspondente ao estado e
 */
char *estado2str(ESTADO e);

/**
 * @brief Função que converte uma string num estado 
 * @param argumentos Uma string contendo os argumentos passados à CGI
 * @returns O estado correspondente à string dos argumentos
 */
ESTADO str2estado(char *argumentos);
/**
 * @brief verifica se tem inimigo em (x,y)
 * @param e estado de jogo
 * @param x abcissa 
 * @param y ordenada
 * @returns 0 caso haja inimigo em (x,y) senão 1
 */
int temInimigo (ESTADO e, int x,int y);

/**
 * @brief verifica se é possível a posição
 * @param e estado de jogo
 * @param x abcissa 
 * @param y ordenada
 * @returns 0 caso haja alguma coisa em (x,y) senão 1
 */
int pospossivel (ESTADO e, int x, int y);
/**
 * @brief verifica se é possível a posição para me conseguir mover
 * @param e estado de jogo
 * @param x abcissa 
 * @param y ordenada
 * @returns 0 caso haja alguma coisa em (x,y) senão 1
 */
int pospossivel2 (ESTADO e, int x, int y);
/**
 * @brief inicializa o estado
 * @param nivel nivel que está o jogador
 * @param vida vida que o jogador tem 
 * @param score score que o jogador tem
 * @param menu se tiver a 1 estou no menu senão está o jogo a decorrer
 * @returns estado de jogo
 */
ESTADO inicializar(int nivel,int vida,int score,int menu);
/**
 * @brief altera o estado de jogo conforme a ação
 * @param e estado de jogo
 * @param acao ação a executar
 * @param x abcissa de monstro ou jogador
 * @param y ordenada de monstro ou jogador
 * @returns estado de jogo
 */
ESTADO alteraAcao (ESTADO e, int acao, int x,int y);
/**
 * @brief altera o estado de jogo conforme a ação
 * @param e estado de jogo
 * @param acao ação a executar
 * @returns estado de jogo
 */
ESTADO alteraAcao_menu (ESTADO e, int acao);













#endif
