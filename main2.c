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
    // DEFINIÇÃO DA EXPRESSÃO
    Fila filaDeEntrada;
    Fila filaDeSaida;
    Pilha Operadores;
    nova_fila(&filaDeEntrada, 100);
    nova_fila(&filaDeSaida, 100);
    nova_pilha(&Operadores, 100);

    char expressao[100];
    char tokens[100][20]; // guardamos strings aqui
    int contadorToken = 0;

    printf("Digite a expressao matematica: ");
    if (!fgets(expressao, sizeof(expressao), stdin)) {
        printf("Erro ao ler entrada.\n");
        return 1;
    }

    // Separa tokens e guarda ponteiros para tokens[][] na fila de entrada
    for (int i = 0; (expressao[i] != '\0' && expressao[i] != '\n'); i++)
    {
        if (isspace((unsigned char)expressao[i]))
        {
            continue;
        }
        else if (isdigit((unsigned char)expressao[i]))
        {
            int j;
            for (j = 0; isdigit((unsigned char)expressao[i]); j++)
            {
                tokens[contadorToken][j] = expressao[i++];
            }
            tokens[contadorToken][j] = '\0';
            // guarda o ponteiro para token atual
            guarde_na_fila(&filaDeEntrada, (ElementoDeFila)tokens[contadorToken]);
            contadorToken++;
            i--;
        }
        else
        {
            tokens[contadorToken][0] = expressao[i];
            tokens[contadorToken][1] = '\0';
            guarde_na_fila(&filaDeEntrada, (ElementoDeFila)tokens[contadorToken]);
            contadorToken++;
        }
    }

    // TABELA DE DECISÃO
    boolean matriz[7][7] = {
        //  (      ^      *      /      +      -      )
        {false, false, false, false, false, false, true}, // (
        {false, false, true,  true,  true,  true,  true}, // ^
        {false, false, true,  true,  true,  true,  true}, // *
        {false, false, true,  true,  true,  true,  true}, // /
        {false, false, false, false, true,  true,  true}, // +
        {false, false, false, false, true,  true,  true}, // -
        {false, false, false, false, false, false, false} // )
    };

    // PROCESSAMENTO (shunting-yard-like)
    char *op_Fila = NULL; // ponteiro para token vindo da fila
    char *op_Topo = NULL; // ponteiro para token no topo da pilha

    while (!fila_vazia(filaDeEntrada))
    {
        // recuperar ponteiro armazenado na fila (não alocar)
        recupere_da_fila(filaDeEntrada, (ElementoDeFila *)&op_Fila);

        if (isdigit((unsigned char)*op_Fila))
        {
            // número → vai direto para fila de saída
            guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Fila);
        }
        else
        {
            if (*op_Fila == ')' && !pilha_vazia(Operadores))
            {
                // pop até encontrar '('
                recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
                while (!pilha_vazia(Operadores) && *op_Topo != '(')
                {
                    guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
                    remova_elemento_da_pilha(&Operadores);
                    if (!pilha_vazia(Operadores))
                        recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
                }
                // remover '(' se houver
                if (!pilha_vazia(Operadores) && *op_Topo == '(')
                {
                    remova_elemento_da_pilha(&Operadores);
                }
                op_Topo = NULL;
            }
            else
            {
                // enquanto top da pilha tem precedência sobre o operador atual,
                // enviar top para a fila de saída
                if (!pilha_vazia(Operadores))
                {
                    recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
                    while (!pilha_vazia(Operadores) &&
                           posicao(*op_Topo) < 7 && posicao(*op_Fila) < 7 &&
                           matriz[posicao(*op_Topo)][posicao(*op_Fila)])
                    {
                        guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
                        remova_elemento_da_pilha(&Operadores);
                        if (!pilha_vazia(Operadores))
                            recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
                    }
                    op_Topo = NULL;
                }
                // empilha o operador atual
                guarde_na_pilha(&Operadores, (ElementoDePilha)op_Fila);
            }
        }

        // remove token da fila de entrada (já processado)
        remova_elemento_da_fila(&filaDeEntrada);
        op_Fila = NULL;
    }

    // esvazia pilha de operadores para a fila de saída
    while (!pilha_vazia(Operadores))
    {
        recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
        guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
        remova_elemento_da_pilha(&Operadores);
    }

    // libera estruturas de dados (não os tokens, pois são array local)
    free_fila(&filaDeEntrada);
    free_pilha(&Operadores);

    // IMPRESSÃO DA FILA DE SAÍDA
    char *teste = NULL;
    printf("Fila de saida separados:\n");
    while (!fila_vazia(filaDeSaida))
    {
        // recupere pointer armazenado na fila
        recupere_da_fila(filaDeSaida, (ElementoDeFila *)&teste);
        // imprimir string (use teste, NÃO *teste)
        printf("'%s'\n", teste);
        remova_elemento_da_fila(&filaDeSaida);
        teste = NULL;
    }

    // libera fila de saída ao final
    free_fila(&filaDeSaida);

    return 0;
}
