#ifndef PILHAENCADEADA_H_INCLUDED
#define PILHAENCADEADA_H_INCLUDED

typedef struct noPilha {
    int dado, id;
    struct noPilha *anterior;
} tNoPilha;

typedef struct {
    int tamanho;
    tNoPilha *topo;
} tPilhaEncadeada;

void cria(tPilhaEncadeada &pilha);
int vazia(tPilhaEncadeada pilha);
int tamanho(tPilhaEncadeada pilha);
int top(tPilhaEncadeada pilha, int *backup, int *id);
int push(tPilhaEncadeada &pilha, int dado, int id);
int pop(tPilhaEncadeada &pilha, int *backup, int *id);
int exibe(tPilhaEncadeada pilha);
int inverte(tPilhaEncadeada &pilha);
int elimina(tPilhaEncadeada &pilha, int dado);
int iguais(tPilhaEncadeada pilha1, tPilhaEncadeada pilha2);
int destroi(tPilhaEncadeada &pilha);
    
#endif // PILHAENCADEADA_H_INCLUDED
