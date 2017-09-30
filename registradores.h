#ifndef REGISTRADORES_H_INCLUDED
#define REGISTRADORES_H_INCLUDED

#include <iostream>

extern void fechar();

union reg_geral_t{
    uint32_t ex;
    uint16_t x;
    struct {
        uint8_t l;
        uint8_t h;
    };
};

union reg_seg_t{
    uint16_t x;
    struct {
        uint8_t l;
        uint8_t h;
    };
};

union reg_apont_t{
    uint16_t x;
    struct {
        uint8_t l;
        uint8_t h;
    };
};

enum regs{
    EAX, EBX, ECX, EDX, CS, DS, SS, SI, DI, BP, SP, IP
};

enum Flags_enum{
    NF = 0x00, //00000000
    CF = 0x01,//00000001
    PF = 0x02,//00000010
    AF = 0x04,//00000100
    ZF = 0x08,//00001000
    SF = 0x10,//00010000
    TF = 0x20,//00100000
    DF = 0x40,//01000000
    OF = 0x80//10000000
};

/*inline constexpr reg_geral_t
operator~(reg_geral_t x)
{
  return static_cast<reg_geral_t>(~x);
}
/*
inline constexpr reg_geral_t
operator&(reg_geral_t x, reg_geral_t y)
{
  return static_cast<reg_geral_t>
    (x & y);
}
inline constexpr reg_geral_t
operator&(reg_geral_t x, int y)
{
  return static_cast<reg_geral_t>
    (x & y);
}
inline constexpr reg_geral_t
operator|(reg_geral_t x, reg_geral_t y)
{
  return static_cast<reg_geral_t>
    (x | y);
}
inline constexpr reg_geral_t
operator^(reg_geral_t x, reg_geral_t y)
{
  return static_cast<reg_geral_t>
    (x ^ y);
}
inline constexpr reg_apont_t
operator+(reg_apont_t x, int y)
{
    return static_cast<reg_apont_t>
    (x.x + y);
}*/

using namespace std;
//registradores gerais
static reg_geral_t eax, ebx, ecx, edx;
//registradores de segmento
static reg_seg_t cs, ds, ss;
//registradores apontadores
static reg_apont_t si, di, bp, sp, ip;

//verifica qual dos regs gerais s se refere
reg_geral_t* is_reg(const char *s, int &offset, int &id){
    if(s[0] == 'e'){ // 32 bit
        if(s[1] == 'a'){ // eax
            offset = 32;
            id = EAX;
            return &eax;
        }else if(s[1] == 'b'){ // ebx
            offset = 32;
            id = EBX;
            return &ebx;
        }else if(s[1] == 'c'){ // ecx
            offset = 32;
            id = ECX;
            return &ecx;
        }else if(s[1] == 'd'){ // edx
            offset = 32;
            id = EDX;
            return &edx;
        }else{
            cout << "Registrador desconhecido" << endl;
            cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
            cout << "Abortando programa..." << endl;
            fechar();
            exit(EXIT_FAILURE);
        }
    }else if(s[1] == 'x'){ //16bit
        if(s[0] == 'a'){ //ax
            offset = 16;
            id = EAX;
            return &eax;
        }else if(s[0] == 'b'){//bx
            offset = 16;
            id = EBX;
            return &ebx;
        }else if(s[0] == 'c'){//cx
            offset = 16;
            id = ECX;
            return &ecx;
        }else if(s[0] == 'd'){//dx
            offset = 16;
            id = EDX;
            return &edx;
        }else{
            cout << "Registrador desconhecido" << endl;
            cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
            cout << "Abortando programa..." << endl;
            fechar();
            exit(EXIT_FAILURE);
        }
    }else if(s[1] == 'h'){ //8bit high
        if(s[0] == 'a'){//ah
            offset = 8;
            id = EAX;
            return &eax;
        }else if(s[0] == 'b'){//bh
            offset = 8;
            id = EBX;
            return &ebx;
        }else if(s[0] == 'c'){//ch
            offset = 8;
            id = ECX;
            return &ecx;
        }else if(s[0] == 'd'){//dh
            offset = 8;
            id = EDX;
            return &edx;
        }else{
            cout << "Registrador desconhecido" << endl;
            cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
            cout << "Abortando programa..." << endl;
            fechar();
            exit(EXIT_FAILURE);
        }
    }else if(s[1] == 'l'){ //8bit low
        if(s[0] == 'a'){//al
            offset = -8;
            id = EAX;
            return &eax;
        }else if(s[0] == 'b'){//bl
            offset = -8;
            id = EBX;
            return &ebx;
        }else if(s[0] == 'c'){//cl
            offset = -8;
            id = ECX;
            return &ecx;
        }else if(s[0] == 'd'){//dl
            offset = -8;
            id = EDX;
            return &edx;
        }else{
            cout << "Registrador desconhecido" << endl;
            cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
            cout << "Abortando programa..." << endl;
            fechar();
            exit(EXIT_FAILURE);
        }
    }else{
        cout << "Registrador desconhecido" << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}

#endif