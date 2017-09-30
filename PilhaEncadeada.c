#include <stdlib.h>
#include <stdio.h>
#include "PilhaEncadeada.h"

void cria(tPilhaEncadeada &pilha) {
    pilha.tamanho = 0;
    pilha.topo = NULL;
}

int tamanho(tPilhaEncadeada pilha) {
    return pilha.tamanho;
}

int vazia(tPilhaEncadeada pilha) {
    return pilha.tamanho == 0 ? 1 : 0;
}

int top(tPilhaEncadeada pilha, int *backup, int *id) {
    if(vazia(pilha))
        return 0;
    *backup = pilha.topo->dado;
    *id = pilha.topo->id;
    return 1;
}

int push(tPilhaEncadeada &pilha, int dado, int id) {
    tNoPilha *novoNo;
    novoNo = (tNoPilha*)malloc(sizeof(tNoPilha));
    if(novoNo == NULL)
        return 0;
    novoNo->dado = dado;
    novoNo->id = id;
    novoNo->anterior = pilha.topo;
    pilha.topo = novoNo;
    pilha.tamanho++;
    return 1;
}

int pop(tPilhaEncadeada &pilha, int *backup, int *id) {
    if(vazia(pilha))
        return 0;
    tNoPilha *noAntigo;
    noAntigo = pilha.topo;
    pilha.topo = noAntigo->anterior;
    *backup = noAntigo->dado;
    *id = noAntigo->id;
    pilha.tamanho--;
    free(noAntigo);
    return 1;
}

int exibe(tPilhaEncadeada pilha) {
    if(vazia(pilha))
        return 0;
    int i;
    tNoPilha *no;
    no = pilha.topo;
    printf("Pilha de tamanho %d \n", pilha.tamanho);
    for(i = 0; i < pilha.tamanho; i++) {
        printf("%d elemento: %d\n", i+1, no->dado);
        no = no->anterior;
    }
    return 1;
}

int inverte(tPilhaEncadeada &pilha) {
    if(vazia(pilha))
        return 0;
    int i, dado;
    int tamanho = pilha.tamanho;
    tPilhaEncadeada invertida;
    cria(invertida);
    for(i = 0; i < tamanho; i++) {
        pop(pilha, &dado, NULL);
        push(invertida, dado, NULL);
    }
    pilha.tamanho = invertida.tamanho;
    pilha.topo = invertida.topo;
    return 1;
}

int elimina(tPilhaEncadeada &pilha, int dado) {
    if(vazia(pilha))
        return 0;
    int i, eliminados = 0, backup;
    tNoPilha *no, *eliminado;
    no = pilha.topo;
    eliminado = no;
    for(i = 0; i < pilha.tamanho; i++) {
        if(i == 0) {
            if(eliminado->dado == dado) {
                pop(pilha, &backup, NULL);
                i--;
            }
        }
        eliminado = no->anterior;
        if(eliminado == NULL)
            break;
        if(eliminado->dado == dado) {
            no->anterior = eliminado->anterior;
            free(eliminado);
            eliminados++;
            pilha.tamanho--;
        }
        no = no->anterior;
    }

    return eliminados;
}

int iguais(tPilhaEncadeada pilha1, tPilhaEncadeada pilha2) {
    if(vazia(pilha1) || vazia(pilha2))
        return 0;
    if(!(pilha1.tamanho == pilha2.tamanho))
        return 0;
    tNoPilha *no1, *no2;
    no1 = pilha1.topo;
    no2 = pilha2.topo;
    int i;
    for(i = 0; i < pilha1.tamanho; i++) {
        if(!no1->dado == no2->dado)
            return 0;
        no1 = no1->anterior;
        no2 = no2->anterior;
    }
    return 1;
}

int destroi(tPilhaEncadeada &pilha) {
    if(vazia(pilha))
        return 0;
    tNoPilha *no, *aux;
    no = pilha.topo;
    aux = no;
    while(aux != NULL) {
        aux = no->anterior;
        free(no);
        no = aux;
    }
    pilha.tamanho = 0;
    pilha.topo = NULL;
    return 1;
}
