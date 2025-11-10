#include "fila.h"
#include "pilha.h"
#include "funcoes.h"

int main(){

    // DEFINE A EXPRESSÃO INFIXA
    Fila filaDeEntrada = definir_expressao_infixa();

    // PRINTA OS TOKENS
    //imprimir_fila(filaDeEntrada);

    // PROCESSA EXPRESSAO INFIXA PARA PÓS-FIXA
    Fila filaDeSaida = processar_infixa_para_posfixa(&filaDeEntrada);

    // LIBERA FILA NÃO MAIS USADA
    free_fila(&filaDeEntrada);

    // PRINTA FILA DE SAÍDA
    //imprimir_fila(filaDeSaida);

    // CALCULA A EXPRESSAO PÓS-FIXA
    Pilha pilhaDeResultados = calcular_expressao_posfixa(&filaDeSaida);

    // PRINTA RESULTADO DO CALCULO
    imprimir_resultado_do_calculo(pilhaDeResultados);
    
    // LIBERA FILA NÃO MAIS USADA
    free_fila(&filaDeSaida);

    // LIBERA PILHA NÃO MAIS USADA
    free_pilha(&pilhaDeResultados);

    return 0;
}