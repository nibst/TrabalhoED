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

NodoRB* inicializa_arvore()
/* Retorna NULL para inicializar o ponteiro par aa raiz da �rvore */
{
    return NULL;
}

//*************************************************************************
//FUNCOES DE ROTA��O RETIRADAS DOS SLIDES SOBRE AVL (LEVEMENTE MODIFICADAS)
//*************************************************************************
NodoRB* rotacao_direita(NodoRB* p)
{
    NodoRB *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;

    p = u;
    return p;
}

NodoRB* rotacao_esquerda(NodoRB *p)
{
    NodoRB *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p = z;
    return p;
}


NodoRB* rotacao_dupla_direita (NodoRB* p)
{
    NodoRB *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;

    p = v;
    return p;
}


NodoRB* rotacao_dupla_esquerda (NodoRB *p)
{
    NodoRB *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;

    p = y;
    return p;
}
//*************************************************


//so pra nao repetir codigo
NodoRB* atribuicoes(NodoRB *no,char *palavra,int id)
{
    no->esq = NULL;
    no->esq->cor = PRETO;
    no->dir = NULL;
    no->dir->cor = PRETO;
    no->pai = NULL;
    no->pai->cor = PRETO;

    strcpy(no->info,palavra);
    return no;
}
//insere os nodos sem ser a raiz
NodoRB* indexaAux(NodoRB *no,char palavra[],int id)
{
    int ret;
    if(no==NULL)
    {
        no = (NodoRB*)malloc(sizeof(NodoRB));
        no->cor = VERMELHO;
        no=atribuicoes(no, palavra,id);
    }
    else
    {

        ret = strcmp(palavra,no->info);
        //palavra menor valor lexografico que a palavra de nodo a
        if(ret<0)
            no->esq = indexaAux(no->esq,palavra,id);


        if(ret>0)
            no->dir = indexaAux(no->dir,palavra,id);

        if(ret==0)
            return no;

    }
    return no;
}

//insere a raiz se for null, se nao for nulo vai pra funcao q insere outros nodos
NodoRB* insere_RB(NodoRB *no,char *palavra,int id,Stats *stats)
{
    int ret;
    //inserir como raiz
    if(no==NULL)
    {
        no = (NodoRB*)malloc(sizeof(NodoRB));
        no->cor = PRETO;
        no=atribuicoes(no,palavra,id);
    }
    else
    {
        ret = strcmp(palavra,no->info);
        //palavra menor valor lexografico que a palavra de nodo a
        if(ret<0)
            no->esq = indexaAux(no->esq,palavra,id);


        if(ret>0)
            no->dir = indexaAux(no->dir,palavra,id);

        if(ret==0)
            return no;

    }
     return no;
}





