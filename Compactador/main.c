#include<stdio.h>
#include "NoArvore.h"
#include "Fila.h"
#include "Letra.h"
#include <locale.h>

int tamanho;

int main()
{
   FILE *ponteiroArquivo;
   NoFila* f = NULL;
  char arq[30];
  int escolha;

  printf("1 - Compactar um arquivo \n\n");
  printf("2 - Descompactar um arquivo \n\n");
  printf("Opção escolhida: ", setlocale(LC_ALL,""));
  scanf("%i", &escolha);
  printf("\n");

  switch(escolha)
  {
    case 1:

        //compactar
        printf("Digite o nome do arquivo a ser compactado: ");
        scanf("%s", arq);
        printf("\n");

        ponteiroArquivo = fopen(arq, "r");
      //printf("%s",arq);

        if(ponteiroArquivo == NULL)
            printf("Erro na abertura do arquivo!");
        else
            compactar(ponteiroArquivo, arq);



            break;

        case 2:
            printf("Digite o nome do arquivo a ser descompactado: ");
            scanf("%s", arq);
            printf("\n\n");
            ponteiroArquivo = fopen(arq, "r");
          //printf("%s",arq);

            if(ponteiroArquivo == NULL)
             printf("Erro na abertura do arquivo!");
            else
                descompactar(ponteiroArquivo,arq);


            break;

      }
}
void descompactar(FILE* ponteiroArquivo, char arq[])
{
    NoFila* f = NULL;
    rewind(ponteiroArquivo);
    int lixo = getc(ponteiroArquivo) - '0';
    //printf("%i",lixo);
    int qtdLetras = getc(ponteiroArquivo) - '0';
    //printf("%i", qtdLetras);

    for(int i = 0; i< qtdLetras;i++)
    {
        char car = getc(ponteiroArquivo);
        //printf("%c", car);
        int fre = getc(ponteiroArquivo) -'0';
        //printf("%i", fre);

        NoFila* atual = buscarLetra(car, fre, f);
        f=atual;
    }

    NoFila* teste = f;
    int qtd = 0;
  while(teste->prox !=NULL)
  {
      char car = teste->info->caracter;
      int fre = teste->info->frequencia;
      teste = teste->prox;
      qtd++;
      //printf("%c", car);
      //printf("%i", fre);
  }
      char car = teste->info->caracter;
      int fre = teste->info->frequencia;
      qtd++;
      //printf("%c", car);
      //printf("%i", fre);

    while(qtd > 1 && f != NULL)
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

        qtd--;
    }



/*
    int qtd = 0;
    char c = getc(ponteiroArquivo);
    while(c != EOF)
    {
        NoFila* atual = buscar(c, f);
        f=atual;
        c = getc(ponteiroArquivo);
    }*/

    printf("\n\n");
    printf("Descompactação realizada com sucesso.", setlocale(LC_ALL,""));
    printf("\n\n");
}

void compactar(FILE* ponteiroArquivo, char arq[])
{
  NoFila* f = NULL;
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

    int copia = qtd;
    while(qtd > 1 && f != NULL)
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

        qtd--;
    }

        int a = altura(f->info);

        NoLetra* filaL =NULL;

        char *auxCod = (char*)malloc(a * sizeof(char));
        int i;
        for(i = 0; i < a; i++)
            auxCod[i] = NULL;

        int auxTam = 0;

        filaL = createCod(filaL, f->info, auxCod, auxTam, a);

        int found = strlen(arq);
        printf("%i",found);
        char arqCodificado[30];
        //arqCodificado = arq;

       for(int i = 0;i<=(found+1);i++)
       {
            arqCodificado[i] = arq[i];
        }

        arqCodificado[found++] = '.';arqCodificado[found++] = 'c'; arqCodificado[found++] = 'm'; arqCodificado[found] = 'p';
        /*

        if(found!= NULL)
        {
            int index = found - arq;
            int fim;

            arqCodificado[fim++] = 'c'; arqCodificado[fim++] = 'm'; arqCodificado[fim] = 'p';

        }*/


        FILE *pontCodificado = fopen(arqCodificado, "wb");
        fprintf(pontCodificado, "%i", 1);

        rewind(ponteiroArquivo);

        char letra = getc(ponteiroArquivo);
        NoFila* copiaRuim = filaL;
        int quantos = 0;
        //printf("%i",copia);
        fprintf(pontCodificado, "%i", copia);

        while(filaL != NULL)
        {
            fprintf(pontCodificado, "%c", filaL->caracter);
            fprintf(pontCodificado, "%i", filaL->frequencia);
            filaL = filaL->prox;
        }

        int qtdQuantos = 0;

        filaL = copiaRuim;
        NoLetra* encontrada = acharLetra(letra, copiaRuim);


        while(letra != EOF && encontrada != NULL)
        {
            int aux=0;
            aux = aux | (1u << (encontrada->tam - 1));//1=pos

            int i;
            for(i = 0; i<encontrada->tam;i++)
            {
               fprintf(pontCodificado, "%c", encontrada->codigo[i]);
               qtdQuantos++;
                if(qtdQuantos == 8)
                {
                    qtdQuantos = 0;
                }
            }

            letra = getc(ponteiroArquivo);
            encontrada = acharLetra(letra, filaL);
        }
        rewind(pontCodificado);
        if(qtdQuantos == 0)
            fprintf(pontCodificado, "%i", 0);
        else
            fprintf(pontCodificado, "%i", 8 - qtdQuantos);

        fclose(pontCodificado);
        fclose(ponteiroArquivo);
        printf("\n\n");
        printf("Compactação realizada com sucesso!!!",setlocale(LC_ALL,""));
        printf("\n\n");
}

