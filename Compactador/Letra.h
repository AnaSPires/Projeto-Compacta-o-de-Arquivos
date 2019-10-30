#ifndef LETRA
#define LETRA
typedef struct Letra
{
    char caracter;
    char*codigo;
    struct Letra* letra;
}Letra;

extern Letra* createL();

#endif

