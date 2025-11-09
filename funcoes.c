#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fila.h"
#include "pilha.h"
#include <math.h>
#include "funcoes.h"



unsigned int posicao(char operador) {
    switch (operador) {
        case '(': return 0;
        case '^': return 1;
        case '*': return 2;
        case '/': return 3;
        case '+': return 4;
        case '-': return 5;
        case ')': return 6;
        default:  return 7; //invalido
    }
}


// TABELA DE DECISÃO
boolean matriz[7][7] = {
    //  (      ^      *      /      +      -      )
    { false, false, false, false, false, false, true  }, // (
    { false, false, true,  true,  true,  true,  true  }, // ^
    { false, false, true,  true,  true,  true,  true  }, // *
    { false, false, true,  true,  true,  true,  true  }, // /
    { false, false, false, false, true,  true,  true  }, // +
    { false, false, false, false, true,  true,  true  }, // -
    { false, false, false, false, false, false, false }  // )
};