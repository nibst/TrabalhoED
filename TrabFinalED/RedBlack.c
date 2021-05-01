#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedBlack.h"

#define PRETO 0
#define VERMELHO 1


//*************************************************
//   OPERAÇÕES DA LISTA SIMPLESMENTE ENCADEADA
//*************************************************

Descritor inicializa_lista(Descritor desc)
/* Inicializa o ponteiro para o início da lista */
{
    desc.fimLista = NULL;
    desc.inicioLista = NULL;

    return desc;
}

//********************************************************************
//********************************************************************

Descritor insere_LSE(Descritor desc, int info)
/* Insere no início da lista os dados de um novo jogo.
 * Atualiza o descritor da lista caso for possível inserir um elemento no final.
 * Se não houver mais espaço na memória, apenas devolve o descritor da lista */
{
    LSE* novo;

    novo = (LSE*)malloc(sizeof(LSE));

    if(novo != NULL)
        //se teve espaço na memória para alocar
    {
        novo->info = info;      //guarda a informação

        if(desc.inicioLista == NULL)    //se a lista está vazia
        {
            desc.inicioLista = novo;    //novo ID é o início e fim da lista
            desc.fimLista = novo;
        }
        else                            //senão
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
/* Verifica se um dado ID está na lista.
 * Devolve 1 se ele estiver.
 * Devolve 0 se não estiver. */
{
    while(desc.inicioLista != NULL) //enquanto não chegou no final da lista
    {
        if(desc.inicioLista->info == info) //se encontrar o elemento
            return 1;              //retorna 1
        desc.inicioLista = desc.inicioLista->prox;
    }

    return 0; //se não encontrou o elemento, retorna 0
}

//*************************************************
//           OPERAÇÕES DA ÁRVORE AVL
//*************************************************

NodoRB* inicializa_arvore(NodoRB *no)
//inicializa o nodo como null
{
    return NULL;
}

//********************************************************************
//********************************************************************

void imprime_formatado(NodoRB* raiz, int nivel)
/* Imprime a árvore formatadamente com identação para identificar os diferentes níveis dos nodos */
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
/* Calcula a altura de uma árvore ou subárvore dada a sua raíz. */
{
    int Alt_Esq, Alt_Dir;

    if (nodo == NULL)
        return 0;
    else
    {
        Alt_Esq = altura(nodo->esq);
        Alt_Dir = altura(nodo->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq); //devolve a altura da subárvore mais alta
        else
            return (1 + Alt_Dir);
    }
}

//*************************************************************************
//FUNCOES DE ROTAÇÃO RETIRADAS DOS SLIDES SOBRE AVL (LEVEMENTE MODIFICADAS)
//*************************************************************************
NodoRB* rotacao_direita(NodoRB **raiz,NodoRB* no)
{

    NodoRB *aux;
    aux = no->esq;
    //trocar a cor ja mesmo acho
    aux->cor = !(aux->cor);
    no->cor = !(aux->cor);

    no->esq = aux->dir;
    aux->dir = no;
    if(no==*raiz)
    {
        *raiz = aux;
        aux->cor = PRETO;
    }
    no = aux;
    return no;
}

NodoRB* rotacao_esquerda(NodoRB **raiz,NodoRB *p)
{

    NodoRB *aux;
    aux = no->dir;
    //trocar a cor ja mesmo acho
    aux->cor = !(aux->cor);
    no->cor = !(aux->cor);
    no->dir = aux->esq;
    aux->esq = no;
    if(no==*raiz)
    {
        *raiz = aux;
        aux->cor = PRETO;
    }
    no = aux;
    return no;
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
NodoRB* paiVermelho(NodoRB **raiz,NodoRB *no,Stats *stats)
{

    //nao sei se tio de no é nodo esquerdo ou direito do avo.
    //Mas eu sei por certeza que um dos filhos do avo de no é vermelho(ja que pai de no é vermelho, isso q causou essa funcao)
    //Portanto fazer um and entre os dois filhos do avo de no
    //Se os dois forem vermelho vai resultar VERMELHO->tio vermelho, se um deles for preto vai resultar PRETO -> tio preto
    if (((no->pai->pai)->esq->cor) && ((no->pai->pai)->dir->cor) == VERMELHO)
    {
        no=alteraCores(no);
        //se o avo for raiz,deixar cor como preto
        if(no->pai->pai->pai == NULL)
            (no->pai->pai)->cor = PRETO;

    }
    //senao tio é preto
    else
    {
        no=balanceamento(no,stats);
    }
    return no;

}

//so pra nao repetir codigo
NodoRB* atribuicoes(NodoRB *no,char *palavra,int id)
{
    no->esq->cor = PRETO;
    no->esq = NULL;
    no->dir->cor = PRETO;
    no->dir = NULL;
    no->desc = insere_LSE(no->desc, id);

    //colocar a palavra no nodo
    strcpy(no->info,palavra);
    return no;
}

//insere a raiz se for null, se nao for nulo vai pra funcao q insere outros nodos
NodoRB* insere_RB(NodoRB **raiz,NodoRB *no,char *palavra,int id,Stats *stats)
{
    int retorno;

    //se a raiz for null a arvore eh vazia
    if(*raiz == NULL)
    {
        no = (NodoRB*)malloc(sizeof(NodoRB));
        no=atribuicoes(no,palavra,id);
        no->desc = insere_LSE(no->desc, id);
        no->cor = PRETO;
        no->pai=NULL;
        *raiz=no;
    }
    else
    {
        retorno = strcmp(palavra,no->info);
        //palavra menor valor lexografico que a palavra de nodo no
        if(retorno<0)
        {   //se esquerdo eh null inserir no esquerdo
            if(no->esq==NULL)
            {
                no->esq = (NodoRB*)malloc(sizeof(NodoRB));
                no->esq=atribuicoes(no->esq,palavra,id);
                no->esq->pai = no;
                //se o pai for vermelho fazer os tratamentos para balancear
                if(no->cor == VERMELHO)
                {
                    no->esq=paiVermelho(raiz,no->esq,stats);
                }
                //senao o pai é preto, entao é so inserir nodo como vermelho
                else
                    no->esq->cor =  VERMELHO;
                return no->esq;
            }
            else
                no->esq = insere_RB(raiz,no->esq,palavra,id,stats);
        }

        else if(retorno>0)
            //palavra de ordem lexografica maior que a do nodo no
        {
            //se direito eh null inserir no direito
            if(no->dir==NULL)
            {
                no->dir = (NodoRB*)malloc(sizeof(NodoRB));
                no->dir=atribuicoes(no->dir,palavra,id);
                no->dir->pai = no;
                if(no->cor == VERMELHO)
                {
                    no->dir=paiVermelho(raiz,no->dir,stats);
                }
                //senao o pai é preto, entao é so inserir nodo como vermelho
                else
                    no->dir->cor =  VERMELHO;
                return no->dir;
            }
            else
                no->dir = insere_RB(raiz,no->dir,palavra,id,stats);
        }

        //senao a palavra ja esta na arvore
        else
        {
            if(!consulta_lista(no->desc, id)) //se o ID não existe ainda na lista de incidência
                no->desc = insere_LSE(no->desc, id);
        }


    }
    return *raiz;
}


//********************************************************************
//********************************************************************

NodoRB* consulta_arvore(NodoRB* raiz, char* palavra, Stats* stats)
/* Busca na árvore a palavra dada, retornando um ponteiro para o nodo encontrado.
 * Se não existir a palavra, retorna NULL */
{
    if(raiz != NULL)  //se a árvore não está vazia
    {
        stats->comparacoes_search++; //aumenta o número de comparações feitas nas consultas

        if(strcmp(palavra, raiz->info) < 0) //se a palavra é lexicograficamente menor que o nodo atual
        {
            return(consulta_arvore(raiz->esq, palavra, stats)); //vai para o nodo esquerdo
        }
        else if(strcmp(palavra, raiz->info) > 0) //se a palavra é lexicograficamente maior que o nodo atual
        {
            return(consulta_arvore(raiz->dir, palavra, stats)); //vai para o nodo direito
        }
        else        //se a palavra foi encontrada, retorna o ponteiro para esse nodo;
            return raiz;
    }
    else        //se não encontrou a palavra, retorna NULL
        return NULL;
}


