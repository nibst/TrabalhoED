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
        printf("%s(%d)\n", raiz->info,raiz->cor);

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
NodoRB* rotacao_direita(NodoRB* no)
{

    NodoRB *auxFilho,*auxPai;

    auxPai = no->pai;
    auxFilho = no->esq;
    //trocar a cor ja mesmo acho
    auxFilho->cor = !(auxFilho->cor);
    no->cor = !(no->cor);

    no->esq = auxFilho->dir;
    if(no->esq != NULL)
        no->esq->pai = no;

    auxFilho->dir = no;
    auxFilho->dir->pai = auxFilho;
    //se for raiz a cor é preto
    if(auxPai==NULL)
    {
        auxFilho->cor = PRETO;
    }
    no = auxFilho;
    no->pai = auxPai;
    return no;
}

NodoRB* rotacao_esquerda(NodoRB *no)
{

    NodoRB *auxFilho,*auxPai;
    auxPai = no->pai;
    auxFilho = no->dir;
    //trocar a cor ja mesmo acho
    auxFilho->cor = !(auxFilho->cor);
    no->cor = !(no->cor);

    no->dir = auxFilho->esq;
    if(no->dir != NULL)
        no->dir->pai = no;

    auxFilho->esq = no;
    auxFilho->esq->pai = auxFilho;
    //se for raiz a cor é preto
    if(auxPai==NULL)
    {
        auxFilho->cor = PRETO;
    }
    no = auxFilho;
    no->pai = auxPai;
    return no;
}


NodoRB* rotacao_dupla_direita (NodoRB* no)
{
    NodoRB *auxFilho, *auxNeto,*auxPai;

    auxPai = no->pai;
    auxFilho = no->esq;
    auxNeto = auxFilho->dir;


    //trocar cor
    no->cor = !(no->cor);
    auxNeto->cor = !(auxNeto->cor);

    auxFilho->dir = auxNeto->esq;
    if(auxFilho->dir != NULL)
        auxFilho->dir->pai = auxFilho;

    auxNeto->esq = auxFilho;
    auxNeto->esq->pai = auxNeto;

    no->esq = auxNeto->dir;
    if(no->esq !=NULL)
        no->esq->pai = no;

    auxNeto->dir = no;
    auxNeto->dir->pai = auxNeto;

    if (auxPai == NULL)
    {
        auxNeto->cor = PRETO;
    }

    no = auxNeto;
    no->pai = auxPai;
    return no;
}


NodoRB* rotacao_dupla_esquerda (NodoRB *no)
{
    NodoRB *auxFilho, *auxNeto,*auxPai;

    auxPai = no->pai;
    auxFilho = no->dir;

    auxNeto = auxFilho->esq;

    //trocar cor
    no->cor = !(no->cor);
    auxNeto->cor = !(auxNeto->cor);

    auxFilho->esq = auxNeto->dir;
    if(auxFilho->esq!=NULL)
        auxFilho->esq->pai = auxFilho;

    auxNeto->dir = auxFilho;
    auxNeto->dir->pai = auxNeto;

    no->dir = auxNeto->esq;
    if(no->dir != NULL)
        no->dir->pai = no;

    auxNeto->esq = no;
    auxNeto->esq->pai = auxNeto;
    //se no fosse raiz, o auxneto vai ser nova raiz ent cor=preto
    if(auxPai == NULL)
    {
        auxNeto->cor = PRETO;
    }

    no = auxNeto;
    no->pai = auxPai;
    return no;
}
//*************************************************

NodoRB* alteraCores(NodoRB *no)
{
    //Not de 0 = 1, Not de 1 = 0 == Troca cores
    //troca cores do pai, tio e avo do nodo que foi inserido
    //como essa funcao foi chamada com o avo do nodo inserido, tem q mudar as cores do no no->dir e no->esq
    no->cor =  !(no->cor);
    no->dir->cor =  !(no->dir->cor);
    no->esq->cor =  !(no->esq->cor);

    return no;
}

