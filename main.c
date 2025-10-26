#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fila.h"
#include "pilha.h"

int main()
{
    /*
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
            tokens[contadorToken++][j] = '\0';
            i--;
            
        } else {                                                            // se for simbolo
            tokens[contadorToken][0] = expressao[i];
            tokens[contadorToken++][1] = '\0';
        }
    }

    // Mostrando os tokens
    char *teste;
    teste=(char*)malloc(sizeof(char));

    printf("Tokens separados:\n");
    for (int i = 0; i < contadorToken; i++) {
        guarde_na_fila (&filaDeEntrada,(ElementoDeFila)tokens[i]);

        recupere_da_fila(filaDeEntrada,(ElementoDeFila*)&teste);
        printf("'%s'\n", teste);
        remova_elemento_da_fila(&filaDeEntrada);
    }

    free(teste);
    teste = NULL;

    return 0;
}