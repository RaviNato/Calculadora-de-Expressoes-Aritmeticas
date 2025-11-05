#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fila.h"
#include "pilha.h"

unsigned int posicao(char operador)
{
    switch (operador)
    {
    case '(':
        return 0;
    case '^':
        return 1;
    case '*':
        return 2;
    case '/':
        return 3;
    case '+':
        return 4;
    case '-':
        return 5;
    case ')':
        return 6;
    default:
        return 7; // invalido
    }
}

int main()
{
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
    nova_fila(&filaDeEntrada, 100);
    nova_fila(&filaDeSaida, 100);
    nova_pilha(&Operadores, 100);

    char expressao[100];
    char tokens[100][20];
    int contadorToken = 0;

    printf("Digite a expressao matematica: ");
    fgets(expressao, sizeof(expressao), stdin);

    for (int i = 0; (expressao[i] != '\0' && expressao[i] != '\n'); i++)
    {
        if (isspace(expressao[i]))
        { // se for espaço
            continue;
        }
        else if (isdigit(expressao[i]))
        { // se for numero
            int j;
            for (j = 0; isdigit(expressao[i]); j++)
            {
                tokens[contadorToken][j] = expressao[i++];
            }
            tokens[contadorToken][j] = '\0';
            guarde_na_fila(&filaDeEntrada, (ElementoDeFila)tokens[contadorToken]);
            contadorToken++;
            i--;
        }
        else
        { // se for simbolo
            tokens[contadorToken][0] = expressao[i];
            tokens[contadorToken][1] = '\0';
            guarde_na_fila(&filaDeEntrada, (ElementoDeFila)tokens[contadorToken]);
            contadorToken++;
        }
    }

    // MOSTRANDO OS TOKENS
    /*char *teste1;
    //teste1=(char*)malloc(sizeof(char));
    printf("Tokens separados:\n");
    for (int i = 0; i < contadorToken; i++) {
        //guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[i]);

        recupere_da_fila(filaDeEntrada,(ElementoDeFila*)&teste1);
        printf("'%s'\n", teste1);
        remova_elemento_da_fila(&filaDeEntrada);
        teste1 = NULL;
    }
    //free(teste1);*/

    // TABELA DE DECISÃO
    boolean matriz[7][7] = {
        //  (      ^      *      /      +      -      )
        {false, false, false, false, false, false, true}, // (
        {false, false, true, true, true, true, true},     // ^
        {false, false, true, true, true, true, true},     // *
        {false, false, true, true, true, true, true},     // /
        {false, false, false, false, true, true, true},   // +
        {false, false, false, false, true, true, true},   // -
        {false, false, false, false, false, false, false} // )
    };

    /*char op_Topo = '(';
    char op_Fila = ')';

    printf("\nTeste da matriz: '%c' x '%c' = %d\n",
           op_Topo, op_Fila, matriz[posicao(op_Topo)][posicao(op_Fila)]);*/

    // PROCESSAMENTO
    char *op_Fila;
    char *op_Topo;
    while (!fila_vazia(filaDeEntrada))
    {
        //op_Fila = (char *)malloc(sizeof(char));
        recupere_da_fila(filaDeEntrada, (ElementoDeFila *)&op_Fila);

        if (isdigit(*op_Fila))
        { 
            guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Fila);
        }
        else
        {
            if (*op_Fila == ')' && !pilha_vazia(Operadores))
            {
                //op_Topo = (char *)malloc(sizeof(char));
                recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
                while (*op_Topo != '(')
                {
                    guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
                    remova_elemento_da_pilha(&Operadores);
                    //op_Topo = NULL;
                    recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
                }
                remova_elemento_da_pilha(&Operadores);
                op_Topo = NULL;
            }
            else
            {
                if (!pilha_vazia(Operadores))
                {
                    
                    //op_Topo = (char *)malloc(sizeof(char));
                    recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);

                    while (matriz[posicao(*op_Topo)][posicao(*op_Fila)] && !pilha_vazia(Operadores))
                    {
                        guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
                        remova_elemento_da_pilha(&Operadores);
                        //op_Topo = NULL;
                        recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
                    }
                    op_Topo = NULL;   
                }
                guarde_na_pilha(&Operadores, (ElementoDePilha)op_Fila);
            }
        }
        remova_elemento_da_fila(&filaDeEntrada);
        op_Fila = NULL;
    }
    
    //free(op_Fila);

    if (fila_vazia(filaDeEntrada) && !pilha_vazia(Operadores))
    {
        //op_Topo = (char *)malloc(sizeof(char));
        while (!pilha_vazia(Operadores))
        {
            recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
            guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
            remova_elemento_da_pilha(&Operadores);
            //op_Topo = NULL;
        }
    }
    //free(op_Topo);

    free_fila(&filaDeEntrada);
    free_pilha(&Operadores);






    char *teste2;
    //teste2=(char*)malloc(sizeof(char));

    printf("Fila de saida separados:\n");
    while (!fila_vazia(filaDeSaida)) {
        recupere_da_fila(filaDeSaida, (ElementoDeFila *)&teste2);
        printf("'%s'\n", teste2);
        remova_elemento_da_fila(&filaDeSaida);
        teste2 = NULL;
    }


    //free(teste2);



    return 0;
}