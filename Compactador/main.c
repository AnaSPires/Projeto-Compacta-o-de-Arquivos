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
    int lixo = getc(ponteiroArquivo);
    //printf("%i",lixo);
    int qtdLetras = getc(ponteiroArquivo);
    //printf("%i", qtdLetras);
    int i = 0;
    for(i = 0; i< qtdLetras;i++)
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

    while(qtd > 1 && f != NULL)
    {
        NoArvore* primeiro = pop(&f);
        printf("\n\n");
        printf("%c", primeiro->caracter);
        printf("%i", primeiro->frequencia);
        printf("\n\n");
        NoArvore *segundo = pop(&f);
        printf("\n\n");
        printf("%c", segundo->caracter);
        printf("%i", segundo->frequencia);
        printf("\n\n");

        int frequencia = (primeiro->frequencia) + (segundo->frequencia);
        NoArvore * novo = (NoFila*)malloc(sizeof(NoFila));
        novo = create();
        novo->frequencia = frequencia;

        novo->esq = primeiro;
        novo->dir = segundo;

        f = insira(f,novo);

        qtd--;
    }

    char novoArq[30];

    int x = 0;
    for(x = 0;x < strlen(arq) -2;x++)
    {
        novoArq[x] = arq[x];
    }

    novoArq[x++] = "d";

    FILE* pontDescompactar = fopen(novoArq, "w");

    fprintf("%c", "aaaaaaaaaaaaaaaaaaaaaaaa");


    fclose(pontDescompactar);

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
        char arqCodificado[30];
        int x = 0;
       for(x = 0;x<(found+1);x++)
       {
            arqCodificado[x] = arq[x];
        }

        arqCodificado[found++] = '.';arqCodificado[found++] = 'c'; arqCodificado[found++] = 'm'; arqCodificado[found] = 'p';

        FILE *pontCodificado = fopen(arqCodificado, "wb");
        found = 0;
        fwrite(&found, sizeof(int), 1, pontCodificado);
        fwrite(&copia, sizeof(int), 1, pontCodificado);

        rewind(ponteiroArquivo);

        NoFila* copiaRuim = filaL;

        while(filaL != NULL)
        {
            fwrite(&filaL->caracter, sizeof(char), 1, pontCodificado);
            fwrite(&filaL->frequencia, sizeof(int), 1, pontCodificado);
            filaL = filaL->prox;
        }
        filaL = copiaRuim;


       int qtdQuantos = 0;

        char letra = getc(ponteiroArquivo);
        NoLetra* encontrada = acharLetra(letra, copiaRuim);

        char aux=0;
        while(letra != EOF && encontrada != NULL)
        {
            char codigo = 0;
            int outroInt = encontrada->tam - 1;
            int indice = 0;
            for(indice = 0;indice < encontrada->tam; indice++)
                if(encontrada->codigo[indice] == '1')
                    codigo += pow(2, outroInt--);

            if(qtdQuantos + encontrada->tam > 8)
            {
                char a = codigo >> (encontrada->tam - (8 - qtdQuantos));
                char b = codigo << (8 - qtdQuantos);
                aux = aux<<(8 - qtdQuantos);
                aux = aux | a;

                fwrite(&aux, sizeof(char), 1, pontCodificado);
                aux = b;
                qtdQuantos = encontrada->tam - (8 - qtdQuantos);
            }
            else
            {
                aux = aux << encontrada->tam;
                aux = aux | codigo;
                qtdQuantos += encontrada->tam;

                if(qtdQuantos == 8)
                {
                    qtdQuantos = 0;
                    fwrite(&aux, sizeof(char), 1, pontCodificado);
                    aux = 0;
                }
            }
            letra = getc(ponteiroArquivo);
            encontrada = acharLetra(letra, filaL);
        }
        if(qtdQuantos != 0)
        {
             fwrite(&aux, sizeof(char), 1,pontCodificado);
             rewind(pontCodificado);
             int aaaa = 8 - qtdQuantos;
             fwrite(&aaaa, sizeof(int), 1, pontCodificado);
        }
        fclose(pontCodificado);
        fclose(ponteiroArquivo);
        printf("\n\n");
        printf("Compactação realizada com sucesso!!!",setlocale(LC_ALL,""));
        printf("\n\n");
}

