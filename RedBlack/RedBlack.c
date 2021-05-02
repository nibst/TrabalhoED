#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedBlack.h"

#define PRETO 0
#define VERMELHO 1


//*************************************************
//   OPERA��ES DA LISTA SIMPLESMENTE ENCADEADA
//*************************************************

Descritor inicializa_lista(Descritor desc)
/* Inicializa o ponteiro para o in�cio da lista */
{
    desc.fimLista = NULL;
    desc.inicioLista = NULL;

    return desc;
}

//********************************************************************
//********************************************************************

Descritor insere_LSE(Descritor desc, int info)
/* Insere no in�cio da lista os dados de um novo jogo.
 * Atualiza o descritor da lista caso for poss�vel inserir um elemento no final.
 * Se n�o houver mais espa�o na mem�ria, apenas devolve o descritor da lista */
{
    LSE* novo;

    novo = (LSE*)malloc(sizeof(LSE));

    if(novo != NULL)
        //se teve espa�o na mem�ria para alocar
    {
        novo->info = info;      //guarda a informa��o

        if(desc.inicioLista == NULL)    //se a lista est� vazia
        {
            desc.inicioLista = novo;    //novo ID � o in�cio e fim da lista
            desc.fimLista = novo;
        }
        else                            //sen�o
        {
            desc.fimLista->prox = novo; //fim da lista aponta para o novo termo
            desc.fimLista = novo;       //novo termo se torna o fim da lista
        }

        novo->prox = NULL;
    }

    //retorna o descritor da lista
    return desc;
}

//********************************************************************
//********************************************************************

int consulta_lista(Descritor desc, int info)
/* Verifica se um dado ID est� na lista.
 * Devolve 1 se ele estiver.
 * Devolve 0 se n�o estiver. */
{
    while(desc.inicioLista != NULL) //enquanto n�o chegou no final da lista
    {
        if(desc.inicioLista->info == info) //se encontrar o elemento
            return 1;              //retorna 1
        desc.inicioLista = desc.inicioLista->prox;
    }

    return 0; //se n�o encontrou o elemento, retorna 0
}

//*************************************************
//           OPERA��ES DA �RVORE AVL
//*************************************************

NodoRB* inicializa_arvore(NodoRB *no)
//inicializa o nodo como null
{
    return NULL;
}

//********************************************************************
//********************************************************************

void imprime_formatado(NodoRB* raiz, int nivel)
/* Imprime a �rvore formatadamente com identa��o para identificar os diferentes n�veis dos nodos */
{
    int i;
    if(raiz != NULL)
    {
        for(i = 0; i < nivel; i++)
        {
            printf("=");
        }
        printf("%s\n", raiz->info);

        imprime_formatado(raiz->esq, nivel + 1);
        imprime_formatado(raiz->dir, nivel + 1);
    }
}

//********************************************************************
//********************************************************************

int altura(NodoRB *nodo)
/* Calcula a altura de uma �rvore ou sub�rvore dada a sua ra�z. */
{
    int Alt_Esq, Alt_Dir;

    if (nodo == NULL)
        return 0;
    else
    {
        Alt_Esq = altura(nodo->esq);
        Alt_Dir = altura(nodo->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq); //devolve a altura da sub�rvore mais alta
        else
            return (1 + Alt_Dir);
    }
}

//*************************************************************************
//FUNCOES DE ROTA��O RETIRADAS DOS SLIDES SOBRE AVL (LEVEMENTE MODIFICADAS)
//*************************************************************************
NodoRB* rotacao_direita(NodoRB* no)
{

    NodoRB *aux;
    aux = no->esq;
    //trocar a cor ja mesmo acho
    aux->cor = !(aux->cor);
    no->cor = !(aux->cor);

    no->esq = aux->dir;
    aux->dir = no;
    //se for raiz a cor � preto
    if(no->pai==NULL)
    {
        aux->cor = PRETO;
    }
    no = aux;
    return no;
}

NodoRB* rotacao_esquerda(NodoRB *no)
{

    NodoRB *aux;
    aux = no->dir;
    //trocar a cor ja mesmo acho
    aux->cor = !(aux->cor);
    no->cor = !(aux->cor);

    no->dir = aux->esq;
    aux->esq = no;
    //se for raiz a cor � preto
    if(no->pai==NULL)
    {
        aux->cor = PRETO;
    }
    no = aux;
    return no;
}


NodoRB* rotacao_dupla_direita (NodoRB* no)
{
    NodoRB *auxFilho, *auxNeto;
    auxFilho = no->esq;

    //trocar cor
    no->cor = !(no->cor);
    auxFilho->cor = !(auxFilho->cor);

    auxNeto = auxFilho->dir;
    auxFilho->dir = auxNeto->esq;
    auxNeto->esq = auxFilho;
    no->esq = auxNeto->dir;
    auxNeto->dir = no;

    if (no->pai == NULL)
    {
        auxNeto->cor = PRETO;
    }

    no = auxNeto;
    return no;
}


