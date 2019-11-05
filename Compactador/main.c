#include<stdio.h>
#include "NoArvore.h"
#include "Fila.h"
#include "Letra.h"

int tamanho;

int main()
{
   FILE *ponteiroArquivo;
   NoFila* f = NULL;
  char *arq = (char*)malloc(sizeof(char));

  printf("Opcao escolhida: ");

  scanf("%s", arq);

  ponteiroArquivo = fopen(arq, "r");
  //printf("%s",arq);

  if(ponteiroArquivo == NULL)
     printf("Erro na abertura do arquivo!");

  fseek(ponteiroArquivo, 0, SEEK_END);
  tamanho = ftell(ponteiroArquivo);

  int qtd = 0;
  rewind(ponteiroArquivo);

  char c = getc(ponteiroArquivo);
  while(c != EOF)
    {
        NoFila* atual = buscar(c, f);
        f=atual;
        c = getc(ponteiroArquivo);
      }

   char car;
   int fre;

  NoFila* teste = f;
  while(teste->prox !=NULL)
  {
      car = teste->info->caracter;
      fre = teste->info->frequencia;
      teste = teste->prox;
      qtd++;
  }
      car = teste->info->caracter;
      fre = teste->info->frequencia;
      qtd++;

    int qtdCaractere = qtd;
    while(qtdCaractere > 1 && f != NULL)
    {
        NoArvore* primeiro = pop(&f);
        NoArvore *segundo = pop(&f);
        int frequencia = (primeiro->frequencia) + (segundo->frequencia);
        NoArvore * novo = (NoFila*)malloc(sizeof(NoFila));
        novo = create();
        novo->frequencia = frequencia;

        novo->esq = primeiro;
        novo->dir = segundo;

        f = insira(f,novo);

        qtdCaractere--;
    }

    int a = altura(f->info);
    //printf("%i",a);

    NoLetra* filaL =NULL;

    char *auxCod = (char*)malloc(a * sizeof(char));
    int i;
    for(i = 0; i < a; i++)
        auxCod[i] = NULL;

    int auxTam = 0;

    filaL = createCod(filaL, f->info, auxCod, auxTam, a);

        /*NoLetra* testeL = filaL;

        while(testeL->prox !=NULL)
        {
            printf("%c\n", testeL->caracter);
            printf("%i\n", testeL->frequencia);
            testeL = testeL->prox;
            int p;
            for(p = 0; p<testeL->tam;p++)
            {
                printf("%c", testeL->codigo[p]);
                printf("-");
            }
            printf("\n\n");
        }
        printf("%c", testeL->caracter);
        printf("\n");
        printf("%i", testeL->frequencia);
        printf("\n");

        int p;
        for(p = 0; p<testeL->tam;p++)
        {
            printf("%c", testeL->codigo[p]);
            printf("-");
        }*/
        rewind(ponteiroArquivo);
        codificar(ponteiroArquivo, filaL);
/*
        char * found = strstr( arq, "." );

        if (found != NULL)
        {
          int index = found - arq;
          printf("tagagag");
          printf("%i",index);

          char* arqCompactado =(char*) malloc(2*(sizeof(char)));

          for(int i = 0;i<index;i++)
          {
            printf("\n\n");
            printf("%c",*arq);
            *arqCompactado = *arq;
            printf("\n\n");
            printf("%c",*arqCompactado);
            arq++;
            arqCompactado++;
            printf("\n\n agr");
            printf("%s",arqCompactado);
            printf("\n\n");
          }
          arqCompactado++;
          *arqCompactado = 'c';
        printf("yyyy");

        FILE *pontCompactado = fopen( arqCompactado,"w");


        fprintf(pontCompactado,"%s", "aaaaaaaaaaaaaa"); //filaL->caracter
        */
}

void codificar(FILE* ponteiroArq, NoLetra* fila){

    char arqCodificado[30] = "compactado.aa";

    FILE *pontCodificado = fopen(arqCodificado, "w+");

    if(pontCodificado == NULL)
        printf("Erro na abertura do arquivo!");


    char letra = getc(ponteiroArq);

    int qtdLixo = 0;

    fprintf(pontCodificado, "pararaera%d", 1);
    fwrite(&qtdLixo, sizeof(int), 1, pontCodificado);

    NoLetra* copiaRuim = fila;
    NoLetra* encontrada = acharLetra(letra, copiaRuim);

    while(letra != EOF && encontrada != NULL)
    {
        copiaRuim = fila;
        encontrada = acharLetra(letra, copiaRuim);

        int aux=0;
        aux = aux | (1u << (tamanho - encontrada->tam));//1=pos

        fprintf(pontCodificado, "%d", aux);
        fprintf(pontCodificado, "%c", encontrada->caracter);
        fprintf(pontCodificado, "%i", encontrada->frequencia);

        printf("%i\n", aux);
        printf("%c\n", encontrada->caracter);
        printf("%i\n", encontrada->frequencia);

        fila = fila->prox;
        letra = getc(ponteiroArq);
    }
    printf("aaaa");
    fclose(pontCodificado);
    fclose(ponteiroArq);
}

