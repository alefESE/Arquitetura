#ifndef MONTADOR_H_INCLUDED
#define MONTADOR_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

extern void fechar();

// quabra IR e retorna um token de comando
string decode(char* str){
    char *token;
    if(strchr(str, ':' != NULL)){
        token = strtok(str, ":");
        return string(token);
    }
    cout << "comando: " << str << endl;
    token = strtok(str, " ");
    if(token == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    int i;
    for(i = 0; i < strlen(token); i++){
        token[i] = tolower(token[i]);
    }
    *remove(token, token+strlen(token), ' ') = 0;
    return string(token);
}

#endif