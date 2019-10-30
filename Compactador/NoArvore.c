#include "Fila.h"
#include "Letra.h"
#include <stdlib.h>

NoArvore* create()
{
    NoArvore* no = (NoArvore*)malloc(sizeof(NoArvore));
    no->dir = NULL;
    no->esq = NULL;
    return no;
}

Letra* createCod(NoArvore* atual, char codigo[], int tam)
{
    if(auxArvore->esq != NULL)
    {
        codigo[tam++] = "0";
        return createCod(atual->esq, codigo,tam);
    }
    else
        if(auxArvore->dir != NULL)
        {
            cod[tam++] = "1";
            return createCod(atual->dir,codigo,tam);
        }
        else{
            Letra* letra = (Letra*)malloc(sizeof(Letra));
            letra->caracter = atual->caracter;
            letra->codigo = &codigo;
            letra
        }


}
/*
int altura(NoArvore* noAtual)
{
    int hEsq, hDir;

    if(noAtual == NULL)
        return 0;

    hEsq = altura(noAtual->esq);
    hDir = altura(noAtual->dir);

    if(hEsq >= hDir)
        return 1 + hEsq;

    return 1 + hDir;
}
*/
