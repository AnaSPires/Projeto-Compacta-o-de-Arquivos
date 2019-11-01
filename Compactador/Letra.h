#include "NoArvore.h"
#ifndef LETRA
#define LETRA
typedef struct NoLetra
{
    char caracter;
    int frequencia;
    char*codigo;
    struct NoLetra* prox;
}NoLetra;

extern NoLetra* createL();
extern NoLetra* add(NoLetra* inicio, NoLetra* no);

#endif

/*
vetior de codigos - letra, freq e codigo vetor de char (altura)

if(NoArvore atual, char[] codigo, int auxQtd)
{
  [0][][][][]
}
*/
