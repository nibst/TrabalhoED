//TAD Rubro-Negra

//*******************************************

typedef struct Tipo_Stats
{
    int nodos;              // Contagem dos nodos da árvore
    int rotacoes;           // Contagem das rotações feitas na indexação
    int altura;             // Altura total da árvore
    int comparacoes_index;  // Comparações feitas na indexação
    int comparacoes_search; // Comparações feitas na consulta
}Stats;

//*******************************************

typedef struct Tipo_LSE
{
    int info;               // ID do tweet
    struct Tipo_LSE* prox;  // Ponteiro para o próximo elemento da lsita
}LSE;

//*******************************************

typedef struct Tipo_Desc
{
    LSE *inicioLista;       // Aponta para o início da lista
    LSE *fimLista;          // Aponta para o fim da lista
}Descritor;


//*******************************************

typedef struct Tipo_RedBlack
{
    struct Tipo_RedBlack *esq;   // Ponteiro para subárvore esquerda
    struct Tipo_RedBlack *dir;   // Ponteiro para subárvore direita
    struct Tipo_RedBlack *pai;   // Ponteiro para o pai do nodo atual
    int cor;                     // Cor do nodo atual (0=preto, 1=vermelho)
    char *info;                  // Palavra do nodo
    Descritor desc;              // Descritor da lista de incidência, apontando para o início e para o fim
}NodoRB;
//*******************************************

//Funções do LSE
Descritor inicializa_lista(Descritor desc);

Descritor insere_LSE(Descritor desc, int info);

int consulta_lista(Descritor desc, int info);

//Funções da Red-Black
NodoRB* inicializa_arvore();

NodoRB* insere_RB(NodoRB *pai, NodoRB *no,char *palavra,int id,Stats *stats);

NodoRB* consulta_arvore(NodoRB *no, char *palavra, Stats *stats);

void imprime_formatado(NodoRB *no, int nivel);

int altura (NodoRB *no);









