#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cstring> // memset
#include <string> // string
#include <sstream>//stringstream
#include <cstdlib> // atoi
#include <algorithm> // find_if
#include "registradores.h"
#include "instrucoes.h"
#include "ULA.hpp"
#include "montador.hpp"
#include "FIFO.hpp"

#define palavra 255

//IR(simulacao)
static string ir;
//flags
unsigned char flags = NF;
//parametros
unsigned int tamanho_c = 0;
unsigned int mapeamento_c = 0;

void fechar(){
    destroi(pilha);
    destroi(labels);
    prog.close();
    mem.close();
    fifo->~FIFO();
}

extern void bind_labels();
extern void bind_mem();

int main(int argc, char **argv){
    cout.flush();
    if(argc < 4){
        cout << "Modo de uso: controle <memoria>.txt <programa>.txt associatividade #tamanho" << endl;
        return 0;
    }

    if(string(argv[1]) == string(argv[2])){
        cout << "O nome dos arquivos sao iguais, isto pode trazer problemas." << endl
        << "Por favor modifique o nome dos arquivos." << endl;
        return 0;
    }

    prog.open(argv[2]);
    if(!prog.is_open()){
        cout << "Erro ao abrir " << argv[2] << "!\nVerifique o nome ou a existencia do arquivo" << endl;
        return 0;
    }

    mem.open(argv[1], std::ios::out | std::ios::in | std::fstream::app);
    if(!mem.is_open()){
        mem.clear();
        mem.open(argv[1], std::ios::out | std::ios::out | std::fstream::trunc);
    } else cout << "Cuidado: o arquivo de memoria pode conter lixo" << endl;
    
    mapeamento_c = atoi(argv[3]);
    tamanho_c = atoi(argv[4]);
    //caches
    fifo =  new FIFO(tamanho_c, mapeamento_c);

    memset(&eax, 0, sizeof(eax));
    memset(&ebx, 0, sizeof(ebx));
    memset(&ecx, 0, sizeof(ecx));
    memset(&edx, 0, sizeof(edx));

    memset(&cs, 0, sizeof(cs));
    memset(&ds, 0, sizeof(ds));
    memset(&ss, 0, sizeof(ss));

    memset(&si, 0, sizeof(si));
    memset(&di, 0, sizeof(di));
    memset(&bp, 0, sizeof(bp));
    memset(&ip, 0, sizeof(ip));

    cria(pilha);
    cria(labels);
    cria(mems);

    bind_labels();
    bind_mem();

    string token;
    cout << "Realizando fetch" << endl;
    int estado = Fetch;
    while(1){
        switch(estado){
            case Fetch:
            {
                ir = fifo->fetch_inst(ip.x, mapeamento_c, &prog);
                if(prog.eof() && prog.fail()){ // endoffile(ufa)
                    cout << "Programa terminado" << endl;
                    fechar();
                    cout << "data_hit: " << fifo->get_data_hit() << endl;
                    cout << "inst_hit: " << fifo->get_inst_hit() << endl;
                    cout << "data_miss: " << fifo->get_data_miss() << endl;
                    cout << "inst_miss: " << fifo->get_inst_miss() << endl;
                    system("pause");
                    return 1;
                }else if(prog.fail()){
                    cout << "Erro de sintaxe." << endl << "Verifique o codigo" << endl;
                    fechar(); 
                    return 0;
                }else{ 
                    //cout << "ip " << ip.x << endl;
                    cout << "Decodificando" << endl;
                    estado = Decode;
                    break;
                }
            }
            case Decode:
            {
                token = decode(ir);
                cout << "Executando " << endl;
                estado = Execute;
                break;
            }
            case Execute:
            {
                switch(hashOp(token)){ //execute
                    case ADD:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        sum(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case SUB:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        sub(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case MUL:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        mul(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case DIV:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        div(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case DEC:
                    {
                        char *op = NULL;
                        dec(op);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;  
                    }
                    case INC:
                    {
                        char *op = NULL;
                        inc(op);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;  
                    }
                    case AND:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        and_op(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case NOT:
                    {
                        char *op = NULL;
                        not_op(op);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case OR:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        or_op(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case XOR:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        xor_op(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case NEG:
                    {
                        char *op = NULL;
                        neg(op);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case CMP:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        cmp(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case MOV:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        mov(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case JMP:
                    {
                        char *lbl = NULL;
                        int i;
                        ip.x = jmp(lbl, labels);
                        cout << "AQUI" << endl;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case JZ:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(flags & ZF){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JNZ:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(!(flags & ZF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JS:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(flags & CF){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JNS:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(!(flags & ZF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JO:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(flags & OF){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JNO:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(!(flags & ZF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JC:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(flags & CF){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JNC:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(!(flags & CF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JB:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(flags & CF){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JBE:
                    {
                        char *lbl =  NULL;
                        int i;
                        if((flags & ZF) || (flags & CF)){
                            ip.x = jmp(lbl, labels);
                            prog.seekg (0, prog.beg); //"rebobina" stream
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JAE:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(!(flags & CF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JA:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(!((flags & ZF) && (flags & CF))){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JL:
                    {
                        char *lbl =  NULL;
                        int i;
                        if((flags & SF) != (flags & OF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JLE:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(((flags & SF) != (flags & OF)) || (flags & ZF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JGE:
                    {
                        char *lbl =  NULL;
                        int i;
                        if((flags & SF) == (flags & OF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case JG:
                    {
                        char *lbl =  NULL;
                        int i;
                        if(((flags & SF) == (flags & OF)) && !(flags & ZF)){
                            ip.x = jmp(lbl, labels);
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        } else{
                            ip.x = ip.x + 1;
                            cout << "Realizando fetch" << endl;
                            estado = Fetch;
                            break;
                        }
                    }
                    case CALL:
                    {
                        char *lbl = NULL;
                        int i;
                        call(lbl);
                        cout << "Decodificando" << endl;
                        estado = Decode;
                        break;
                    }
                    case RET:
                    {
                        if(ret()){
                            cout << "Decodificando" << endl;
                            estado = Decode;
                            break;
                        } else {
                            ip.x = ip.x + 1;
                            cout << "Decodificando" << endl;
                            estado = Decode;
                            break;
                        }
                    }
                    case PUSH:
                    {
                        char *reg = NULL;
                        push_reg(reg);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case POP:
                    {
                        char *reg = NULL;
                        pop_reg(reg);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case LEA:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        lea(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                    case STR:
                    {
                        char *op1 = NULL;
                        char *op2 = NULL;
                        str(op1, op2);
                        ip.x = ip.x + 1;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;  
                    }
                    case LBL: // do_noting
                    {
                        ip.x = ip.x + 1;
                        cout << "Do nothing" << endl;
                        cout << "Realizando fetch" << endl;
                        estado = Fetch;
                        break;
                    }
                }
            }
        }
    }
/* testes
    flags = Flags_enum(flags | CF);//ativa
    flags = Flags_enum(flags | ZF);//ativa
    flags = Flags_enum(flags & ~CF);//desativa

    if((flags & CF) && (flags & ZF)){
        cout << "aqui" << endl;
    }
    char s[20] = "ADD eax, 1\n"; //lembrar de tirar isso
    decode(s);
*/
    return 1;
}

void bind_labels(){
    string s;
    int pos;
    int i = 0, result = 0, j;
    while(!(prog.eof())){
        getline(prog, s, '\n');
        i++;
        *remove_if(s.begin(), s.end(), ::isspace) = 0;
        if(!((pos = s.find(':')) == -1)){
            string erro = s.substr(pos+1);
            //cout << "erro: " << erro << endl;
            if(!erro.empty()){
                cout << "Erro de sintaxe na linha " << i << endl;
                cout << "Abortando programa." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }else{
                string lbl = s.substr(0, pos);
                //cout << "lbl: " << lbl << endl;
                for(j = 0; j < lbl.size(); j++) result += lbl[j];
                //cout << result << endl;
                insere(labels, labels.tamanho+1, result, i);
            }
        }
    }
    prog.clear();
    prog.seekg (0, prog.beg); //"rebobina" stream
    //exibe(labels);
}

void bind_mem(){
    string s;
    int pos;
    int i = 0;
    while(!(mem.eof())){
        getline(mem, s);
        //cout << "mem eof: " << mem.eof() << endl;
        i++;
        if((pos = s.find(':')) != -1){
            string erro = s.substr(pos+1);
            //cout << "erro: " << erro << endl;
            *remove_if(erro.begin(), erro.end(), ::isspace) = 0;
            //cout << "erromem: " << erro << endl;
            if(!erro.empty()){
                cout << "Memoria corrompida na linha: " << i << endl;
                cout << "Abortando programa." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }else{
                string var = s.substr(0, pos);
                //cout << "var: " << var << endl;
                insere(mems, mems.tamanho+1, atoi(var.c_str()), i);
            }
        }
    }
    mem.clear();
    mem.seekg (0, prog.beg); //"rebobina" stream
    //exibe(mems);
}