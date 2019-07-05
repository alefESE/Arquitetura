#ifndef ULA_H_INCLUDED
#define ULA_H_INCLUDED

#define palavra 255
#include "FIFO.hpp"
#include "PilhaEncadeada.h"
#include "ListaDinamica.h"
#include <algorithm>

extern void fechar();
extern unsigned char flags;
extern unsigned int mapeamento_c;

//labels
static tLista mems;
static tLista labels;
//streams
static fstream mem;
static ifstream prog;
//pilha
static tPilhaEncadeada pilha;
static FIFO *fifo;

uint32_t add_full(reg_geral_t a, reg_geral_t b, int offset1, int offset2)
{
    if(offset1 == 32){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.ex + b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.ex + b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.ex + b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.ex + b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == 16){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.x + b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.x + b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.x + b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.x + b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == 8){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.h + b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.h + b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.h + b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.h + b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } if(offset1 == -8){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.l + b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.l + b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.l + b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.l + b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    }
}

uint32_t sub_full(reg_geral_t a, reg_geral_t b, int offset1, int offset2)
{
    if(offset1 == 32){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.ex - b.ex;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.ex - b.x;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.ex - b.h;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.ex - b.l;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == 16){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.x - b.ex;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.x - b.x;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.x - b.h;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.x - b.l;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == 8){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.h - b.ex;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.h - b.x;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.h - b.h;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.h - b.l;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == -8){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.l - b.ex;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.l - b.x;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.l - b.h;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.l - b.l;
            result < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return result;
        }
    }
}

uint32_t mul_full(reg_geral_t a, reg_geral_t b, int offset1, int offset2)
{
    if(offset1 == 32){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.ex * b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.ex * b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.ex * b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.ex * b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == 16){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.x * b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.x * b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.x * b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.x * b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == 8){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.h * b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.h * b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.h * b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.h * b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == -8){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.l * b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.l * b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.l * b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.l * b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    }
}

uint32_t div_full(reg_geral_t a, reg_geral_t b, int offset1, int offset2)
{
    if(offset1 == 32){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.ex / b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.ex / b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);;
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.ex / b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.ex / b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == 16){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.x / b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.x / b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.x / b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.x / b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == 8){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.h / b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.h / b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.h / b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.h / b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    } else if(offset1 == -8){
        if(offset2 == 32){
            uint32_t result = 0;
            result = a.l / b.ex;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 16){
            uint32_t result = 0;
            result = a.l / b.x;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset2 == 8){
            uint32_t result = 0;
            result = a.l / b.h;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        } else if(offset1 == -8){
            uint32_t result = 0;
            result = a.l / b.l;
            result < 0 ? Flags_enum(flags | CF | OF) : Flags_enum(flags & ~CF | ~OF);
            result == 0 ? Flags_enum(flags | ZF) : Flags_enum(flags & ~ZF);
            return result;
        }
    }
}