NodoRB* balanceamento_esq(NodoRB *no, Stats *stats,int *balance)
{
    //essa funcao foi chamada com o avo do nodo inserido, com pai do nodo inserido estando a esquerda do avo
    //entao pode somente ser as rotacoes: simples a direita e dupla a direita

    //Rotacao a direita
    //nodo a esquerda de seu pai e filho a sua esquerda

    NodoRB *filho;
    filho = no->esq;

    //verificar qual neto do no q causou desbalanceamento
    if(filho->esq != NULL)
    {
        if(filho->esq->cor == VERMELHO)
        {
            //filho->esq é o q causou desbalanceamento
            //como filho é no->esq então fazer rotacao simples a direita
            no=rotacao_direita(no);
            stats->rotacoes++;
        }
        else
        {
            //Rotacao dupla a direita
            //filho de no está a esquerda, neto de no esta a direita de filho.
            no=rotacao_dupla_direita(no);
            stats->rotacoes+=2;
        }
    }
    else
    {
        //Rotacao dupla a direita
        //filho de no está a esquerda, neto de no esta a direita de filho.
        no=rotacao_dupla_direita(no);
        stats->rotacoes+=2;
    }
    //balanceamento esta ok, balance =4
    *balance = 4;
    return no;


}
NodoRB* balanceamento_dir(NodoRB *no, Stats *stats,int *balance)
{
    //essa funcao foi chamada com o avo do nodo inserido, com pai do nodo inserido estando a direita do avo
    //entao pode somente ser as rotacoes: simples a esquerda e dupla a esquerda

    NodoRB *filho;
    filho = no->dir;

    //verificar qual neto do no q causou desbalanceamento
    if(filho->dir != NULL)
    {
        if(filho->dir->cor == VERMELHO)
        {
            //filho->dir é o q causou desbalanceamento
            //como filho é no->dir então fazer rotacao simples a esquerda
            no=rotacao_esquerda(no);
            stats->rotacoes++;
        }

        else
        {

            //Rotacao dupla a esquerda
            //filho de no está a direita, neto de no esta a esquerda de filho.
            no=rotacao_dupla_esquerda(no);
            stats->rotacoes+=2;
        }
    }
    else
    {
        //Rotacao dupla a esquerda
        //filho de no está a direita, neto de no esta a esquerda de filho.
        no=rotacao_dupla_esquerda(no);
        stats->rotacoes+=2;
    }
    //balanceamento esta ok, balance =4
    *balance = 4;

    return no;
}
int paiVermelho(NodoRB *no)
{

    NodoRB *Avo;
    Avo = no->pai->pai;
    //nao sei se tio de no é nodo esquerdo ou direito do avo.
    //Mas eu sei por certeza que um dos filhos do avo de no é vermelho(ja que pai de no é vermelho, isso q causou essa funcao)
    //Portanto fazer um and entre os dois filhos do avo de no
    //Se algum dos dois for null vai resultar 0 = false. Como null é  considerado preto e eu sei q pai é vermelho ent tio é o null e é preto.
    if (((Avo)->esq) && ((Avo)->dir))
    {
        //sabendo q os dois nao sao null. Ver se os dois são vermelhos. Se os dois forem vermelhos ->tio vermelho.
        if((((Avo)->esq->cor) && ((Avo)->dir->cor)) == VERMELHO)
        {
            //alterar cor
            return 0;
        }

        //senao tio é preto
        else
        {
            //fazer rotacoes
            return 2;
        }
    }
    //senao tio é preto
    else
    {
        //fazer rotacoes
        return 2;
    }
}



