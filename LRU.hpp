#ifndef LRU_H_INCLUDED
#define LRU_H_INCLUDED

#include "Cache.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class LRU : public Cache{
public:
    LRU(const int tamanho, const int mapeamento): Cache::Cache(tamanho, mapeamento), 
    data_last_access(tamanho), inst_last_access(tamanho)
    {
        tempo = 0;
        prox_lru = 0;
        idx = 0;
    }

    ~LRU()
    {

    }

    std::string fetch_data(unsigned int tag, const unsigned int mapeamento, std::fstream *mem)
    {
        tempo++;
        //cout << "TAG: "<<tag<< endl;
        idx = tag;
        if(mapeamento == 0){
            //enquanto o idx nao estiver entre os estremos da cache
            //o ojetivo eh procurar pelo idx equivalente a tag solicitada
            while(!(idx >= 0 && idx <= tamanho-1))
                idx -= tamanho;//subtrai tamanho do idx
            //vertifica a tag em cache
            if(data_tags[idx] == tag){//hit
                cout << "data_hit" << endl;
                data_hit++;
                data_last_access[idx] = tempo;
                return data_buffer[idx];
            } else { //miss **LRU eh indiferente nesse caso**
                cout << "data_miss" << endl;
                std::string buff;
                data_miss++;
                mem->seekg(mem->beg);//rebubina arquivo
                //para na linha da tag
                for(int i = 0; i <= tag; i++)
                    std::getline(*mem, buff);
                
                //cout << "idx: " << idx << endl;
                data_buffer[idx] = buff;//traz da memoria para a cache
                data_tags[idx] = tag;//corrige tag da linha
                data_last_access[idx] = tempo;
                return data_buffer[idx];
            }
        } else {
            //procura pela tag solicitada
            for(int i = 0; i < tamanho; i++){
                if(data_tags[i] == tag){//hit
                    cout << "data_hit" << endl;
                    data_hit++;
                    data_last_access[i] = tempo;
                    return data_buffer[i];
                }
            }
            cout << "data_miss" << endl;
            //miss
            data_miss++;
            std::string buff;
            mem->seekg(mem->beg);
            //para na linha da tag
            for(int i = 0; i < tag; i++)
                std::getline(*mem, buff);

            //cout << "idx: " << idx << endl;
            int menor = 0; //aux
            for(int i = 0; i < tamanho; i++){
                if(data_tags[i] == -1){//espaco vazio
                    prox_lru = i;
                    break;
                }
                if(data_last_access[i] <= menor){
                    menor = data_last_access[i];
                    prox_lru = i;
                }
            }

            data_buffer[prox_lru] = buff;//traz da memoria para cache
            data_tags[prox_lru] = tag;//corrige tag da linha
            data_last_access[prox_lru] = tempo;
            return data_buffer[prox_lru];
        }
    }

    std::string fetch_inst(unsigned int tag, const unsigned int mapeamento, std::istream *mem)
    {
        tempo++;
        //cout << "TAG: "<<tag<< endl;
        idx = tag;
        if(mapeamento == 0){//cout << "tag: " << tag << endl;
            //enquanto o idx nao estiver entre os estremos da cache
            //o ojetivo eh procurar pelo idx equivalente a tag solicitada
            while(!(idx >= 0 && idx <= tamanho-1))
                idx -= tamanho;//subtrai tamanho do idx
            //cout << "idx: " << idx << endl;
            //vertifica a tag em cache
            if(inst_tags[idx] == tag){//hit
                cout << "inst_hit" << endl;
                inst_hit++;
                inst_last_access[idx] = tempo;
                return inst_buffer[idx];
            } else { //miss **LRU eh indiferente nesse caso**
                cout << "inst_miss" << endl;
                std::string buff;
                inst_miss++;
                mem->seekg(mem->beg);//rebubina arquivo
                //para na linha da tag
                for(int i = 0; i <= tag; i++)
                    std::getline(*mem, buff);

                //cout << "idx: " << idx << endl;
                //cout << "LRU fetch " << buff << endl;
                inst_buffer[idx] = buff;//traz da memoria para a cache
                inst_tags[idx] = tag;//corrige tag da linha
                inst_last_access[idx] = tempo;
                //cout << "buff: " << inst_buffer[idx] << endl;
                return inst_buffer[idx];
            }
        } else {
            //procura pela tag solicitada
            for(int i = 0; i < tamanho; i++){
                if(data_tags[i] == tag){//hit
                    cout << "inst_hit" << endl;
                    data_hit++;
                    inst_last_access[i] = tempo;
                    return data_buffer[i];
                }
            }
            cout << "inst_miss" << endl;
            //miss
            data_miss++;
            std::string buff;
            mem->seekg(mem->beg);
            //para na linha da tag
            for(int i = 0; i < tag; i++)
                std::getline(*mem, buff);

            //cout << "idx: " << idx << endl;
            int menor = 0; //aux
            for(int i = 0; i < tamanho; i++){
                if(inst_tags[i] == -1){//espaco vazio
                    prox_lru = i;
                    break;
                }
                if(inst_last_access[i] <= menor){
                    menor = inst_last_access[i];
                    prox_lru = i;
                }
            }

            inst_buffer[prox_lru] = buff;//traz da memoria para cache
            inst_tags[prox_lru] = tag;//corrige tag da linha
            inst_last_access[prox_lru] = tempo;
            return inst_buffer[prox_lru];
        }
    }

    //write LRU
    void write_data(unsigned int tag, std::string linha, const unsigned int mapeamento, std::fstream *mem)
    {
        tempo++;
        //cout << "TAG: "<<tag<< endl;
        idx = tag;
        if(mapeamento == 0){
            //enquanto o idx nao estiver entre os estremos da cache
            //o ojetivo eh procurar pelo idx equivalente a tag solicitada
            while(!(idx >= 0 && idx <= tamanho-1))
                idx -= tamanho;//subtrai tamanho do idx
            //vertifica a tag em cache
            if(data_tags[idx] == tag){//hit
                cout << "data_hit" << endl;
                data_hit++;
                data_buffer[idx] = linha;//escreve na cache
                data_tags[idx] = tag;//altera tag
                data_last_access[idx] = tempo;
                mem->seekg(mem->beg);//rebubina arquivo
                mem->clear();//so pra ter certeza
                //para na linha da tag**WRITE THROUGH**
                for(int i = 0; i <= tag; i++){
                    mem->ignore(256,'\n');
                    if(mem->eof() && mem->fail()){
                        mem->clear();
                        *mem << endl;//tag depois do final
                        mem->flush();
                    }
                }
                *mem << linha << ':';
                mem->flush();
                return;
            } else { //miss
                cout << "data_miss" << endl;
                std::string buff;
                data_miss++;
                std::ofstream out("mem.txt");
                mem->seekp(mem->beg);//rebubina arquivo
                mem->clear();//so pra ter certeza
                //para na linha da tag**WRITE THROUGH**
                for(int i = 0; i <= tag; i++){
                    std::getline(*mem, buff);
                    out << buff;
                    if(mem->eof() && mem->fail()){
                        mem->clear();
                        *mem << endl;//tag depois do final
                        out << endl;
                        mem->flush();
                    }
                }

                out << linha << ':';
                out.close();
                mem->close();
                mem->open("mem.txt");
                //mem << linha << ':';
                //mem.flush();
                data_buffer[idx] = buff;//traz da memoria para a cache
                data_tags[idx] = tag;//corrige tag da linha
                data_last_access[idx] = tempo;
                return;
            }
        } else {
            //procura pela tag solicitada
            for(int i = 0; i < tamanho; i++){
                if(data_tags[i] == tag){//hit
                    cout << "data_hit" << endl;
                    data_hit++;
                    data_buffer[i] = linha;//modifica cache
                    data_tags[i] = tag;//modifica tag da cache
                    data_last_access[i] = tempo;
                    mem->seekg(mem->beg);//rebobina
                    mem->clear();//so pra ter certeza
                    //para na linha da tag**WRITE THROUGH**
                    for(int i = 0; i <= tag; i++){
                        mem->ignore(256,'\n');
                        if(mem->eof() && mem->fail()){//talvez no caso do hit isso nao aconteca
                            mem->clear();
                            *mem << endl;//tag depois do final
                            mem->flush();
                        }
                    }
                    *mem << linha << ':';
                    mem->flush();
                    return;
                }
            }
            cout << "data_miss" << endl;
            //miss
            data_miss++;
            std::string buff;
            mem->seekg(mem->beg);
            mem->clear();//so pra ter certeza
            //para na linha da tag**WRITE THROUGH**
            for(int i = 0; i <= tag; i++){
                std::getline(*mem, buff);
                if(mem->eof() && mem->fail()){
                    mem->clear();
                    *mem << endl;//tag depois do final
                    mem->flush();
                }
            }
            *mem << linha << ':';
            mem->flush();

            int menor = 0;
            for(int i = 0; i < tamanho; i++){
                if(data_tags[i] == -1){//espaco vazio
                    prox_lru = i;
                    break;
                }
                if(data_last_access[i] <= menor){
                    menor = data_last_access[i];
                    prox_lru = i;
                }
            }

            data_buffer[prox_lru] = buff;//traz da memoria para cache
            data_tags[prox_lru] = tag;//corrige tag da linha
            data_last_access[prox_lru] = tempo;
            return;
        }
    }
    //write LRU
    void write_inst(unsigned int tag, std::string linha, const unsigned int mapeamento, std::fstream *mem)
    {
        idx = tag;
        if(mapeamento == 0){
            //enquanto o idx nao estiver entre os estremos da cache
            //o ojetivo eh procurar pelo idx equivalente a tag solicitada
            while(!(idx >= 0 && idx <= tamanho))
                idx -= tamanho;//subtrai tamanho do idx
            //vertifica a tag em cache
            if(inst_tags[idx] == tag){//hit
                inst_hit++;
                inst_buffer[idx] = linha;//escreve na cache
                inst_tags[idx] = tag;//altera tag
                mem->seekg(mem->beg);//rebubina arquivo
                mem->clear();//so pra ter certeza
                //para na linha da tag**WRITE THROUGH**
                for(int i = 0; i < tag; i++){
                    mem->ignore(256,'\n');
                    if(mem->eof() && mem->fail()){
                        mem->clear();
                        *mem << endl;//tag depois do final
                        mem->flush();
                    }
                }
                *mem << linha << ':';
                mem->flush();
                return;
            } else { //miss 
                std::string buff;
                inst_miss++;
                mem->seekg(mem->beg);//rebubina arquivo
                mem->clear();//so pra ter certeza
                //para na linha da tag**WRITE THROUGH**
                for(int i = 0; i < tag; i++){
                    std::getline(*mem, buff);
                    if(mem->eof() && mem->fail()){
                        mem->clear();
                        *mem << endl;//tag depois do final
                        mem->flush();
                    }
                }
                *mem << linha << ':';
                mem->flush();
                inst_buffer[idx] = buff;//traz da memoria para a cache
                inst_tags[idx] = tag;//corrige tag da linha
                return;
            }
        } else {
            //procura pela tag solicitada
            for(int i = 0; i < tamanho; i++){
                if(inst_tags[i] == tag){//hit
                    inst_hit++;
                    inst_buffer[i] = linha;//modifica cache
                    inst_tags[i] = tag;//modifica tag da cache
                    mem->seekg(mem->beg);//rebobina
                    mem->clear();//so pra ter certeza
                    //para na linha da tag**WRITE THROUGH**
                    for(int i = 0; i < tag; i++){
                        mem->ignore(256,'\n');
                        if(mem->eof() && mem->fail()){//talvez no caso do hit isso nao aconteca
                            mem->clear();
                            *mem << endl;//tag depois do final
                            mem->flush();
                        }
                    }
                    *mem << linha << ':';
                    mem->flush();
                    return;
                } 
            }
            //miss
            inst_miss++;
            std::string buff;
            mem->seekg(mem->beg);
            mem->clear();//so pra ter certeza
            //para na linha da tag**WRITE THROUGH**
            for(int i = 0; i < tag; i++){
                std::getline(*mem, buff);
                if(mem->eof() && mem->fail()){
                    mem->clear();
                    *mem << endl;//tag depois do final
                    mem->flush();
                }
            }
            *mem << linha << ':';
            mem->flush();

            inst_buffer[prox_lru] = buff;//traz da memoria para cache
            inst_tags[prox_lru] = tag;//corrige tag da linha
            prox_lru = (prox_lru+1)%tamanho;//circular
            return;
        }
    }

private:
    int tempo;//vai simular um relogio interno
    unsigned int prox_lru; //prox a ser trocado
    unsigned int idx;//aux
    std::vector <int> data_last_access;//ultimo acesso a linha de data_buffer
    std::vector <int> inst_last_access;//ultimo acesso a linha de inst_buffer
};

#endif