#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "RedBlack.h"

void converte_minuscula (char *s)
{
    int i;
    for (i=0; i<strlen(s); i++)
        s[i]=tolower(s[i]);
}
//nao te preocupa com essa main agora foco na funcoes
int main (int argc, char *argv[])
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados
    FILE * entrada;
    FILE * saida;
    pNodoA *raiz;

    char *palavra, linha[300], *id; // linhas a serem lidas do arquivo
    char separador[]= {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"}; //caracteres separadores para as palavras
    int id_num;


    if (argc!=3)  //testa se o numero de parametros esperado está correto (deve ser 3): nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("Número incorreto de parâmetros.\n Para chamar o programa digite: %s <arq_entrada> <arq_saida>\n",argv[0]);
        return 1;
    }


    if ((entrada=fopen(argv[1],"r"))==NULL)   // testa se consegue abrir o arquivo de entrada
    {
        printf("erro ao abrir arquivo %s \n",argv[1]);
        return 1;
    }

    if ((saida=fopen(argv[2],"w"))==NULL)   // testa se consegue criar o arquivo de saída
    {
        printf("erro ao criar arquivo %s \n",argv[2]);
        return 1;
    }

    while (fgets(linha,1000,entrada)) //l� cada linha do arquivo texto
    {
        id = strtok (linha, ";"); //pega o id do tweet
        id_num = atoi(id); //converte o id para num�rico (vai ser necess�rio para inserir o id tweet na lista de ocorr�ncias)
        fprintf(saida,"%d;", id_num);

        palavra = strtok (NULL, separador); //pega a 1a palavra do tweet

        while (palavra != NULL) //enquanto encontrar palavras no tweet
        {
            converte_minuscula(palavra); //converte a palavra para min�sculo
            raiz = indexa(raiz,palavra,id_num); //indexa a palavra na árvore
            palavra = strtok (NULL, separador); //pega a pr�xima palavra do tweet
        }





        fprintf(saida,"\n");
    }
    fclose(entrada); //fecha os arquivos
    fclose(saida);
    return 0; //retorna 0 para indicar que foi bem sucedido
}
