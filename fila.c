#include <stdlib.h>
#include "fila.h"

boolean nova_fila (Fila* f, unsigned int capacidade){
    if (capacidade<=0) return false;

    (*f).capacidade_inicial=capacidade;
    (*f).capacidade=capacidade;

    (*f).vetor=(ElementoDeFila*)malloc(capacidade*sizeof(ElementoDeFila));

    (*f).qtd_atual=0;
    
    (*f).inicio=0;
    
    (*f).final=0;

    return true;
}

boolean guarde_na_fila (Fila* f, ElementoDeFila e){
    if ((*f).qtd_atual==(*f).capacidade){
        (*f).vetor=(ElementoDeFila*)realloc((*f).vetor,2*(*f).capacidade*sizeof(ElementoDeFila));
        
        if ((*f).inicio != 0 && (*f).final != 0){
            for (int i = (*f).inicio, p = 1; p <= ((*f).qtd_atual-(*f).inicio); i++, p++){
                (*f).vetor[(*f).qtd_atual+i] = (*f).vetor[i];
                (*f).vetor[i] = NULL;
            }
            (*f).inicio += (*f).qtd_atual;
        }
    }

    (*f).vetor[(*f).final]=e;
    (*f).qtd_atual++;
    
    (*f).final = ((*f).final+1)%(*f).capacidade;
    
    return true;
}

boolean recupere_da_fila (Fila f, ElementoDeFila* e){
    if (f.qtd_atual==0) return false;

    *e=f.vetor[f.inicio];
    return true;
}

boolean remova_elemento_da_fila (Fila* f){
    if ((*f).qtd_atual==0) return false;

    (*f).qtd_atual--;
    (*f).vetor[(*f).inicio] = NULL;
    (*f).inicio = ((*f).inicio+1)%(*f).capacidade;
    
    
    if ((*f).qtd_atual<=0.25*(*f).capacidade && (*f).capacidade>(*f).capacidade_inicial){
        if ((*f).inicio > ((*f).capacidade/2)-1 || (*f).final-1 > ((*f).capacidade/2)-1){
            while ((*f).inicio!=0){
                for (int p = 1, q = (*f).qtd_atual, ff = (*f).final; p <= q; ff--, p++){
                    (*f).vetor[ff] = (*f).vetor[(ff-1)%(*f).capacidade];
                    (*f).vetor[(ff-1)%(*f).capacidade] = NULL;
                }
                (*f).final = ((*f).final+1)%(*f).capacidade;
                (*f).inicio = ((*f).inicio+1)%(*f).capacidade;
            }
            
        (*f).vetor=(ElementoDeFila*)realloc((*f).vetor,((*f).capacidade/2)*sizeof(ElementoDeFila));
        }
    }  
	
    return true;
}

boolean fila_cheia (Fila f){
    /*
    if (f.qtd_atual==f.capacidade)
        return true;
    else
        return false;
    */
    return f.qtd_atual==f.capacidade;
}

boolean fila_vazia (Fila f)
{
    /*
    if (f.qtd_atual==0)
        return true;
    else
        return false;
    */
    return f.qtd_atual==0;
}

boolean free_fila (Fila* f)
{
    if ((*f).vetor==NULL) return false;

    
    for (int i=(*f).inicio; (*f).qtd_atual>0; (*f).qtd_atual--, (*f).inicio = (*f).inicio+1==(*f).capacidade?0:(*f).inicio+1){
        (*f).vetor[i]=NULL;
        free((*f).vetor[i]);
    }

    free((*f).vetor);
    (*f).vetor=NULL;

    return true;
}