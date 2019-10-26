#include<stdio.h>
#include "Letra.h"

Letra* create(){
    return (Letra*)malloc(sizeof(Letra));
}
