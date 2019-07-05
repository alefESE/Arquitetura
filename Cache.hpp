#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED

#include <vector>
#include <string>

class Cache{
public:
    Cache(const int tamanho, const int mapeamento) : tamanho(tamanho),
    data_buffer(tamanho), inst_buffer(tamanho), data_tags(tamanho, -1), inst_tags(tamanho, -1)
    {
        data_miss = 0, inst_miss = 0;
        data_hit = 0, inst_hit = 0;
    }
    virtual ~Cache(){}

    unsigned int get_data_miss(){
        return data_miss;
    }

    unsigned int get_data_hit(){
        return data_hit;
    }

    unsigned int get_inst_miss(){
        return inst_miss;
    }

    unsigned int get_inst_hit(){
        return inst_hit;
    }
    
protected:
    int tamanho;
    unsigned int data_miss, inst_miss;
    unsigned int data_hit, inst_hit;

    std::vector <std::string> data_buffer;//linhas da cache de dados
    std::vector <std::string> inst_buffer;//linhas da cache de instrucoes
    std::vector <int> data_tags;//tags das linhas de data_buffer
    std::vector <int> inst_tags;//tags das linhas de inst_buffer
};

#endif