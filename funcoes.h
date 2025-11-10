#ifndef FUNCOES
#define FUNCOES

#include "basics.h"

unsigned int posicao(char operador);
boolean matriz[7][7];
void imprimir_fila(Fila fila);
Fila definir_expressao_infixa(void);
Fila processar_infixa_para_posfixa(Fila* filaDeEntrada);
Pilha calcular_expressao_posfixa(Fila* filaDeSaida);
void imprimir_resultado_do_calculo(Pilha pilha);

#endif // FUNCOES