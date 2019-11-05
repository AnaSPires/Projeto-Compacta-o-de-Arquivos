#include "NoArvore.h"
#ifndef LETRA
#define LETRA
typedef struct NoLetra
{
    char caracter;
    int frequencia;
    char *codigo;
    struct NoLetra* prox;
    int tam;
}NoLetra;

extern NoLetra* createL();
extern NoLetra* add(NoLetra* inicio, NoLetra* no);
extern NoLetra* acharLetra(char l, NoLetra* lista);

#endif

/*
vetior de codigos - letra, freq e codigo vetor de char (altura)

if(NoArvore atual, char[] codigo, int auxQtd)
{
  [0][][][][]
}
*/
