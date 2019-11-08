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

        ponteiroArquivo = fopen(arq, "rb");
        if(ponteiroArquivo == NULL)
            printf("Erro na abertura do arquivo!");
        else
            compactar(ponteiroArquivo, arq);
            break;

        case 2:
            printf("Digite o nome do arquivo a ser descompactado: ");
            scanf("%s", arq);
            printf("\n\n");
            ponteiroArquivo = fopen(arq, "rb");
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

    for(int i = 0; i< qtdLetras;i++)
    {
        unsigned char car;
        fread(&car,sizeof(char),1,ponteiroArquivo);
        int fre;
        fread(&fre,sizeof(int),1,ponteiroArquivo);
        NoArvore* nozinho = create();
        nozinho->caracter = car;
        nozinho->frequencia = fre;
        f = insira(f, nozinho);
    }

    NoFila* teste = f;
    int qtd = 0;
    while(teste->prox !=NULL)
    {
      unsigned char car = teste->info->caracter;
      int fre = teste->info->frequencia;
      teste = teste->prox;
      qtd++;
    }
    unsigned char car = teste->info->caracter;
    int fre = teste->info->frequencia;
    qtd++;

    while(qtd > 1 && f != NULL)
    {
        NoArvore* primeiro = pop(&f);
        NoArvore *segundo = pop(&f);
        int frequencia = (primeiro->frequencia) + (segundo->frequencia);
        NoArvore * novo = create();
        novo->frequencia = frequencia;

        novo->esq = primeiro;
        novo->dir = segundo;
        f = insira(f,novo);
        qtd--;
    }

    char novoArq[30];
    int i;
    for(i = 0; i<(strlen(arq)-4);i++)
        novoArq[i] = arq[i];


    /*strtok(arq, "cmp");
    char novoArq[30];

    for(int i = 0; i < strlen(arq);i++)
        novoArq[i] = arq[i];*/

    FILE* pontDescompactar = fopen("testeeeeeeeeeeeeeeeeeee.jpg", "wb");

    unsigned char codigo;
    NoArvore *atual = f->info;
    int max = 8;
    long posAtual;
   // fseek(ponteiroArquivo, sizeof(int) + qtdLetras * (sizeof(int) + sizeof(char)),SEEK_SET);
    posAtual= ftell(ponteiroArquivo);

    fseek(ponteiroArquivo, 0, SEEK_END);
    long posFinal = ftell(ponteiroArquivo);

    fseek(ponteiroArquivo, posAtual, SEEK_SET);

    int acabou = 0;

    while(!feof(ponteiroArquivo) && !acabou)
    {
        fread(&codigo, sizeof(char), 1, ponteiroArquivo);
        posAtual= ftell(ponteiroArquivo);//01101101 0000 0000

        if(posAtual == posFinal){
            max = max - lixo;
            acabou = 1;
        }//0110 1101

        for(int i = 0; i < max; i++)
        {
            if(codigo & (1u << (7 - i)))
                atual = atual->dir;
            else
                atual = atual->esq;

            if((atual->dir == NULL) && (atual->esq == NULL))
            {
                fwrite(&(atual->caracter), sizeof(char), 1, pontDescompactar);//escreve o caracter
                atual= f->info;
            }
        }
    }
    fclose(pontDescompactar);
    fclose(ponteiroArquivo);
    printf("\n\n");
    printf("Descompactação realizada com sucesso!!!", setlocale(LC_ALL,""));
    printf("\n\n");
}

void compactar(FILE* ponteiroArquivo, char arq[])
{
    NoFila* f = NULL;
    int qtd = 0;
    unsigned char c;

    /*fseek(ponteiroArquivo, 0, SEEK_END);
    tamanho = ftell(ponteiroArquivo);
    fseek(ponteiroArquivo, 0, SEEK_SET);*/

    fread(&c,sizeof(unsigned char),1,ponteiroArquivo);

    while(c != EOF && !feof(ponteiroArquivo))
    {
        f = buscar(c, f);
        fread(&c,sizeof(unsigned char),1,ponteiroArquivo);

    }

    NoFila* teste = f;
    while(teste !=NULL)
    {
        teste = teste->prox;
        qtd++;
    }

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

    int alturaArvore = altura(f->info);

    NoLetra* filaL = NULL;

    char *auxCod = (char*)malloc(alturaArvore * sizeof(char));
    for(int i = 0; i < alturaArvore; i++)
        auxCod[i] = NULL;

    int auxTam = 0;

    filaL = createCod(filaL, f->info, auxCod, auxTam, alturaArvore);

    int found = strlen(arq);
    int tam = found;
    char arqCodificado[found+4];
    int x = 0;

    for(x = 0;x<(found);x++)
        arqCodificado[x] = arq[x];

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

    unsigned char letra;
    fread(&letra,sizeof(char),1,ponteiroArquivo);
    NoLetra* encontrada = acharLetra(letra, copiaRuim);

    unsigned char aux=0;

    while(letra != EOF && encontrada != NULL && !feof(ponteiroArquivo))
    {
        unsigned char codigo = 0;
        int outroInt = encontrada->tam - 1;

        int indice = 0;
        for(indice = 0;indice < encontrada->tam; indice++, outroInt--)
            if(encontrada->codigo[indice] == '1')
                codigo += pow(2, outroInt);

        if(qtdQuantos + encontrada->tam > 8)
        {
            int coisa = encontrada->tam - (8 - qtdQuantos);//0
            char restoAtual = codigo >> coisa;  //  00000000
            aux = aux << (8 - qtdQuantos);  //01101101
            aux = aux | restoAtual;
            fwrite(&aux, sizeof(char), 1, pontCodificado);
            char faltaIncluir = codigo << (8 - coisa);

            while(coisa>8)
            {
                coisa = coisa - 8;
                restoAtual = faltaIncluir >> coisa;
                aux = restoAtual;
                fwrite(&aux, sizeof(char), 1, pontCodificado);
                faltaIncluir = faltaIncluir << (coisa);
            }

            aux = faltaIncluir;
            qtdQuantos = coisa;
        }
        //1111 1111 - eeee
        //1110 1010 - eddd
        //1000 0000 - dccc
        //0001 1011
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
        fread(&letra,sizeof(char),1,ponteiroArquivo);
        encontrada = acharLetra(letra, filaL);
    }
    if(qtdQuantos != 0)
    {
        int quantosLixos = 8 - qtdQuantos;
        fwrite(&aux, sizeof(char), 1,pontCodificado);
        rewind(pontCodificado);

        fwrite(&quantosLixos, sizeof(int), 1, pontCodificado);
    }
    fclose(pontCodificado);
    fclose(ponteiroArquivo);
    printf("\n\n");
    printf("Compactação realizada com sucesso!!!",setlocale(LC_ALL,""));
    printf("\n\n");
}

