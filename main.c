#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "estado.h"
#include <time.h>
/**
 * @file
 */

/**
 * @brief indicações de html, titulo de jogo e tamanho do svg
 */


void print_header () {

    printf ("Content-Type: text/html; charset=utf-8\n\n");
    printf ("<header><title> Rogue </title></header>\n");
    printf ("<body>\n");
    printf ("<svg width=1500 height=900>\n");

}
/**
 * @brief fecha svg e body
 */


void print_footer () {
    
    printf ("</svg>\n");
    printf ("</body>\n");
}
/**
 * @brief main do jogo
 */


int main () {
    srand(time (NULL));
    print_header ();
    parser ();
    print_footer ();
    return 0;
}
