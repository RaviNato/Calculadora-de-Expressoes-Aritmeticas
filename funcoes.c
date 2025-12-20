#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "fila.h"
#include "pilha.h"
#include "funcoes.h"

/*
VALIDAÇÕES FEITAS:
    dar erro se houver algo diferente de "1234567890+-/*()^ "
    dar erro se houver espaço entre digitos "5 9"
    dar erro se não houver mais elementos na filadesaida mas houver mais de um elemento na pilhaderesultados "expressao mal formada"
    dar erro se houver divisão por zero
    dar erro se começar ou terminar com operador
    dar erro se houver operador antes de ')'
    dar erro se houver operador depois de '('
    dar erro se houver operador seguido de operador, excluso '(' e ')'
*/

// DERTERMINAR COLUNA E LINHA DA TABELA
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

// PRINTAR FILA
void imprimir_fila(Fila fila) {
    char* temp;
    printf("\nFila: ");
    while (!fila_vazia(fila)) {
        recupere_da_fila(fila, (ElementoDeFila*)&temp);
        printf("%s ", temp);
        remova_elemento_da_fila(&fila);
        temp = NULL;
    }
    printf("\n\n");
    exit(EXIT_SUCCESS);
}

// DEFINIR EXPRESSÃO INFIXA
Fila definir_expressao_infixa(void){
    Fila filaDeEntrada;
    nova_fila (&filaDeEntrada,100);

    char expressao[100];
    char tokens[100][20];
    int contadorToken = 0, espacoentredigitos = 0, divisaoporzero = 0, comecoucomoperador = 0, terminoucomoperador = 0, operadorduplo = 0;

    printf("\nDigite a expressao matematica: ");
    fgets(expressao, sizeof(expressao), stdin);

    for (int i = 0; (expressao[i] != '\0' && expressao[i] != '\n'); i++){
        if (expressao[i]=='0'||expressao[i]=='1'||expressao[i]=='2'||expressao[i]=='3'||
            expressao[i]=='4'||expressao[i]=='5'||expressao[i]=='6'||expressao[i]=='7'||
            expressao[i]=='8'||expressao[i]=='9'||expressao[i]=='+'||expressao[i]=='-'||expressao[i]=='*'||
            expressao[i]=='/'||expressao[i]=='^'||expressao[i]=='('||expressao[i]==')'||expressao[i]==' '){     // tem que estar nesse range se não encerra o programa

            if (isspace(expressao[i])) {                                        // se for espaço
                if (espacoentredigitos = 1) espacoentredigitos = 2;

                continue;
                
            } else if (isdigit(expressao[i])) {                                 // se for numero
                if (operadorduplo == 1) operadorduplo = 0;
                if (terminoucomoperador == 1) terminoucomoperador = 0;
                if (comecoucomoperador == 0) comecoucomoperador = 1;
                if (espacoentredigitos == 0) espacoentredigitos = 1;            // se houver numero-espaço-numero, encerra o programa
                if (espacoentredigitos == 2) {
                    printf("\nEspacos entre digitos. Programa encerrado!\n\n");
                    exit(EXIT_FAILURE);
                }

                int j;
                for (j = 0; isdigit(expressao[i]); j++){
                    if (expressao[i] == '0' && divisaoporzero == 1){
                        i++;
                        j--;
                        continue;
                    } else {
                        tokens[contadorToken][j] = expressao[i++];
                        divisaoporzero = 0;
                    }
                }

                tokens[contadorToken][j] = '\0';
                guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[contadorToken]);
                contadorToken++;
                i--;

                if (divisaoporzero == 1) {                                      // se houver divisão por zero, encerra o programa
                    printf("\nDivisao por zero. Programa encerrado!\n\n");
                    exit(EXIT_FAILURE);
                }

            } else if (expressao[i]=='('){                                      // se for '('
                comecoucomoperador = 0;
                terminoucomoperador = 1;
                operadorduplo = 0;

                tokens[contadorToken][0] = expressao[i];
                tokens[contadorToken][1] = '\0';
                guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[contadorToken]);
                contadorToken++;

            } else if (expressao[i]==')'){                                      // se for ')'
                if (terminoucomoperador == 1) {
                    printf("\nExpressao mal formada. Programa encerrado!\n\n");
                    exit(EXIT_FAILURE);
                }

                comecoucomoperador = 1;
                terminoucomoperador = 0;
                operadorduplo = 0;

                tokens[contadorToken][0] = expressao[i];
                tokens[contadorToken][1] = '\0';
                guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[contadorToken]);
                contadorToken++;

            } else {                                                            // se for simbolo
                if (operadorduplo == 1) {
                    printf("\nOperadores seguidos. Programa encerrado!\n\n");
                    exit(EXIT_FAILURE);
                }
                if (comecoucomoperador == 0) {
                    printf("\nExpressao mal formada. Programa encerrado!\n\n");
                    exit(EXIT_FAILURE);
                }
                if (expressao[i]=='/') divisaoporzero = 1;

                espacoentredigitos = 0;
                terminoucomoperador = 1;
                operadorduplo = 1;
                
                tokens[contadorToken][0] = expressao[i];
                tokens[contadorToken][1] = '\0';
                guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[contadorToken]);
                contadorToken++;

            }
        } else {
            printf("\nCaracteres invalidos. Programa encerrado!\n\n");
            exit(EXIT_FAILURE);                                                 // Encerra o programa direto
        }
    }

    if (terminoucomoperador == 1) {
        printf("\nExpressao mal formada. Programa encerrado!\n\n");
        exit(EXIT_FAILURE);
    }

    return filaDeEntrada;
}