NodoRB* insere_arvore(NodoRB *pai,NodoRB *no,char *palavra,int id,Stats *stats,int *balance)
{
    int retorno;
    stats->comparacoes_index++;
    //se o no for null pode ser arvore vazia ou nodo folha
    if(no == NULL)
    {
        no = (NodoRB*)malloc(sizeof(NodoRB));

        no->esq = NULL;
        no->dir = NULL;

        no->pai= pai;
        no->info = (char*)malloc((strlen(palavra) + 1) * sizeof(char)); //armazena espaço na memória para guardar a palavra
        //colocar a palavra no nodo
        strcpy(no->info,palavra);
        no->desc = inicializa_lista(no->desc);
        no->desc = insere_LSE(no->desc, id);
        //se o nodo for raiz
        if(pai==NULL)
            no->cor = PRETO;
        else
        {
            //inserir vermelho
            no->cor = VERMELHO;
        }
        stats->nodos++;

    }
    else
    {
        //comparar o valor lexografico das palavras
        retorno = strcmp(palavra,no->info);
        //palavra menor valor lexografico que a palavra de nodo no
        if(retorno<0)
        {
            no->esq = insere_arvore(no,no->esq,palavra,id,stats,balance);

             //se pai e filho forem vermelho balancear, verificar o tio do filho
            if((no->cor && no->esq->cor) == VERMELHO)
                *balance = paiVermelho(no->esq);
            //balanceamentos tem q ser depois de definir o no->esq e dps de definir no->dir.
            switch(*balance)
            {

            case 0:
                //atrasar em 1 a volta da recursao para chamar balanceamento com o avo do novo nodo inserido
                (*balance)++;
                break;
            case 1:
                no=alteraCores(no);
                //se o pai for null, nodo é raiz,deixar cor como preto
                if(no->pai == NULL)
                    no->cor = PRETO;
                //balanceamento esta ok, balance =4
                *balance = 4;
                break;
            case 2:
                //atrasar em 1 a volta da recursao para chamar balanceamento com o avo do novo nodo inserido
                (*balance)++;
                break;
            case 3:
                no=balanceamento_esq(no,stats,balance);
                break;
            default:
                break;
            }
        }

        // se palavra de ordem lexografica maior que a do nodo no
        else if(retorno>0)
        {
            no->dir = insere_arvore(no,no->dir,palavra,id,stats,balance);

            //se pai e filho forem vermelho balancear, verificar o tio do filho
              if((no->cor && no->dir->cor) == VERMELHO)
                *balance = paiVermelho(no->dir);
            switch(*balance)
            {

            case 0:
                //atrasar em 1 a volta da recursao para chamar balanceamento com o avo do novo nodo inserido
                (*balance)++;
                break;
            case 1:
                no=alteraCores(no);
                //se o pai for null, nodo é raiz,deixar cor como preto
                if(no->pai == NULL)
                    no->cor = PRETO;
                //balanceamento esta ok, balance =4
                *balance = 4;
                break;
            case 2:
                //atrasar em 1 a volta da recursao para chamar balanceamento com o avo do novo nodo inserido
                (*balance)++;
                break;
            case 3:
                no=balanceamento_dir(no,stats,balance);
                break;
            default:
                break;
            }
        }

        //senao a palavra ja esta na arvore
        else
        {
            if(!consulta_lista(no->desc, id)) //se o ID não existe ainda na lista de incidência
                no->desc = insere_LSE(no->desc, id);
        }
    }
    return no;
}


//********************************************************************
//********************************************************************
NodoRB* consulta_arvore(NodoRB* raiz, char* palavra, Stats* stats)
/* Busca na árvore a palavra dada, retornando um ponteiro para o nodo encontrado.
 * Se não existir a palavra, retorna NULL */
{
    int retorno;

    if(raiz != NULL && palavra !=NULL)  //se a árvore não está vazia e a palavra existe
    {
        retorno = strcmp(palavra, raiz->info);
        stats->comparacoes_search++; //aumenta o número de comparações feitas nas consultas

        if(retorno < 0) //se a palavra é lexicograficamente menor que o nodo atual
        {
            return(consulta_arvore(raiz->esq, palavra, stats)); //vai para o nodo esquerdo
        }
        else if(retorno > 0) //se a palavra é lexicograficamente maior que o nodo atual
        {
            return(consulta_arvore(raiz->dir, palavra, stats)); //vai para o nodo direito
        }
        else        //se a palavra foi encontrada, retorna o ponteiro para esse nodo;
            return raiz;
    }
    else        //se não encontrou a palavra, retorna NULL
        return NULL;
}
