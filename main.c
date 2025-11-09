#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fila.h"
#include "pilha.h"
#include "funcoes.h"
#include <math.h>

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




    // PROCESSAMENTO
    char* op_Fila;
    char* op_Topo;
    while(!fila_vazia(filaDeEntrada)){
        recupere_da_fila(filaDeEntrada,(ElementoDeFila*)&op_Fila);

        if (isdigit(*op_Fila)){                                         // se for digito, talvez *op_Fila?
            guarde_na_fila(&filaDeSaida,(ElementoDeFila)op_Fila);
        } else {                                                       // se for operador

            if (!pilha_vazia(Operadores)  && *op_Fila == ')'){            // se for ) faz desempilhamento até (, e () são deletados
                recupere_da_pilha(Operadores,(ElementoDePilha*)&op_Topo);
                while(!pilha_vazia(Operadores) && *op_Topo != '('){
                    guarde_na_fila(&filaDeSaida,(ElementoDeFila)op_Topo);
                    remova_elemento_da_pilha(&Operadores);
                    recupere_da_pilha(Operadores,(ElementoDePilha*)&op_Topo);
                }

                remova_elemento_da_pilha(&Operadores);
                op_Topo = NULL;
                
            } else {
                if (!pilha_vazia(Operadores)){                           // se for comun, desempilha até achar F na tabela
                    recupere_da_pilha(Operadores,(ElementoDePilha*)&op_Topo);
                    while (matriz[posicao(*op_Topo)][posicao(*op_Fila)] && !pilha_vazia(Operadores))
                    {
                        guarde_na_fila(&filaDeSaida, (ElementoDeFila)op_Topo);
                        remova_elemento_da_pilha(&Operadores);
                        recupere_da_pilha(Operadores, (ElementoDePilha *)&op_Topo);
                    }

                    op_Topo = NULL;
                }
                guarde_na_pilha(&Operadores,(ElementoDePilha)op_Fila);  // empilhamento
            }
        } 

        remova_elemento_da_fila(&filaDeEntrada);
        op_Fila = NULL;
    }


    if (fila_vazia(filaDeEntrada) && !pilha_vazia(Operadores)){          // desempilhamento até pilha_vazia(Operadores)
        while (!pilha_vazia(Operadores)){
            recupere_da_pilha(Operadores,(ElementoDePilha*)&op_Topo);
            guarde_na_fila(&filaDeSaida,(ElementoDeFila)op_Topo);
            remova_elemento_da_pilha(&Operadores);
        }
    }

    free_fila(&filaDeEntrada);
    free_pilha(&Operadores);



    char *teste2;
    printf("Fila de saida separados:\n");
    while (!fila_vazia(filaDeSaida)) {
        recupere_da_fila(filaDeSaida, (ElementoDeFila *)&teste2);
        printf("'%s'\n", teste2);
        remova_elemento_da_fila(&filaDeSaida);
        teste2 = NULL;
    }



    /*Pilha pilhaDeResultados;
    nova_pilha(&pilhaDeResultados, 100);

    char* temp;
    double* num1;
    double* num2;
    num1=(double*)malloc(sizeof(double));
    num2=(double*)malloc(sizeof(double));

    while(!fila_vazia(filaDeSaida)){
        recupere_da_fila(filaDeSaida,(ElementoDeFila*)&temp);
        if (isdigit(*temp)){                                         // se for digito, talvez *temp?
            guarde_na_pilha(&pilhaDeResultados,(ElementoDePilha)temp);
        } else {                                                       // se for operador
            if (!pilha_vazia(pilhaDeResultados)){                       // desempilha dois numeros da pilha de resultados e faz a conta com o op recuperado
                recupere_da_pilha(pilhaDeResultados,(ElementoDePilha*)&num1);
                remova_elemento_da_pilha(&pilhaDeResultados);
                recupere_da_pilha(pilhaDeResultados,(ElementoDePilha*)&num2);
                remova_elemento_da_pilha(&pilhaDeResultados);

                switch (*temp) {
                    case '+':
                        *temp = *num1+*num2;
                        guarde_na_pilha(&pilhaDeResultados,(ElementoDePilha)temp);
                        break;
                    case '-':
                        *temp = *num1-*num2;
                        guarde_na_pilha(&pilhaDeResultados,(ElementoDePilha)temp);
                        break;
                    case '*':
                        *temp = (*num1)*(*num2);
                        guarde_na_pilha(&pilhaDeResultados,(ElementoDePilha)temp);
                        break;
                    case '/':
                        *temp = (*num1)/(*num2);
                        guarde_na_pilha(&pilhaDeResultados,(ElementoDePilha)temp);
                        break;
                    case '^': {
                        int* e;
                        e=(int*)malloc(sizeof(int));
                        *e = pow(*num1, *num2);
                        guarde_na_pilha(&pilhaDeResultados,(ElementoDePilha)e);
                        free(e);
                        e = NULL;
                        break;
                    }
                    default:  
                        break; //invalido
                }

                num1 = NULL;
                num1 = NULL;
            }
        }
        remova_elemento_da_fila(&filaDeSaida);
        temp = NULL;
    }
    free(num1);
    free(num2);

    /*char *teste3;
    //teste3=(char*)malloc(sizeof(char));
    printf("Pilha de resultados:\n");
    while (!pilha_vazia(pilhaDeResultados)) {
        recupere_da_pilha(pilhaDeResultados, (ElementoDePilha *)&teste3);
        printf("'%s'\n", teste3);
        remova_elemento_da_pilha(&pilhaDeResultados);
        teste3 = NULL;
    }
    //free(teste3);*/


    /*free_fila(&filaDeSaida);
    free_pilha(&pilhaDeResultados);*/


    return 0;
}