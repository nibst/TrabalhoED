#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedBlack.h"

#define PRETO 1
#define VERMELHO 0

//*************************************************************************
//FUNCOES DE ROTAÇÃO RETIRADAS DOS SLIDES SOBRE AVL (LEVEMENTE MODIFICADAS)
//*************************************************************************
pNodoA* rotacao_direita(pNodoA* p)
{
    pNodoA *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;

    p = u;
    return p;
}

pNodoA* rotacao_esquerda(pNodoA *p)
{
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p = z;
    return p;
}


pNodoA* rotacao_dupla_direita (pNodoA* p)
{
    pNodoA *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;

    p = v;
    return p;
}


pNodoA* rotacao_dupla_esquerda (pNodoA *p)
{
    pNodoA *z, *y;
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
pNodoA* atribuicoesResto(pNodoA *no,char palavra[],int id_num)
{
    no = (pNodoA*)malloc(sizeof(pNodoA));
    no->cor = VERMELHO;
    no->esq = NULL;
    no->esq->cor = PRETO;
    no->dir = NULL;
    no->dir->cor = PRETO;

    no->info.id = id_num;
    strcpy(no->info.palavra,palavra);
    return no;
}

pNodoA* atribuicoesRaiz(pNodoA *no,char palavra[],int id_num)
{
    no = (pNodoA*)malloc(sizeof(pNodoA));
    no->cor = VERMELHO;
    no->esq = NULL;
    no->esq->cor = PRETO;
    no->dir = NULL;
    no->dir->cor = PRETO;

    no->info.id = id_num;
    strcpy(no->info.palavra,palavra);
    return no;
}

pNodoA* indexaAux(pNodoA *no,char palavra[],int id_num)
{
    int ret;
    if(no==NULL)
    {
        no=atribuicoesResto(no, palavra,id_num);
    }
    else
    {

        ret = strcmp(palavra,no->info.palavra);
        //palavra menor valor lexografico que a palavra de nodo a
        if(ret<0)
            no->esq = indexaAux(no->esq,palavra,id_num);


        if(ret>0)
            no->dir = indexaAux(no->dir,palavra,id_num);

        if(ret==0)
            return no;

    }
    return no;
}


pNodoA* indexa(pNodoA *no,char palavra[],int id_num)
{
    int ret;
    //inserir como raiz
    if(no==NULL)
    {
        no=atribuicoesRaiz(no,palavra,id_num);
    }
    else
    {
        ret = strcmp(palavra,no->info.palavra);
        //palavra menor valor lexografico que a palavra de nodo a
        if(ret<0)
            no->esq = indexaAux(no->esq,palavra,id_num);


        if(ret>0)
            no->dir = indexaAux(no->dir,palavra,id_num);

        if(ret==0)
            return no;

    }
     return no;
}





