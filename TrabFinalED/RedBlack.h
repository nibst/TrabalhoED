//TAD Rubro-Negra

typedef struct tInfo
{
    int id;
    char palavra[20];
}TipoInfo;

typedef struct TNodoA{
TipoInfo info;
int cor;
struct TNodoA *esq;
struct TNodoA *dir;

}pNodoA;


//Funções da Red-Black

pNodoA* rotacao_direita(pNodoA* p);

pNodoA* rotacao_esquerda(pNodoA *p);

pNodoA* rotacao_dupla_direita (pNodoA* p);

pNodoA* rotacao_dupla_esquerda (pNodoA *p);

//insere nodos à árvore
pNodoA* indexa(pNodoA *no,char palavra[],int id_num);







