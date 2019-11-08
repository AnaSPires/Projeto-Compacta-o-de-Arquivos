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
    int lixo;
    fread(&lixo,sizeof(int),1,ponteiroArquivo);
    int qtdLetras;
    fread(&qtdLetras,sizeof(int),1,ponteiroArquivo);
    //printf("%i", qtdLetras);
    for(int i = 0; i< qtdLetras;i++)
    {
        char car;
        fread(&car,sizeof(char),1,ponteiroArquivo);
        //printf("%c", car);
        int fre;
        fread(&fre,sizeof(int),1,ponteiroArquivo);
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
        //printf("\n\n");
        //printf("%c", primeiro->caracter);
        //printf("%i", primeiro->frequencia);
        //printf("\n\n");
        NoArvore *segundo = pop(&f);
        //printf("\n\n");
        //printf("%c", segundo->caracter);
        //printf("%i", segundo->frequencia);
        //printf("\n\n");

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

    for(int i = 0; i<strlen(arq);i++)
        novoArq[i] = arq[i];


    strtok(novoArq, ".cmp");

    FILE* pontDescompactar = fopen(novoArq, "wb");


    char codigo;
    fread(&codigo, sizeof(char), 1, ponteiroArquivo);
    //char c = buscaCaracter(codigo);
    NoArvore *atual = f->info;
    int max = 8;
    long posAtual;
    posAtual= ftell(ponteiroArquivo);

    fseek(ponteiroArquivo, 0, SEEK_END);
    long posFinal = ftell(ponteiroArquivo);

    fseek(ponteiroArquivo, posAtual, SEEK_SET);

    while(codigo != EOF)
    {
        printf("%s","entrou no whilw \n");
        if(posAtual == posFinal)
            max = max - lixo;

        for(int i = 0; i < max; i++)
        {
            printf("%s","entrou no for \n");
            //BUGOU AQ

            printf("%s","aaaaaaaaaaaaaaaa\n");
            if(codigo & (1u << (7 - i)))
            {
                printf("%s","foi pra direita \n");
                if(atual->dir == NULL)
                printf("%s","QUE MERDA \n");
                atual = atual->dir;
                printf("%s","nhe\n");
                // é 1
            }
            else
            {
                printf("%s","foi pra esquerda \n");
                atual = atual->esq;
                //é 0
            }
            printf("%s","cansei\n");
             if((atual->dir == NULL) && (atual->esq == NULL))
            {
                printf("%s","chegou na folha \n");
                 fwrite(&(atual->caracter), sizeof(char), 1, pontDescompactar);//escreve o caracter
                 atual= f;
            }


            printf("%s","chegou no final do for \n");
        }

        fread(&codigo, sizeof(char), 1, ponteiroArquivo);
        printf("%s","leu outro caracter \n");
    }
    printf("%s","saiu do while \n");

    fclose(pontDescompactar);
    fclose(ponteiroArquivo);
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

        for(int i = 0; i < a; i++)
            auxCod[i] = NULL;

        int auxTam = 0;

        filaL = createCod(filaL, f->info, auxCod, auxTam, a);

        int found = strlen(arq);
        int tam = found ;
        char arqCodificado[found+4];
        int x = 0;
        for(x = 0;x<(found);x++)
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
            unsigned char parte1 = (fre & 255);
            unsigned char parte2 = ((fre>>8) & 255);
            unsigned char parte3 = ((fre>>16) & 255);
            unsigned char parte4 = ((fre>>24) & 255);

            fwrite(&filaL->caracter, sizeof(char), 1, pontCodificado);
            fwrite(&parte1, sizeof(char), 1, pontCodificado);
            fwrite(&parte2, sizeof(char), 1, pontCodificado);
            fwrite(&parte3, sizeof(char), 1, pontCodificado);
            fwrite(&parte4, sizeof(char), 1, pontCodificado);
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

