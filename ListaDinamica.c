#include <stdio.h>
#include <stdlib.h>
#include "ListaDinamica.h"

void cria(tLista &lista)
{
    lista.cabeca = NULL;
    lista.tamanho = 0;
}

int vazia(tLista lista)
{
    return lista.tamanho == 0 ? 1 : 0;
}

int tamanho(tLista lista)
{
    return lista.tamanho;
}

int elemento(tLista lista, int pos, int *backup)
{
    int i;
    if(pos <= 0 || pos > lista.tamanho)
        return 0;
    tNoLista *no;
    no = lista.cabeca;
    if(lista.tamanho == 0)
        return 0;
    for(i = 1; i < pos; i++) {
        no = no->proximo;
    }

    *backup = no->dado;
    return 1;
}

int posicao(tLista lista, int dado, int *backup, int *ip)
{
    int i;
    tNoLista *no;
    no = lista.cabeca;
   for(i = 1; no != NULL; i++){
        if(no->dado == dado) {
            *backup = i;
            *ip = no->ip;
            return 1;
        }
        no = no->proximo;
    }

    return 0;
}

int insere(tLista &lista, int pos, int dado, int ip)
{
    int i;
    tNoLista *no, *novoNo;

    if(pos <= 0 || pos > lista.tamanho+1)
        return 0;
    if(pos == 1 && vazia(lista))
    {
        lista.tamanho++;
        lista.cabeca = (tNoLista*)malloc(sizeof(tNoLista));
        novoNo = lista.cabeca;
        if(novoNo == NULL)
            return 0;
        novoNo->proximo = NULL;
        novoNo->dado = dado;
        novoNo->ip = ip;
        lista.cabeca = novoNo;
        return 1;
    }

    no = lista.cabeca;
    //aponta para a posi��o anterior a desejada
    for(i = 2; i < pos; i++) {
        no = no->proximo;
    }

    if(pos == lista.tamanho+1)
    {
        novoNo = (tNoLista*)malloc(sizeof(tNoLista));
        if(novoNo == NULL)
            return 0;
        lista.tamanho++;
        novoNo->dado = dado;
        novoNo->ip = ip;
        no->proximo = novoNo;
        novoNo->proximo = NULL;
        return 1;
    }

    novoNo = (tNoLista*)malloc(sizeof(tNoLista));
    if(novoNo == NULL)
        return 0;
    lista.tamanho++;
    novoNo->dado = dado;
    novoNo->ip = ip;
    novoNo->proximo = no->proximo;
    no->proximo = novoNo;
    return 1;
}

int remover(tLista &lista, int pos, int *backup)
{
    int i;
    tNoLista *no, *noAnterior;

    if(pos <= 0 || pos > lista.tamanho)
        return 0;
    noAnterior = lista.cabeca;
    no = noAnterior->proximo;

    if(pos == 1)
    {
        *backup = noAnterior->dado;
        free(noAnterior);
        lista.cabeca = no;
        lista.tamanho--;
        return 1;
    }

    for(i = 2; i < pos; i++)
    {
        noAnterior = no;
        no = no->proximo;
    }

    noAnterior->proximo = no->proximo;
    *backup = no->dado;
    free(no);
    lista.tamanho--;
    return 1;
}

void exibe(tLista lista)
{
    int i;
    tNoLista *no = lista.cabeca;
    printf("Lista Encadeada com %d elementos\n", lista.tamanho);
    for(i = 0; i < lista.tamanho; i++)
    {
        printf("%d - Elemento da lista: %d\n", i+1, no->dado);
        no = no->proximo;
    }
}

void divide(tLista lista, tLista &pares, tLista &impares){
    int n;
    tNoLista *no, *p, *i;
    no = lista.cabeca;
    p = (tNoLista*)malloc(sizeof(tNoLista));
    pares.cabeca = p;
    i = (tNoLista*)malloc(sizeof(tNoLista));
    impares.cabeca = i;

    for(n = 0; n < lista.tamanho; n++)
    {
        if(no->dado%2 == 0)
        {
            p->dado = no->dado;
            p->ip = p->ip;
            p->proximo = (tNoLista*)malloc(sizeof(tNoLista));
            p = p->proximo;
            pares.tamanho++;
        } else {
            i->dado = no->dado;
            i->ip = i->ip;
            i->proximo = (tNoLista*)malloc(sizeof(tNoLista));
            i = i->proximo;
            impares.tamanho++;
        }
        no = no->proximo;
    }
    free(p);
    free(i);
}

tLista concatena(tLista lista1, tLista lista2){
    int i;
    tNoLista *no = lista1.cabeca, *novoNo;
    tLista novaLista;
    novoNo = (tNoLista*)malloc(sizeof(tNoLista));
    novaLista.cabeca = novoNo;
    novaLista.tamanho = lista1.tamanho + lista2.tamanho;

    for(i = 0; i < lista1.tamanho; i++)
    {
        novoNo->proximo = (tNoLista*)malloc(sizeof(tNoLista));
        novoNo->dado = no->dado;
        novoNo->ip = no->ip;
        no = no->proximo;
        novoNo = novoNo->proximo;
    }

    no = lista2.cabeca;

    for(i = 0; i < lista2.tamanho; i++)
    {
        novoNo->proximo = (tNoLista*)malloc(sizeof(tNoLista));
        novoNo->dado = no->dado;
        novoNo->ip = no->ip;
        no = no->proximo;
        novoNo = novoNo->proximo;
    }

    free(novoNo);
    return novaLista;
}

int modifica(tLista lista, int pos, int dado, int ip) {
    int i;
    tNoLista *no;
    no = lista.cabeca;
    if(pos <= 0 || pos > lista.tamanho)
        return 0;
    for(i = 1; i < pos; i++){
        no = no->proximo;
    }
    no->dado = dado;
    no->ip = ip;
    return 1;
}

void removeValor(tLista &lista, int dado) {
    int i;
    tNoLista *no, *noAnterior = NULL;
    no = lista.cabeca;

    for(i = 1; i < lista.tamanho; i++) {
        if(no->dado == dado){
            if(i == 1){
                lista.cabeca = no->proximo;
                free(no);
                lista.tamanho--;
            }
            noAnterior->proximo = no->proximo;
            free(no);
            no = noAnterior->proximo;
            lista.tamanho--;
        } else {
            noAnterior = no;
            no = no->proximo;
        }
    }
}

void destroi(tLista &lista){
    int i;
    tNoLista *no = lista.cabeca;
    tNoLista *aux = no;
    for(i = 0; i < lista.tamanho; i++)
    {
        no = no->proximo;
        free(aux);
        aux = no;
    }

}