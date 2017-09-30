#ifndef LISTADINAMICA_H
#define LISTADINAMICA_H
#define MAX 100

typedef struct noLista {
    int dado, ip;
    struct noLista *proximo;
} tNoLista;

typedef struct{
    tNoLista *cabeca;
    int tamanho;
}tLista;

extern void cria(tLista &lista);
extern int vazia(tLista lista);
extern int tamanho(tLista lista);
extern int modifica(tLista lista, int pos, int dado, int ip);
extern void removeValor(tLista &lista, int dado);
extern void exibe(tLista lista);
extern void divide(tLista lista, tLista &pares, tLista &impares);
extern tLista concatena(tLista lista1, tLista lista2);
extern int elemento(tLista lista, int pos, int *backup);
extern int posicao(tLista lista, int dado, int *backup, int *ip);
extern int insere(tLista &lista, int pos, int dado, int ip);
extern int remover(tLista &lista, int pos, int *backup);
extern void destroi(tLista &lista);

#endif // LISTA