NodoRB* rotacao_dupla_esquerda (NodoRB *no)
{
    NodoRB *auxFilho, *auxNeto;
    auxFilho = no->dir;

    //trocar cor
    no->cor = !(no->cor);
    auxFilho->cor = !(auxFilho->cor);

    auxNeto = auxFilho->esq;
    auxFilho->esq = auxNeto->dir;
    auxNeto->dir = auxFilho;
    no->dir = auxNeto->esq;
    auxNeto->esq = no;
    //se no fosse raiz, o auxneto vai ser nova raiz ent cor=preto
    if(no->pai == NULL)
    {
        auxNeto->cor = PRETO;
    }

    no = auxNeto;
    return no;
}
//*************************************************

NodoRB* alteraCores(NodoRB *no)
{
    //Not de 0 = 1, Not de 1 = 0 == Troca cores
    (no->pai->pai)->cor =  !((no->pai->pai)->cor);
    (no->pai->pai)->dir->cor =  !((no->pai->pai)->dir->cor);
    (no->pai->pai)->esq->cor =  !((no->pai->pai)->esq->cor);

    return no;
}

NodoRB* balanceamento(NodoRB *no, Stats *stats)
{

    return no;
}
NodoRB* paiVermelho(NodoRB *no,Stats *stats)
{

    //nao sei se tio de no � nodo esquerdo ou direito do avo.
    //Mas eu sei por certeza que um dos filhos do avo de no � vermelho(ja que pai de no � vermelho, isso q causou essa funcao)
    //Portanto fazer um and entre os dois filhos do avo de no
    //Se os dois forem vermelho vai resultar VERMELHO->tio vermelho, se um deles for preto vai resultar PRETO -> tio preto
    if (((no->pai->pai)->esq->cor) && ((no->pai->pai)->dir->cor) == VERMELHO)
    {
        no=alteraCores(no);
        //se o avo for raiz,deixar cor como preto
        if(no->pai->pai->pai == NULL)
            (no->pai->pai)->cor = PRETO;

    }
    //senao tio � preto
    else
    {
        no=balanceamento(no,stats);
    }
    return no;

}

//so pra nao repetir codigo
NodoRB* atribuicoes(NodoRB *pai,NodoRB *no,char *palavra,int id)
{
    no->esq->cor = PRETO;
    no->esq = NULL;
    no->dir->cor = PRETO;
    no->dir = NULL;
    no->desc = insere_LSE(no->desc, id);
    no->pai= pai;

    //colocar a palavra no nodo
    strcpy(no->info,palavra);
    return no;
}


NodoRB* insere_RB(NodoRB *pai,NodoRB *no,char *palavra,int id,Stats *stats)
{
    int retorno;

    //se o no for null pode ser arvore vazia ou nodo folha
    if(no == NULL)
    {
        no = (NodoRB*)malloc(sizeof(NodoRB));
        no=atribuicoes(pai,no,palavra,id);
        //se o nodo for raiz
        if(pai==NULL)
            no->cor = PRETO;
        else
        {
            //inserir vermelho
            no->cor = VERMELHO;
            //se pai for vermelho balancear
            if(pai->cor == VERMELHO)
                no=paiVermelho(no,stats);
        }


    }
    else
    {
        //comparar o valor lexografico das palavras
        retorno = strcmp(palavra,no->info);
        //palavra menor valor lexografico que a palavra de nodo no
        if(retorno<0)
            no->esq = insere_RB(no,no->esq,palavra,id,stats);

        // se palavra de ordem lexografica maior que a do nodo no
        else if(retorno>0)
            no->dir = insere_RB(no,no->dir,palavra,id,stats);

        //senao a palavra ja esta na arvore
        else
        {
            if(!consulta_lista(no->desc, id)) //se o ID n�o existe ainda na lista de incid�ncia
                no->desc = insere_LSE(no->desc, id);
        }


    }
    return no;
}


//********************************************************************
//********************************************************************

NodoRB* consulta_arvore(NodoRB* raiz, char* palavra, Stats* stats)
/* Busca na �rvore a palavra dada, retornando um ponteiro para o nodo encontrado.
 * Se n�o existir a palavra, retorna NULL */
{
    if(raiz != NULL)  //se a �rvore n�o est� vazia
    {
        stats->comparacoes_search++; //aumenta o n�mero de compara��es feitas nas consultas

        if(strcmp(palavra, raiz->info) < 0) //se a palavra � lexicograficamente menor que o nodo atual
        {
            return(consulta_arvore(raiz->esq, palavra, stats)); //vai para o nodo esquerdo
        }
        else if(strcmp(palavra, raiz->info) > 0) //se a palavra � lexicograficamente maior que o nodo atual
        {
            return(consulta_arvore(raiz->dir, palavra, stats)); //vai para o nodo direito
        }
        else        //se a palavra foi encontrada, retorna o ponteiro para esse nodo;
            return raiz;
    }
    else        //se n�o encontrou a palavra, retorna NULL
        return NULL;
}


