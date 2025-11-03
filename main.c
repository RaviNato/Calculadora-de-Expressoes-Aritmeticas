#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fila.h"
#include "pilha.h"

int main(){
    /* EXMPLO DO MALIGNO

    Fila fil;
    nova_fila (&fil,10);
    
    int*  i;

    i=(int*)malloc(sizeof(int));
    *i=2;
    guarde_na_fila (&fil,(ElementoDeFila)i);
    i=NULL;

    i=(int*)malloc(sizeof(int));
    *i=3;
    guarde_na_fila (&fil,(ElementoDeFila)i);
    i=NULL;

    i=(int*)malloc(sizeof(int));
    *i=5;
    guarde_na_fila (&fil,(ElementoDeFila)i);
    i=NULL;

    while (!fila_vazia(fil))
    {
        recupere_da_fila(fil,(ElementoDeFila*)&i);
        remova_elemento_da_fila(&fil);
        printf("%d ",*i);
        free(i);
        i=NULL;
    }

    free_fila(&fil);
    */





    // DEFINIÇÃO DA EXPRESSÃO
    Fila filaDeEntrada;
    Fila filaDeSaida;
    Pilha Operadores;
    nova_fila (&filaDeEntrada,100);
    nova_fila (&filaDeSaida,100);
    nova_pilha (&Operadores,100);

    char expressao[100];
    char tokens[100][20];
    int contadorToken = 0;

    printf("Digite a expressao matematica: ");
    fgets(expressao, sizeof(expressao), stdin);

    for (int i = 0; (expressao[i] != '\0' && expressao[i] != '\n'); i++){
        if (isspace(expressao[i])) {                                        // se for espaço
            continue;
            
        } else if (isdigit(expressao[i])) {                                 // se for numero
            int j;
            for (j = 0; isdigit(expressao[i]); j++){
                tokens[contadorToken][j] = expressao[i++];
            }
            tokens[contadorToken][j] = '\0';
            guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[contadorToken]);
            contadorToken++;
            i--;
            
        } else {                                                            // se for simbolo
            tokens[contadorToken][0] = expressao[i];
            tokens[contadorToken][1] = '\0';
            guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[contadorToken]);
            contadorToken++;
        }
    }


    // MOSTRANDO OS TOKENS
    /*char *teste;
    teste=(char*)malloc(sizeof(char));

    printf("Tokens separados:\n");
    for (int i = 0; i < contadorToken; i++) {
        //guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[i]);

        recupere_da_fila(filaDeEntrada,(ElementoDeFila*)&teste);
        printf("'%s'\n", teste);
        remova_elemento_da_fila(&filaDeEntrada);
    }

    free(teste);
    teste = NULL;*/





    // TABELA DE DECISÃO
    boolean matriz[7][7] = {
        //  (      ^      *      /      +      -      )
        { false, false, false, false, false, false, true }, // (
        { false, false, true,  true,  true,  true,  true }, // ^
        { false, false, true,  true,  true,  true,  true }, // *
        { false, false, true,  true,  true,  true,  true }, // /
        { false, false, false, false, true,  true,  true }, // +
        { false, false, false, false, true,  true,  true }, // -
        { false, false, false, false, false, false, false }  // )
    };

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

    char op_Topo = '(', op_Fila = ')';

    printf("\nTeste da matriz: '%c' x '%c' = %d\n",
           op_Topo, op_Fila, matriz[posicao(op_Topo)][posicao(op_Fila)]);







    // PROCESSAMENTO
    char* a;
    while(fila_cheia(filaDeEntrada)){
        a=(char*)malloc(sizeof(char));
        recupere_da_fila(filaDeEntrada,(ElementoDeFila*)&a);

        if (isdigit(a)){                                    // se for digito
            guarde_na_fila(&filaDeSaida,(ElementoDeFila)a);
        } else {                                            // se for operador
            if (pilha_cheia(Operadores)){
                //desempilhamento
                // se for ) faz desempilhamento até (, e () são deletados
                // se for comun, desempilha até achar F na tabela
            }
            // empilhamento
            guarde_na_pilha(&Operadores,(ElementoDePilha)a);
        } 

        remova_elemento_da_fila(&filaDeEntrada);
        a = NULL;
    }
    free(a);

    if (fila_vazia(filaDeEntrada) && pilha_cheia(Operadores)){
        // desempilhamento até pilha_vazia(Operadores)
    }

    free_fila(&filaDeEntrada);
    free_pilha(&Operadores);








    return 0;
}