#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fila.h"
#include "pilha.h"
#include "funcoes.h"
#include <math.h>

int main(){

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




    // OS TOKENS
    /*char *teste1;
    //teste1=(char*)malloc(sizeof(char));
    printf("Tokens separados:\n");
    for (int i = 0; i < contadorToken; i++) {
        recupere_da_fila(filaDeEntrada,(ElementoDeFila*)&teste1);
        printf("'%s'\n", teste1);
        remova_elemento_da_fila(&filaDeEntrada);
        teste1 = NULL;
    }
    //free(teste1);*/




    // PROCESSAMENTO
    char* op_Fila;
    char* op_Topo;
    while (!fila_vazia(filaDeEntrada)) {
        recupere_da_fila(filaDeEntrada, (ElementoDeFila*)&op_Fila);

        if (isdigit(*op_Fila)) {                                                // se for digito
            guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Fila);
        } else {                                                                // se for operador
            if (*op_Fila == ')') {                                              // se for ')', desempilha até achar ')'
                while (!pilha_vazia(Operadores)) {
                    recupere_da_pilha(Operadores, (ElementoDePilha*)&op_Topo);
                    remova_elemento_da_pilha(&Operadores);
                    if (*op_Topo == '(') break;
                    guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
                }
            } else {
                while (!pilha_vazia(Operadores)) {                              // se for operador comun, desempilha até achar false na tabela
                    recupere_da_pilha(Operadores, (ElementoDePilha*)&op_Topo);
                    if (!matriz[posicao(*op_Topo)][posicao(*op_Fila)]) break;
                    remova_elemento_da_pilha(&Operadores);
                    guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
                }
                guarde_na_pilha(&Operadores, (ElementoDePilha)op_Fila);
            }
        }

        remova_elemento_da_fila(&filaDeEntrada);
    }

    if (fila_vazia(filaDeEntrada) && !pilha_vazia(Operadores)){                 // desempilhamento até pilha_vazia(Operadores)
        while (!pilha_vazia(Operadores)){
            recupere_da_pilha(Operadores,(ElementoDePilha*)&op_Topo);
            guarde_na_fila(&filaDeSaida,(ElementoDeFila)op_Topo);
            remova_elemento_da_pilha(&Operadores);
        }
    }

    free_fila(&filaDeEntrada);
    free_pilha(&Operadores);




    // FILA DE SAÍDA
    /*char *teste2;
    printf("Fila de saida separados:\n");
    while (!fila_vazia(filaDeSaida)) {
        recupere_da_fila(filaDeSaida, (ElementoDeFila *)&teste2);
        printf("'%s'\n", teste2);
        remova_elemento_da_fila(&filaDeSaida);
        teste2 = NULL;
    }*/




    // CALCULO
    Pilha pilhaDeResultados;
    nova_pilha(&pilhaDeResultados, 100);

    char* valor_recuperado;
    while(!fila_vazia(filaDeSaida)){
        recupere_da_fila(filaDeSaida,(ElementoDeFila*)&valor_recuperado);
        remova_elemento_da_fila(&filaDeSaida);

        if (isdigit(*valor_recuperado)) {                                       // se for digito
            double* valor = (double*)malloc(sizeof(double));                    // converte string para double e empilha
            *valor = atof(valor_recuperado);
            guarde_na_pilha(&pilhaDeResultados, (ElementoDePilha)valor);
        } else {                                                                // se for operador
            if (!pilha_vazia(pilhaDeResultados)) {                              // desempilha dois valores, e faz a conta com o operador recuperado
                double *num2, *num1;
                recupere_da_pilha(pilhaDeResultados, (ElementoDePilha*)&num2);
                remova_elemento_da_pilha(&pilhaDeResultados);
                recupere_da_pilha(pilhaDeResultados, (ElementoDePilha*)&num1);
                remova_elemento_da_pilha(&pilhaDeResultados);

                double* resultado = (double*)malloc(sizeof(double));

                switch (*valor_recuperado) {
                    case '+': *resultado = *num1 + *num2; break;
                    case '-': *resultado = *num1 - *num2; break;
                    case '*': *resultado = *num1 * *num2; break;
                    case '/': *resultado = *num1 / *num2; break;
                    case '^': *resultado = pow(*num1, *num2); break;
                    default: 
                        printf("Operador inválido: %c\n", *valor_recuperado);
                        *resultado = 0;
                        break;
                }

                guarde_na_pilha(&pilhaDeResultados, (ElementoDePilha)resultado);

                free(num1);
                free(num2);
            }
        }
    }




    // RESULTADO FINAL
    if (!pilha_vazia(pilhaDeResultados)) {
        double* resultadoFinal;
        recupere_da_pilha(pilhaDeResultados, (ElementoDePilha*)&resultadoFinal);
        printf("\nResultado final: %.2f\n\n", *resultadoFinal);
        free(resultadoFinal);
        resultadoFinal = NULL;
        remova_elemento_da_pilha(&pilhaDeResultados);
    }
    



    free_fila(&filaDeSaida);
    free_pilha(&pilhaDeResultados);

    return 0;
}