// a = a + b
void sum(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    //find_if(op2, op2+strlen(op2), )
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    //cout << "op2: " << op2 << endl;
    //bool neg = false;
    //if(op2[0] == '-'){neg = true; op2++;}
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        //cout << "temp: " << temp.ex << endl;
        int offset = 0, c;
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
            //cout << "op1_reg: " << (*ptr).ex << endl;
            //cout << "op2_const: " << temp.ex << endl;
            (*ptr).ex = add_full(*ptr, temp, offset, 32);
            //cout << "op1_added: " << (*ptr).ex << endl;
            return;
        } else if(offset == 16){
            //cout << "op1_reg: " << (*ptr).x << endl;
            //cout << "op2_const: " << temp.x << endl;
            (*ptr).x = add_full(*ptr, temp, offset, 32);
            //cout << "op1_added: " << (*ptr).x << endl;
            return;
        } else if(offset == 8){
            //cout << "op1_reg: " << (*ptr).h << endl;
            //cout << "op2_const: " << temp.h << endl;
            (*ptr).x = add_full(*ptr, temp, offset, 32);
            //cout << "op1_added: " << (*ptr).h << endl;
            return;
        } else if(offset == -8){
            //cout << "op1_reg: " << (*ptr).l << endl;
            //cout << "op2_const: " << temp.l << endl;
            (*ptr).x = add_full(*ptr, temp, offset, 32);
            //cout << "op1_added: " << (*ptr).l << endl;
            return;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int offset1 = 0, offset2 = 0, c;
        reg_geral_t *ptr2 = is_reg(op2, offset2, c);
        ptr = is_reg(op1, offset1, c);
        if(offset1 == 32){
            //cout << "op1_reg: " << (*ptr).ex << endl;
            //cout << "op2_reg: " << ptr2->ex << endl;
            (*ptr).ex = add_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_added: " << (*ptr).ex << endl;
            return;
        } else if(offset1 == 16){
            //cout << "op1_reg: " << (*ptr).x << endl;
            //cout << "op2_reg: " << ptr2->x << endl;
            (*ptr).x = add_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_added: " << (*ptr).x << endl;
            return;
        } else if(offset1 == 8){
            //cout << "op1_reg: " << (*ptr).h << endl;
            //cout << "op2_reg: " << ptr2->h << endl;
            (*ptr).h = add_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_added: " << (*ptr).h << endl;
            return;
        } else if(offset1 == -8){
            //cout << "op1_reg: " << (*ptr).l << endl;
            //cout << "op2_reg: " << ptr2->l << endl;
            (*ptr).l = add_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_added: " << (*ptr).l << endl;
            return;
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// a = a - b
void sub(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    if((op2 = strtok(NULL, " ")) == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    //cout << "op2: " << op2 << endl;
    //bool neg = false;
    //if(op2[0] == '-'){neg = true; op2++;}
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        //cout << "temp: " << temp.ex << endl;
        int offset = 0, c;
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
            //cout << "op1_reg: " << (*ptr).ex << endl;
            //cout << "op2_const: " << temp.ex << endl;
            (*ptr).ex = sub_full(*ptr, temp, offset, 32);
            //cout << "op1_sub: " << (*ptr).ex << endl;
            return;
        } else if(offset == 16){
            //cout << "op1_reg: " << (*ptr).x << endl;
            //cout << "op2_const: " << temp.x << endl;
            (*ptr).x = sub_full(*ptr, temp, offset, 32);
            //cout << "op1_sub: " << (*ptr).x << endl;
            return;
        } else if(offset == 8){
            //cout << "op1_reg: " << (*ptr).h << endl;
            //cout << "op2_const: " << temp.h << endl;
            (*ptr).x = sub_full(*ptr, temp, offset, 32);
            //cout << "op1_sub: " << (*ptr).h << endl;
            return;
        } else if(offset == -8){
            //cout << "op1_reg: " << (*ptr).l << endl;
            //cout << "op2_const: " << temp.l << endl;
            (*ptr).x = sub_full(*ptr, temp, offset, 32);
            //cout << "op1_sub: " << (*ptr).l << endl;
            return;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int c, offset1 = 0, offset2 = 0;
        reg_geral_t *ptr2 = is_reg(op2, offset2, c);
        ptr = is_reg(op1, offset1, c);
        if(offset1 == 32){
            //cout << "op1_reg: " << (*ptr).ex << endl;
            //cout << "op2_reg: " << ptr2->ex << endl;
            (*ptr).ex = sub_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_sub: " << (*ptr).ex << endl;
            return;
        } else if(offset1 == 16){
            //cout << "op1_reg: " << (*ptr).x << endl;
            //cout << "op2_reg: " << ptr2->x << endl;
            (*ptr).x = sub_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_sub: " << (*ptr).x << endl;
            return;
        } else if(offset1 == 8){
            //cout << "op1_reg: " << (*ptr).h << endl;
            //cout << "op2_reg: " << ptr2->h << endl;
            (*ptr).h = sub_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_sub: " << (*ptr).h << endl;
            return;
        } else if(offset1 == -8){
            //cout << "op1_reg: " << (*ptr).l << endl;
            //cout << "op2_reg: " << ptr2->l << endl;
            (*ptr).l = sub_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_sub: " << (*ptr).l << endl;
            return;
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// a = a * b (para ficar se overflow seria necessario usar um registrador auxiliar, mas acho que nao precisa)
void mul(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    if((op2 = strtok(NULL, " ")) == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    //cout << "op2: " << op2 << endl;
    //bool neg = false;
    //if(op2[0] == '-'){neg = true; op2++;}
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        cout << "temp: " << temp.ex << endl;
        int offset = 0, c;
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
            //cout << "op1_reg: " << (*ptr).ex << endl;
            //cout << "op2_const: " << temp.ex << endl;
            (*ptr).ex = mul_full(*ptr, temp, offset, 32);
            //cout << "op1_mul: " << (*ptr).ex << endl;
            return;
        } else if(offset == 16){
            //cout << "op1_reg: " << (*ptr).x << endl;
            //cout << "op2_const: " << temp.x << endl;
            (*ptr).x = mul_full(*ptr, temp, offset, 32);
            //cout << "op1_mul: " << (*ptr).x << endl;
            return;
        } else if(offset == 8){
            //cout << "op1_reg: " << (*ptr).h << endl;
            //cout << "op2_const: " << temp.h << endl;
            (*ptr).x = mul_full(*ptr, temp, offset, 32);
            //cout << "op1_mul: " << (*ptr).h << endl;
            return;
        } else if(offset == -8){
            //cout << "op1_reg: " << (*ptr).l << endl;
            //cout << "op2_const: " << temp.l << endl;
            (*ptr).x = mul_full(*ptr, temp, offset, 32);
            //cout << "op1_mul: " << (*ptr).l << endl;
            return;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int c, offset1 = 0, offset2 = 0;
        reg_geral_t *ptr2 = is_reg(op2, offset2,c);
        ptr = is_reg(op1, offset1,c);
        if(offset1 == 32){
            //cout << "op1_reg: " << (*ptr).ex << endl;
            //cout << "op2_reg: " << ptr2->ex << endl;
            (*ptr).ex = mul_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_mul: " << (*ptr).ex << endl;
            return;
        } else if(offset1 == 16){
            //cout << "op1_reg: " << (*ptr).x << endl;
            //cout << "op2_reg: " << ptr2->x << endl;
            (*ptr).x = mul_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_mul: " << (*ptr).x << endl;
            return;
        } else if(offset1 == 8){
            //cout << "op1_reg: " << (*ptr).h << endl;
            //cout << "op2_reg: " << (*ptr).h << endl;
            (*ptr).h = mul_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_mul: " << (*ptr).h << endl;
            return;
        } else if(offset1 == -8){
            //cout << "op1_reg: " << (*ptr).l << endl;
            //cout << "op2_reg: " << (*ptr).l << endl;
            (*ptr).l = mul_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_mul: " << (*ptr).l << endl;
            return;
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// a = a / b (o assembly original guarda o quociente e o resto, melhor nao implementar isso)
void div(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    //cout << "op2: " << op2 << endl;
    //bool neg = false;
    //if(op2[0] == '-'){neg = true; op2++;}
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        cout << "temp: " << temp.ex << endl;
        int offset = 0, c;
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
            //cout << "op1_reg: " << (*ptr).ex << endl;
            //cout << "op2_const: " << temp.ex << endl;
            (*ptr).ex = div_full(*ptr, temp, offset, 32);
            //cout << "op1_div: " << (*ptr).ex << endl;
            return;
        } else if(offset == 16){
            //cout << "op1_reg: " << (*ptr).x << endl;
            //cout << "op2_const: " << temp.x << endl;
            (*ptr).x = div_full(*ptr, temp, offset, 32);
            //cout << "op1_div: " << (*ptr).x << endl;
            return;
        } else if(offset == 8){
            //cout << "op1_reg: " << (*ptr).h << endl;
            //cout << "op2_const: " << temp.h << endl;
            (*ptr).x = div_full(*ptr, temp, offset, 32);
            //cout << "op1_div: " << (*ptr).h << endl;
            return;
        } else if(offset == -8){
            //cout << "op1_reg: " << (*ptr).l << endl;
            //cout << "op2_const: " << temp.l << endl;
            (*ptr).x = div_full(*ptr, temp, offset, 32);
            //cout << "op1_div: " << (*ptr).l << endl;
            return;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int c, offset1 = 0, offset2 = 0;
        reg_geral_t *ptr2 = is_reg(op2, offset2, c);
        ptr = is_reg(op1, offset1, c);
        if(offset1 == 32){
            //cout << "op1_reg: " << (*ptr).ex << endl;
            //cout << "op2_reg: " << ptr2->ex << endl;
            (*ptr).ex = div_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_div: " << (*ptr).ex << endl;
            return;
        } else if(offset1 == 16){
            //cout << "op1_reg: " << (*ptr).x << endl;
            //cout << "op2_reg: " << ptr2->x << endl;
            (*ptr).x = div_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_div: " << (*ptr).x << endl;
            return;
        } else if(offset1 == 8){
            //cout << "op1_reg: " << (*ptr).h << endl;
            //cout << "op2_reg: " << ptr2->h << endl;
            (*ptr).h = div_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_div: " << (*ptr).h << endl;
            return;
        } else if(offset1 == -8){
            //cout << "op1_reg: " << (*ptr).l << endl;
            //cout << "op2_reg: " << ptr2->l << endl;
            (*ptr).l = div_full(*ptr, *ptr2, offset1, offset2);
            //cout << "op1_duv: " << (*ptr).l << endl;
            return;
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// a = a - 1
void dec(char *op){
    op = strtok(NULL, " ");
    if(op == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op, op+strlen(op), ' ') = 0;
    *remove(op, op+strlen(op), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    int offset = 0, c;
    ptr = is_reg(op, offset, c);
    if(offset == 32){
        (*ptr).ex = (*ptr).ex - 1;
        //cout << "op_dec: " << (*ptr).ex;
        return;
    } else if(offset == 16){
        (*ptr).x = (*ptr).x - 1;
        //cout << "op_dec: " << (*ptr).x;
        return;
    } else if(offset == 8){
        (*ptr).h = (*ptr).h - 1;
        //cout << "op_dec: " << (*ptr).h;
        return;
    } else if(offset == -8){
        (*ptr).l = (*ptr).l - 1;
        //cout << "op_dec: " << (*ptr).l;
        return;
    }
}
// a = a + 1
void inc(char *op){
    op = strtok(NULL, " ");
    if(op == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op, op+strlen(op), ' ') = 0;
    *remove(op, op+strlen(op), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    int offset = 0, c;
    ptr = is_reg(op, offset, c);
    if(offset == 32){
        (*ptr).ex = (*ptr).ex - 1;
        //cout << "op_inc: " << (*ptr).ex;
        return;
    } else if(offset == 16){
        (*ptr).x = (*ptr).x - 1;
        //cout << "op_inc: " << (*ptr).x;
        return;
    } else if(offset == 8){
        (*ptr).h = (*ptr).h - 1;
        //cout << "op_inc: " << (*ptr).h;
        return;
    } else if(offset == -8){
        (*ptr).l = (*ptr).l - 1;
        //cout << "op_inc: " << (*ptr).l;
        return;
    }
}
// a = a & b
void and_op(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        //cout << "temp: " << temp.ex << endl;
        int c, offset = 0;
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
           (*ptr).ex = (*ptr).ex & temp.x;
           //cout << "op1_and: " << (*ptr).ex << endl;
        } else if(offset == 16){
            (*ptr).x = (*ptr).x & temp.x;
            //cout << "op1_and: " << (*ptr).x << endl;
        } else if(offset == 8){
            (*ptr).h = (*ptr).h & temp.h;
            //cout << "op1_and: " << (*ptr).h << endl;
        } else if(offset == -8){
            (*ptr).l = (*ptr).l & temp.l;
            //cout << "op1_and: " << (*ptr).l << endl;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int c, offset = 0;
        reg_geral_t *ptr2 = is_reg(op2, offset,c);
        ptr = is_reg(op1, offset,c );
        if(offset == 32){
            (*ptr).ex = (*ptr).ex & ptr2->ex;
        } else if(offset == 16){
            (*ptr).x = (*ptr).x & ptr2->x;
        } else if(offset == 8){
            (*ptr).h = (*ptr).x & ptr2->h;
        } else if(offset == -8){
            (*ptr).l = (*ptr).x & ptr2->l;
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// a = a ^ -1
void not_op(char *op){
    op = strtok(NULL, " ");
    if(op == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op, op+strlen(op), ' ') = 0;
    *remove(op, op+strlen(op), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    int offset = 0, c;
    ptr = is_reg(op, offset, c);
    if(offset == 32){
        (*ptr).ex = (*ptr).ex ^ 0xFFFFFFFF;
        //cout << "op1_not: " << (*ptr).ex << endl;
        return;
    } else if(offset == 16){
        (*ptr).x = (*ptr).x ^ 0xFFFF;
        //cout << "op1_not: " << (*ptr).x << endl;
        return;
    } else if(offset == 8){
        (*ptr).h = (*ptr).h ^ 0xFF;
        //cout << "op1_not: " << (*ptr).h << endl;
        return;
    } else if(offset == -8){
        (*ptr).l = (*ptr).l ^ 0xFF;
        //cout << "op1_and: " << (*ptr).l << endl;
        return;
    }
}
// a = a | b
void or_op(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        //cout << "temp: " << temp.ex << endl;
        int c, offset = 0;
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
           (*ptr).ex = (*ptr).ex | temp.x;
           //cout << "op1_or: " << (*ptr).ex << endl;
           return;
        } else if(offset == 16){
            (*ptr).x = (*ptr).x | temp.x;
            //cout << "op1_or: " << (*ptr).x << endl;
            return;
        } else if(offset == 8){
            (*ptr).h = (*ptr).h | temp.h;
            //cout << "op1_or: " << (*ptr).h << endl;
            return;
        } else if(offset == -8){
            //cout << "op1_or: " << (*ptr).h << endl;
            (*ptr).l = (*ptr).l | temp.l;
            return;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int c, offset = 0;
        reg_geral_t *ptr2 = is_reg(op2, offset, c);
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
            (*ptr).ex = (*ptr).ex | ptr2->ex;
        } else if(offset == 16){
            (*ptr).x = (*ptr).x | ptr2->x;
        } else if(offset == 8){
            (*ptr).h = (*ptr).x | ptr2->h;
        } else if(offset == -8){
            (*ptr).l = (*ptr).x | ptr2->l;
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// a = a ^ b
void xor_op(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        //cout << "temp: " << temp.ex << endl;
        int c, offset = 0;
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
           (*ptr).ex = (*ptr).ex ^ temp.x;
           //cout << "op1_xor: " << (*ptr).ex << endl;
           return;
        } else if(offset == 16){
            (*ptr).x = (*ptr).x ^ temp.x;
            //cout << "op1_xor: " << (*ptr).x << endl;
            return;
        } else if(offset == 8){
            (*ptr).h = (*ptr).h ^ temp.h;
            //cout << "op1_xor: " << (*ptr).h << endl;
            return;
        } else if(offset == -8){
            (*ptr).l = (*ptr).l ^ temp.l;
            //cout << "op1_xor: " << (*ptr).l << endl;
            return;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int c, offset = 0;
        reg_geral_t *ptr2 = is_reg(op2, offset, c);
        ptr = is_reg(op1, offset, c);
        if(offset == 32){
            (*ptr).ex = (*ptr).ex ^ ptr2->ex;
            //cout << "op1_xor: " << (*ptr).ex << endl;
            return;
        } else if(offset == 16){
            (*ptr).x = (*ptr).x ^ ptr2->x;
            //cout << "op1_xor: " << (*ptr).ex << endl;
            return;
        } else if(offset == 8){
            (*ptr).h = (*ptr).x ^ ptr2->h;
            //cout << "op1_xor: " << (*ptr).ex << endl;
            return;
        } else if(offset == -8){
            (*ptr).l = (*ptr).x ^ ptr2->l;
            //cout << "op1_xor: " << (*ptr).ex << endl;
            return;
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// a = a * -1
void neg(char *op){
    op = strtok(NULL, " ");
    if(op == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op, op+strlen(op), ' ') = 0;
    *remove(op, op+strlen(op), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    int offset = 0, i;
    ptr = is_reg(op, offset, i);
    if(offset == 32){
        (*ptr).ex = (*ptr).ex * 0xFFFFFFFF;
        //cout << "op1_neg: " << (*ptr).ex << endl;
        return;
    } else if(offset == 16){
        (*ptr).x = (*ptr).x * 0xFFFF;
        //cout << "op1_neg: " << (*ptr).x << endl;
        return;
    } else if(offset == 8){
        (*ptr).h = (*ptr).h * 0xFF;
        //cout << "op1_neg: " << (*ptr).h << endl;
        return;
    } else if(offset == -8){
        (*ptr).l = (*ptr).l * 0xFF;
        //cout << "op1_neg: " << (*ptr).l << endl;
        return;
    }
}
// compara a e b
void cmp(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    //cout << "op2: " << op2 << endl;
    //bool neg = false;
    //if(op2[0] == '-'){neg = true; op2++;}
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        //cout << "temp: " << temp.ex << endl;
        int offset = 0, i;
        ptr = is_reg(op1, offset, i);
        reg_geral_t result;
        if(offset == 32){
            result.ex = (*ptr).ex - temp.ex;
            result.ex < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result.ex == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
            return;
        } else if(offset == 16){
            result.x = (*ptr).x - temp.x;
            result.x < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result.x == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
           return;
        } else if(offset == 8){
            result.h = (*ptr).h - temp.h;
            result.h < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result.h == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
           return;
        } else if(offset == -8){
            result.l = (*ptr).l - temp.l;
            result.l < 0 ? flags = Flags_enum(flags | CF | OF) : flags = Flags_enum(flags & ~CF | ~OF);
            result.l == 0 ? flags = Flags_enum(flags | ZF) : flags = Flags_enum(flags & ~ZF);
           return;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int offset1 = 0, offset2 = 0, i;
        reg_geral_t temp;
        reg_geral_t *ptr2 = is_reg(op2, offset2, i);
        ptr = is_reg(op1, offset1, i);
        if(offset1 == 32){
            temp.ex = sub_full(*ptr, *ptr2, offset1, offset2);
        } else if(offset1 == 16){
            temp.ex = sub_full(*ptr, *ptr2, offset1, offset2);
        } else if(offset1 == 8){
            temp.ex = sub_full(*ptr, *ptr2, offset1, offset2);
        } else if(offset1 == -8){
            temp.ex = sub_full(*ptr, *ptr2, offset1, offset2);
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// push ip++
void call(char *op){
    op = strtok(NULL, " ");
    if(op == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op, op+strlen(op), ' ') = 0;
    *remove(op, op+strlen(op), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    ip.x = ip.x + 1;
    push(pilha, ip.x, IP);
    int i, label_int = 0, pos, count;
    for(i = 0; i < strlen(op); i++) label_int += op[i];
    cout << "label_int: " << label_int << endl;
    if(posicao(labels, label_int, &pos, &count)){
        ip.x = count;
        prog.seekg (0, prog.beg); //"rebobina" stream
        for(i = 0; i < ip.x; i++) prog.getline(NULL, palavra, '\n');
    }else{
        cout << "Jump para label inexistente"<< endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// pop ip
int ret(){
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    int i, id;
    if(!(top(pilha, &i, &id))) return 0;
    if(id == IP){
        ip.x = i;
        pop(pilha, &i, &id);
        prog.seekg (0, prog.beg); //"rebobina" stream
        for(i = 0; i < ip.x; i++) prog.getline(NULL, palavra, '\n');
    }
    return 1;
}
// push reg
void push_reg(char *reg){
    reg = strtok(NULL, " ");
    if(reg == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(reg, reg+strlen(reg), ' ') = 0;
    *remove(reg, reg+strlen(reg), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    int offset = 0, id;
    ptr = is_reg(reg, offset, id);
    if(offset == 32){
        if(id == EAX){
            push(pilha, eax.ex, EAX);
            return;
        } else if(id == EBX){
            push(pilha, ebx.ex, EBX);
            return;
        } else if(id == ECX){
            push(pilha, ecx.ex, ECX);
            return;
        } else if(id == EDX){
            push(pilha, edx.ex, EDX);
            return;
        }
    } else if(offset == 16){
        if(id == EAX){
            push(pilha, eax.x, EAX);
            return;
        } else if(id == EBX){
            push(pilha, ebx.x, EBX);
            return;
        } else if(id == ECX){
            push(pilha, ecx.x, ECX);
            return;
        } else if(id == EDX){
            push(pilha, edx.x, EDX);
            return;
        }
    } else if(offset == 8){
        if(id == EAX){
            push(pilha, eax.h, EAX);
            return;
        } else if(id == EBX){
            push(pilha, ebx.h, EBX);
            return;
        } else if(id == ECX){
            push(pilha, ecx.h, ECX);
            return;
        } else if(id == EDX){
            push(pilha, edx.h, EDX);
            return;
        }
    } else if(offset == -8){
        if(id == EAX){
            push(pilha, eax.l, EAX);
            return;
        } else if(id == EBX){
            push(pilha, ebx.l, EBX);
            return;
        } else if(id == ECX){
            push(pilha, ecx.l, ECX);
            return;
        } else if(id == EDX){
            push(pilha, edx.l, EDX);
            return;
        }
    }
}
// pop reg
void pop_reg(char *reg){
    reg = strtok(NULL, " ");
    if(reg == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(reg, reg+strlen(reg), ' ') = 0;
    *remove(reg, reg+strlen(reg), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    int offset = 0, id, bkp, i;
    ptr = is_reg(reg, offset, id);
    top(pilha, &bkp, &i);
    if(offset == 32){
        if(id == EAX){
            if(!(i == EAX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            eax.l;
            return;
        } else if(id == EBX){
            if(!(i == EBX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ebx.l;
            return;
        } else if(id == ECX){
            if(!(i == ECX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ecx.l;
            return;
        } else if(id == EDX){
            if(!(i == EDX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            edx.l;
            return;
        }
    } else if(offset == 16){
        if(id == EAX){
            if(!(i == EAX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            eax.l;
            return;
        } else if(id == EBX){
            if(!(i == EBX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ebx.l;
            return;
        } else if(id == ECX){
            if(!(i == ECX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ecx.l;
            return;
        } else if(id == EDX){
            if(!(i == EDX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            edx.l;
            return;
        }
    } else if(offset == 8){
        if(id == EAX){
            if(!(i == EAX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            eax.l;
            return;
        } else if(id == EBX){
            if(!(i == EBX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ebx.l;
            return;
        } else if(id == ECX){
            if(!(i == ECX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ecx.l;
            return;
        } else if(id == EDX){
            if(!(i == EDX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            edx.l;
            return;
        }
    } else if(offset == -8){
        if(id == EAX){
            if(!(i == EAX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ebx.l;
            return;
        } else if(id == EBX){
            if(!(i == EBX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ebx.l;
            return;
        } else if(id == ECX){
            if(!(i == ECX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            ecx.l;
            return;
        } else if(id == EDX){
            if(!(i == EDX)){
                cout << "Ordem de desempilhamento incorreta na linha: "<< (ip.x + 1) << endl;
                cout << "Abortando programa..." << endl;
                fechar();
                exit(EXIT_FAILURE);
            }
            int b;
            pop(pilha, &b, &id);
            edx.l = b;
            return;
        }
    }
}
// jump label
int jmp(char *lbl, tLista &labels){
    lbl = strtok(NULL, " ");
    if(lbl == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(lbl, lbl+strlen(lbl), ' ') = 0;
    *remove(lbl, lbl+strlen(lbl), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    int i, label_int = 0, pos, count;
    for(i = 0; i < strlen(lbl); i++) label_int += lbl[i];
    //cout << "label_int: " << label_int << endl;
    if(posicao(labels, label_int, &pos, &count)) return count;
    else{
        cout << "Jump para label inexistente"<< endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// a = b
void mov(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        //cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    //cout << "op2: " << op2 << endl;
    //bool neg = false;
    //if(op2[0] == '-'){neg = true; op2++;}
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        //cout << "temp: " << temp.ex << endl;
        int offset = 0, i;
        ptr = is_reg(op1, offset, i);
        if(offset == 32){
           (*ptr).ex = temp.ex;
        } else if(offset == 16){
            (*ptr).x = temp.x;
        } else if(offset == 8){
            (*ptr).h = temp.h;
        } else if(offset == -8){
            (*ptr).l = temp.l;
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int offset = 0, i;
        reg_geral_t *ptr2 = is_reg(op2, offset, i);
        ptr = is_reg(op1, offset, i);
        if(offset == 32){
            (*ptr).ex = ptr2->ex;
        } else if(offset == 16){
            (*ptr).x = ptr2->x;
        } else if(offset == 8){
            (*ptr).h = ptr2->h;
        } else if(offset == -8){
            (*ptr).l = ptr2->l;
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// le da memoria
void lea(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << op1 << endl;
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    //cout << "op2: " << op2 << endl;
    //bool neg = false;
    //if(op2[0] == '-'){neg = true; op2++;}
    if((std::all_of(op2, op2+strlen(op2), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op2);
        //string s;
        //cout << "temp: " << temp.ex << endl;
        int offset = 0, var, i;
        ptr = is_reg(op1, offset, i);
        if(offset == 32){
            (*ptr).ex = atoi((fifo->fetch_data(temp.ex, mapeamento_c, &mem)).c_str());
        } else if(offset == 16){
            (*ptr).x = atoi((fifo->fetch_data(temp.x, mapeamento_c, &mem)).c_str());
        } else if(offset == 8){
            (*ptr).h = atoi((fifo->fetch_data(temp.h, mapeamento_c, &mem)).c_str());
        } else if(offset == -8){
            (*ptr).l =atoi((fifo->fetch_data(temp.l, mapeamento_c, &mem)).c_str());
        }
    }else if(std::all_of(op2, op2+strlen(op2), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int offset = 0, i;
        reg_geral_t *ptr2 = is_reg(op2, offset, i);
        ptr = is_reg(op1, offset, i);
        if(offset == 32){
            (*ptr).ex = atoi((fifo->fetch_data(ptr2->ex, mapeamento_c, &mem)).c_str());
        } else if(offset == 16){
            (*ptr).x = atoi((fifo->fetch_data(ptr2->x, mapeamento_c, &mem)).c_str());
        } else if(offset == 8){
            (*ptr).h = atoi((fifo->fetch_data(ptr2->h, mapeamento_c, &mem)).c_str());
        } else if(offset == -8){
            (*ptr).l = atoi((fifo->fetch_data(ptr2->l, mapeamento_c, &mem)).c_str());
        }
    }else{
        //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
}
// escreve na memoria
void str(char *op1, char *op2){
    op1 = strtok(NULL, ",");
    if(op1 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op1, op1+strlen(op1), ' ') = 0;
    if(find_if(op1, op1+strlen(op1), ::isspace) == 0){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    op2 = strtok(NULL, " ");
    if(op2 == NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    *remove(op2, op2+strlen(op2), ' ') = 0;
    *remove(op2, op2+strlen(op2), '\n') = 0;
    if(strtok(NULL, "") != NULL){
        cout << "Erro de sintaxe na linha "<< (ip.x + 1) << endl;
        cout << "Abortando programa..." << endl;
        fechar();
        exit(EXIT_FAILURE);
    }
    reg_geral_t *ptr;
    stringstream s;
    ////cout << "op2: " << op2 << endl;
    //bool neg = false;
    //if(op2[0] == '-'){neg = true; op2++;}
    if((std::all_of(op1, op1+strlen(op1), ::isdigit))){ // b constante
        reg_geral_t temp;
        //if(neg) op2--;
        temp.ex = atoi(op1);
        //cout << "temp: " << temp.ex << endl;
        int offset = 0, i;
        ptr = is_reg(op2, offset, i);
        if(offset == 32){
            s << (*ptr).ex;
            fifo->write_data(temp.ex, s.str(), mapeamento_c, &mem);
            return;
        } else if(offset == 16){
            s << (*ptr).x;
            fifo->write_data(temp.ex, s.str(), mapeamento_c, &mem);
            return;
        } else if(offset == 8){
            s << (*ptr).h;
            fifo->write_data(temp.ex, s.str(), mapeamento_c, &mem);
            return;
        } else if(offset == -8){
            s << (*ptr).l;
            fifo->write_data(temp.ex, s.str(), mapeamento_c, &mem);
            return;
        }
    }else if(std::all_of(op1, op1+strlen(op1), ::isalpha)){ // b registrador (truncado para o maior registrador)
        int offset1 = 0, offset2 = 0, i, var;
        reg_geral_t *ptr2 = is_reg(op1, offset1, i);
        ptr = is_reg(op2, offset2, i);
        if(offset1 == 32){
            if(offset2 == 32){
                s << (*ptr).ex;
                fifo->write_data(ptr2->ex, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == 16){
                s << (*ptr).x;
                fifo->write_data(ptr2->ex, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == 8){
                s << (*ptr).h;
                fifo->write_data(ptr2->ex, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == -8){
                s << (*ptr).l;
                fifo->write_data(ptr2->ex, s.str(), mapeamento_c, &mem);
                return;
            }
        } else if(offset1 == 16){
            if(offset2 == 32){
                s << (*ptr).ex;
                fifo->write_data(ptr2->x, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == 16){
                s << (*ptr).x;
                fifo->write_data(ptr2->x, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == 8){
                s << (*ptr).h;
                fifo->write_data(ptr2->x, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == -8){
                s << (*ptr).l;
                fifo->write_data(ptr2->x, s.str(), mapeamento_c, &mem);
                return;
            }
        } else if(offset1 == 8){
            if(offset2 == 32){
                s << (*ptr).ex;
                fifo->write_data(ptr2->h, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == 16){
                s << (*ptr).x;
                fifo->write_data(ptr2->h, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == 8){
                s << (*ptr).h;
                fifo->write_data(ptr2->h, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == -8){
                s << (*ptr).l;
                fifo->write_data(ptr2->h, s.str(), mapeamento_c, &mem);
                return;
            }
        } else if(offset1 == -8){
            if(offset2 == 32){
                s << (*ptr).ex;
                fifo->write_data(ptr2->l, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == 16){
                s << (*ptr).x;
                fifo->write_data(ptr2->l, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == 8){
                s << (*ptr).h;
                fifo->write_data(ptr2->l, s.str(), mapeamento_c, &mem);
                return;
            } else if(offset2 == -8){
                s << (*ptr).l;
                fifo->write_data(ptr2->l, s.str(), mapeamento_c, &mem);
                return;
            }
        }else{
            //cout << "operador nao identificado na linha "<< (ip.x + 1) << endl;
            cout << "Abortando programa..." << endl;
            fechar();
            exit(EXIT_FAILURE);
        }
    }
}

#endif