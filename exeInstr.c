#include "exeInstr.h"

void execInstr(Instrct* instr, GPR* regs, int mem[])
{
    if(instr->oppcode == ADD)
    {
        int32_t res = regs->tReg[instr->rs] + regs->tReg[instr->rt];
        regs->tReg[instr->rd] = res;
    }
    else if (instr->oppcode == ADDI && instr->type == 'I')
    {
        int32_t res = regs->tReg[instr->rs] + instr->imm;
        regs->tReg[instr->rt] = res;
    }
    else if (instr->oppcode == AND)
    {
        int32_t res = regs->tReg[instr->rs] & regs->tReg[instr->rt];
        regs->tReg[instr->rd] = res;
    }
    else if (instr->oppcode == BEQ)
    {
        if(regs->tReg[instr->rs] == regs->tReg[instr->rt]){
            regs->mReg.pc = (regs->mReg.pc + instr->imm)-1;
        }
    }
    else if (instr->oppcode == BGTZ)
    {
        if(regs->tReg[instr->rs] > 0){
            regs->mReg.pc = (regs->mReg.pc + instr->imm)-1;
        }
    }
    else if (instr->oppcode == BLEZ)
    {
        if(regs->tReg[instr->rs] <= 0){
            regs->mReg.pc = (regs->mReg.pc + instr->imm)-1;
        }
    }
    else if (instr->oppcode == BNE)
    {
        if(regs->tReg[instr->rs] != regs->tReg[instr->rt]){
            regs->mReg.pc = (regs->mReg.pc + instr->imm)-1;
        }
    }
    else if (instr->oppcode == DIV)
    {
        int q = regs->tReg[instr->rs] / regs->tReg[instr->rt];
        int m = regs->tReg[instr->rs] % regs->tReg[instr->rt];
        regs->mReg.lo = q;
        regs->mReg.hi = m;
    }
    else if (instr->oppcode == J && instr->type == 'J')
    {   
        regs->mReg.pc = (instr->imm | (regs->mReg.pc & 0xF0000000))-1;
    }
    else if (instr->oppcode == JAL && instr->type == 'R')
    {
        regs->mReg.ra = regs->mReg.pc + 1;
        regs->mReg.pc = (instr->imm | (regs->mReg.pc & 0xF0000000))-1;
    }
    else if (instr->oppcode == JR)
    {
        regs->mReg.pc = (regs->tReg[instr->rs]/4)-1;
    }
    else if (instr->oppcode == LUI)
    {
        int32_t shift = instr->imm;
        shift = shift << 16;
        regs->tReg[instr->rt] = shift;
    }
    else if (instr->oppcode == LW)
    {
        regs->tReg[instr->rt] = mem[instr->imm];
    }
    else if (instr->oppcode == MFHI)
    {
        regs->tReg[instr->rd] = regs->mReg.hi;
    }
    else if (instr->oppcode == MFLO)
    {
        regs->tReg[instr->rd] = regs->mReg.lo;
    }
    else if (instr->oppcode == MULT)
    {
        int64_t res = (int64_t)regs->tReg[instr->rs] * (int64_t)regs->tReg[instr->rt];
        regs->mReg.lo = (int32_t)res;
        regs->mReg.hi = (int32_t)(res >> 32);
    }
    else if (instr->oppcode == OR)
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rs] | regs->tReg[instr->rt];        
    }
    else if (instr->oppcode == ROTR && instr->rs != 0)
    {
        int temp = regs->tReg[instr->rt];
        int bit = temp & 1;
        for (int i = 0; i < instr->imm; ++i)
        {
            temp = temp >> 1;
            bit = bit << 31;
            temp = bit | temp;
            bit = temp & 1;
        }
        regs->tReg[instr->rd] = temp;
    }
    else if (instr->oppcode == SLL) //ou instr->oppcode == NOP
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rt] << instr->imm;
    }
    else if (instr->oppcode == SLT)
    {
        if(regs->tReg[instr->rs] < regs->tReg[instr->rt]){
            regs->tReg[instr->rd] = 1;
        }else{
            regs->tReg[instr->rd] = 0;
        }
    }
    else if (instr->oppcode == SRL && instr->rs == 0)
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rt] >> instr->imm;
    }
    else if (instr->oppcode == SUB)
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rs] - regs->tReg[instr->rt];
    }
    else if (instr->oppcode == SW)
    {
        mem[instr->imm] = regs->tReg[instr->rt];
    }
    else if (instr->oppcode == SYSCALL)
    {
        printf("This is a System Call Exception\n");
    }
    else if (instr->oppcode == XOR)
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rs] ^ regs->tReg[instr->rt];
    } 
}