#ifndef LRU_H_INCLUDED
#define LRU_H_INCLUDED

#include "Cache.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;
class RANDOM : public Cache{
public:
    RANDOM(const int tamanho, const int mapeamento): Cache::Cache(tamanho, mapeamento)
    {
        prox_random = 0;
        idx = 0;
        srand(time(NULL));
    }

    ~RANDOM()
    {

    }

    std::string fetch_data(unsigned int tag, const unsigned int mapeamento, std::fstream *mem)
    {
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
                return data_buffer[idx];
            } else { //miss **RANDOM eh indiferente nesse caso**
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
                return data_buffer[idx];
            }
        } else {
            //procura pela tag solicitada
            for(int i = 0; i < tamanho; i++){
                if(data_tags[i] == tag){//hit
                    cout << "data_hit" << endl;
                    data_hit++;
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
            //gera numero de 0 a tamanho-1
            prox_random = rand() % (tamanho-1);

            data_buffer[prox_random] = buff;//traz da memoria para cache
            data_tags[prox_random] = tag;//corrige tag da linha
            return data_buffer[prox_random];
        }
    }

    std::string fetch_inst(unsigned int tag, const unsigned int mapeamento, std::istream *mem)
    {
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
                return inst_buffer[idx];
            } else { //miss **RANDOM eh indiferente nesse caso**
                cout << "inst_miss" << endl;
                std::string buff;
                inst_miss++;
                mem->seekg(mem->beg);//rebubina arquivo
                //para na linha da tag
                for(int i = 0; i <= tag; i++)
                    std::getline(*mem, buff);

                //cout << "idx: " << idx << endl;
                //cout << "RANDOM fetch " << buff << endl;
                inst_buffer[idx] = buff;//traz da memoria para a cache
                inst_tags[idx] = tag;//corrige tag da linha
                //cout << "buff: " << inst_buffer[idx] << endl;
                return inst_buffer[idx];
            }
        } else {
            //procura pela tag solicitada
            for(int i = 0; i < tamanho; i++){
                if(data_tags[i] == tag){//hit
                    cout << "inst_hit" << endl;
                    inst_hit++;
                    return inst_buffer[i];
                }
            }
            cout << "inst_miss" << endl;
            //miss
            inst_miss++;
            std::string buff;
            mem->seekg(mem->beg);
            //para na linha da tag
            for(int i = 0; i < tag; i++)
                std::getline(*mem, buff);

            //gera numero de 0 a tamanho-1
            prox_random = rand() % (tamanho-1);

            for(int i = 0; i < tamanho; i++){
                if(inst_tags[i] == -1){
                    prox_random = i;//vazio
                    break;
                }
            }

            inst_buffer[prox_random] = buff;//traz da memoria para cache
            inst_tags[prox_random] = tag;//corrige tag da linha
            return inst_buffer[prox_random];
        }
    }

    //write RANDOM
    void write_data(unsigned int tag, std::string linha, const unsigned int mapeamento, std::fstream *mem)
    {
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
                mem->seekg(mem->beg);//rebubina arquivo
                mem->clear();//so pra ter certeza
                //para na linha da tag**WRITE THROUGH**
                for(int i = 0; i <= tag; i++){
                    mem->ignore(256,'\n');
                    if(mem->eof()){
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
                mem->seekg(mem->beg);//rebubina arquivo
                mem->clear();//so pra ter certeza
                //para na linha da tag**WRITE THROUGH**
                for(int i = 0; i <= tag; i++){
                    std::getline(*mem, buff);
                    if(mem->eof()){
                        mem->clear();
                        *mem << endl;//tag depois do final
                        mem->flush();
                    }
                }
                *mem << linha << ':';
                mem->flush();
                data_buffer[idx] = buff;//traz da memoria para a cache
                data_tags[idx] = tag;//corrige tag da linha
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
                    mem->seekg(mem->beg);//rebobina
                    mem->clear();//so pra ter certeza
                    //para na linha da tag**WRITE THROUGH**
                    for(int i = 0; i <= tag; i++){
                        mem->ignore(256,'\n');
                        if(mem->eof()){//talvez no caso do hit isso nao aconteca
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
                if(mem->eof()){
                    mem->clear();
                    *mem << endl;//tag depois do final
                    mem->flush();
                }
            }
            *mem << linha << ':';
            mem->flush();

            //gera numero de 0 a tamanho-1
            prox_random = rand() % (tamanho-1);

            for(int i = 0; i < tamanho; i++){
                if(data_tags[i] == -1){
                    prox_random = i;//vazio
                    break;
                }
            }

            data_buffer[prox_random] = buff;//traz da memoria para cache
            data_tags[prox_random] = tag;//corrige tag da linha
            return;
        }
    }

/*!!!!!!!! memoria de inst eh read-only
    //write RANDOM
    void write_inst(unsigned int tag, std::string linha, const unsigned int mapeamento, std::fstream &mem)
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
                    if(mem->eof()){
                        mem->clear();
                        mem << endl;//tag depois do final
                        mem->flush();
                    }
                }
                mem << linha << ':';
                mem->flush();
                return;
            } else { //miss 
                std::string buff;
                inst_miss++;
                mem->seekg(mem->beg);//rebubina arquivo
                mem->clear();//so pra ter certeza
                //para na linha da tag**WRITE THROUGH**
                for(int i = 0; i < tag; i++){
                    std::getline(mem, buff);
                    if(mem->eof()){
                        mem->clear();
                        mem << endl;//tag depois do final
                        mem->flush();
                    }
                }
                mem << linha << ':';
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
                        if(mem->eof()){//talvez no caso do hit isso nao aconteca
                            mem->clear();
                            mem << endl;//tag depois do final
                            mem->flush();
                        }
                    }
                    mem << linha << ':';
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
                std::getline(mem, buff);
                if(mem->eof()){
                    mem->clear();
                    mem << endl;//tag depois do final
                    mem->flush();
                }
            }
            mem << linha << ':';
            mem->flush();

            inst_buffer[prox_random] = buff;//traz da memoria para cache
            inst_tags[prox_random] = tag;//corrige tag da linha
            prox_random = (prox_random+1)%tamanho;//circular
            return;
        }
    }
!!!!!!!!!*/

private:
    unsigned int prox_random; //prox a ser trocado
    unsigned int idx;//aux
};

#endif