// PROCESSAR EXPRESSAO INFIXA PARA PÓS-FIXA
Fila processar_infixa_para_posfixa(Fila* filaDeEntrada) {
    // Inicializa estruturas
    Fila filaDeSaida;
    Pilha Operadores;
    nova_fila(&filaDeSaida, 100);
    nova_pilha(&Operadores, 100);

    // PROCESSAMENTO
    char* op_Fila;
    char* op_Topo;
    while (!fila_vazia(*filaDeEntrada)) {
        recupere_da_fila(*filaDeEntrada, (ElementoDeFila*)&op_Fila);

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

        remova_elemento_da_fila(filaDeEntrada);
    }

    if (fila_vazia(*filaDeEntrada) && !pilha_vazia(Operadores)){                 // desempilhamento até pilha_vazia(Operadores)
        while (!pilha_vazia(Operadores)){
            recupere_da_pilha(Operadores,(ElementoDePilha*)&op_Topo);
            guarde_na_fila(&filaDeSaida,(ElementoDeFila)op_Topo);
            remova_elemento_da_pilha(&Operadores);
        }
    }

    free_pilha(&Operadores);

    return filaDeSaida;
}

// CALCULAR EXPRESSAO PÓS-FIXA
Pilha calcular_expressao_posfixa(Fila* filaDeSaida) {
    Pilha pilhaDeResultados;
    nova_pilha(&pilhaDeResultados, 100);

    char* valor_recuperado;
    while(!fila_vazia(*filaDeSaida)){
        recupere_da_fila(*filaDeSaida,(ElementoDeFila*)&valor_recuperado);
        remova_elemento_da_fila(filaDeSaida);

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
                        printf("\nOperador invalido: %c\n", *valor_recuperado);
                        *resultado = 0;
                        break;
                }

                guarde_na_pilha(&pilhaDeResultados, (ElementoDePilha)resultado);

                free(num1);
                free(num2);
            }
        }
    }

    

    return pilhaDeResultados;
}

// PRINTAR RESULTADO DO CALCULO
void imprimir_resultado_do_calculo(Pilha pilha){
    if (!pilha_vazia(pilha)) {
        double* resultadoFinal;
        recupere_da_pilha(pilha, (ElementoDePilha*)&resultadoFinal);
        remova_elemento_da_pilha(&pilha);
        if (!pilha_vazia(pilha)){
            printf("\nExpressao mal formada. Programa encerrado!\n\n");
            exit(EXIT_FAILURE);
        } else printf("\nResultado final: %.2f\n\n", *resultadoFinal);
        free(resultadoFinal);
        resultadoFinal = NULL;
        exit(EXIT_SUCCESS);
    } else printf("\nFila vazia!\n\n");
}