#ifndef INSTRUCOES_H_INCLUDED
#define INSTRUCOES_H_INCLUDED

enum Estado{
    Fetch = 0x01,
    Decode = 0x02,
    Execute = 0x03
};

enum Op{
    // aritmetica
    ADD, // add
    SUB, // subtracao
    DIV, // divisao sem sinal
    IDIV, // divisao com sinal
    MUL, // multiplicacao sem sinal
    IMUL, // multiplicacao com sinal
    DEC, // decrementa por um
    INC, // incrementa por um
    // logica
    AND, // and logico
    NOT, // nega o operando
    OR, // ou logico
    XOR, // ou exclusivo
    NEG, // negacao por complemento de dois
    CMP, // compara operandos
    // controle
    CALL , // ip aponta pra instrucao posterior a call
    INT, // interrupcao
    RET, // retorna do procedimento
    JMP, // pulo incondicional
    JZ, // pula se cz1
    JNZ, // pula se cz0
    JS, // pula se cs1
    JNS, // pula se cs0
    JO, // pula se of1
    JNO, // pula se of0
    JC, // pula se cf1
    JNC, // pula se cf0
    JB, // pula se cf1
    JBE, // pula se cf1 ou zf1
    JAE, // pula se cf0
    JA, // pula se cf0 e zf0
    JL, // pula se sf != of
    JLE, // pula se (sf != of) ou zf
    JGE, // pula se sf == of
    JG, // pula se (sf == of) e zf0
    // movimento de dados
    MOV, // copia de uma localizacao pra outra
    LEA, // carrega um valor da memoria
    STR, // armazena um valor na memoria
    PUSH, // push na pilha
    POP, // pop na pilha
    // misc(variado)
    CLC, // clear no cf
    CLD, // clear no cf 
    STC, // seta cf
    STD, // seta df
    LBL // label
};

Op hashOp(string s){
    if(s == "add") return ADD; // add
    if(s == "sub") return SUB; // subtracao
    if(s == "div") return DIV; // divisao sem sinal
    if(s == "idiv") return IDIV; // divisao com sinal
    if(s == "mul") return MUL; // multiplicacao sem sinal
    if(s == "imul") return IMUL; // multiplicacao com sinal
    if(s == "dec") return DEC; // decrementa por um
    if(s == "inc") return INC; // incrementa por um
    // logica
    if(s == "and") return AND; // and logico
    if(s == "not") return NOT; // nega o operando
    if(s == "or") return OR; // ou logico
    if(s == "xor") return XOR; // ou exclusivo
    if(s == "neg") return NEG; // negacao por complemento de dois
    if(s == "cmp") return CMP; // compara operandos
    // controle
    if(s == "call") return CALL; // ip aponta pra instrucao posterior a call
    if(s == "int") return INT; // interrupcao
    if(s == "ret") return RET; // retorna do procedimento
    if(s == "jmp") return JMP; // pulo incondicional
    if(s == "jz") return JZ; // pula se cz1
    if(s == "jnz") return JNZ; // pula se cz0
    if(s == "js") return JS; // pula se cs1
    if(s == "jns") return JNS; // pula se cs0
    if(s == "jo") return JO; // pula se of1
    if(s == "jno") return JNO; // pula se of0
    if(s == "jc") return JC; // pula se cf1
    if(s == "jnc") return JNC; // pula se cf0
    if(s == "jb") return JB; // pula se cf1
    if(s == "jbe") return JBE; // pula se cf1 ou zf1
    if(s == "jae") return JAE; // pula se cf0
    if(s == "ja") return JA; // pula se cf0 e zf0
    if(s == "jl") return JL; // pula se sf != of
    if(s == "jle") return JLE; // pula se (sf != of) ou zf
    if(s == "jge") return JGE; // pula se sf == of
    if(s == "jg") return JG; // pula se (sf == of) e zf0
    // movimento de dados
    if(s == "mov") return MOV; // copia de uma localizacao pra outra
    if(s == "lea") return LEA; // carrega um valor da memoria
    if(s == "str") return STR; // store
    if(s == "push") return PUSH; // push na pilha
    if(s == "pop") return POP; // pop na pilha
    // misc(variado)
    if(s == "clc") return CLC; // clear no cf
    if(s == "cld") return CLD; // clear no cf 
    if(s == "stc") return STC; // seta cf
    if(s == "std") return STD; // seta df*/
    if(s.find(':') != -1) return LBL; // label
}

#endif